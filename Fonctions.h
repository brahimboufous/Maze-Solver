#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED
#include"Structures.h"

int adjList[16][16]={0};
void charger(FILE *fichier,int (*adjList)[16])
{   int i=0;char T[16];
     while(i<16)
    {
        fgets(T,18,fichier);
        for(int j=0;j<16;j++)
        {
            adjList[i][j]=T[j]-48; // pour changer '0' et '1' en 0 et 1
        }
        i++;
    }
}

void afficher_matrice(int (*adjList)[16])
{
        for(int i=0;i<16;i++)
    {
        for(int j=0;j<16;j++)
        {
            printf("%d",adjList[i][j]);
        }
        printf("\n");

    }
}


int posx(int n)
{
   int a=(n%4);
   return (a*100)+250+34;
}

int posy(int n)
{
  int a=n/4;
  return (a*100)+150+34;
}

//-----------------------------------------------------------------------------
void initalisation(aux* par,PILE* parcours,PILE* chemin)
{
    int i;
    chemin->top =-1;
    parcours->top =-1;
    for ( i=0;i<16;i++)
     {
        par->visited[i]=0;
     }
    for (i=0;i<30;i++)
     {
        par->pere[i]=-1;
     }

}



//-----------------------------------------------------------------------------------


void empiler(PILE *p,int element)
   {
     if (p->top >= size - 1)
        return;
      p->top++;
      p->tab[p->top] = element;
   }


int depiler(PILE *p)
   {
      if (p->top == -1)
      return 1;
      int element;
      element = p->tab[p->top];
      p->top--;
      return element;
   }



void DFSrec(PILE*passage,aux*p,int entree)
{
    int i;
    //process
    empiler(passage,entree);
    p->visited[entree]=1;

    for(i=0;i<=16;i++)
    {
        if (adjList[entree][i] == 1 && p->visited[i] == 0)

         {
             p->pere[i]=entree;
             DFSrec(passage,p,i);
             //process
             empiler(passage,entree);
         }

    }
}


void recherche(PILE*chemin,PILE*parcours,aux*par,int entree,int sortie)
{
     int i=0,j=-1;
    PILE*passage=(PILE*)malloc(sizeof(PILE));
    passage->top =-1;

    DFSrec(passage,par,entree);

    int courant=sortie;

    do
    {
        j++;
        empiler(parcours,passage->tab[j]);
    }while (parcours->tab[j]!=sortie);



    while(courant!=-1 )
    {
        empiler(chemin,courant);
        courant=par->pere[courant];
        i++;
    }


}
#endif // FONCTIONS_H_INCLUDED
