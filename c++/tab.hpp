#ifndef __tab_hpp__
#define __tab__hpp__
class tab{
	public:
		int n,v;
		int **t;
		tab();
		tab(int );
		tab(tab const &);
		int get();
		void set(int );
		void afficher();
};
#endif 
