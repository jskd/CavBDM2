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

#ifndef SRC_BDD_DISK_H
#define SRC_BDD_DISK_H

#include <stdio.h>
#include "bufferExtended.h"
#include "table.h"

/**
 * @brief Structure de donnée repésentant un buffer
 * Remarque: Structure caché! Ne pas initilialiser autrement
 * qu'avec les fonctions prévu à cet effet!
 */
struct disk;

size_t disk_count(const struct disk* disk);

struct disk* disk_create( const char * dir);

void disk_destroy(struct disk* disk);

FILE* disk_item(const struct disk* disk, int index);

void disk_storeContentInTable(const struct disk* disk, struct buffer* buf, struct table* tab);

#endif
