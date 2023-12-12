#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "listes.h"

/* fichier à compléter au besoin */

void init_liste_vide(liste_t* L)
{
    L->tete = NULL;
    return;
}

void liberer_liste(liste_t* L)
{
    init_liste_vide(L);
    return;
}

int ajouter_tete(liste_t* L, string c)
{ /* retourne 0 si OK, 1 sinon  */
    cellule_t *cell = malloc(sizeof(cellule_t));
    cell->val = c;
    cell->suivant = L->tete;
    L->tete = cell;
    return 0;
}