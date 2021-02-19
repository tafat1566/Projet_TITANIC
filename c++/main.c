/* Programme d'othello avec une recherche en negamax. La fonction
   d'evaluation est tres simple (difference du nombre de pions), et
   les cas ou un joueur ne peut pas jouer ne sont pas traites.
   
   Bernard Helmstetter, 2006
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOIR 0
#define BLANC 1
#define VIDE 2
#define AUTRE_JOUEUR(j) (1-(j))
#define INFINI 1000000		/* evaluation plus grande que toutes
				   les evaluations possibles */
#define GAGNE 10000		/* evaluation pour une partie gagnee */
#define NOEUDS_MAX 1000000

int plateau[8][8];
int nb_pions[2];		/* nb de pions noirs et blancs */
int ordinateur_joue[2] = {1, 0}; /* noir et blancs sont-ils geres par l'IA ? */
int compteur_noeuds;		/* nb de noeuds dans le negamax */

/* deplacements en x et y correspondant aux 8 directions */
int deltax[8] = {1, -1, 0, 0, 1, 1, -1, -1};
int deltay[8] = {0, 0, 1, -1, 1, -1, 1, -1};

void afficher_plateau()
{
  int x, y;
  
  for (y = 0; y < 8; y++) {
    printf("%d ", y+1);
    for (x = 0; x < 8; x++) {
      if (plateau[x][y] == VIDE)
	printf(". ");
      else if (plateau[x][y] == NOIR)
	printf("x ");
      else if (plateau[x][y] == BLANC)
	printf("o ");
    }
    printf("\n");
  }
  printf("  ");
  for (x = 0; x < 8; x++)
    printf("%c ", 'a'+x);
  printf("\n\n");
}

void initialiser_plateau()
{
  int x, y;
  
  for (x = 0; x < 8; x++)
    for (y = 0; y < 8; y++)
      plateau[x][y] = VIDE;
  
  plateau[3][4] = plateau[4][3] = BLANC;
  plateau[3][3] = plateau[4][4] = NOIR;
  nb_pions[BLANC] = nb_pions[NOIR] = 2;
}

int dans_plateau(int x, int y)
{
  return (x >= 0 && x < 8 && y >= 0 && y < 8);
}

/* retourne la ligne dans la direction d, apres un coup du joueur en
   (x,y), et renvoit le nonbre de pions retournes */
int retourner_ligne(int x, int y, int d, int joueur)
{
  int x2, y2;
  int nb_retournes = 0;
  
  /* determniner le nb de pions a retourner */
  x2 = x+deltax[d];
  y2 = y+deltay[d];
  while (1) {
    if (!dans_plateau(x2, y2) || plateau[x2][y2] == VIDE)
      return 0;
    if (plateau[x2][y2] == joueur)
      break;
    nb_retournes++;
    x2 += deltax[d];
    y2 += deltay[d];
  }
  
  /* recommencer en retournant les pions */
  if (nb_retournes > 0) {
    x2 = x+deltax[d];
    y2 = y+deltay[d];
    while (plateau[x2][y2] != joueur) {
      plateau[x2][y2] = joueur;
      x2 += deltax[d];
      y2 += deltay[d];
    }
  }
  return nb_retournes;
}

/* joue le coup si il est legal, et renvoit le nombre de pions
   retournes */
int essayer_coup(int x, int y, int joueur)
{
  int d;
  int nb_retournes = 0;
  
  if (!dans_plateau(x, y) || plateau[x][y] != VIDE)
    return 0;
  
  for (d = 0; d < 8; d++)
    nb_retournes += retourner_ligne(x, y, d, joueur);
  
  if (nb_retournes == 0)
    return 0;
  
  plateau[x][y] = joueur;
  nb_pions[joueur] += 1 + nb_retournes;
  nb_pions[AUTRE_JOUEUR(joueur)] -= nb_retournes;
  return nb_retournes;
}

