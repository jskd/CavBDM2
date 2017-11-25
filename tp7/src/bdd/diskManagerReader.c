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

#include "diskReader.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

struct diskManagerReader {
  struct diskReader** dr;
  size_t dr_count;
};

// Filtre pour les disk uniquement
int _disk_filter(const struct dirent *entry){
    struct stat st;
    stat(entry->d_name, &st);
    if(S_ISDIR(st.st_mode) && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, ".."))
        return 1;
    return 0;
}

/**
 * @brief     Retourne le diskReader à l'index correspondant
 * @param[in] dmr      diskManagerReader
 * @param[in] index    index
 * @return    Si NULL alors disk inexistant
 */
struct diskManagerReader* disk_manager_r_create(const char* name) {

  struct dirent** diskNameList;
  int diskNameCount;

  diskNameCount = scandir(name, &diskNameList, _disk_filter, alphasort);

  if (diskNameCount < 0) {
    return NULL;
  }

  struct diskManagerReader* dmr= (struct diskManagerReader*) malloc(sizeof(struct diskManagerReader));
  dmr->dr_count = diskNameCount;

  if(diskNameCount == 0) {
    dmr->dr = NULL;
    return dmr;
  }

  dmr->dr = (struct diskReader**) malloc(dmr->dr_count * sizeof(struct diskReader*));

  for (int indexName = 0; indexName < diskNameCount; indexName++) {
    dmr->dr[indexName] = disk_r_create(diskNameList[indexName]->d_name);
    free(diskNameList[indexName]);
  }
  free(diskNameList);

  return dmr;
}

/**
 * @brief     Retourne le diskReader à l'index correspondant
 * @param[in] dmr      diskManagerReader
 * @param[in] index    index
 * @return    Si NULL alors disk inexistant
 */
struct diskReader* disk_manager_r_get_item( struct diskManagerReader* dmr, int index) {
  if(index >= 0 && index < dmr->dr_count )
    return dmr->dr[index];
  else
    return NULL;
}

/**
 * @brief     Retourne le nombre de disk
 * @param[in] dmr      diskManagerReader
 * @return    nombre de disk
 */
size_t disk_manager_r_count( struct diskManagerReader* dmr) {
  return dmr->dr_count;
}

/**
 * @brief     Detruit le diskWriterManger
 * @param[in] dmr        diskManagerReader
 */
void disk_manager_r_destroy( struct diskManagerReader* dmr) {
  if(dmr->dr_count > 0)
    free(dmr->dr);
  free(dmr);
}
