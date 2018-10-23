#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;


#include "keyMatrix.h"


//initialize an empty matrix
void keyMatrix::init(){
  for (int i=0; i<16; i++){
    matrix[i]=0;
  }
  for (int i=0; i<4; i++){
    line[i]=0;
  }
}

keyMatrix::keyMatrix(const byte entry[16]){
  init();
  for (int i=0; i<16; i++){
    matrix[i]=entry[i];
  }
}

void keyMatrix::expansionKey(){
  //copying the last line, which gonna have many operations
  for (int i=0; i<4; i++){
    line[i]=matrix[12+i];
  }
  rotWord();
  subWord(sbox);
  Rcon(rcon);
  for (int i=0; i<4; i++){
    for (int j=0; j<4; j++){
      line[j]^=matrix[4*i+j];
      matrix[4*i+j]=line[j];
    }
  }
  rouund++;
}

void keyMatrix::rotWord(){
  byte stock=line[0];
  for (int i=0; i<3; i++){
    line[i]=line[i+1];
  }
  line[3]=stock;
}

void keyMatrix::subWord(const byte sbox[256]){
  for (int i=0; i<4; i++){
    line[i]=sbox[line[i]];
  }
}

void keyMatrix::Rcon(const byte rcon[10]){
  line[0]^=rcon[rouund];
}
