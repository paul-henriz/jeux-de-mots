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


char* creerTab1D(int taille){
    char* tab = malloc(taille * sizeof(char));
    initTab1D(tab, taille);
    return tab;
}
void initTab1D(char* tab, int taille){
    if(taille == -1) return;
    *(tab + taille - 1) = '*';
    initTab1D(tab, --taille);
}
void affichageTab1D(char* tab, int taille){
    if(*tab){
        printf("%c ", *tab);
        affichageTab1D(++tab, taille);
    }
}

char** creerTab2D(int taille, int tailley){
    return '**';
}


int main(int argc, const char * argv[]) {
    
    affichageTab1D(creerTab1D(10), 10);
    return 0;

}
