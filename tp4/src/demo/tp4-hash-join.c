/**
* TP n°: 4
*
* Titre du TP : Hash Join
*
* Date : 27/10/17
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

#include "../bdd/hashtable.h"

static const size_t buf_size= 10;

int main(int argc, char** argv){

  // hashtable R.txt
  struct hashtable* ht_r = storeFileInHashtable("res/R.txt", 11);
  if(ht_r == NULL) {
    printf("Erreur lors de la lecture de R.txt.\n");
    return -1;
  }

  // buffer S.txt
  struct buf* buf_s= storeFileBuffer("res/S.txt", buf_size);
  if(buf_s == NULL) {
    printf("Erreur lors de la lecture de S.txt.\n");
    return -1;
  }

  // buffer de sortie
  struct buf* buf_rs= buf_create( buf_size);

  hashjoin(ht_r, buf_s, buf_rs);

  writeBufferInFile("res/RS.txt", buf_rs);

  hashtable_destroy(ht_r);
  buf_destroy(buf_rs);
  buf_destroy(buf_s);

  return 0;
}
