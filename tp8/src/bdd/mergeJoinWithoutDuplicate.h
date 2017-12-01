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
#ifndef SRC_BDD_MERGEJOINWITHOUTDUPLICATE_H
#define SRC_BDD_MERGEJOINWITHOUTDUPLICATE_H

#include "buffer.h"

/**
 * @brief Merge join without duplicate
 *
 * @param[in]  buf_a   relation a
 * @param[in]  buf_b   relation b
 * @param[out] buf_out resultat du merge_join de la relation a et b
 */
void merge_join_without_duplicate(const struct buffer* buf_a, const struct buffer* buf_b, struct buffer* buf_out);

#endif
