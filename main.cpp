#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#define size 31
#include"Fonctions.h"
#include"Structures.h"
#include"NomsFonctions.h"
#include<time.h>







int main(int argc, char** argv)

{

     srand(time(NULL));
    /**********Déclaration des variables**********/
    SDL_Window * window=NULL;
    SDL_Surface * surface=NULL;
    SDL_Surface * icon=NULL;
    SDL_Surface * labyrinthe=NULL;
    SDL_Surface *guide=NULL;
    SDL_Surface * homepage=NULL     ;
    SDL_Surface * S1=NULL     ;
    SDL_Surface * S2=NULL     ;
    SDL_Event  event ;
    SDL_Rect robot,possortie1,possortie2,position1,position2;
    SDL_Rect pos;
    SDL_bool   lancer=SDL_TRUE;
    int compt=0,comptx=0,j=0,sortie1=7,sortie2=8,
    SDL_width=900,SDL_height=700,
    active1=0,active2=0,active3=0,active4=0,s=0,s1=0;
    int entree;
    int T[]={12,15,9,2,1,3,6,13};
    entree=T[rand()% 8] ;
    int l=0;

    /**********Déclaration et initialisation des variables des fonctions**********/
    aux* par=(aux*)malloc(sizeof(aux));
    PILE* chemin=(PILE*)malloc(sizeof(PILE));
    PILE* parcours=(PILE*)malloc(sizeof(PILE));
    initalisation(par,parcours,chemin);



    /**********Matrice d'adjacence**********/
    FILE *fichier;
    fichier=fopen("Ressources/matriceadjacence.txt","r");///ouvrir le fichier matriceadjacence.txt
    charger(fichier,adjList);       ///Remplir la matrice adjList a partir du fichier



    /**********Initialisation de la SDL**********/

    if(SDL_Init(SDL_INIT_VIDEO)!=0)
    {
        fprintf(stderr,"error-->%s",SDL_GetError());
        exit (EXIT_FAILURE);
    }


    /**********Creation de la fenetre :**********/
    window=SDL_CreateWindow("labyrinthe",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SDL_width,SDL_height,0);

    /**********creation de la surface  :**********/
    surface=SDL_GetWindowSurface(window);

    /**********Gestion d'erreur :**********/
    //Pour window
    if(window==NULL)
    {
        fprintf(stderr,"error-->%s",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    //Pour Surface
    if(surface==NULL)
    {
        fprintf(stderr,"error-->%s",SDL_GetError());
        exit (EXIT_FAILURE);
    }

    /**********Window Icone**********/
    icon=SDL_LoadBMP("Ressources/icone.BMP") ;
    SDL_SetWindowIcon(window,icon);

    /**********charger la photo homepage dans la surface A la position pos**********/
    homepage=SDL_LoadBMP("Ressources/homepage.BMP") ;
    pos={0,0,SDL_width,SDL_height};
    SDL_BlitSurface(homepage, NULL,surface,&pos);

    /**********Initialisations des positions probabilistes du robot**********/
    robot={posx(entree),posy(entree),32,32};
    possortie1={posx(sortie1),posy(sortie1),32,32};
    possortie2={posx(sortie2),posy(sortie2),32,32};
    position1={250,150,400,400};
    position2={25,150,200,350};

    /**********chargement de l'image du labyrinthe et du guide d'utilisateur**********/
    labyrinthe=SDL_LoadBMP("Ressources/labyrinthe.BMP");
    guide=SDL_LoadBMP("Ressources/tut.BMP");
    S1=SDL_LoadBMP("Ressources/S1.BMP");
    S2=SDL_LoadBMP("Ressources/S2.BMP");


    /**********Remplissage des deux PILES parcours et chemin**********/

    recherche(chemin, parcours, par,entree,sortie1);

    /**********Lancement du programme**********/


    while(lancer)
    {
        if(SDL_PollEvent(&event)!=0)
        {
            if(event.type==SDL_QUIT)
            {
                lancer=SDL_FALSE;
                goto QUIT;
                break;
            }

            else if(event.type==SDL_KEYDOWN)
                {   // cliquer sur  a  Pour faire le parcours
                    if(event.key.keysym.sym==SDLK_a)
                        {
                            active1=1;
                            printf(">>Recherche de la sortie s1 en cours...\n ");
                        }
                    else if(event.key.keysym.sym==SDLK_c)
                        {
                            active3=1;
                            printf(">>Recherche de la sortie s2 en cours...\n");
                        }
                    // cliquer sur  b  Pour faire le chemin
                    else if(event.key.keysym.sym==SDLK_b)
                    {
                        active2=1;
                        compt=0;
                        SDL_FillRect(surface,NULL,SDL_MapRGB(surface->format,11,25,37));// Arriere plan
                        SDL_BlitSurface(labyrinthe, NULL,surface,&position1);// Image du labyrinthe
                        printf("\n\n>>tracage du premier chemin en cours...\n");

                    }
                    else if(event.key.keysym.sym==SDLK_d)
                    {
                        active4=1;
                        comptx=0;
                        SDL_FillRect(surface,NULL,SDL_MapRGB(surface->format,11,25,37));// Arriere plan
                        SDL_BlitSurface(labyrinthe, NULL,surface,&position1);// Image du labyrinthe
                        printf(">>tracage du deuxieme chemin en cours...\n");

                    }
                }
                // Se mettre en position de depart
                else if(event.type==SDL_MOUSEBUTTONDOWN || active2==-1)
                {
                    if(event.button.button==SDL_BUTTON_LEFT || active2==-1)
                    {
                        if((event.button.x>360.084 && event.button.x<540.832) || active2==-1)
                        { if ((event.button.y>495.473 && event.button.y<560.526) || active2==-1)
                            {

                                active2=0;
                                l++;
                                compt=1;
                                comptx=1;
                                SDL_FillRect(surface,NULL,SDL_MapRGB(surface->format,11,25,37)); // Arriere plan

                                SDL_BlitSurface(labyrinthe, NULL,surface,&position1);
                                SDL_BlitSurface(guide, NULL,surface,&position2); // Guide d'utilisateur
                                SDL_FillRect(surface,&robot,SDL_MapRGB(surface->format,255,0,0));// Afficher la position d'entree du robot
                                SDL_BlitSurface(S1, NULL,surface,&possortie1);
                                SDL_BlitSurface(S2, NULL,surface,&possortie2);
                            }
                        }

                    }
                }

        }

        /**********Tracer le parcours :**********/
        if((compt==1 && active1==1) || (comptx==1 && active3==1))
        {   int b=1;

            if(comptx==1 && active3==1) // parcours pour la sortie s2
            {
                par=(aux*)malloc(sizeof(aux));
                s=1;
                robot={posx(entree),posy(entree),32,32};
                initalisation(par,parcours,chemin);
                recherche(chemin, parcours, par,entree,sortie2);
                b=0;
                active3=-1;
            }
            //Deplacement du robot :
            for(j=1;j<=1+parcours->top;j++)
            {   int i;

                int k=(posx(parcours->tab[j])-robot.x);
                int h=(posy(parcours->tab[j])-robot.y);
                for(i=0;i<25;i++)
                {

                    (robot.x)+=k/25;
                    (robot.y)+=h/25;

                    SDL_Delay(30);

                    SDL_FillRect(surface,&robot,SDL_MapRGB(surface->format,0,0,255));//afficher la position instantanee du robot
                    SDL_UpdateWindowSurface(window);



                    if (b==0)SDL_BlitSurface(S1, NULL,surface,&possortie1);
                    if (b==1)SDL_BlitSurface(S2, NULL,surface,&possortie2);
                    SDL_FillRect(surface,&robot,SDL_MapRGB(surface->format,255,0,0));


                }

            }
            if(s==0) printf("- Recherche de s1 terminer\n\n");
            else printf("- Recherche de s2 terminer\n\n");
            active1=-1;

        }
        /**********Tracer le chemin :**********/
        if((compt==0 && active2==1)|| (comptx==0 && active4==1))
        {
            if(comptx==0 && active4==1)
            {
                s1=1;
                robot={posx(entree),posy(entree),32,32};
                active4=-1;
            }

            //Tracer le chemin final
            for(j=-1+chemin->top;j>=-1;j--)
            {
                int i=depiler(chemin);
                int k=(posx(i)-robot.x);
                int h=(posy(i)-robot.y);
                for(i=0;i<25;i++)
                {
                (robot.x)+=k/25;
                (robot.y)+=h/25;

                SDL_Delay(3);
                SDL_FillRect(surface,&robot,SDL_MapRGB(surface->format,255,255,255));
                SDL_UpdateWindowSurface(window);

                }
            }
            SDL_Delay(3000);
            active2=-1;
            if(s1==0) printf("- premier chemin tracer\n\n");
            else printf("- deuxieme chemin tracer\n\n");

            }






        SDL_SetWindowIcon(window,icon);
        SDL_UpdateWindowSurface(window);




    }


    /**********Free :**********/
    SDL_free(window);
    SDL_free(surface);
    SDL_free(homepage);
    SDL_free(labyrinthe);
    SDL_free(guide);
    SDL_free(icon);
QUIT :
    SDL_Quit();
    return 0;
}


