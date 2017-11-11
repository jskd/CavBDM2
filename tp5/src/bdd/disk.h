
#ifndef SRC_BDD_DISK_H
#define SRC_BDD_DISK_H

#include <stdio.h>

/**
 * @brief Structure de donnée repésentant un buffer
 * Remarque: Structure caché! Ne pas initilialiser autrement
 * qu'avec les fonctions prévu à cet effet!
 */
struct disk;

size_t disk_count(const struct disk* disk);

struct disk* disk_create( const char * dir, const char* mode);

void disk_destroy(struct disk* disk);

FILE* disk_item(const struct disk* disk, int index);

#endif
