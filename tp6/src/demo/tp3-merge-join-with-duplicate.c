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

#include "../bdd/mergeJoinWithDuplicate.h"

static const size_t buf_size= 10;

int main(int argc, char** argv){

  // buffer R.txt
  struct buf* buf_r= storeFileBuffer("res/Rduplicate.txt", buf_size);
  if(buf_r == NULL) {
    printf("Erreur lors de la lecture de R.txt.\n");
    return -1;
  }

  // buffer S.txt
  struct buf* buf_s= storeFileBuffer("res/Sduplicate.txt", buf_size);
  if(buf_s == NULL) {
    printf("Erreur lors de la lecture de S.txt.\n");
    return -1;
  }

  // buffer de sortie
  struct buf* buf_rs= buf_create( buf_size);

  // Jointure
  merge_join_with_duplicate(buf_r, buf_s, buf_rs);

  // Ecriture du resultat dans RS.txt
  if(writeBufferInFile("res/RS.txt", buf_rs))
    printf("Erreur lors de l'ecriture de RS.txt.\n");

  printf("Terminé, fichier dans res/RS.txt\n");

  // Remove buf
  buf_destroy(buf_r);
  buf_destroy(buf_s);
  buf_destroy(buf_rs);

  return 0;
}
