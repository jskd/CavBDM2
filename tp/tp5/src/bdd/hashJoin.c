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

#include "hashJoin.h"

/**
 * @brief Hash join
 * @param[in]  ht      hashtable de la relation a
 * @param[in]  buf_in  relation b
 * @param[out] buf_out resultat du hash join avec la relation a et b
 */
void hash_join(const struct hashtable* ht, const struct buf* buf_in, struct buf* buf_out) {
  for(char index=0; index < buf_count(buf_in); index++)
  {
    char key= buf_val(buf_in, index);

    if(hashtable_get(ht, key) != VAL_NOT_IN_HASHTABLE)
      buf_put(buf_out, key);
  }
}
