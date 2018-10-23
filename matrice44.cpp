#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;


#include "matrice44.h"

int* int_binary(int monEntier);
int binary_int(int * binary);

const byte sbox[256]={0x63,0x7c,0x77,0x7b,0xf2,0x6b,0x6f,0xc5,0x30,0x01,0x67,0x2b,0xfe,0xd7,0xab,0x76,0xca,0x82,0xc9,0x7d,0xfa,0x59,0x47,0xf0,0xad,0xd4,0xa2,0xaf,0x9c,0xa4,0x72,0xc0,0xb7,0xfd,0x93,0x26,0x36,0x3f,0xf7,0xcc,0x34,0xa5,0xe5,0xf1,0x71,0xd8,0x31,0x15,0x04,0xc7,0x23,0xc3,0x18,0x96,0x05,0x9a,0x07,0x12,0x80,0xe2,0xeb,0x27,0xb2,0x75,0x09,0x83,0x2c,0x1a,0x1b,0x6e,0x5a,0xa0,0x52,0x3b,0xd6,0xb3,0x29,0xe3,0x2f,0x84,0x53,0xd1,0x00,0xed,0x20,0xfc,0xb1,0x5b,0x6a,0xcb,0xbe,0x39,0x4a,0x4c,0x58,0xcf,0xd0,0xef,0xaa,0xfb,0x43,0x4d,0x33,0x85,0x45,0xf9,0x02,0x7f,0x50,0x3c,0x9f,0xa8,0x51,0xa3,0x40,0x8f,0x92,0x9d,0x38,0xf5,0xbc,0xb6,0xda,0x21,0x10,0xff,0xf3,0xd2,0xcd,0x0c,0x13,0xec,0x5f,0x97,0x44,0x17,0xc4,0xa7,0x7e,0x3d,0x64,0x5d,0x19,0x73,0x60,0x81,0x4f,0xdc,0x22,0x2a,0x90,0x88,0x46,0xee,0xb8,0x14,0xde,0x5e,0x0b,0xdb,0xe0,0x32,0x3a,0x0a,0x49,0x06,0x24,0x5c,0xc2,0xd3,0xac,0x62,0x91,0x95,0xe4,0x79,0xe7,0xc8,0x37,0x6d,0x8d,0xd5,0x4e,0xa9,0x6c,0x56,0xf4,0xea,0x65,0x7a,0xae,0x08,0xba,0x78,0x25,0x2e,0x1c,0xa6,0xb4,0xc6,0xe8,0xdd,0x74,0x1f,0x4b,0xbd,0x8b,0x8a,0x70,0x3e,0xb5,0x66,0x48,0x03,0xf6,0x0e,0x61,0x35,0x57,0xb9,0x86,0xc1,0x1d,0x9e,0xe1,0xf8,0x98,0x11,0x69,0xd9,0x8e,0x94,0x9b,0x1e,0x87,0xe9,0xce,0x55,0x28,0xdf,0x8c,0xa1,0x89,0x0d,0xbf,0xe6,0x42,0x68,0x41,0x99,0x2d,0x0f,0xb0,0x54,0xbb,0x16};

const byte rcon[10]={0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36};


void Matrice44::init(){
  for (int i=0; i<16; i++){
    matrice[i]=0;
    key[i]=0;
  }
  for (int i=0; i<4; i++){
    colonne[i]=0;
  }
  tour = 0;
}

Matrice44::Matrice44(const byte message[16],const byte cle[16]){
  init();
  for (int i=0; i<16; i++){
    matrice[i]=message[i];
    key[i]=cle[i];
  }
}

void Matrice44::loop(){

  cout<<"Start"<<endl;
  affich();

  cout<<"RoundKey Value"<<endl;
  affich(2);

  for (int k=0; k<9; k++){

    cout<<"\n\n------------tour n° : "<<k+1<<endl;

    addRoundKey();
    cout<<"Start of round"<<endl;
    affich();

    subBytes(sbox);
    cout<<"subBytes"<<endl;
    affich();

    shiftRow();
    cout<<"shiftRow"<<endl;
    affich();

    mixColumns();
    cout<<"mixColumns"<<endl;
    affich();

    expansionKey();
    cout<<"Round Key Value"<<endl;
    affich(2);
  }

  cout<<"\n\n------------dernier tour : "<<endl;
  addRoundKey();
  cout<<"Start of round"<<endl;
  affich();

  subBytes(sbox);
  cout<<"subBytes"<<endl;
  affich();

  shiftRow();
  cout<<"shiftRow"<<endl;
  affich();

  expansionKey();
  cout<<"Round Key Value"<<endl;
  affich(2);

  addRoundKey();
  cout<<"End"<<endl;
  affich();
}

