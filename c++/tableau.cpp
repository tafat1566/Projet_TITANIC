#include <iostream>
#include "tableau.hpp"
tableau::tableau(){
	tab=new int[2];
	n=2;
	for(int i=0;i<this->n;i++){
		tab[i]=0;
	}
	//delete tab[];
}
tableau::tableau(int n){
	tab=new int[n];
	for(int i=0;i<n;i++){
		tab[i]=i;
	}
}


tableau::tableau(tableau const & p){
	tab=new int [n];
	for(int i=0;i<n;i++){
		tab[i]=p.tab[i];
	}
}


tableau::~tableau(){
	delete [] tab;
	std::cout<<"je suis le destr"<<std::endl;
	}

int tableau::gettab(){
	for(int i=0;i<n;i++){
		return tab[i];
	}
}


void tableau::settab(int v){
	for(int i=0;i<n;i++){
		tab[i]=v;
	}
}


int tableau::size(){
	int j=n;
	return j;
}

void tableau::resize(){
	int j;
	for(int i=0;i<n;i++){
		tab1[i]=tab[i];
	}
}


int  tableau::belongs(int a){
	int x=0;
	for(int i=0;i<n;i++){
		if(tab[i]==a){
			x=1;
		}
	}
	return x;
}

int  tableau::find(int a){
	int x=0;

	for(int i=0;i<n;i++){
		if(tab[i]==a){
			x=1;
			int c=i;
			break();
		}
	}
	if(x==1){
		return c;
}

}


void tableau:: insert(int a,int indice){
	tab=new int[n+1];
	int *temp=new int [n+1];
	for(int i=0;i<n+1;i++){
		temp[i]=0;
	}

	temp[indice]=a;
	for(int i=0;i<n+1;i++){
		tab[i]=temp[i];
	}
}

void tableau::supprimer(int indice ){
	int *temp=new int [n-1];
	tab=int [n-1];
	
	


void tableau::afficher(){
	std::cout<<"entrer la taille de n="<<std::endl;
	std::cin >>n;
	tab=new int[this->n];
	for(int i=0;i<n;i++){
		std::cout<<"tab[i]="<<tab[i]<<std::endl;
		
	}
}







