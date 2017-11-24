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

#ifndef SRC_BDD_DISK_MANAGER_READER_H
#define SRC_BDD_DISK_MANAGER_READER_H

#include <stdio.h>
#include <stdlib.h>

struct diskManagerReader;

/**
 * @brief     Retourne le diskReader à l'index correspondant
 * @param[in] dmr      diskManagerReader
 * @param[in] index    index
 * @return    Si NULL alors disk inexistant
 */
struct diskManagerReader* disk_manager_r_create(const char* name);

/**
 * @brief     Retourne le diskReader à l'index correspondant
 * @param[in] dmr      diskManagerReader
 * @param[in] index    index
 * @return    Si NULL alors disk inexistant
 */
struct diskReader* disk_manager_r_get_item( struct diskManagerReader* dmr, int index);

/**
 * @brief     Retourne le nombre de disk
 * @param[in] dmr      diskManagerReader
 * @return    nombre de disk
 */
size_t disk_manager_r_count( struct diskManagerReader* dmr);

/**
 * @brief     Detruit le diskWriterManger
 * @param[in] dmr        diskManagerReader
 */
void disk_manager_r_destroy( struct diskManagerReader* dmr);

#endif