void Matrice44::shiftRow(){
  decalage(1,1);
  decalage(2,2);
  decalage(3,3);
}

void Matrice44::decalage(int nb, int line){
  if (nb==1){
    byte stock = matrice[1];
    for (int i=0; i<3; i++){
      matrice[4*i+1]=matrice[4*(i+1)+1];
    }
    matrice[12+1]=stock;
  } else if (nb==2){
    byte stock1 = matrice[2];
    byte stock2 = matrice[4+2];
    matrice[2] = matrice[4*2+2];
    matrice[4+2] = matrice[4*3+2];
    matrice[4*2+2] = stock1;
    matrice[4*3+2] = stock2;
  } else if (nb==3){
    byte stock = matrice[15];
    for (int i=0; i<3; i++){
      matrice[4*(3-i)+3]=matrice[4*(3-i-1)+3];
    }
    matrice[3]=stock;
  }
}

void Matrice44::subBytes(const byte sbox[256]){
  for (int i=0; i<16; i++){
    matrice[i]=sbox[matrice[i]];
  }
}


void Matrice44::addRoundKey(){
  for (int octet=0; octet<16; octet++){
    matrice[octet]^=key[octet];
  }
}

void Matrice44::mixColumns(){
  for (int i=0; i<4; i++){
    byte a[4];
    byte b[4];
    byte h;
    for (int c=0; c<4; c++){
      a[c]=matrice[4*i+c];
      h = (byte)((int8_t)matrice[4*i+c]>>7);
      b[c]=matrice[4*i+c]<<1;
      b[c]^=0x1B & h;
    }
    matrice[4*i] = b[0] ^ a[3] ^ a[2] ^ b[1] ^ a[1];
    matrice[4*i+1] = b[1] ^ a[0] ^ a[3] ^ b[2] ^ a[2];
    matrice[4*i+2] = b[2] ^ a[1] ^ a[0] ^ b[3] ^ a[3];
    matrice[4*i+3] = b[3] ^ a[2] ^ a[1] ^ b[0] ^ a[0];
  }
}

void Matrice44::expansionKey(){

  //colonne temporaire = dernière colonne matrice courante
  for (int i=0; i<4; i++){
    colonne[i]=key[12+i];
  }
  rotWord();
  subWord(sbox);
  Rcon(rcon);
  for (int i=0; i<4; i++){
    for (int j=0; j<4; j++){
      colonne[j]^=key[4*i+j];
      key[4*i+j]=colonne[j];
    }
  }
  tour++;
}

void Matrice44::rotWord(){
  byte stock=colonne[0];
  for (int i=0; i<3; i++){
    colonne[i]=colonne[i+1];
  }
  colonne[3]=stock;
}

void Matrice44::subWord(const byte sbox[256]){
  for (int i=0; i<4; i++){
    colonne[i]=sbox[colonne[i]];
  }
}

void Matrice44::Rcon(const byte rcon[10]){
  colonne[0]^=rcon[tour];
}


void Matrice44::affich(int i){
  cout<<endl;
  int compteur=0;
  for (int n=0; n<4; n++) {
    cout<<"[";
    for (int p=0; p<4; p++){
      cout<<"[";
      // cout<<matrice[compteur];
      if (i==1){
        cout << hex << int(matrice[compteur]);
      }else if (i=2){
        cout << hex << int(key[compteur]);
      }
      compteur++;
      cout<<"]";
    }
    cout<<"]"<<endl;
  }
  cout<<endl;
}

/*void Matrice44::remplissage(){
  int ascii;
	int length = strlen(msg);
  int compteur=0;

	for(int i = 0; i < length; i++){

		ascii = msg[i];

    int* binary;
    binary=int_binary(ascii);

    for (int bit=0; bit<8; bit++){
      matrice[i][bit]=binary[bit];
    }
    compteur++;
  }

  while(compteur<length){
    for (int i=0; i<8;i++){
      matrice[compteur][i]=0;
    }
    compteur++;
  }
}

int* int_binary(int ascii){

  int* octet_reverse = new int [8];
  int* octet = new int [8];

  int j = 0;

  while(ascii != 1){
    octet_reverse[j] = ascii%2;
    ascii /= 2;
    j++;
  }

  if(ascii == 1){
    octet_reverse[j] = 1;
    j++;
  }

  if(j < 8){
    for(; j < 8; j++){
      octet_reverse[j] = 0;
    }
  }

  for(int z = 0; z < 8; z++){
    octet[z] = octet_reverse[7 - z];
  }

  return octet;
}

int binary_int(int * binary){
  int entier=0;
  for (int i=0; i<4; i++){
    entier+=binary[3-i]*pow(2,i);
  }
  return entier;
}*/
