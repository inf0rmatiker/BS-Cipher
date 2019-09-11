#ifndef CIPHER_H_INCLUDED
#define CIPHER_H_INCLUDED

#include <iostream>
#include <string>

class Cipher {
  public:
    Cipher(string keyFile, string inputFile) : keyFileName(keyFile), 
      inputFileName(inputFile) {};
    ~Cipher() = default;
    
  private:
    std::string keyFileName;
    std::string inputFileName;
};

#endif /* CIPHER_H_INCLUDED */
