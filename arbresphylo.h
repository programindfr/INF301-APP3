#ifndef ARBRESPHYLO_H
#define ARBRESPHYLO_H

#include "listes.h"


/* Analyse un arbre: doit mettre à jour le nombre d'espèces et de 
 * caractéristiques.
 */
void analyse_arbre (arbre racine, int* nb_esp, int* nb_carac);

/* Implementation récursive de analyse arbre */
void analyse_arbre_rec(arbre racine, int *nb_esp, int *nb_carac);

/* Recherche une espèce dans l'arbre et remplit seq avec la séquence de ses 
 * caractéristiques.
 *
 * Doit retourner 0 si l'espèce a été retrouvée, 1 sinon.
 */
int rechercher_espece (arbre racine, char *espece, liste_t* seq);

/*
   Fontion recherche récursive utilisée par rechercher espece
   Retourne 0 si espece trouvée et 1 sinon
*/
int rechercher_espece_rec(noeud *n, char *espece, liste_t *seq);

/* Doit renvoyer 0 si l'espece a bien ete ajoutee, 1 sinon, et ecrire un
 * message d'erreur.
 */
int ajouter_espece (arbre* racine, char *espece, cellule_t* cell);

/* Fonction récursive utilisée par ajouter_espece */
int ajouter_espece_rec(noeud *n, char *espece, cellule_t *cell);

void afficher_par_niveau(arbre racine, FILE* fout);

// on considère qu'il n'est pas possible
// d'insérer une caractéristique à un arbre vide, ni d'insérer une caractéristique
// qui n'est possédée par aucune espèce déjà présente dans l'arbre (pour ce
// cas-là, ajout_espece fait l'affaire). Ceci permet d'éviter d'avoir à ajouter
// des noeuds caractéristique sans enfant qui seraient confondues avec des
// espèces/feuilles.
int ajouter_carac(arbre* a, char* carac, cellule_t* seq);


#endif
