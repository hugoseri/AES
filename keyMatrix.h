#pragma once
#include "matrix44.h"

//R-Con standard
const byte rcon[10]={0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36};

//parent class for a 4x4 matrix
class keyMatrix:public Matrix44{
public:
  keyMatrix(const byte entry[16]);
  void expansionKey();
private:
  void shift(int nb); //shift for shiftRow
  void init();
  void rotWord();
  void subWord(const byte sbox[256]);
  void Rcon(const byte rcon[10]);
  byte line[4]; //saved line for expansionKey
};
