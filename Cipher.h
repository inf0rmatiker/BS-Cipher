#ifndef CIPHER_H_INCLUDED
#define CIPHER_H_INCLUDED

#include <iostream>
#include <string>

class Cipher {
  public:
    Cipher(std::string, std::string, bool);
    ~Cipher() = default;

  private:
    std::string keyFileName;
    std::string inputFileName;
    char blockKey[8];
    bool isBlockCipher;
};

#endif /* CIPHER_H_INCLUDED */
