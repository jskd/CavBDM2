/**
* TP n°: 5
*
* Titre du TP : Nested loop join disk
*
* Date : 10 Nov 2017
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
// Pour getline (standard GNU)
#define _GNU_SOURCE

#include "bufferExtended.h"
#include "hexdump.h"
#include "quicksort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * @brief Structure de donnée repésentant un buffer
 */
struct buffer {
  /// Valeur
  char* v;
  /// Taille
  size_t s;
  /// Nombre de valeur entrée
  size_t c;
  /// Taille des données
  size_t data_size;
  // mode des sortie fichier
  buffer_file_mode mode;
  /// compteur de Lecture (en octet)
  int read_counter;
  /// compteur d'écriture (en octet)
  int write_counter;
};

// See Header
struct buffer* buffer_create( size_t size , size_t num, buffer_file_mode mode ){
  struct buffer* buf= (struct buffer*) malloc(sizeof(struct buffer));
  buf->v= (char*) malloc( size * num );
  buf->s= size;
  buf->data_size= num;
  buf->c=0;
  buf->mode = mode;
  buf->read_counter = 0;
  buf->write_counter = 0;
  return buf;
}

/**
 * Détruit le buffer
 * @param[in] buf buffer à détruire
 */
void buffer_destroy(struct buffer* buf) {
  free(buf->v);
  free(buf);
}


static char * _buffer_val_offset( const struct buffer* buf, int index) {
  return buf->v+index*buf->data_size;
}

static void _printValue(FILE* stream, struct buffer* buf, int index) {
  if(buf->mode == BUFFER_CHARACTERS) {
    fprintf(stream, "%.*s\n", (int) buf->data_size, _buffer_val_offset(buf, index));
  } else if(buf->mode == BUFFER_DECIMALS) {
    long long value=0;
    buffer_get(buf, index, &value);
    switch(buf->data_size) {
      case 1:
        fprintf(stream, "%d\n",  (char) value);
        break;
      case 2:
        fprintf(stream, "%d\n",  (short) value);
        break;
      case 4:
        fprintf(stream, "%d\n",  (int) value);
        break;
      default:
        printf("Print value decimimal lenght %ld not implemented\n", buf->data_size);
        return;
        break;
    }
  }
}

/**
 * Ajoute un caractere dans le buffer s'il reste de la place
 * @param[out] buf_dst  buffer de destination
 * @param[in] buf_src  buffer source
 * @param[in] src_index  index du buffer source à copier
 * @return    0   succès
 *            -1  erreur: buffer incompatible
 *            -2  erreur: buffer plein
 */
char buffer_put_cpy(struct buffer* buf_dst, const struct buffer* buf_src, int src_index) {
  if(buf_dst->data_size != buf_src->data_size)
    return -1;

  return buffer_put(buf_dst, _buffer_val_offset(buf_src, src_index));
}

char buffer_put(struct buffer* buf, const void * data) {
  if(buf->c >= buf->s)
    return -1;

  memcpy ( _buffer_val_offset(buf, buf->c), data, buf->data_size );
  buf->c++;

  return 0;
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
struct buffer* buffer_read_file(const char* file_name, size_t buffer_size, size_t data_lenght, buffer_file_mode mode) {
  FILE* file = fopen(file_name, "r");
  if (file == NULL)
    return NULL;

  struct buffer* buf= buffer_create( buffer_size, data_lenght, mode );

  buffer_read_file_from_descriptor(file, buf);

  fclose(file);

  return buf;
}



void buffer_flush(struct buffer* buf) {
  buf->c= 0;
}


void buffer_read_file_from_descriptor(FILE* file, struct buffer* buf)
{
  buffer_flush(buf);
  rewind(file);

  char* line = NULL;
  size_t len = 0;

  while((getline(&line, &len, file)) != -1) {
    if(buf->mode == BUFFER_CHARACTERS) {
      buffer_put(buf, line);
    }
    else if(buf->mode == BUFFER_DECIMALS) {
      int value= atoi(line);
      buffer_put(buf, &value);
    }
    buf->read_counter++;
  }
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
char buffer_write_file(const char* file_name, struct buffer* buf) {

  FILE* file = fopen( file_name, "w");
  if (file == NULL)
    return -1;

  buffer_write_file_from_descriptor(file, buf);

  fclose(file);
  return 0;
}



void buffer_write_file_from_descriptor(FILE* file, struct buffer* buf) {
  for(int index=0; index<buf->c; index++) {
    _printValue(file, buf, index);
    if(file != stderr && file != stdout)
      buf->write_counter++;
  }
}

/**
 * @brief Quick sort buffer
 * @param[in] buf buffer à trier
 */
void buffer_quicksort(struct buffer* buf) {
  quicksort(buf->v, 0, (buf->c) -1);
}

/**
 * @brief Hex dump buffer
 * @param[in] buf buffer à trier
 */
void buffer_dump(const struct buffer* buf) {
  printf ("buffer count: %zu\n", buf->c);
  printf ("buffer size: %zu\n", buf->s);
  hexDump("buffer value:", buf->v, buf->c * buf->data_size);
}

/**
 * @brief Retourne le nombre de caractere enregistré dans le buffer
 *
 * @param[in]  buf       Buffer
 *
 * @return Nombre de caractere enregistré
 */
size_t buffer_count(const struct buffer* buf)
{
  return buf->c;
}

size_t buffer_size(const struct buffer* buf)
{
  return buf->s;
}
int buffer_cmp(const struct buffer* buf_a, int index_a, const struct buffer* buf_b, int index_b) {
  return memcmp( _buffer_val_offset(buf_a, index_a),
     _buffer_val_offset(buf_b, index_b), buf_a->data_size);
}

char buffer_isFull(const struct buffer* buf) {
  return buf->s == buf->c;
}

char buffer_isEmpty(const struct buffer* buf) {
  return buf->c == 0;
}

void buffer_get(const struct buffer* buf, int index, void* destination) {
  memcpy ( destination,  _buffer_val_offset(buf, index), buf->data_size );
}

/**
 * Affiche les valeurs
 */
void buffer_printValue(struct buffer* buf) {
  for(int index=0; index< buf->c; index++) {
    _printValue(stdout, buf, index);
  }
}

/**
 * Retourne le mode de fonctionnement du buffer
 */
int buffer_mode(const struct buffer* buf) {
  return buf->mode;
}

/**
 * Retourne la taille en octet de chaque données
 */
size_t buffer_datasize(const struct buffer* buf) {
  return buf->data_size;
}


int buffer_get_read_stat(const struct buffer* buf) {
  return  buf->read_counter;
}

int buffer_get_write_stat(const struct buffer* buf) {
  return  buf->write_counter;
}


void buffer_fprint_stat(FILE* stream, const struct buffer* buf) {
  fprintf(stream, "- Read in file: %d lines\n", buf->read_counter);
  fprintf(stream, "- Write in file: %d lines\n", buf->write_counter);
}
