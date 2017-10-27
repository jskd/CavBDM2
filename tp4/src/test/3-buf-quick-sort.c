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

#include "../bdd/buffer.h"

static const size_t buf_size= 16;

int main(int argc, char** argv){

    // buffer R.txt
    struct buf* buf_r= storeFileBufferOC("res/R.txt", buf_size);
    if(buf_r == NULL) {
      printf("Erreur lors de la lecture de R.txt.\n");
      return -1;
    }

    buf_quicksort(buf_r);

    buf_dump(buf_r);

    // Remove buf
    buf_destroy(buf_r);
}
