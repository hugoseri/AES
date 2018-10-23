#include <iostream>
#include <cstring>
#include <stdint.h>
using namespace std;
#pragma once

#include "matrix44.h"

typedef uint8_t byte;

//parent class for a 4x4 matrix
class messageMatrix:public Matrix44{
public:
  messageMatrix(const byte entry[16]);
  void shiftRow();
  void subBytes(const byte sbox[256]);
  void addRoundKey(const byte key[16]);
  void mixColumns();
private:
  int round;
  void init();
  void shift(int nb); //sub function for shiftRow
  //void remplissage(); //rempli la matrice avec le binaire de msg, utilisé dans le constructeur
};
