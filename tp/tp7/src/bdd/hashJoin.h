/**
* TP n°: 4
*
* Titre du TP : Hash Join
*
* Date : 28/10/17
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
#ifndef SRC_BDD_HASHJOIN_H
#define SRC_BDD_HASHJOIN_H

#include "buffer.h"
#include "hashtable.h"

/**
 * @brief Hash join
 * @param[in]  ht      hashtable de la relation a
 * @param[in]  buf_in  relation b
 * @param[out] buf_out resultat du hash join avec la relation a et b
 */
void hash_join(const struct hashtable* ht, const struct buffer* buf_in, struct buffer* buf_out);

#endif
