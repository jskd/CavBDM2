/**
 * TP n°: 6
 *
 * Titre du TP :
 *
 * Date : 21/10/17
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
#ifndef SRC_BDD_TABLE_H
#define SRC_BDD_TABLE_H

#include <stdio.h>
#include "bufferExtended.h"

struct table;

struct table* table_create(size_t bucket, const char* directory);

void table_insertbuffer(struct table* tab, const struct buffer* buf);

void table_putBuffer(struct table* tab, const struct buffer* buf);

void table_destroy(struct table* tab) ;
size_t table_get_n_bucket(const struct table* tab);

int table_get_write_stat(const struct table* tab);
void table_fprint_stat(FILE* stream, const struct table* tab);

struct diskReader* create_disk_from_bucket(const struct table* tab, int indexBucket) ;
#endif
