/**
* TP n°: 1
*
* Titre du TP : Join Array
*
* Date : 06/10/17
*
* Nom : Lefranc
* Prenom : Joaquim
* email : lefrancjoaquim@gmail.com
*
* Nom : Skoda
* Prenom : Jérôme
* email : contact@jeromeskoda.fr
*
* Remarques : Code Block -> Trash. Makefile <3
*/

#include "../bdd/bdd.h"

static const size_t buf_size= 16;


int main(int argc, char** argv){

  struct buf* buf_r= storeFileBufferOC("res/R.txt", 16);
  if(buf_r == NULL) {
    printf("Erreur lors de la lecture de R.txt.\n");
    return -1;
  }
  buf_dump(buf_r);

  struct buf* buf_s= storeFileBufferOC("res/S.txt", 16);
  if(buf_s == NULL) {
    printf("Erreur lors de la lecture de S.txt.\n");
    return -1;
  }
  buf_dump(buf_r);


  buf_quicksort(buf_r);
  buf_quicksort(buf_s);
  buf_dump(buf_s);

  // Store natural join of buf_r and buf_s in buf_rs
  struct buf* buf_rs= buf_create( buf_size);
  merge_join(buf_r, buf_s, buf_rs);


  if(writeBufferInFileOC("res/RS.txt", buf_rs))
    printf("Erreur lors de la lecture de RS.txt.\n");

  buf_dump(buf_rs);

  // Remove buf
  buf_destroy(buf_r);
  buf_destroy(buf_s);
  buf_destroy(buf_rs);

  return 0;
}
