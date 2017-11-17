/**
* TP n°: 5
*
* Titre du TP : Nested loop join disk
*
* Date : 10 Nov 2017
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

static const size_t _buf_size= 16;

int main(int argc, char** argv){

  // buffer R.txt
  struct buffer* buf_r= buffer_read_file("res/test/R.txt", _buf_size, 1, BUFFER_CHARACTERS);
  if(buf_r == NULL) {
    printf("Erreur lors de la lecture de R.txt.\n");
    return -1;
  }

  buffer_dump(buf_r);

  buffer_destroy(buf_r);
  return 0;
}
