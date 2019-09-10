#include <iostream>
#include <string>
#include <fstream>

using namespace std;

static const string usageMessage = "Usage: ./cipher (B|S) <inputFile> <keyFile> <opMode>";


// Function declarations
bool argumentsAreValid(int, char**);

// Function definitions
bool argumentsAreValid(int argc, char* argv[]) {
  if (argc == 6) {
    string cipherType = argv[1];
    if (cipherType.compare("S") == 0 || cipherType.compare("B") == 0) {
      string inputFileName = argv[2];
      ifstream inputFileStream(inputFileName);
      if (inputFileStream.good()) {
        return true; 
      } else {
        cerr << "Input file " << inputFileName << " does not exist.\n";
        return false;
      } 
    }
    else {
      cerr << "Incorrect cypher type specified. Please use either S or B.\n"; 
      return false;
    }

  }
  else {
    cerr << "Incorrect number of arguments specified.\n";
    return false;
  }
}

int main(int argc, char* argv[]) {
  if (!argumentsAreValid(argc, argv)) {
    cerr << usageMessage << endl;
    return 1;
  }
  
  return 0;
}
