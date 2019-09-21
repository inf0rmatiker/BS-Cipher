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

void Cipher::decryptBlocks() {
  // Read the input file one block at a time
  // Write the decrypted output to the output file as we go.
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

// Swaps the values in the reverse order they were swapped in
char * Cipher::unswappedBytes(char * encryptedBlock) {
  // We start from the end, and work our way backwards
  char * start  = encryptedBlock + 7;
  char * end    = encryptedBlock;
  int value;
  for (int i = 7; i >= 0; --i) {
    value = abs(encryptedBlock[i] % 2);
    cout << "Start: " << (int) (start - encryptedBlock) << " end: " << (int) (end - encryptedBlock) << " value: " << value << '\n';
    if (start > end) {  
      if (value == 0) {
        start--;
      }
      else {
        swap(start--, end++);
      }
      printBlock(encryptedBlock);
    }
    else {
      break;
    }
  }
  return encryptedBlock; 
}

char * Cipher::swappedBytes(char * encryptedBlock) {
  char * start = encryptedBlock;
  char * end   = encryptedBlock + 7;
  int value;
  for (int i = 0; i < 8; ++i) {
    value = abs(blockKey[i] % 2);
    cout << "Start: " << (int) (start - encryptedBlock) << " end: " << (int) (end - encryptedBlock) << " value: " << value << '\n';
    if (end > start) {
      if (value == 0) {
        ++start;
      }
      else {
        swap(start++, end--);
      }
      printBlock(encryptedBlock);
      cout << '\n';
    }
    else break;
  }
  printBlock(encryptedBlock);
  cout << '\n';
  return encryptedBlock;
}



void Cipher::encryptBlocks() {
  // Read the input file one block at a time.
  // Write the encrypted output to the output file as we go.
  ifstream in(inputFileName);
  out.open(outputFileName);

  int charCounter = 0;
  char plaintextBlock[8];
  char c;
  while (in.get(c)) {
    plaintextBlock[charCounter] = c;
    if (charCounter == 7) {
      // Handle full plaintext block
      // printBlock(plaintextBlock);
      printBlock(plaintextBlock);
      
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
    cout << "MADE IT HERE\n";
    // Pad the last block to 64 bits
    for (int i = charCounter-1; i < 8; ++i) {
      plaintextBlock[i] = (char) 0x80;
    }
    printBlock(plaintextBlock);
    writeBlockToFile(swappedBytes(encryptedBlock(plaintextBlock)), true);
  }
  out.close();
}

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

void Cipher::printBlock(char * block) {
  for (int i = 0; i < 8; ++i) {
    cout << block[i];
  }
  cout << "\n";
}

char * Cipher::encryptedBlock(char * plaintext) {
  // XOR every plaintext character (and padded characters) with the corresponding 
  // character in the blockKey char array
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


void Cipher::encryptStream() {
  cout << "Encrypting stream... \n\n";
  int keySize = streamKey.size();
  keySize--; // To account for EOF
  out.open(outputFileName);
  ifstream in(inputFileName);
  
  int byteCounter = 0;
  char currentChar;
  while (in.get(currentChar)) {
    cout << currentChar;
    cout << streamKey[byteCounter % keySize] << '\n';
    out << (char) (currentChar ^ (streamKey[byteCounter++ % keySize]));
  }
  
  out.close();
}

void Cipher::decryptStream() {
  cout << "Decrypting stream... \n\n";
  int keySize = streamKey.size();
  out.open(outputFileName);
  ifstream in(inputFileName);
  
  keySize--; // To account for EOF
  int byteCounter = 0;
  char currentChar;
  while (in.get(currentChar)) {
    cout << currentChar;
    cout << streamKey[byteCounter % keySize] << '\n';
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
