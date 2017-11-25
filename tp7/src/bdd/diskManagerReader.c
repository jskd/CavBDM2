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


/**
 * @brief     Retourne le diskReader à l'index correspondant
 * @param[in] dmr      diskManagerReader
 * @param[in] index    index
 * @return    Si NULL alors disk inexistant
 */
struct diskManagerReader* disk_manager_r_create(const char* path) {

  struct dirent** nameList;
  int nameCount= scandir(path, &nameList, NULL, alphasort);

  if(nameCount < 0) {
    return NULL;
  }


  struct diskManagerReader* dmr= (struct diskManagerReader*) malloc(sizeof(struct diskManagerReader));


  dmr->dr_count=0;
  for (int indexName = 0; indexName < nameCount; indexName++) {
    char filename[NAME_MAX];
    struct stat st;

    snprintf(filename, sizeof(filename), "%s/%s", path, nameList[indexName]->d_name);
    stat(filename, &st);

    if(strcmp( nameList[indexName]->d_name, ".") != 0 && strcmp( nameList[indexName]->d_name, "..") && st.st_mode & S_IFDIR)
      dmr->dr_count++;
  }


  if(dmr->dr_count == 0) {
    dmr->dr = NULL;
    return dmr;
  }

  dmr->dr = (struct diskReader**) malloc(dmr->dr_count * sizeof(struct diskReader*));
  int index_dr=0;
  for (int indexName = 0; indexName < nameCount; indexName++) {
    char filename[NAME_MAX];
    struct stat st;

    snprintf(filename, sizeof(filename), "%s/%s", path, nameList[indexName]->d_name);
    stat(filename, &st);

    if(strcmp( nameList[indexName]->d_name, ".") != 0 && strcmp( nameList[indexName]->d_name, "..") && st.st_mode & S_IFDIR) {
      dmr->dr[index_dr]= disk_r_create(filename);
      index_dr++;
    }
    free(nameList[indexName]);
  }


  free(nameList);

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
