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

static const size_t _buf_size= 10;
static const size_t _buf_data_lenght= 1;
static const char* _file_r= "res/demo/tp1/R.txt";

int main(int argc, char** argv){

  // buffer R.txt
  struct buffer* buf_r= buffer_read_file(_file_r, _buf_size, _buf_data_lenght, BUFFER_CHARACTERS);
  if(buf_r == NULL) {
    printf("Erreur lors de la lecture de %s.\n", _file_r);
    return -1;
  }

  buffer_printValue(buf_r);

  // Remove buf
  buffer_destroy(buf_r);

  return 0;
}
