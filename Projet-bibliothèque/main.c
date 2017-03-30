//
//  main.c
//  Projet-bibliothèque
//
//  Created by Paul-Henri Zimmerlin on 16/03/2017.
//  Copyright © 2017 Paul-Henri Zimmerlin. All rights reserved.
//
//

#include <stdio.h>
#include <stdlib.h>
#define FLAG_HORIZONTAL 1
#define FLAG_VERTICAL 0

char* creerTab1D(int taille);
void initTab1D(char* tab, int taille);
void affichageTab1D(char* tab, int taille);
char** creerTab2D(int taillex, int tailley);
void init2D(char **x, int taillex, int tailley);
void AffichageTab2D(char **tab, int ligne, int colonne, int i, int j);
void insererCharDansTab2D(char ***tab, int *taillex, int *tailley, int posx, int posy, char c);
void insererMotDansTab2D(char ***tab, int *taillex, int *tailley, int posx, int posy, int horizontal, char *mot);
char accesTad2D(char **tab, int taillex, int tailley, int posx, int posy);



// Alloue dynamiquement un tableau 1D de taille donnée et l'initialise
char* creerTab1D(int taille){
    char* tab = malloc(taille * sizeof(char));
    initTab1D(tab, taille);
    return tab;
}

// Initialise un tableau 1D avec des "*"
void initTab1D(char* tab, int taille){
    if(taille > 0){
        *tab = '*';
        initTab1D(tab + 1, taille - 1);
    }
}

// Affiche un tableau 1D de taille donnée
void affichageTab1D(char* tab, int taille){
    if(*tab){
        printf("%c ", *tab);
        affichageTab1D(++tab, taille);
    }
}

// Créé un tableau 2D de taille donnée et l'initialise
char** creerTab2D(int taillex, int tailley){
    char** x = malloc(taillex * sizeof(char*));
    init2D(x, taillex, tailley);
    return x;
}

// Initialise chaque dimension d'un tableau 2D avec des "*"
void init2D(char **x, int taillex, int tailley){
    if(taillex > 0){
        *x = creerTab1D(tailley);
        init2D(x + 1, taillex - 1,tailley);
    }
    
}

// Affiche un tableau 2D
void AffichageTab2D(char **tab, int ligne, int colonne, int i, int j){
    if((i<ligne) && (j<colonne)){
        printf("%c", *(*(tab +i) + j));
        AffichageTab2D(tab, ligne, colonne, i, j+1);
    }
    else if(i < ligne){
        printf("\n");
        AffichageTab2D(tab, ligne, colonne, i+1, 0);
    }
}


// Insère un caractère dans le tableau, et agrandi le tableau au besoin
void insererCharDansTab2D(char ***tab, int *taillex, int *tailley, int posx, int posy, char c){
    if(posx >= 0 && posy >= 0){ // On vérifie que la position est bien positive
        
        if (posx + 1 > *taillex) { // On traite le cas où il faut rajouter des lignes
            *tab = realloc(*tab, (posx + 1) * sizeof(char **)); // On rajoute les cases manquantes
            
            for(int i = *taillex; i < posx + 1; i++){ // On alloue et on initialise la dimension
                (*tab)[i] = creerTab1D(*tailley);
            }
            
            *taillex = posx + 1; // On change la définition de la taille du tableau
        }
        if (posy + 1 > *tailley){ // On traite le cas où il faut rajouter des colonnes
            for(int ligne = 0; ligne < *taillex; ligne++){ // On parcours les lignes
                (*tab)[ligne] = realloc((*tab)[ligne], (posy + 1) * sizeof(char *)); // On rajoute les cases manquantes sur chaque ligne
                for(int colonne = *tailley; colonne < (posy + 1); colonne++){ // On initialise les cases nouvellement créées
                    (*tab)[ligne][colonne] = '*';
                }
            }
            *tailley = posy + 1; // On change la définition de la taille du tableau
        }
        
        (*tab)[posx][posy] = c; // On insère le caractère
    }
    else if(DEBUG) printf("\nLa position n'est pas correcte (inférieure à 0)\n"); // On prévient qu'on ne traitera pas le cas où la cible est au dessus, ou à gauche du tableau
}

// Insère un mot dans le tableau 2D
void insererMotDansTab2D(char ***tab, int *taillex, int *tailley, int posx, int posy, int horizontal, char *mot){
    while(*mot){ // Tant qu'on ne rencontre pas le caractère nul
        insererCharDansTab2D(tab, taillex, tailley, posx, posy, *mot); // On réutilise la sous-fonction pour le caractère courant
        mot++;
        if (horizontal) posy++; // On fait un saut de ligne
        else posx++; // On passe à la colonne suivante
        
    }
}

// Permet de récupèrer le contenu d'une case du tableau, et gère le cas où elle est en dehors du tableau
char accesTad2D(char **tab, int taillex, int tailley, int posx, int posy){
    if(posx < (taillex - 1) && posy < (tailley - 1)) return *(*(tab + posx) + posy); // On retourne le contenu de la case
    else return '*'; // Pour éviter un segmentation fault, on retourne le caractère '*' qui représente la valeur par défaut
}



int main(int argc, const char * argv[]) {
    int taillex = 5;
    int tailley = 5;
    
    char** tab_test = creerTab2D(taillex, tailley);
    char* mot_a_inserer = "coucou";
    insererMotDansTab2D(&tab_test, &taillex, &tailley, 2, 2, FLAG_HORIZONTAL, mot_a_inserer);
    
    AffichageTab2D(tab_test, taillex, tailley, 0, 0);

    return 0;
    
}
