# BS-Cipher

## Description
This program's purpose is to encrypt and decrypt either a **block** or a **stream** of data, given to it by an input file specified in the arguments.
It takes this encrypted / decrypted data, and writes it to an output file specified in the arguments.

---

The program takes 5 arguments: `<cipher_type> <inputfile> <outputfile> <keyfile> <mode>`
- `<cipher_type>` should be either the character **B** for block encryption, or **S** for stream encryption.
- `<inputfile>` should be the path to the file (absolute or relative) to your data you would like ciphered.
- `<outputfile>` should be the name of the file you wish to output the ciphered data to.
- `<keyfile>` should be the path to the file containing the secret key to cipher your data with.
- `<mode>` should be the mode of operation, either **E** for encryption, or **D** for decryption.

## Usage

**FIRST!** *Please build the program.*
You can do so by running `make` on GNU/Linux.

This will output the `cipher` C++ executable.

Usage: `./cipher (B|S) <inputfile> <outputfile> <keyfile> (E|D)`
- E.g. for block encryption: `$ ./cipher B plaintext.txt encryptedtext.txt keyfile.txt E`
- E.g. for stream decryption: `$ ./cipher S encryptedtext.txt decryptedtext.txt keyfile.txt D`
