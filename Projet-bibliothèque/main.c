//
//  main.c
//  Projet-bibliothèque
//
//  Created by Paul-Henri Zimmerlin on 16/03/2017.
//  Copyright © 2017 Paul-Henri Zimmerlin. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

char* creerTab1D(int taille);
void initTab1D(char* tab, int taille);
void affichageTab1D(char* tab, int taille);
char** creerTab2D(int taillex, int tailley);
void init2D(char **x, int taillex, int tailley);
void affichageTab2D(char** tab, int taillex, int tailley);


char* creerTab1D(int taille){
    char* tab = malloc(taille * sizeof(char));
    initTab1D(tab, taille);
    return tab;
}
void initTab1D(char* tab, int taille){
    if(taille > 0){
        *(tab) = '*';
        initTab1D(tab + 1, taille - 1);
    }
}
void affichageTab1D(char* tab, int taille){
    if(*tab){
        printf("%c ", *tab);
        affichageTab1D(++tab, taille);
    }
}

char** creerTab2D(int taillex, int tailley){
    char** x = malloc(taillex * sizeof(char*));
    init2D(x, taillex, tailley);
    return x;
}
void init2D(char **x, int taillex, int tailley){
    if(taillex > 0){
        *x = creerTab1D(tailley);
        init2D(x + 1, taillex - 1,tailley);
    }
    
}
void affichageTab2D(char** tab, int taillex, int tailley){
    for(int i = 0; i < taillex; i++){
        for(int j = 0; j < tailley; j++){
            printf("%c ", *(*(tab + i) + j));
        }
        printf("\n");
    }
}




int main(int argc, const char * argv[]) {
    
    //affichageTab1D(creerTab1D(4), 4);
    //creerTab2D(4, 5);
    affichageTab2D(creerTab2D(4, 5), 4, 5);
    return 0;
    
}
