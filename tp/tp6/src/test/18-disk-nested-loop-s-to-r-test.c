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
#include "../bdd/disk.h"
#include "../bdd/nestedLoopJoin.h"

static const size_t _buf_size=   10;
static const size_t _data_lenght= 2;
static const size_t _out_size= 270;

int main(int argc, char** argv){

  struct disk* disk_r= disk_create("res/test/disk/R");
  if(disk_r == NULL) {
    printf("Erreur lors de la lecture de res/disk/R.\n");
    return -1;
  }

  struct disk* disk_s= disk_create("res/test/disk/S");
  if(disk_s == NULL) {
    printf("Erreur lors de la lecture de res/disk/S.\n");
    return -1;
  }

  struct buffer* buf_r  = buffer_create(_buf_size, _data_lenght, BUFFER_CHARACTERS);
  struct buffer* buf_s  = buffer_create(_buf_size, _data_lenght, BUFFER_CHARACTERS);
  struct buffer* buf_out= buffer_create(_out_size, _data_lenght, BUFFER_CHARACTERS);

  nested_loop_join_disk(disk_s, buf_s, disk_r, buf_r, buf_out, 0);

  buffer_dump(buf_out);

  buffer_destroy(buf_r);
  buffer_destroy(buf_s);
  buffer_destroy(buf_out);
  disk_destroy(disk_r);
  disk_destroy(disk_s);
}
