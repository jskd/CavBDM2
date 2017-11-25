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


struct diskReader {
  FILE** v;
  size_t s;
  size_t c;
};

static int _count_regular_file(DIR * dirp) {
  rewinddir(dirp); // si utilisé deux fois de suite
  int file_count = 0;
  struct dirent * entry;
  while ((entry = readdir(dirp)) != NULL) {
    if (entry->d_type == DT_REG) {
      file_count++;
    }
  }
  return file_count;
}

static char _store_file_descriptor(struct diskReader* disk, const char * dir, DIR * dirp) {
  struct dirent * entry;
  FILE** ptr= disk->v;
  char filename[PATH_MAX];
  rewinddir(dirp); // si utilisé deux fois de suite
  while ((entry = readdir(dirp)) != NULL) {
    if (entry->d_type == DT_REG) {
      if(disk->c == disk->s) // Overflow
        return -1;
      sprintf(filename, "%s/%s", dir, entry->d_name);
      *ptr= fopen(filename, "r");
      if(*ptr == NULL) // Open error
        return -2;
      ptr++;
      disk->c++;
    }
  }
  return 0;
}

struct diskReader* disk_r_create( const char * dir) {

  DIR* dirp = opendir(dir);
  if(dirp == NULL)
    return NULL;

  struct diskReader* disk= (struct diskReader*) malloc(sizeof(struct diskReader));

  disk->s=  _count_regular_file(dirp);
  disk->v= (FILE**) malloc( sizeof(FILE*) * disk->s );
  disk->c= 0;

  char error= _store_file_descriptor(disk, dir, dirp);
  closedir(dirp);

  if(error) {
    disk_r_destroy(disk);
    return NULL;
  }

  return disk;
}

size_t disk_r_count(const struct diskReader* disk) {
  return disk->c;
}

FILE* disk_r_item(const struct diskReader* disk, int index) {
  return disk->v[index];
}

void disk_r_destroy(struct diskReader* disk) {
  for(int i=0; i< disk_r_count(disk); i++)
    fclose(disk_r_item(disk, i));
  free(disk->v);
  free(disk);
}

void disk_r_storeContentInTable(const struct diskReader* disk, struct buffer* buf, struct table* tab) {
  for(int index_disk=0; index_disk<disk_r_count(disk); index_disk++) {
    buffer_read_file_from_descriptor( disk_r_item(disk, index_disk),  buf);
    table_putBuffer(tab, buf);
  }
}
