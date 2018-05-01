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

/**
 * @brief Structure caché des données repésentant un diskManagerWriter
 */
struct diskManagerWriter{
  char* dir;
  char* d_prefixe;
  char* d_suffixe;
  char* f_prefixe;
  char* f_suffixe;
  int dw_number;
  struct diskWriter* current_dw;
};

static struct diskWriter* _dmw_disk_w_create_from_index(struct diskManagerWriter* dmw, int index) {
  char diskname[PATH_MAX];
  sprintf(diskname, "%s/%s%03d%s", dmw->dir, dmw->d_prefixe, index, dmw->d_suffixe);
  return disk_w_create(diskname, dmw->f_prefixe, dmw->f_suffixe);
}

/**
 * @brief     Creation d'un diskManagerWriter
 *         Les disk écrit sont dans le format "{dst} / {prefix} + {index} + {suffixe}".
 * @param[in] dst      Repertoire de destination
 * @param[in] prefixe  Prefixe de nommage des disks
 * @param[in] suffixe  Sufixe de nommage des disks
 */
struct diskManagerWriter* disk_manager_w_create(const char* dir, const char* disk_prefixe,
  const char* disk_suffixe, const char* file_prefixe, const char* file_suffixe)
{
  struct diskManagerWriter* dmw= (struct diskManagerWriter*) malloc(sizeof(struct diskManagerWriter));
  dmw->dir= strdup(dir);
  dmw->d_prefixe= strdup(disk_prefixe);
  dmw->d_suffixe= strdup(disk_suffixe);
  dmw->f_prefixe= strdup(file_prefixe);
  dmw->f_suffixe= strdup(file_suffixe);

  rmrf(dir);
  mkdir(dir, 0777);

  dmw->current_dw= _dmw_disk_w_create_from_index(dmw, 0);
  dmw->dw_number=1;

  return dmw;
}

/**
 * @brief     Retourne le diskWriter (écrase le contenu s'il existe déjà)
 * @param[in] dmw        DiskManagerWriter
 * @return    diskWriter
 */
struct diskWriter* disk_manager_w_get_current_dw(struct diskManagerWriter* dmw) {
  return dmw->current_dw;
}

/**
 * @brief     Passage au diskWriter suivant
 * @param[in] dmw      DiskManagerWriter
 */
void disk_manager_w_next_dw(struct diskManagerWriter* dmw) {
  disk_w_destroy(dmw->current_dw);
  dmw->current_dw= _dmw_disk_w_create_from_index(dmw, dmw->dw_number);
  dmw->dw_number++;
}

int disk_manager_w_count(struct diskManagerWriter* dmw) {
  return dmw->dw_number;
}

/**
 * @brief     Detruit le diskWriterManger
 * @param[in] dmw        DiskManagerWriter
 */
void disk_manager_w_destroy(struct diskManagerWriter* dmw) {
  disk_w_destroy(dmw->current_dw);
  free(dmw->dir);
  free(dmw->d_prefixe);
  free(dmw->d_suffixe);
  free(dmw->f_prefixe);
  free(dmw->f_suffixe);
  free(dmw);
}
