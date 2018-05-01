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
void merge_join_with_duplicate(const struct buffer* buf_a, const struct buffer* buf_b, struct buffer* buf_out) {
  int index_a=0;
  int index_b=0;

  while(index_a < buffer_count(buf_a) && index_b < buffer_count(buf_b))
  {
    if( buffer_cmp(buf_a, index_a, buf_b, index_b) == 0 ) {
      int index_b_before= index_b;
      do {
        buffer_put_cpy(buf_out, buf_a, index_a);
        index_b++;
      } while( buffer_cmp(buf_a, index_a, buf_b, index_b) == 0 );
      index_b= index_b_before;
      index_a++;
    } else if ( buffer_cmp(buf_a, index_a, buf_b, index_b) < 0 ) {
      index_a++;
    } else {
      index_b++;
    }
  }
}
