#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "arbres.h"
#include "arbresphylo.h"
#include "listes.h"

void analyse_arbre_rec(arbre racine, int *nb_esp, int *nb_carac)
{
   if (!racine)
   {
      return;
   }
   if ((!(racine->droit) && !(racine->gauche)))
   {
      (*nb_esp)++;
   }
   else
   {
      (*nb_carac)++;
      analyse_arbre_rec(racine->droit, nb_esp, nb_carac);
      analyse_arbre_rec(racine->gauche, nb_esp, nb_carac);
   }
   return;
}

void analyse_arbre (arbre racine, int* nb_esp, int* nb_carac)
{
   *nb_esp = 0;
   *nb_carac = 0;
   analyse_arbre_rec(racine, nb_esp, nb_carac);
}

/* ACTE II */
/* 
   Recherche l'espece dans l'arbre. Modifie la liste passée en paramètre pour y mettre les
   caractéristiques.
   Retourne 0 si l'espèce a été retrouvée, 1 sinon.
 */
int rechercher_espece (arbre racine, char *espece, liste_t* seq)
{
   init_liste_vide(seq);
   cellule_t *current = NULL;

   if (rechercher_espece_rec(racine, espece, seq) == 1)
   {
      printf("L'espèce n'est pas référée dans l'arbre.\n");
      return 1;
   }
   
   // Affichage de la liste
   current = seq->tete;

   while (current)
   {
      printf("%s ", current->val);
      current = current->suivant;
   }
   printf("\n");
   return 0;
}

/* 
   Implémentation recherche récursive
   Retourne 0 si espece trouvée et 1 sinon
*/
int rechercher_espece_rec(noeud *n, char *espece, liste_t *seq)
{
   if (n == NULL)
   {
      return 1;
   }
   if ((strcmp(espece, n->valeur)) == 0)
   {
      return 0;
   }
   if (rechercher_espece_rec(n->droit, espece, seq) == 0)
   {
      if (seq->tete != NULL)
      {
         ajouter_tete(seq, n->valeur);
         return 0;
      }
      seq->tete = malloc(sizeof(cellule_t));
      seq->tete->suivant = NULL;
      seq->tete->val = NULL;
      seq->tete->val = n->valeur;
      return 0;
   }
   if (rechercher_espece_rec(n->gauche, espece, seq) == 0)
   {
      return 0;
   }
   return 1;
}

int ajouter_espece (arbre* a, char *espece, cellule_t* cell)
{
   if ((*a) == NULL)
   {
      (*a) = nouveau_noeud();
   }

   if (ajouter_espece_rec((*a), espece, cell) == 0)
   {
      affiche_arbre((*a));
      return 0;
   }
   affiche_arbre((*a));
   return 1;
}

int ajouter_espece_rec(noeud *n, char *espece, cellule_t *cell)
{
   int resultat_recherche;
   char *buffer = NULL;

   if (n == NULL)
   {
      n = nouveau_noeud();
      return ajouter_espece_rec(n, espece, cell);
   }
   if (n->valeur == NULL && cell == NULL)
   {
      n->valeur = espece;
      return 0;
   }
   if (n->valeur == NULL && cell != NULL)
   {
      n->valeur = cell->val;
      n->droit = nouveau_noeud();
      return ajouter_espece_rec(n->droit, espece, cell->suivant);
   }

   resultat_recherche = (n->gauche != NULL) || (n->droit != NULL);
   if (resultat_recherche == 0 && cell == NULL)
   {
      printf("Ne peut ajouter %s: possède les mêmes caractères que %s\n", espece, n->valeur);
      return 1;
   }
   if (resultat_recherche == 0 && cell != NULL)
   {
      buffer = n->valeur;
      n->valeur = cell->val;
      n->droit = nouveau_noeud();
      n->gauche = nouveau_noeud();
      n->gauche->valeur = buffer;
      return ajouter_espece_rec(n->droit, espece, cell->suivant);
   }
   if (resultat_recherche == 1 && cell == NULL)
   {
      return ajouter_espece_rec(n->gauche, espece, cell);
   }
   if (resultat_recherche == 1 && cell != NULL)
   {
      if (strcmp(n->valeur, cell->val) == 0)
      {
         return ajouter_espece_rec(n->droit, espece, cell->suivant);
      }
      else
      {
         return ajouter_espece_rec(n->gauche, espece, cell);
      }
   }
   assert(0);
}

/* Doit afficher la liste des caractéristiques niveau par niveau, de gauche
 * à droite, dans le fichier fout.
 * Appeler la fonction avec fout=stdin pour afficher sur la sortie standard.
 */
void afficher_par_niveau (arbre racine, FILE* fout) {
   printf ("<<<<< À faire: fonction afficher_par_niveau fichier " __FILE__ "\n >>>>>");
}

// Acte 4


int ajouter_carac(arbre* a, char* carac, cellule_t* seq) {
   printf ("<<<<< À faire: fonction ajouter_carac fichier " __FILE__ "\n >>>>>");
   return 0;
}
