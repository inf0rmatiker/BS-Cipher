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
    ~Cipher() = default;
  
    void encryptBlocks();
    void decryptBlocks();

    void encryptStream();
    void decryptStream();


  private:
    std::ofstream out;
    std::string keyFileName;
    std::string inputFileName;
    std::string outputFileName;
    bool isBlockCipher;
     
    std::vector<std::string> streamKey;
    char blockKey[8];

    char * encryptedBlock(char *);
    void printBlock(char *);  
    void writeBlockToFile(char *, bool);
    char * swappedBytes(char *);
    char * unswappedBytes(char *);
    void swap(char *, char *);

};

#endif /* CIPHER_H_INCLUDED */
