#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED
//Strture pile (LAST IN FIRST OUT°
typedef struct pile
{
    int tab[size];
    int top;
}PILE;


//Structure contenant deux tableaux
typedef struct aux
{
    int visited[16];
    int pere[30];
}aux;



#endif // STRUCTURES_H_INCLUDED
