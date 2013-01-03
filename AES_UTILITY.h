#ifndef AES_AES_UTILITY_h
#define AES_AES_UTILITY_h

#include <stdio.h>

typedef unsigned char byte;
typedef unsigned int size;
typedef unsigned int counter;

void EncryptStream(FILE *, byte *, size, FILE *);
void DecryptStream(FILE *, byte *, size, FILE *);

byte * Encrypt(byte *, size, byte *, size);
byte * Decrypt(byte *, size, byte *, size);

void Cipher(byte *, byte *, byte *);
void InvCipher(byte *, byte *, byte *);

void ExpandKey(byte *, byte *, size);

void AddRoundKey(byte *, byte *);

void MixColumns(byte *);
void InvMixColumns();

void ShiftRows(byte *);
void InvShiftRows(byte *);

void SubBytes(byte *);
void InvSubBytes(byte *);

void RotWord(byte *);
void SubWord(byte *);

byte multiply2(byte);
byte multiply3(byte);
byte multiply9(byte);
byte multiply11(byte);
byte multiply13(byte);
byte multiply14(byte);

// multiply replaced by multiplyXX
// byte multiply(byte, byte);

#endif
