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

#include "../bdd/bufferExtended.h"

static const size_t _buf_size=   10;
static const size_t _data_lenght= 2;

int main(int argc, char** argv){

  // buffer R.txt
  struct buffer* buf_r= buffer_read_file("res/test/disk/R/R0.txt", _buf_size, _data_lenght);
  if(buf_r == NULL) {
    printf("Erreur lors de la lecture de R.txt.\n");
    return -1;
  }

  buffer_dump(buf_r);

  buffer_destroy(buf_r);
  return 0;
}
