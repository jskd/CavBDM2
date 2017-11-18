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

#include "disk.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct disk {
  FILE** v;
  size_t s;
  size_t c;
  int n_lecture;
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

static char _store_file_descriptor(struct disk* disk, const char * dir, DIR * dirp, const char* mode) {
  struct dirent * entry;
  FILE** ptr= disk->v;
  char filename[PATH_MAX];
  rewinddir(dirp); // si utilisé deux fois de suite
  while ((entry = readdir(dirp)) != NULL) {
    if (entry->d_type == DT_REG) {
      if(disk->c == disk->s) // Overflow
        return -1;
      sprintf(filename, "%s/%s", dir, entry->d_name);
      *ptr= fopen(filename, mode);
      if(*ptr == NULL) // Open error
        return -2;
      ptr++;
      disk->c++;
    }
  }
  return 0;
}

struct disk* disk_create( const char * dir, const char* mode) {

  DIR* dirp = opendir(dir);
  if(dirp == NULL)
    return NULL;

  struct disk* disk= (struct disk*) malloc(sizeof(struct disk));

  disk->s=  _count_regular_file(dirp);
  disk->v= (FILE**) malloc( sizeof(FILE*) * disk->s );
  disk->c= 0;
  disk->n_lecture= 0;

  char error= _store_file_descriptor(disk, dir, dirp, mode);
  closedir(dirp);

  if(error) {
    disk_destroy(disk);
    return NULL;
  }

  return disk;
}

size_t disk_count(const struct disk* disk) {
  return disk->c;
}

FILE* disk_item(const struct disk* disk, int index) {
  return disk->v[index];
}

void disk_destroy(struct disk* disk) {
  for(int i=0; i< disk_count(disk); i++)
    fclose(disk_item(disk, i));
  free(disk->v);
  free(disk);
}

void disk_storeContentInTable(const struct disk* disk, struct buffer* buf, struct table* tab) {
  for(int index_disk=0; index_disk<disk_count(disk); index_disk++) {
    buffer_read_file_from_descriptor( disk_item(disk, index_disk),  buf);
    table_putBuffer(tab, buf);
  }
}
