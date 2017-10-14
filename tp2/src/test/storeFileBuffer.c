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

  // buffer R.txt
  struct buf* buf_r= storeFileBufferOC("res/R.txt", buf_size);
  if(buf_r == NULL) {
    printf("Erreur lors de la lecture de R.txt.\n");
    return -1;
  }

  buf_dump(buf_r);

  buf_destroy(buf_r);
  return 0;
}
