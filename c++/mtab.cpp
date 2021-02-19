#include <iostream>
#include "tab.hpp"
using namespace std;
tab::tab(){
	int i,j;
	 t = new int* [ 20 ];
  for (int i=0; i < 20; i++){
    t[i] = new int[20 ];
 }
 for(i=0;i<20;i++){
 	for(j=0;j<20;j++){
 		t[i][j]=0;
	 }
 }
}

tab::tab(int n){
	int i,j;
	 t = new int* [ n ];
  for (int i=0; i < n; i++){
    t[i] = new int[n ];
 }
 for(i=0;i<n;i++){
 	for(j=0;j<n;j++){
 		t[i][j]=i;
	 }
 }
}

void tab::afficher(){
	int i,j;
	for(i=0;i<this->n;i++){
 	for(j=0;j<this>n;j++){
 		cout <<t[i][j]<<;
	 }
	 cout<<endl;
 }
	
}


