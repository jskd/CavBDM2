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
#include <stdlib.h>
#include <stdio.h>
#include "diskOutput.h"
#include "diskReader.h"
#include <string.h>

struct bucket {
  size_t c;
  struct disk_output* disk_out;
  int current_line;
  int n_file;
  char* dir;
};

struct bucket* bucket_create(const char* dir, int indexBucket) {
  struct bucket* bucket= (struct bucket*) malloc(sizeof(struct bucket));
  bucket->dir= strdup(dir);
  bucket->disk_out= disk_output_create(dir, "", ".txt", 0);
  bucket->current_line= 0;
  bucket->n_file= 1;
  return bucket;
}

void bucket_puts( struct bucket* bucket, const char* str) {
  fprintf( disk_output_get_current_file_descriptor( bucket->disk_out ), "%s\n", str);
  bucket->current_line++;
  if(bucket->current_line == 10) {
    disk_output_next_file(bucket->disk_out);
    bucket->current_line=0;
    bucket->n_file++;
  }
}

struct diskReader* bucket_create_disk( struct bucket* bucket ) {
  fflush(disk_output_get_current_file_descriptor(bucket->disk_out));
  return disk_r_create(bucket->dir);
}

int bucket_get_n_file(struct bucket* bucket ) {
  return bucket->n_file;
}

void bucket_destroy(struct bucket* bucket ) {
  free(bucket);
}
