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
#include "naturalJoin.h"
#include "buffer.h"

/**
 * Natual join
 *
 * @param[in]  buf_a   relation externe
 * @param[in]  buf_b   relation interne
 * @param[out] buf_out resultat du natural join de buf_a et buf_b
 */
void natural_join(const struct buf* buf_a, const struct buf* buf_b, struct buf* buf_out) {
  for(int a=0; a< buf_count(buf_a); a++) {
    for(int b=0; b< buf_count(buf_b); b++) {
      if(buf_val(buf_a, a) == buf_val(buf_b, b)) {
        buf_put(buf_out, buf_val(buf_a, a));
        break; // pass to next a
      }
    }
  }
}
