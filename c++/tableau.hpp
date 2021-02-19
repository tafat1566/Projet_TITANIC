#ifndef __tableau_hpp__
#define __tableau_hpp__
class tableau{
	public:
		int n,v;
		int* tab;
		int *tab1;
		tableau();
		tableau(int );
		tableau(int ,int);
		tableau(tableau const &);
		~tableau();
		int gettab();
		void settab(int);
		void afficher();
		int siez();
		void resize();
		int  belongs(int );
		int find(int);
		void insert(int,int  );
		void supprimer(int );
		int static compt;
	};
#endif

