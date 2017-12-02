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

// Pour DT_REG (standard GNU)
#define _GNU_SOURCE

#include "diskReader.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

struct diskReader {
  FILE** f;
  char** fp;
  size_t f_count;
};

static int _count_file_in_path(const char* path, struct dirent** direntList, int count) {
  int nb_file=0;
  for (int index = 0; index < count; index++) {
    char filename[NAME_MAX];
    struct stat st;
    snprintf(filename, sizeof(filename), "%s/%s", path, direntList[index]->d_name);
    stat(filename, &st);
    if(st.st_mode & S_IFREG)
      nb_file++;
  }
  return nb_file;
}

static void _alloc_file(FILE** dr, char** fp, const char* path, struct dirent** direntList, int count) {
  int nb_file=0;
  for (int index = 0; index < count; index++) {
    char filename[NAME_MAX];
    struct stat st;
    snprintf(filename, sizeof(filename), "%s/%s", path, direntList[index]->d_name);
    stat(filename, &st);
    if(st.st_mode & S_IFREG) {
      dr[nb_file]= fopen(filename, "r");
      fp[nb_file]= strdup(filename);
      nb_file++;
    }
  }
}

struct diskReader* disk_r_create( const char * path) {

  struct dirent** direntList;
  int direntCount= scandir(path, &direntList, NULL, alphasort);

  if(direntCount < 0) {
    return NULL;
  }

  struct diskReader* dr= (struct diskReader*) malloc(sizeof(struct diskReader));
  dr->f_count= _count_file_in_path(path, direntList, direntCount);

  if(dr->f_count == 0) {
    dr->f = NULL;
    return dr;
  }

  dr->f =  (FILE**) malloc(dr->f_count * sizeof(FILE*));
  dr->fp = (char**) malloc(dr->f_count * sizeof(char*));

  _alloc_file(dr->f, dr->fp, path, direntList, direntCount);

  for (int index = 0; index < direntCount; index++) {
    free(direntList[index]);
  }

  return dr;
}

size_t disk_r_count(const struct diskReader* disk) {
  return disk->f_count;
}

FILE* disk_r_item(const struct diskReader* disk, int index) {
  rewind(disk->f[index]);
  return disk->f[index];
}

char* disk_r_item_path(const struct diskReader* disk, int index) {
  return disk->fp[index];
}
void disk_r_destroy(struct diskReader* disk) {
  for(int i=0; i< disk_r_count(disk); i++) {
    fclose(disk_r_item(disk, i));
    free(disk->fp[i]);
  }

  free(disk->f);
  free(disk);
}

void disk_r_storeContentInTable(const struct diskReader* disk, struct buffer* buf, struct table* tab) {
  for(int index_disk=0; index_disk<disk_r_count(disk); index_disk++) {
    buffer_read_file_from_descriptor( disk_r_item(disk, index_disk),  buf);
    table_putBuffer(tab, buf);
  }
}

void disk_r_dump( FILE* f,  struct diskReader* dr) {
  char ch;

  for(int index=0; index< disk_r_count(dr); index++) {
    rewind(dr->f[index]);
    FILE* source= dr->f[index];

    while( ( ch = fgetc(source) ) != EOF )
      fputc(ch, f);
  }
}
