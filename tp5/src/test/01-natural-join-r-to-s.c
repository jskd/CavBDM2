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

#include "../bdd/nestedLoopJoin.h"

static const size_t _buf_size= 10;
static const size_t _buf_data_lenght= 1;

int main(int argc, char** argv){


  // buffer R.txt
  struct buffer* buf_r= buffer_read_file("res/R.txt", _buf_size, _buf_data_lenght);
  if(buf_r == NULL) {
    printf("Erreur lors de la lecture de R.txt.\n");
    return -1;
  }

  // buffer S.txt
  struct buffer* buf_s= buffer_read_file("res/S.txt", _buf_size, _buf_data_lenght);
  if(buf_s == NULL) {
    printf("Erreur lors de la lecture de S.txt.\n");
    return -1;
  }

  // buffer de sortie
  struct buffer* buf_rs= buffer_create( _buf_size, _buf_data_lenght);

  // Jointure
  natural_join(buf_r, buf_s, buf_rs);


  buffer_dump(buf_rs);

  // Remove buf
  buffer_destroy(buf_r);
  buffer_destroy(buf_s);
  buffer_destroy(buf_rs);

  return 0;
}
