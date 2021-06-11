#ifndef NOMSFONCTIONS_H_INCLUDED
#define NOMSFONCTIONS_H_INCLUDED
//charger la matrice d'adjacence depuis le fichier matriceadjacence.txt
void charger(FILE *fichier,int (*adjList)[16]);
//afficher la matrice adjList
void afficher_matrice(int (*adjList)[16]);
//Position du robot suivant l'axe X
int posx(int n);
//Position du robot suivant l'axe X
int posy(int n);
//initialisation des parametres
void initalisation(aux* par,PILE* parcours,PILE* chemin);
//Charger les elements (noeuds) dans la pile
void empiler(PILE *p,int element);
//Afficher les elements (noeuds) dans la pile
int depiler(PILE *p);
//le choix du bon noeud parmi les cas favorables
void DFSrec(PILE*passage,aux*p,int entree);
//Remplissage des deux PILES parcours et chemin
void recherche(PILE*chemin,PILE*parcours,aux*par,int entree,int sortie);

#endif // NOMSFONCTIONS_H_INCLUDED
