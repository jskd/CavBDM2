/**
* TP n°: 2
*
* Titre du TP : Merge Join
*
* Date : 13/10/17
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

#ifndef SRC_BDD_NATURALJOIN_H
#define SRC_BDD_NATURALJOIN_H

#include "buffer.h"

/**
 * Natual join
 *
 * @param[in]  buf_a   relation externe
 * @param[in]  buf_b   relation interne
 * @param[out] buf_out resultat du natural join de buf_a et buf_b
 */
void natural_join(const struct buf* buf_a, const struct buf* buf_b, struct buf* buf_out);

#endif
