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

#ifndef SRC_BDD_DISK_OUTPUT_H
#define SRC_BDD_DISK_OUTPUT_H

#include <stdio.h>
#include <stdlib.h>
#include "buffer.h"
#include "diskReader.h"

struct diskWriter;

struct diskWriter* disk_w_create(const char* dir, const char* prefix,
  const char* extension);

FILE* disk_w_get_current_f( struct diskWriter* disk_o);

void disk_w_new_f( struct diskWriter* dw);

void disk_w_destroy( struct diskWriter* disk_o );

void disk_w_copy(struct diskReader* dr, struct diskWriter* dw, struct buffer* buf);
char* disk_w_get_current_path( struct diskWriter* dw);

#endif
