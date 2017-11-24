/**
* TP n°: 7
*
* Titre du TP : Disk Merge Join
*
* Date : 24 Nov 2017
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

#ifndef SRC_BDD_DISK_MANAGER_WRITER_H
#define SRC_BDD_DISK_MANAGER_WRITER_H

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Structure caché des données repésentant un diskManagerWriter
 */
struct diskManagerWriter;

/**
 * @brief     Creation d'un diskManagerWriter
 *         Les disk écrit sont dans le format "{dst} / {prefix} + {index} + {suffixe}".
 * @param[in] dst      Repertoire de destination
 * @param[in] prefixe  Prefixe de nommage des disks
 * @param[in] suffixe  Sufixe de nommage des disks
 */
struct diskManagerWriter* disk_manager_w_create(const char* dst, const char* prefixe,
  const char* suffixe);

/**
 * @brief     Retourne le diskWriter (écrase le contenu s'il existe déjà)
 * @param[in] dmw        DiskManagerWriter
 * @return    diskWriter
 */
struct diskWriter* disk_manager_w_get_current_dw(struct diskManagerWriter* dmw);

/**
 * @brief     Passage au diskWriter suivant
 * @param[in] dmw      DiskManagerWriter
 */
void disk_manager_w_next(struct diskManagerWriter* dmw);

/**
 * @brief     Detruit le diskWriterManger
 * @param[in] dmw        DiskManagerWriter
 */
void disk_manager_w_destroy(struct diskManagerWriter* dmw);

#endif
