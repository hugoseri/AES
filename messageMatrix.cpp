#include "messageMatrix.h"


//initialize an empty matrix
void messageMatrix::init(){
  for (int i=0; i<16; i++){
    matrix[i]=0;
  }
}


messageMatrix::messageMatrix(const byte entry[16]){
  init();
  for (int i=0; i<16; i++){
    matrix[i]=entry[i];
  }
}

void messageMatrix::shiftRow(){
  shift(1);
  shift(2);
  shift(3);
}

void messageMatrix::shift(int nb){
  if (nb==1){
    byte stock = matrix[1];
    for (int i=0; i<3; i++){
      matrix[4*i+1]=matrix[4*(i+1)+1];
    }
    matrix[12+1]=stock;
  } else if (nb==2){
    byte stock1 = matrix[2];
    byte stock2 = matrix[4+2];
    matrix[2] = matrix[4*2+2];
    matrix[4+2] = matrix[4*3+2];
    matrix[4*2+2] = stock1;
    matrix[4*3+2] = stock2;
  } else if (nb==3){
    byte stock = matrix[15];
    for (int i=0; i<3; i++){
      matrix[4*(3-i)+3]=matrix[4*(3-i-1)+3];
    }
    matrix[3]=stock;
  }
}

void messageMatrix::subBytes(const byte sbox[256]){
  for (int i=0; i<16; i++){
    matrix[i]=sbox[matrix[i]];
  }
}


void messageMatrix::addRoundKey(const byte key[16]){
  for (int octet=0; octet<16; octet++){
    matrix[octet]^=key[octet];
  }
}

void messageMatrix::mixColumns(){
  for (int i=0; i<4; i++){
    byte a[4];
    byte b[4];
    byte h;
    for (int c=0; c<4; c++){
      a[c]=matrix[4*i+c];
      h = (byte)((int8_t)matrix[4*i+c]>>7);
      b[c]=matrix[4*i+c]<<1;
      b[c]^=0x1B & h;
    }
    matrix[4*i] = b[0] ^ a[3] ^ a[2] ^ b[1] ^ a[1];
    matrix[4*i+1] = b[1] ^ a[0] ^ a[3] ^ b[2] ^ a[2];
    matrix[4*i+2] = b[2] ^ a[1] ^ a[0] ^ b[3] ^ a[3];
    matrix[4*i+3] = b[3] ^ a[2] ^ a[1] ^ b[0] ^ a[0];
  }
}
