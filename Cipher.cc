#include "Cipher.h"
#include <fstream>

using namespace std;

/* Constructor */
Cipher::Cipher(string inputfile, string keyfile, bool blockMode) :
  keyFileName(keyfile), inputFileName(inputfile), isBlockCipher(blockMode) {

  // Read the key file into the size 8 char array if we are in block cipher mode
  if (blockMode) {
    ifstream keyInputStream(keyFileName);
    int i = 0;
    while (keyInputStream >> blockKey[i] && i < 8) {
      ++i;
    }

    if (!keyInputStream.eof()) {
      cerr << "Key too large! Please limit to 8 characters.\n";
    }
  }
}

