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
#include "diskWriter.h"
#include "diskReader.h"

/**
 *  Trie fusion sur disque
 *  @param[in] dr disk à trie
 *  @param[in] buf_a    buffer utilisé pour la lecture majoritairement
 *  @param[in] buf_b    buffer utilisé pour la lecture majoritairement
 *  @param[in] buf_out  buffer utilisé pour récuprer les calcules intermédiaire
 *                      et ecriture
 */
void disk_sort_merge(struct diskReader* dr, struct buffer*buf_a,
  struct buffer*buf_b, struct buffer*buf_out, const char* path_output);
  
#endif
