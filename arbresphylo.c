#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "arbres.h"
#include "arbresphylo.h"
#include "listes.h"

#define TAILLE_MAX 10000

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
   // gerer le cas arbre nul
   if ((*a) == NULL)
   {
      (*a) = nouveau_noeud();
   }

   // cree/ecris affichage_arbre.dot
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

   // cas noeud null (atteint apres l'ajout d'un carac)
   if (n == NULL)
   {
      n = nouveau_noeud();
      return ajouter_espece_rec(n, espece, cell);
   }
   // cas n->valeur null et pas de carac diff (atteint lors de l'ajout de nouveaux caracs)
   if (n->valeur == NULL && cell == NULL)
   {
      n->valeur = espece;
      return 0;
   }
   // cas n->valeur null et carac diff (atteint lors de l'ajout de nouveaux carac)
   if (n->valeur == NULL && cell != NULL)
   {
      n->valeur = cell->val;
      n->droit = nouveau_noeud();
      return ajouter_espece_rec(n->droit, espece, cell->suivant);
   }

   resultat_recherche = (n->gauche != NULL) || (n->droit != NULL); // espece -> 1  carac -> 0
   // cas espece sans carac diff
   if (resultat_recherche == 0 && cell == NULL)
   {
      printf("Ne peut ajouter %s: possède les mêmes caractères que %s\n", espece, n->valeur);
      return 1;
   }
   // cas espece avec carac diff
   if (resultat_recherche == 0 && cell != NULL)
   {
      // on remplace n->valeur (une espece) par le caractère
      // on ajoute ensuite l'espece retiree dans la branche gauche
      // on appelle alors ajouter_espece_rec sur les caracs restants et le noeud cree
      buffer = n->valeur;
      n->valeur = cell->val;
      n->droit = nouveau_noeud();
      n->gauche = nouveau_noeud();
      n->gauche->valeur = buffer;
      return ajouter_espece_rec(n->droit, espece, cell->suivant);
   }
   // cas carac sans carac diff
   // on renvoie l'appel sur la gauche
   if (resultat_recherche == 1 && cell == NULL)
   {
      return ajouter_espece_rec(n->gauche, espece, cell);
   }
   // cas carac avec carac diff
   // on regarde si carac est le premier carac diff
   // si oui on renvoie l'appel avec le carac diff suivant et le noeud droit
   // sinon on renvoie l'appel avec le meme carac diff et le noeud gauche
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
   // en cas d'erreur (non atteint)
   assert(0);
}

/* Doit afficher la liste des caractéristiques niveau par niveau, de gauche
 * à droite, dans le fichier fout.
 * Appeler la fonction avec fout=stdin pour afficher sur la sortie standard.
 */
void afficher_par_niveau (arbre racine, FILE* fout)
{
   int i, j;
   noeud **visiter = NULL;
   noeud **buffer = NULL;

   visiter = malloc(sizeof(arbre) * TAILLE_MAX);
   buffer = malloc(sizeof(arbre) * TAILLE_MAX);
   
   if (racine == NULL)
   {
      return;
   }

   // initialisation des tableaux de noeud a visiter
   for (i = 0; i < TAILLE_MAX; i++)
   {
      visiter[i] = NULL;
      buffer[i] = NULL;
   }

   visiter[0] = racine;
   fprintf(fout, "%s\n", visiter[0]->valeur);
   while (visiter[0] != NULL)
   {
      j = 0;
      for (i = 0; (i < TAILLE_MAX) && (visiter[i] != NULL); i++)
      {
         // element gauche ?
         if (visiter[i]->gauche != NULL) 
         {
            // element gauche espece ?
            if ((visiter[i]->gauche->droit != NULL) || (visiter[i]->gauche->gauche != NULL))
            {
               buffer[j] = visiter[i]->gauche;
               j++;
            }
         }
         // element droit ?
         if (visiter[i]->droit != NULL)
         {
            // element droit espece ?
            if ((visiter[i]->droit->droit != NULL) || (visiter[i]->droit->gauche != NULL))
            {
               buffer[j] = visiter[i]->droit;
               j++;
            }
         }
      }

      // ecriture dans fout
      for (j = 0; (j < TAILLE_MAX) && (buffer[j] != NULL); j++)
      {
         fprintf(fout, "%s ", buffer[j]->valeur);  
      }
      fprintf(fout, "\n");

      // on passe les elements du buffer dans visiter et on vide buffer
      for (j = 0; j < TAILLE_MAX; j++)
      {
         visiter[j] = buffer[j];
         buffer[j] = NULL;
      }
   }

   free(buffer);
   free(visiter);

   return;
}

// Acte 4

// Non faite le 21/12
int ajouter_carac(arbre* a, char* carac, cellule_t* seq)
{
   printf ("<<<<< À faire: fonction ajouter_carac fichier " __FILE__ "\n >>>>>");
   return 0;
}
