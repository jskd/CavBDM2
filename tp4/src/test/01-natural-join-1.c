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

#include "../bdd/naturalJoin.h"

static const size_t buf_size= 16;

int main(int argc, char** argv){

    // buffer R.txt
    struct buf* buf_r= storeFileBuffer("res/R.txt", buf_size);
    if(buf_r == NULL) {
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

    // Jointure
    natural_join(buf_s, buf_r, buf_rs);


    buf_dump(buf_rs);

    // Remove buf
    buf_destroy(buf_r);
    buf_destroy(buf_s);
    buf_destroy(buf_rs);
}
