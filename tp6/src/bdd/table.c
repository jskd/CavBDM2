/**
 * TP n°: 6
 *
 * Titre du TP :
 *
 * Date : 21/10/17
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
#include "table.h"
#include "buffer.h"
#include "bucket.h"
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUCKET_FILE_EXTENSION ".txt"
/**
 * @brief Structure de donnée repésentant un buffer
 */
struct table {
  /// bucket
  struct bucket** b;
  /// n bucket
  size_t n_bucket;
};

static int _table_hash(const struct table* tab, short key) {
  return key % tab->n_bucket;
}

struct table* table_create(size_t n_bucket, const char* directory) {
  struct table* tab= (struct table*) malloc(sizeof(struct table));
  tab->b= (struct bucket**) malloc(n_bucket * sizeof(struct bucket*) );
  mkdir(directory, 0777);
  for(int indexBucket=0; indexBucket<n_bucket; indexBucket++) {
    char filename[PATH_MAX];
    sprintf(filename, "%s/%d.bucket.txt", directory, indexBucket);
    tab->b[indexBucket]= bucket_create(filename);
  }
  tab->n_bucket= n_bucket;
  return tab;
}

void table_putBuffer(struct table* tab, const struct buffer* buf) {
  if(buffer_mode(buf) == BUFFER_DECIMALS
    && buffer_datasize(buf) == sizeof(short))
  {
    for(int index_buf=0; index_buf< buffer_count(buf); index_buf++) {
      short key=0;
      char str[100];
      sprintf(str, "%d", key);
      bucket_puts( tab->b[ _table_hash(tab, key) ], str);
    }
  }
  else
  {
    printf("Erreur, table put non implementé pour ce type de buffer\n");
  }
}

void table_storeBucketInBuffer(struct table* tab, int index, struct buffer* buf)
{
  if(index > 0 && index < tab->n_bucket)
    buffer_read_file_from_descriptor(  bucket_getFile(tab->b[index]), buf);
}
