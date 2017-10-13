/**
* TP n°: 2
*
* Titre du TP : Merge Join
*
* Date : 13/10/17
*
* Nom : Lefranc
* Prenom : Joaquim
* email : lefrancjoaquim@gmail.com
*
* Nom : Skoda
* Prenom : Jérôme
* email : contact@jeromeskoda.fr
*
* Remarques :
*
* History: 146488d PASS (avec struct)
*          7d1b9de PASS (sans struct)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bdd.h"

/**
 * @brief Structure de donnée repésentant un buffer
 */
struct buf {
  char* v;  //< Valeur
  size_t s; //< Taille
  size_t c; //< Nombre de valeur entrée
};

/**
 * Creation d'un buffer
 * @param[in] size Taille du buffer
 */
struct buf* buf_create( size_t size ) {
  struct buf* buf= (struct buf*) malloc(sizeof(struct buf));
  buf->v= (char*) malloc(size);
  buf->s= size;
  buf->c=0;
  return buf;
}

/**
 * Détruit le buffer
 * @param[in] buf buffer à détruire
 */
void buf_destroy(struct buf* buf) {
  free(buf->v);
  free(buf);
}

/**
 * Ajoute un caractere dans le buffer s'il reste de la place
 * @param[in] buf   buffer d'entrée
 * @param[in] value valeur à entrer
 * @return    0   succès
 *            -1  erreur: buffer plein
 */
char buf_put(struct buf* buf, char value) {
  if(buf->c >= buf->s)
    return -1;

  buf->v[buf->c]= value;
  buf->c++;

  return 0;
}

/**
 * @brief Enregistre un le 1er caractére de chaque
 *        ligne d'un fichier dans un buffer
 *
 * @param[in]  Fichier d'entrée
 * @param[out] Buffer de sortie
 */
void storeFileBuffer(FILE* fp, struct buf* buf) {
  char* line = NULL;
  size_t len = 0;

  while((getline(&line, &len, fp)) != -1) {
    buf_put(buf, line[0]);
  }
}

/**
 * Ecrit un buffer dans un fichier
 *
 * @param[out] fp  fichier de sortie
 * @param[in]  buf fichier d'entrée
 */
void writeBufferInFile(FILE* fp, struct buf* buf) {
  for(int i=0; i<buf->c; i++)
    fprintf(fp, "%c\n", buf->v[i]);
}

/**
 * Natual join
 *
 * @param[in]  buf_a   relation externe
 * @param[in]  buf_b   relation interne
 * @param[out] buf_out resultat du natural join de buf_a et buf_b
 */
void natural_join(struct buf* buf_a, struct buf* buf_b, struct buf* buf_out) {
  for(int a=0; a< buf_a->c; a++) {
    for(int b=0; b< buf_b->c; b++) {
      if(buf_a->v[a] == buf_b->v[b]) {
        buf_put(buf_out, buf_a->v[a]);
        break; // pass to next a
      }
    }
  }
}

/**
 * @brief Merge join
 *
 * @param[in]  buf_a   relation externe
 * @param[in]  buf_b   relation interne
 * @param[out] buf_out resultat du merge_join
 */
void merge_join(struct buf* buf_a, struct buf* buf_b, struct buf* buf_out) {
  char* buf_a_ptr= buf_a->v;
  char* buf_b_ptr= buf_b->v;

  // calculate pointer limit
  const char* buf_a_ptr_limit= buf_a->v + buf_a->c;
  const char* buf_b_ptr_limit= buf_b->v + buf_b->c;

  while( buf_a_ptr < buf_a_ptr_limit && buf_b_ptr_limit)
  {
    if(*buf_a_ptr == *buf_b_ptr) {
      buf_put(buf_out, *buf_a_ptr);
      buf_a_ptr++;
    } else if (*buf_a_ptr < *buf_b_ptr) {
      buf_a_ptr++;
    } else {
      buf_b_ptr++;
    }
  }
}

/**
 * Quick sort buffer
 */
void buf_quicksort(struct buf* buf) {
  quicksort(buf->v, 0, (buf->c) -1);
}
