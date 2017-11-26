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

// output disk config
static const char* _dir_sort_dst= "res/demo/tp7/R-Run0";
static const char* _dir_sort_prefix= "block";
static const char* _dir_sort_suffixe= "";
static const char* _file_prefixe= "R";
static const char* _file_suffixe= ".txt";


int main(int argc, char** argv){

  struct diskReader* dr= disk_r_create(_file_r);
  if(dr == NULL) {
    printf("Erreur lors de la lecture de %s.\n", _file_r);
    return -1;
  }

  struct diskWriterManger* dmw= disk_manager_w_create(_dir_sort_dst, _dir_sort_prefix, _dir_sort_suffixe, _file_prefixe, _file_suffixe);


  struct buffer* buf_a  = buffer_create(_buf_size, _data_lenght, _buffer_type);
  struct buffer* buf_b  = buffer_create(_buf_size, _data_lenght, _buffer_type);
  struct buffer* buf_out= buffer_create(_buf_size, _data_lenght, _buffer_type);


  disk_explode_and_sort_to_disk_manager(dr, buf_a, dmw);


  return 0;
}
