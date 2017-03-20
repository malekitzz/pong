#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define MAX 50 

	/************PROTOTYPES DES FONCTIONS ***************************/

/* Initialise la grille de façon à ce qu'elle contienne ce qu'il 
y a à la figure de droite 
*/
void init_grille (char grille[][MAX],int pos_balle_x,int pos_balle_y);
/* Affiche le rectangle d'étoiles et la balle (tout ceci en même
temps et non pas le rectangle puis la balle...) 
*/
void affiche_grille (char grille[][MAX]); /* 10 lignes 10 colonnes */
/* Calcule la nouvelle position de la balle en fonction de 
l'ancienne position de la balle (old_pos_balle_x, old_pos_balle_y) 
et du vecteur de déplacement (deplacement_x, deplacement_y).
*/
void calcule_position_balle (char grille[][MAX], int *pos_balle_x, int *pos_balle_y, int *deplacement_x, int *deplacement_y);
void init_barre(char grille[][MAX], int pos_barre_left, int pos_barre_right);

void moove_barres(char grille[][MAX], char **argv, int pos_barre_left, int pos_barre_right);

	/*************  IMPLEMENTATION DES FONCTIONS ****************/

	
void init_barre(char grille[][MAX], int pos_barre_left, int pos_barre_right){ /* initialise les positions des barres */
	grille[pos_barre_left][1] = '|';
	grille[pos_barre_left - 1][1] = '|';
	grille[pos_barre_left - 2][1] = '-';
	grille[pos_barre_left + 1][1] = '-';

	grille[pos_barre_right + 1][MAX-2] = '-';
	grille[pos_barre_right - 2][MAX-2] = '-';
	grille[pos_barre_right-1][MAX-2] = '|';
	grille[pos_barre_right][MAX-2] = '|';
}
void moove_barres(char grille[][MAX], char **argv, int pos_barre_left, int pos_barre_right){ /*sensé faire bouger les barres O_o'*/
	if(argv[1] == "z"){
		pos_barre_left += 1;	
	}
	if(argv[1] == "s"){
		pos_barre_left -= 1;	
	}
	if(argv[1] == "p"){
		pos_barre_right += 1;	
	}
	if(argv[1] == "m"){
		pos_barre_right -= 1;	
	}
}
void init_grille (char grille[][MAX], int pos_balle_x,int pos_balle_y){ /* initialise la grille avec la balle */
int lignes, colonnes;
	memset(grille, ' ', 2500);
	colonnes = 0;
	while(colonnes < MAX){
		grille[0][colonnes] = '*';
		grille[MAX - 1][colonnes] = '*';
		colonnes++;
	}

	lignes = 0;
	while(lignes < MAX){
		grille[lignes][0] = '*';
		grille[lignes][MAX - 1] = '*';
		lignes++;
	}
	
	grille[pos_balle_x][pos_balle_y] = 'O';
}
void affiche_grille (char grille[][MAX]){
	int i, j;
	i = 0;
	while(i < MAX){
		j = 0;
		while(j < MAX){				/* affiche juste la grille */
			printf("%c",grille[i][j]);	
			j++;	
		}
		printf("\n");
		i++;
	}
}
void calcule_position_balle (char grille[][MAX], int *pos_balle_x,int *pos_balle_y,int *deplacement_x,int *deplacement_y){

	int old_pos_balle_x = *pos_balle_x;
	int old_pos_balle_y = *pos_balle_y;
	
	grille[*pos_balle_x][*pos_balle_y] = ' ';
	printf("position actuelle %d / %d n", *pos_balle_x, *pos_balle_y);
	printf("deplacement : %d / %d\n", *deplacement_x, *deplacement_y);
	old_pos_balle_x = *pos_balle_x + *deplacement_x;
	old_pos_balle_y = *pos_balle_y + *deplacement_y;

	if((old_pos_balle_x == MAX - 1) || (old_pos_balle_x == 0)){	/* si la balle tape sur un coté elle change diamétralement de direction */
		*deplacement_x = - *deplacement_x;
	}
	if((old_pos_balle_y == MAX - 1) || (old_pos_balle_y == 0)){
		*deplacement_y = - *deplacement_y;	
	}
	*pos_balle_x += *deplacement_x;
	*pos_balle_y += *deplacement_y;

	printf("Nouvelle pos : %d / %d\n",*pos_balle_x, *pos_balle_y);

	grille[*pos_balle_x][*pos_balle_y] = 'O';
	
}
int main(int argc, char **argv){
	char test;
	int pos_balle_x=22, pos_balle_y=12;    		/* position  balle au départ  */
	int deplacement_x = 1, deplacement_y = 1;	/* déplacement balle  */
	char grille[MAX][MAX]; 			
	int pos_barre_left = MAX / 2 - 5; 		/* position de départ de la barre de gauche */
	int pos_barre_right = MAX / 2 - 1;		/* position de départ de la barre de droite */
	init_grille (grille, pos_balle_x, pos_balle_y);	/* on affiche la grille */
	init_barre(grille, pos_barre_left, pos_barre_right);	/* on affiche les barres */
		while (1) { 				/*boucle infinie de test */
			system("clear");		/* efface l'affichage */
			affiche_grille(grille);		/* affiche la nouvelle grille avec la nouvelle position de la ballle a chaque tour de boucle */
				scanf("%c" &test);
				printf("%c", test);
				moove_barres(grille, &argv, &pos_barre_left, &pos_barre_right); /* prend en compte l'entree clavier utilisisateur si il y en a */
				calcule_position_balle (grille, &pos_balle_x, &pos_balle_y, &deplacement_x, &deplacement_y); /* change la pos de la balle */
			usleep(300000); 		 /* Pause de 300 000 micro secondes donc 1/2 seconde */
       		}
}
