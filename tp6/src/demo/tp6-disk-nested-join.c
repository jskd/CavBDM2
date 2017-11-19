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

#include "../bdd/nestedLoopJoin.h"

// Buffer config
static const size_t _buf_size= 10;
static const size_t _data_lenght= sizeof(short);
static const int _buffer_type= BUFFER_DECIMALS;

// input disk config
static const char* _file_r= "res/demo/tp6/R";
static const char* _file_s= "res/demo/tp6/S";

// output disk config
static const char* _dir_rs= "res/demo/tp6/RS-nested";
static const char* _prefix_rs= "RS";
static const char* _ext_rs= ".txt";
static const int   _offset_rs= 0;

int main(int argc, char** argv){

  struct disk* disk_r= disk_create(_file_r);
  if(disk_r == NULL) {
    printf("Erreur lors de la lecture de %s.\n", _file_r);
    return -1;
  }

  struct disk* disk_s= disk_create(_file_s);
  if(disk_s == NULL) {
    printf("Erreur lors de la lecture de %s.\n", _file_s);
    return -1;
  }

  struct disk_output* disk_o= disk_output_create(_dir_rs, _prefix_rs, _ext_rs, _offset_rs);

  struct buffer* buf_r  = buffer_create(_buf_size, _data_lenght, _buffer_type);
  struct buffer* buf_s  = buffer_create(_buf_size, _data_lenght, _buffer_type);
  struct buffer* buf_rs= buffer_create(_buf_size, _data_lenght, _buffer_type);

  nested_loop_join_disk( disk_r, buf_r, disk_s, buf_s, buf_rs, disk_o);

  // Si buffer non vide alors vidage dans disk_o
  if(!buffer_isEmpty(buf_rs))
    buffer_write_file_from_descriptor(
      disk_output_get_current_file_descriptor(disk_o), buf_rs);

  printf("Stat Buffer R:\n");
  buffer_fprint_stat(stdout, buf_r);
  printf("Stat Buffer S:\n");
  buffer_fprint_stat(stdout, buf_s);
  printf("Stat Buffer RS:\n");
  buffer_fprint_stat(stdout, buf_rs);
  printf("\n");

  printf("Terminé, fichier dans %s.\n", _dir_rs);

  buffer_destroy(buf_r);
  buffer_destroy(buf_s);
  buffer_destroy(buf_rs);
  disk_destroy(disk_r);
  disk_destroy(disk_s);

  return 0;
}
