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
#include "diskWriter.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <ftw.h>
#include <unistd.h>
#include "rmrf.h"

struct diskWriter {
  char* dir;
  char* prefix;
  char* extension;
  int file_number;
  char* current_path;
  FILE* current_file;
  int current_line;
};

struct diskWriter* disk_w_create(const char* dir, const char* prefix,
  const char* extension)
{
  struct diskWriter* dw= (struct diskWriter*) malloc(sizeof(struct diskWriter));
  dw->dir= strdup(dir);
  dw->prefix= strdup(prefix);
  dw->extension= strdup(extension);
  dw->file_number= 0;
  dw->current_file= NULL;
  dw->current_path= (char*) malloc( PATH_MAX * sizeof(char) );

  rmrf(dir);
  mkdir(dir, 0777);

  return dw;
}

FILE* disk_w_get_current_f( struct diskWriter* dw) {
  return dw->current_file;
}

char* disk_w_get_current_path( struct diskWriter* dw) {
  return dw->current_path;
}

void disk_w_new_f( struct diskWriter* dw) {

  if(dw->file_number > 0) {
    fflush(dw->current_file);
    fclose(dw->current_file);
  }

  sprintf(dw->current_path, "%s/%s%03d%s", dw->dir, dw->prefix, dw->file_number, dw->extension);
  dw->current_file= fopen(dw->current_path, "w+");
  dw->file_number++;
}

int disk_w_count(struct diskWriter* dw) {
  return dw->file_number;
}

void disk_w_destroy( struct diskWriter* dw ) {
  fflush(dw->current_file);
  fclose(dw->current_file);
  free(dw->current_path);
  free(dw->dir);
  free(dw->prefix);
  free(dw->extension);
  free(dw);
}

void disk_w_copy(struct diskReader* dr, struct diskWriter* dw, struct buffer* buf)
{
  for(int r=0; r<disk_r_count(dr); r++) {
    buffer_read_file_from_descriptor( disk_r_item(dr, r),  buf);
    disk_w_new_f(dw);
    buffer_write_file_from_descriptor( disk_w_get_current_f(dw), buf);
    fflush(dw->current_file);
  }
}
