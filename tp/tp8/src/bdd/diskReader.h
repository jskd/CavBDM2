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

#ifndef SRC_BDD_DISK_READER_H
#define SRC_BDD_DISK_READER_H

#include "table.h"
#include <stdio.h>

/**
 * @brief Structure de donnée repésentant un buffer
 * Remarque: Structure caché! Ne pas initilialiser autrement
 * qu'avec les fonctions prévu à cet effet!
 */
struct diskReader;

size_t disk_r_count(const struct diskReader* disk);

struct diskReader* disk_r_create( const char * dir);

void disk_r_destroy(struct diskReader* disk);

FILE* disk_r_item(const struct diskReader* disk, int index);

char* disk_r_item_path(const struct diskReader* disk, int index);

void disk_r_storeContentInTable(const struct diskReader* disk, struct buffer* buf, struct table* tab);

void disk_r_dump( FILE* f,  struct diskReader* dr);

#endif
