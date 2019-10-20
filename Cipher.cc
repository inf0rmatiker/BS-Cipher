#include "Cipher.h"
#include <fstream>
#include <vector>

using namespace std;

/* Constructor */
Cipher::Cipher(string inputfile, string keyfile, string outfile, bool blockMode) :
  keyFileName(keyfile), inputFileName(inputfile), outputFileName(outfile), isBlockCipher(blockMode) {

  // Read the key file into the size 8 char array if we are in block cipher mode
  if (blockMode) {
    ifstream keyInputStream(keyFileName);
    int i = 0;
    char c;
    while (keyInputStream.get(c) && i < 8) {
      blockKey[i++] = c;
    }
    // Allocate char vector for encrypted file contents on heap
    encryptedContents = new vector<char>();
  }
  else {
    // Read the key file into the streamKey vector since we are in stream cipher mode
    ifstream in(keyFileName);
    char c;
    while (in.get(c)) {
      streamKey.push_back(c);
    }
    if (!in.eof()) {
      cerr << "Problem reading key!\n";
    }
  }
}

/* Destructor */
Cipher::~Cipher() {
  delete encryptedContents;
}

/* --------- BLOCK CIPHERING ------------- */

/* Encrypts all blocks of the input file, writing the encrypted
 * output to the outputfile. Uses the key from the keyfile.
 */  
void Cipher::encryptBlocks() {
  out.open(outputFileName);
  readFile();
  padChars();
  xorBytes();
  swapContents();
  writeOut(true);
  out.close();
}

/* Read the encrypted input file, and write the decrypted
 * plaintext to the output file.
 */
void Cipher::decryptBlocks() {
  out.open(outputFileName); 
  readFile();  
  swapContents();   
  xorBytes(); 
  writeOut(false); 
  out.close();
}

/* Helper function for encryption, swaps the bytes
 * of the contents according to the key.
 */
void Cipher::swapContents() {
  int size = encryptedContents->size();
  for (int start = 0, end = size - 1; start < end; ++start) {
    //cout << "Start: " << start << " End: " << end << '\n';
    if (blockKey[start % 8] % 2 == 1){
      //cout << (*encryptedContents)[start] << " " << (*encryptedContents)[end] << " "; 
      swapChars(start, end--);
      //printEncryptedContents();
    }
  }
}

/* Pads the encrypted contents with 0x80 chars
 * so that the encrypted size is a multiple of 64 bits. 
 */
void Cipher::padChars() {
  int requiredPadding = (8 - (encryptedContents->size() % 8));
  for (int i = 0; i < requiredPadding; i++) {
    encryptedContents->push_back((char) 0x80);
  }
  //printEncryptedContents(); // TODO: Remove
}


/* Reads either plaintext or ciphertext into
 * the encryptedContents vector.
 */
void Cipher::readFile() {
  ifstream in(inputFileName);
  encryptedContents->clear();
  char c;
  while (in.get(c)) {  
    encryptedContents->push_back(c);
  }
}

/* Writes the completed vector out to the "out" file. 
 * We are assuming that Cipher::out has already been
 * opened for us in a calling function.
 */
void Cipher::writeOut(bool writePadding) {;
  for (auto c: *encryptedContents) {
    if (writePadding || c != (char) 0x80) {
      out << c;
    }
  } 
}

void Cipher::printEncryptedContents() {
  for (auto c: *encryptedContents)
    cout << c;
  cout << '\n'; 
}

/* Encrypts/decrypts by XOR'ing every
 * byte with the corresponding byte of the key.
 */
void Cipher::xorBytes() {
  int size = encryptedContents->size();
  for (int i = 0; i < size; i++) {
    (*encryptedContents)[i] ^= blockKey[i % 8];
  }
}

void Cipher::swapChars(int i, int j) {
  char temp = (*encryptedContents)[i];
  (*encryptedContents)[i] = (*encryptedContents)[j];
  (*encryptedContents)[j] = temp;
}

/* ------------ STREAM CIPHER ------------ */

/* Simply XOR's the incoming bytes of the stream
    with the provided key, wrapping on exhaustion.
*/
void Cipher::cipherStream() {
  out.open(outputFileName);
  ifstream in(inputFileName);
  
  int keySize = streamKey.size(); 
  int byteCounter = 0;
  char currentChar;
  while (in.get(currentChar)) {
    out << (char) (currentChar ^ (streamKey[byteCounter++ % keySize]));
  }
  
  out.close();
}
