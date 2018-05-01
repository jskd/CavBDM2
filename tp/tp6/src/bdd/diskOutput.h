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

struct disk_output;

struct disk_output* disk_output_create(const char* dir, const char* prefix,
  const char* extension, int offset);

FILE* disk_output_get_current_file_descriptor( struct disk_output* disk_o);

FILE* disk_output_next_file( struct disk_output* disk_o);

void disk_output_destroy( struct disk_output* disk_o );

#endif
