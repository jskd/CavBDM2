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

#include "diskOutput.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

struct disk_output {
  char* dir;
  char* prefix;
  char* extension;
  int file_number;
  FILE* current_file;
};

struct disk_output* disk_output_create(const char* dir, const char* prefix,
  const char* extension, int offset)
{
  struct disk_output* disk_o= (struct disk_output*) malloc(sizeof(struct disk_output));
  disk_o->dir= strdup(dir);
  disk_o->prefix= strdup(prefix);
  disk_o->extension= strdup(extension);
  disk_o->file_number= offset;
  mkdir(dir, 0777);


  char filename[PATH_MAX];
  sprintf(filename, "%s/%s%d%s", disk_o->dir, disk_o->prefix, disk_o->file_number, disk_o->extension);
  disk_o->current_file= fopen(filename, "w+");
  return disk_o;
}

FILE* disk_output_get_current_file_descriptor( struct disk_output* disk_o) {
  return disk_o->current_file;
}

FILE* disk_output_next_file( struct disk_output* disk_o) {

  fclose(disk_o->current_file);

  disk_o->file_number++;
  char filename[PATH_MAX];
  sprintf(filename, "%s/%s%d%s", disk_o->dir, disk_o->prefix, disk_o->file_number, disk_o->extension);
  disk_o->current_file= fopen(filename, "w+");

  return disk_o->current_file;
}


void disk_output_destroy( struct disk_output* disk_o ) {
  free(disk_o->dir);
  free(disk_o->prefix);
  free(disk_o->extension);
  free(disk_o);
}
