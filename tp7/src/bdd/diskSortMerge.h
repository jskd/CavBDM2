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

#ifndef SRC_BDD_DISK_SORT_MERGE_H
#define SRC_BDD_DISK_SORT_MERGE_H


#include "buffer.h"
#include "diskManagerWriter.h"
#include "diskManagerReader.h"



void disk_explode_and_sort_to_disk_manager(struct diskReader* dr, struct buffer* buf, struct diskManagerWriter* dmw);

void disk_manager_merge_step(struct DiskManagerReader in, struct diskManagerWriter* out);

#endif
