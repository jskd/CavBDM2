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
#include "mergeJoinWithDuplicate.h"
#include "buffer.h"

/**
 * @brief Merge join with duplicate
 *
 * @param[in]  buf_a   relation a
 * @param[in]  buf_b   relation b
 * @param[out] buf_out resultat du merge join avec duplication de la relation a et b
 */
void merge_join_with_duplicate(const struct buf* buf_a, const struct buf* buf_b, struct buf* buf_out) {
  int index_a=0; // pointer vers le buffer a
  int index_b=0; // pointer vers le buffer b

  while(index_a < buf_count(buf_a) && index_b < buf_count(buf_b))
  {
    const char val_a= buf_val(buf_a, index_a);
    char val_b= buf_val(buf_b, index_b);
    if(val_a == val_b) {
      int index_b_before= index_b;
      do {
        buf_put(buf_out, val_a);
        index_b++;
        val_b= buf_val(buf_b, index_b);
      } while(val_a == val_b);
      index_b= index_b_before;
      index_a++;
    } else if (val_a < val_b) {
      index_a++;
    } else {
      index_b++;
    }
  }
}
