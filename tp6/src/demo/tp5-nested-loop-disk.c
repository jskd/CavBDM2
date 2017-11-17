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

static const size_t _buf_size=   10;
static const size_t _data_lenght= 2;
static const char*  _output_file_name= "res/disk/RS.txt";

int main(int argc, char** argv){

  struct disk* disk_r= disk_create("res/disk/R", "r");
  if(disk_r == NULL) {
    printf("Erreur lors de la lecture de res/disk/R.\n");
    return -1;
  }

  struct disk* disk_s= disk_create("res/disk/S", "r");
  if(disk_s == NULL) {
    printf("Erreur lors de la lecture de res/disk/S.\n");
    return -1;
  }

  FILE* _output_file= fopen(_output_file_name, "w+");

  struct buffer* buf_r  = buffer_create(_buf_size, _data_lenght, BUFFER_CHARACTERS);
  struct buffer* buf_s  = buffer_create(_buf_size, _data_lenght, BUFFER_CHARACTERS);
  struct buffer* buf_out= buffer_create(_buf_size, _data_lenght, BUFFER_CHARACTERS);

  nested_loop_join_disk( disk_r, buf_r, disk_s, buf_s, buf_out, _output_file);

  // Si n'est pas vide alors ecriture
  if(!buffer_isEmpty(buf_out))
    buffer_write_file_from_descriptor(_output_file, buf_out);

  printf("Terminé, fichier dans %s.\n", _output_file_name);

  buffer_destroy(buf_r);
  buffer_destroy(buf_s);
  buffer_destroy(buf_out);
  disk_destroy(disk_r);
  disk_destroy(disk_s);

  return 0;
}
