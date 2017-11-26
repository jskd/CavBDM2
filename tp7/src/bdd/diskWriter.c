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

  rmrf(dir);
  mkdir(dir, 0777);

  char filename[PATH_MAX];
  sprintf(filename, "%s/%s%d%s", dw->dir, dw->prefix, dw->file_number, dw->extension);
  dw->current_file= fopen(filename, "w+");
  dw->file_number++;

  return dw;
}

FILE* disk_w_get_current_f( struct diskWriter* dw) {
  return dw->current_file;
}

FILE* disk_w_next_f( struct diskWriter* dw) {

  fclose(dw->current_file);

  char filename[PATH_MAX];
  sprintf(filename, "%s/%s%d%s", dw->dir, dw->prefix, dw->file_number, dw->extension);
  dw->current_file= fopen(filename, "w+");
  dw->file_number++;

  return dw->current_file;
}

void disk_w_puts( struct diskWriter* dw, const char* str) {
  if(dw->current_line == 10) {
    disk_w_next_f(dw);
    dw->current_line=0;
  }
  fprintf( dw->current_file, "%s\n", str);
  dw->current_line++;
}

void disk_w_destroy( struct diskWriter* dw ) {
  free(dw->dir);
  free(dw->prefix);
  free(dw->extension);
  free(dw);
}
