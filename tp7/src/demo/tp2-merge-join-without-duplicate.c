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

#include "../bdd/mergeJoinWithoutDuplicate.h"

static const size_t _buf_size= 10;
static const size_t _buf_data_lenght= 1;
static const char* _file_r= "res/demo/tp2/R.txt";
static const char* _file_s= "res/demo/tp2/S.txt";
static const char* _file_rs= "res/demo/tp2/RS.txt";

int main(int argc, char** argv){

  // buffer R.txt
  struct buffer* buf_r= buffer_read_file(_file_r, _buf_size, _buf_data_lenght, BUFFER_CHARACTERS);
  if(buf_r == NULL) {
    printf("Erreur lors de la lecture de %s.\n", _file_r);
    return -1;
  }

  // buffer S.txt
  struct buffer* buf_s= buffer_read_file(_file_s, _buf_size, _buf_data_lenght, BUFFER_CHARACTERS);
  if(buf_s == NULL) {
    printf("Erreur lors de la lecture de %s.\n", _file_s);
    return -1;
  }

  // buffer de sortie
  struct buffer* buf_rs= buffer_create( _buf_size, _buf_data_lenght, BUFFER_CHARACTERS);

  // Jointure
  merge_join_without_duplicate(buf_r, buf_s, buf_rs);

  // Ecriture du resultat dans RS.txt
  if(buffer_write_file(_file_rs, buf_rs))
    printf("Erreur lors de la lecture de %s.\n", _file_rs);

  printf("Terminé, fichier dans %s\n", _file_rs);

  // Remove buf
  buffer_destroy(buf_r);
  buffer_destroy(buf_s);
  buffer_destroy(buf_rs);

  return 0;
}