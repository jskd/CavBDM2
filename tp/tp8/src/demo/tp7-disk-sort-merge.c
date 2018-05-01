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

#include "../bdd/diskSortMerge.h"

// Buffer config
static const size_t _buf_size= 10;
static const size_t _data_lenght= sizeof(short);
static const int _buffer_type= BUFFER_DECIMALS;

// input disk config
static const char* _file_r= "res/demo/tp7/R";
static const char* _path_output="res/demo/tp7/R-sort";


int main(int argc, char** argv){

  struct diskReader* dr= disk_r_create(_file_r);
  if(dr == NULL) {
    printf("Erreur lors de la lecture de %s.\n", _file_r);
    return -1;
  }

  struct buffer* buf_a  = buffer_create(_buf_size, _data_lenght, _buffer_type);
  struct buffer* buf_b  = buffer_create(_buf_size, _data_lenght, _buffer_type);
  struct buffer* buf_out= buffer_create(_buf_size, _data_lenght, _buffer_type);

  disk_sort_merge(dr, buf_a, buf_b,  buf_out, _path_output);

  printf("Stat Buffer A:\n");
  buffer_fprint_stat(stdout, buf_a);
  printf("Stat Buffer B:\n");
  buffer_fprint_stat(stdout, buf_b);
  printf("Stat Buffer Out:\n");
  buffer_fprint_stat(stdout, buf_out);
  printf("\n");

  printf("Terminé, fichier dans %s.\n", _path_output);

  buffer_destroy(buf_a);
  buffer_destroy(buf_b);
  buffer_destroy(buf_out);
  disk_r_destroy(dr);

  return 0;
}
