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
/* Recherche l'espece dans l'arbre. Modifie la liste passée en paramètre pour y mettre les
 * caractéristiques. Retourne 0 si l'espèce a été retrouvée, 1 sinon.
 */
int rechercher_espece (arbre racine, char *espece, liste_t* seq)
{
   init_liste_vide(seq);
   cellule_t *current = NULL;

   if (!rechercher_espece_rec(racine, espece, seq))
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

int rechercher_espece_rec(noeud *n, char *espece, liste_t *seq)
{
   if (!n)
   {
      return 0;
   }
   if (!(strcmp(espece, n->valeur)))
   {
      return 1;
   }
   if (rechercher_espece_rec (n->droit, espece, seq))
   {
      if (seq->tete->val)
      {
         ajouter_tete(seq, n->valeur);
         return 1;
      }
      seq->tete->val = n->valeur;
      return 1;
   }
   if (rechercher_espece_rec(n->gauche, espece, seq))
   {
      return 1;
   }
   return 0;
}

/* Doit renvoyer 0 si l'espece a bien ete ajoutee, 1 sinon, et ecrire un 
 * message d'erreur.
 */
int ajouter_espece (arbre* a, char *espece, cellule_t* cell)
{
   affiche_arbre(*a);
   return 1;
}

int ajouter_espece_rec(noeud *n, char *espece, cellule_t *cell)
{
   if (!n)
   {
      return 0;
   }
   
   return 0;
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
