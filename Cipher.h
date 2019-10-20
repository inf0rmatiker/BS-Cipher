#ifndef CIPHER_H_INCLUDED
#define CIPHER_H_INCLUDED

#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>

class Cipher {
  public:
    Cipher(std::string, std::string, std::string, bool);
    ~Cipher();
  
    void encryptBlocks();
    void decryptBlocks();
    void cipherStream();

  private:
    std::ofstream out;
    std::string keyFileName;
    std::string inputFileName;
    std::string outputFileName;
    bool isBlockCipher;
    std::vector<char> * encryptedContents;     
    std::vector<char> streamKey;
    char blockKey[8];
    
    void readFile();
    void writeOut(bool);
    void swapContents();
    void padChars();
    void swapChars(int, int);
    void xorBytes();
    void printEncryptedContents();
};

#endif /* CIPHER_H_INCLUDED */
