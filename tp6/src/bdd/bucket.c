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

struct bucket {
  FILE* file;
  size_t c;
};

struct bucket* bucket_create(const char* filename, int mode) {
  struct bucket* bucket= (struct bucket*) malloc(sizeof(struct bucket));
  bucket->file= fopen(filename , "w+");
  if(bucket->file == NULL) {
    free(bucket);
    return NULL;
  }
  bucket->c= 0;
  return bucket;
}

void bucket_puts( struct bucket* bucket, const char* str) {
  printf("%s", str);
}


FILE* bucket_getFile(struct bucket* bucket) {
  return bucket->file;
}
