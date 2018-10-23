#include <iostream>
#include <cstring>
#include <stdint.h>
using namespace std;
#pragma once

typedef uint8_t byte;

class Matrice44{
public:
  Matrice44(const byte message[16],const byte cle[16]);
  void loop();
  void shiftRow();
  void subBytes(const byte sbox[256]);
  void addRoundKey();
  void mixColumns();
  void expansionKey(); //pour keyMatrix
  void affich(int i=1);
private:
  void decalage(int nb, int line); //décallage pour shitRow
  void init();
  void rotWord();
  void subWord(const byte sbox[256]);
  void Rcon(const byte rcon[10]);
  //void remplissage(); //rempli la matrice avec le binaire de msg, utilisé dans le constructeur
  byte matrice[16];
  byte key[16];
  byte colonne[4];
  int tour;
};