/* fonction d'evaluation dans une position non terminale */
int evaluation(int joueur)
{
  return nb_pions[joueur] - nb_pions[AUTRE_JOUEUR(joueur)];
}

int negamax(int joueur, int *mx, int *my, int prof)
{
  int x, y;
  int eval, e;
  int mx2, my2;
  int plateau2[8][8];		/* pour sauvegarder la position
				   initiale */
  int nb_pions2[2];
  
  compteur_noeuds++;
  
  if (nb_pions[NOIR] + nb_pions[BLANC] == 64) /* fin de la partie */
    return GAGNE*(nb_pions[joueur] - nb_pions[AUTRE_JOUEUR(joueur)]);
  
  if (prof <= 0)
    return evaluation(joueur);
  
  /* on cherche tous les coups pour joueur et on renvoit le max des opposes 
     des evaluations aux noeuds fils */
  memcpy(plateau2, plateau, sizeof(plateau));
  memcpy(nb_pions2, nb_pions, sizeof(nb_pions));
  eval = -INFINI;
  for (x = 0; x < 8; x++)
    for (y = 0; y < 8; y++)
      if (essayer_coup(x, y, joueur)) {
	e = -negamax(AUTRE_JOUEUR(joueur), &mx2, &my2, prof-1);
	if (e > eval) {
	  *mx = x; *my = y;
	  eval = e;
	}
	memcpy(plateau, plateau2, sizeof(plateau));
	memcpy(nb_pions, nb_pions2, sizeof(nb_pions));
      }
  return eval;
}

/* lance des recherches minimax pour des profondeurs croissantes,
   jusqu'a atteindre la borne sur le nombre de noeuds */
int approfondissement_iteratif(int joueur, int *x, int *y)
{
  int prof, eval;
  
  printf("prof\tnoeuds\teval\tcoup\n");
  for (prof = 1; ; prof++) {
    compteur_noeuds = 0;
    eval = negamax(joueur, x, y, prof);
    printf("%d\t%d\t%d\t%c%d\n", prof, compteur_noeuds, eval, 'a'+*x, *y+1);
    if (abs(eval) >= GAGNE || compteur_noeuds > NOEUDS_MAX)
      return eval;
  }
}

/* les coordonnees du coup sont renvoyees dans *x et *y.  Le coup doit
 etre entre sous la forme "c3" */
void demander_coup(int joueur, int *x, int *y)
{
  char buffer[100];
  
  printf("Votre coup (%c) : ", (joueur == NOIR) ? 'x' : 'o');
  if (fgets(buffer, 100, stdin) == NULL) {
    fprintf(stderr, "demander_coup : erreur lecture\n");
    exit(1);
  }
  *x = buffer[0]-'a';
  *y = buffer[1]-'1';
}

int main()
{
  int eval;
  int joueur;
  int x, y;
  
  initialiser_plateau();
  joueur = NOIR;
  
  afficher_plateau();
  for (;;)
    {		    /* boucle principale pour jouer interactivement */
      if (ordinateur_joue[joueur]) { /* tour de l'ia */
	eval = approfondissement_iteratif(joueur, &x, &y);
	if (!essayer_coup(x, y, joueur)) {
	  printf("Erreur : negamax renvoie un coup illegal\n");
	  exit(1);
	}
      }
      else {
      demander_coup:
	demander_coup(joueur, &x, &y); /* tour du joueur humain */
	if (!essayer_coup(x, y, joueur)) {
	  printf("Coup illegal\n");
	  goto demander_coup;
	}
      }
      
      afficher_plateau();
      
      /* fin de la partie ? */
      if (nb_pions[BLANC] + nb_pions[NOIR] == 64) {
	printf("noir : %d\n", nb_pions[NOIR]);
	printf("blanc : %d\n", nb_pions[BLANC]);
	break;
      }
      
      joueur = AUTRE_JOUEUR(joueur);
    }
  
  return 0;
}
