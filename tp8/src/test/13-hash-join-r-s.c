/**
* TP n°: 4
*
* Titre du TP : Hash Join
*
* Date : 27/10/17
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

#include "../bdd/hashJoin.h"

static const size_t _buf_size= 10;
static const size_t _ht_size= 11;
static const size_t _buf_data_lenght= 1;
static const char* _file_r= "res/demo/tp4/R.txt";
static const char* _file_s= "res/demo/tp4/S.txt";

int main(int argc, char** argv){

  // hashtable R.txt
  struct hashtable* ht_r = storeFileInHashtable( _file_r, _ht_size);
  if(ht_r == NULL) {
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

  hash_join(ht_r, buf_s, buf_rs);

  buffer_printValue(buf_rs);

  hashtable_destroy(ht_r);
  buffer_destroy(buf_rs);
  buffer_destroy(buf_s);

  return 0;
}
