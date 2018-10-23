#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

//simon.pontie@cea.fr

#include "matrice44.h"

int main() {


  byte message[16]={'m','o','n','m','e','s','s','a','g','e','s','e','c','r','e','t'};
  byte key[16]={'m','a','s','u','p','e','r','c','l','e','f','d','e','a','e','s'};

  //byte message[16]={0x32,0x43,0xf6,0xa8,0x88,0x5a,0x30,0x8d,0x31,0x31,0x98,0xa2,0xe0,0x37,0x07,0x34};
  //byte key[16]={0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c};

  // do {
    // cout<<"Entrer message à chiffrer : ";
    // cin>>message;
  // } while (strlen(message)>16);

  // cout<<"mon msg : "<<message<<endl;

  // do {
    // cout<<"Entrer clé de chiffrement : ";
    // cin>>key;
  // } while (strlen(key)>16);

  // cout<<"ma clé : "<<key<<endl;


  Matrice44 matrix(message,key);

  matrix.loop();



  return 0;
}
