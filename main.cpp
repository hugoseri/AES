#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

//simon.pontie@cea.fr

#include "keyMatrix.h"
#include "messageMatrix.h"

int main() {

  //example message and key in ASCII
  // byte message[16]={'m','o','n','m','e','s','s','a','g','e','s','e','c','r','e','t'};
  // byte key[16]={'m','a','s','u','p','e','r','c','l','e','f','d','e','a','e','s'};

  //message and key used in the AES paper example
  //byte message[16]={0x32,0x43,0xf6,0xa8,0x88,0x5a,0x30,0x8d,0x31,0x31,0x98,0xa2,0xe0,0x37,0x07,0x34};
  //byte key[16]={0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c};


  //interactive interface : ask the client the message and key
  byte message[16];
  byte key[16];

  cout<<"Enter message to cypher [16 characters-length maximum] : ";
  cin>>message;
  cout<<"My message : "<<message<<endl;

  cout<<"Enter cypher key [16 characters-length maximum]: ";
  cin>>key;
  cout<<"My key : "<<key<<endl;


  messageMatrix msgMatrix(message);
  keyMatrix kMatrix(key);


  cout<<"Start"<<endl;
  msgMatrix.show();

  // show(2);
  //cout<<"RoundKey Value"<<endl;

  for (int k=0; k<9; k++){
    // cout<<"\n\n------------Loop number : "<<k+1<<endl;

    msgMatrix.addRoundKey(kMatrix.matrix);
    // cout<<"Start of round"<<endl;
    // msgMatrix.show();

    msgMatrix.subBytes(sbox);
    // cout<<"subBytes"<<endl;
    // msgMatrix.show();

    msgMatrix.shiftRow();
    // cout<<"shiftRow"<<endl;
    // msgMatrix.show();

    msgMatrix.mixColumns();
    // cout<<"mixColumns"<<endl;
    // msgMatrix.show();

    kMatrix.expansionKey();
    // cout<<"Round Key Value"<<endl;
    // keyMatrix.show();
  }

  // cout<<"\n\n------------dernier round : "<<endl;
  msgMatrix.addRoundKey(kMatrix.matrix);
  // cout<<"Start of round"<<endl;
  // msgMatrix.show();

  msgMatrix.subBytes(sbox);
  // cout<<"subBytes"<<endl;
  // msgMatrix.show();

  msgMatrix.shiftRow();
  // cout<<"shiftRow"<<endl;
  // msgMatrix.show();

  kMatrix.expansionKey();
  // cout<<"Round Key Value"<<endl;
  // keyMatrix.show();

  msgMatrix.addRoundKey(kMatrix.matrix);
  cout<<"End"<<endl;
  msgMatrix.show();



  return 0;
}
