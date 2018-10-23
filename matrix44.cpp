#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;


#include "matrix44.h"


void Matrix44::show(){
  cout<<endl;
  int compteur=0;
  for (int n=0; n<4; n++) {
    cout<<"[";
    for (int p=0; p<4; p++){
      cout<<"[";
      cout << hex << int(matrix[compteur]);
      compteur++;
      cout<<"]";
    }
    cout<<"]"<<endl;
  }
  cout<<endl;
}
