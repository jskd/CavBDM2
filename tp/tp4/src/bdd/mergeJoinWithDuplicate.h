/**
* TP n°: 3
*
* Titre du TP : Merge Join Duplicate
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
#ifndef SRC_BDD_MERGEJOINWITHDUPLICATE_H
#define SRC_BDD_MERGEJOINWITHDUPLICATE_H

#include "buffer.h"

/**
 * @brief Merge join with duplicate
 *
 * @param[in]  buf_a   relation a
 * @param[in]  buf_b   relation b
 * @param[out] buf_out resultat du merge join avec duplication de la relation a et b
 */
void merge_join_with_duplicate(const struct buf* buf_a, const struct buf* buf_b, struct buf* buf_out);

#endif
