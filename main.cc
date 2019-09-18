#include <iostream>
#include <string>
#include <fstream>
#include "Cipher.h"

using namespace std;

static const string usageMessage = "Usage: ./cipher (B|S) <inputFile> <keyFile> <opMode>";


// Function declarations
bool argumentsAreValid(int, char**);
bool fileExists(string &);

// Function definitions
bool argumentsAreValid(int argc, char* argv[]) {
  if (argc != 6) {
    cerr << "Incorrect number of arguments specified.\n";
    return false;
  }
  
  string cipherType = argv[1];
  if (cipherType != "S" && cipherType != "B") {
    cerr << "Incorrect cypher type specified. Please use either S or B.\n"; 
    return false;
  }

  string inputFileName = argv[2];
  if (!fileExists(inputFileName)) {
    cerr << "Input file " << inputFileName << " does not exist.\n";
    return false;
  }

  string keyFileName = argv[4];
  if (!fileExists(keyFileName)) {
    cerr << "Key file " << keyFileName << " does not exist.\n";
    return false;
  }

  string mode = argv[5];
  if (mode != "E" && mode != "D") {
    cerr << "Invalid mode of operation. Please use\n\tE for encryption, or\n\tD for decryption.\n";
    return false;
  }

  // All validation tests passed
  return true;
}


bool fileExists(string & filename) {
  ifstream inputFileStream(filename);
  return inputFileStream.good();
}


// ------ Main Program ------

int main(int argc, char* argv[]) {
  if (!argumentsAreValid(argc, argv)) {
    cerr << usageMessage << endl;
    return 1;
  }

  Cipher test(argv[2], argv[4], true);
  return 0;
}
