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

#include "../bdd/hashtable.h"

static const size_t buf_size= 10;

int main(int argc, char** argv){

  // buffer R.txt
  struct buf* buf_r= storeFileBufferOC("res/Rduplicate.txt", buf_size);
  if(buf_r == NULL) {
    printf("Erreur lors de la lecture de R.txt.\n");
    return -1;
  }

  // buffer S.txt
  struct buf* buf_s= storeFileBufferOC("res/Sduplicate.txt", buf_size);
  if(buf_s == NULL) {
    printf("Erreur lors de la lecture de S.txt.\n");
    return -1;
  }

  // buffer de sortie
  struct buf* buf_rs= buf_create( buf_size);

  struct hashtable* ht= hashtable_create( buf_count(buf_r) );

  storeBufferToHashtable(buf_r, ht);

  hashtable_print(ht);

  return 0;
}
