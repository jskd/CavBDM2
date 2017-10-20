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
#include "mergeJoinWithoutDuplicate.h"
#include "buffer.h"

/**
 * @brief Merge join
 *
 * @param[in]  buf_a   relation a
 * @param[in]  buf_b   relation b
 * @param[out] buf_out resultat du merge_join
 */
void merge_join_without_duplicate(const struct buf* buf_a, const struct buf* buf_b, struct buf* buf_out) {
  int index_a=0; // pointer vers le buffer a
  int index_b=0; // pointer vers le buffer b

  while( index_a < buf_count(buf_a) && index_b < buf_count(buf_b))
  {
    const char val_a= buf_val(buf_a, index_a);
    const char val_b= buf_val(buf_b, index_b);
    if(val_a == val_b ) {
      buf_put(buf_out, val_a );
      index_a++;
    } else if (val_a < val_b) {
      index_a++;
    } else {
      index_b++;
    }
  }
}
