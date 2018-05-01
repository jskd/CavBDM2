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
#include "bufferExtended.h"
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
  /// bench
  int write_counter;
};

static int _table_hash(const struct table* tab, short key) {
  return key % tab->n_bucket;
}

struct table* table_create(size_t n_bucket, const char* directory) {
  struct table* tab= (struct table*) malloc(sizeof(struct table));
  tab->b= (struct bucket**) malloc(n_bucket * sizeof(struct bucket*) );
  mkdir(directory, 0777);
  for(int indexBucket=0; indexBucket<n_bucket; indexBucket++) {
    char bucketdir[PATH_MAX];
    sprintf(bucketdir, "%s/%d", directory, indexBucket);
    tab->b[indexBucket]= bucket_create(bucketdir);
  }
  tab->write_counter= 0;
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
      buffer_get(buf, index_buf, &key);
      sprintf(str, "%d", key);
      bucket_puts( tab->b[ _table_hash(tab, key) ], str);
      tab->write_counter++;
    }
  }
  else
  {
    printf("Erreur, table put non implementé pour ce type de buffer\n");
  }
}

struct disk* create_disk_from_bucket(const struct table* tab, int indexBucket) {
  return bucket_create_disk(tab->b[indexBucket]);
}

size_t table_get_n_bucket(const struct table* tab) {
  return tab->n_bucket;
}

void table_destroy(struct table* tab) {
  for(int indexBucket=0; indexBucket<tab->n_bucket; indexBucket++)
    bucket_destroy(tab->b[indexBucket]);
  free(tab);
}

int table_get_write_stat(const struct table* tab) {
  return  tab->write_counter;
}

int table_get_wfile_stat(const struct table* tab) {
  int n_file=0;
  for(int indexBucket=0; indexBucket<tab->n_bucket; indexBucket++)
    n_file+= bucket_get_n_file(tab->b[indexBucket]);
  return n_file;
}
void table_fprint_stat(FILE* stream, const struct table* tab) {
  fprintf(stream, "- Write in bucket: %d lines to %d files\n", tab->write_counter,
     table_get_wfile_stat(tab));
}
