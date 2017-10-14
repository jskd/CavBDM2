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
* History: 8871b16 [PASS]
*          5b1768f [PASS]
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bdd.h"
#include "hexdump.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
 * @brief Ouvre un fichier
 *        Stoque son contenu dans un buffer
 *        Ferme le fichier
 *
 * @param[in]  File_name Fichier
 * @param[in] buffer_size Taille du buffer,
 *             si trop petit pour contenir le fichier entirerement
 *             alors le reste du fichier est ignoré
 *
 * @return buffer si NULL alors erreur de lecture du fichier
 *
 */
struct buf* storeFileBufferOC(const char* file_name, size_t buffer_size) {
  FILE* file = fopen(file_name, "r");
  if (file == NULL)
    return NULL;

  struct buf* buf= buf_create( buffer_size );
  storeFileBuffer(file, buf);
  fclose(file);

  return buf;
}

/**
 * Ecrit un buffer dans un fichier
 *
 * @param[out] fp  fichier de sortie
 * @param[in]  buf fichier d'entrée
 */
void writeBufferInFile(FILE* fp, const struct buf* buf) {
  for(int i=0; i<buf->c; i++)
    fprintf(fp, "%c\n", buf->v[i]);
}

/**
 * @brief Ouvre un fichier
 *        Ecrit le contenu du buffer dans le fichier
 *        Ferme le fichier
 *
 * @param[in]  File_name Fichier
 * @param[in]  buf       Buffer à écrire dans le fichier
 *
 * @return -1 si erreur dans l'ouverture du fichier
 *
 */
char writeBufferInFileOC(const char* file_name, const struct buf* buf) {

  FILE* file = fopen( file_name, "w");
  if (file == NULL)
    return -1;

  writeBufferInFile(file, buf);
  fclose(file);
  return 0;
}

/**
 * Natual join
 *
 * @param[in]  buf_a   relation externe
 * @param[in]  buf_b   relation interne
 * @param[out] buf_out resultat du natural join de buf_a et buf_b
 */
void natural_join(const struct buf* buf_a, const struct buf* buf_b, struct buf* buf_out) {
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
 * @param[in]  buf_a   relation a
 * @param[in]  buf_b   relation b
 * @param[out] buf_out resultat du merge_join
 */
void merge_join(const struct buf* buf_a, const struct buf* buf_b, struct buf* buf_out) {
  char* buf_a_ptr= buf_a->v; // pointer vers le buffer a
  char* buf_b_ptr= buf_b->v; // pointer vers le buffer b

  // Calcule la dernier case memoire du buffer + 1
  const char* buf_a_ptr_limit= buf_a->v + buf_a->c;
  const char* buf_b_ptr_limit= buf_b->v + buf_b->c;

  while( buf_a_ptr < buf_a_ptr_limit && buf_b_ptr < buf_b_ptr_limit)
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
 * @brief Quick sort buffer
 * @param[in] buf buffer à trier
 */
void buf_quicksort(struct buf* buf) {
  quicksort(buf->v, 0, (buf->c) -1);
}

/**
 * @brief Hex dump buffer
 * @param[in] buf buffer à trier
 */
void buf_dump(const struct buf* buf) {
  printf ("buffer count: %d\n", buf->c);
  printf ("buffer size: %d\n", buf->s);
  hexDump("buffer value:", buf->v, (buf->s) -1);
}
