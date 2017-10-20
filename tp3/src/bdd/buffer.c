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
*/
#include "buffer.h"
#include "hexdump.h"
#include "quicksort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Structure de donnée repésentant un buffer
 */
struct buf {
  /// Value: Valeur
  char* v;
  /// Size: Taille
  size_t s;
  /// Count: Nombre de valeur entrée
  size_t c;
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
  printf ("buffer count: %zu\n", buf->c);
  printf ("buffer size: %zu\n", buf->s);
  hexDump("buffer value:", buf->v, buf->c);
}

/**
 * @brief Retourne la valeur à la position d'un buffer
 *
 * @param[in]  buf   Buffer
 * @param[in]  index Index of value
 *
 * @return Value
 *         Si -1: Erreur index > count
 */
char buf_val(const struct buf* buf, int index)
{
  if(index < buf->c)
    return buf->v[index];
  return -1;
}

/**
 * @brief Retourne le nombre de caractere enregistré dans le buffer
 *
 * @param[in]  buf       Buffer
 *
 * @return Nombre de caractere enregistré
 */
size_t buf_count(const struct buf* buf)
{
  return buf->c;
}
