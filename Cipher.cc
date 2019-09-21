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
    printVector(streamKey);
  }
}

/* --------- BLOCK CIPHERING ------------- */

/* Encrypts all blocks of the input file, writing the encrypted
    output to the outputfile. Uses the key from the keyfile.
    We read the input file one block at a time, and write the
    encrypted block to the output file as we go. */
void Cipher::encryptBlocks() {
  ifstream in(inputFileName);
  out.open(outputFileName);

  int charCounter = 0;
  char plaintextBlock[8];
  char c;
  while (in.get(c)) {
    plaintextBlock[charCounter] = c;
    if (charCounter == 7) {
      // Handle full plaintext block
      writeBlockToFile(swappedBytes(encryptedBlock(plaintextBlock)), true); 
      charCounter = 0;
    }
    else {
      // Continue reading characters
      ++charCounter;
    } 
  }
  
  if (!in.eof()) {
    // Could not read, but not at end of file
    cerr << "Something went wrong while reading file " << inputFileName << '\n';
  }
  else if (plaintextBlock[0] != (char) 0x80) {
    // Pad the last incomplete block to 64 bits
    for (int i = charCounter-1; i < 8; ++i) {
      plaintextBlock[i] = (char) 0x80;
    }
    writeBlockToFile(swappedBytes(encryptedBlock(plaintextBlock)), true);
  }
  out.close();
}

/* Read the encrypted input file, and write the decrypted
    plaintext to the output file. We read one encrypted block
    at a time, and write the decrypted block to the output
    file, with any padding removed.
*/
void Cipher::decryptBlocks() {
  ifstream in(inputFileName);
  out.open(outputFileName); 
  int charCounter = 0;
  char encryptedSwappedBlock[8];
  char c;
  while (in.get(c)) {
    encryptedSwappedBlock[charCounter] = c;
    if (charCounter == 7) {
      // Handle full encrypted and swapped block
      writeBlockToFile(encryptedBlock(swappedBytes(encryptedSwappedBlock)), false);
      charCounter = 0;
    }
    else {
      // Continue reading characters
      ++charCounter;
    }
  }
  out.close();
}

/* Helper function for encryption, swaps the bytes
    of a block according to the key.
*/
char * Cipher::swappedBytes(char * encryptedBlock) {
  char * start = encryptedBlock;
  char * end   = encryptedBlock + 7;
  int value;
  for (int i = 0; i < 8; ++i) {
    value = abs(blockKey[i] % 2);
    if (end > start) {
      if (value == 0) {
        ++start;
      }
      else {
        swap(start++, end--);
      }
    }
    else break;
  }
  return encryptedBlock;
}

/* Writes the completed block to the output file.
    We are assuming that Cipher::out has already been
    opened for us in a calling function.
*/
void Cipher::writeBlockToFile(char * block, bool writePadding) {;
  for (int i = 0; i < 8; ++i) {
    if (!writePadding && block[i] == (char) 0x80) {
      continue;
    }
    else {
      out << block[i];
    }
  }
}

/* Encrypts the plaintext block by XOR'ing every
    byte with the corresponding byte of the key.
*/
char * Cipher::encryptedBlock(char * plaintext) {
  for (int i = 0; i < 8; ++i) {
    plaintext[i] ^= blockKey[i % 8];
  }
  return plaintext;
}

void Cipher::swap(char * i, char * j) {
  char temp = *i;
  *i = *j;
  *j = temp;
}

/* ------------ STREAM CIPHER ------------ */

/* Simply XOR's the incoming bytes of the stream
    with the provided key, wrapping on exhaustion.
*/
void Cipher::cipherStream() {
  out.open(outputFileName);
  ifstream in(inputFileName);
  
  int keySize = streamKey.size() - 1; // To account for EOF
  int byteCounter = 0;
  char currentChar;
  while (in.get(currentChar)) {
    out << (char) (currentChar ^ (streamKey[byteCounter++ % keySize]));
  }
  
  out.close();
}

void Cipher::printVector(vector<char> & vect) {
  for (char c: vect) {
    cout << c;
  }
  cout << '\n';

}

void Cipher::printBlock(char * block) {
  for (int i = 0; i < 8; ++i) {
    cout << block[i];
  }
  cout << "\n";
}
