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
#include "../bdd/diskReader.h"

static const size_t _buf_size=   10;
static const size_t _data_lenght= 2;

int main(int argc, char** argv){

  // buffer R.txt

  struct diskReader* disk= disk_r_create("res/test/minidisk");
  if(disk == NULL) {
    printf("Erreur lors de la lecture de res/test/minidisk.\n");
    return -1;
  }

  struct buffer* buf= buffer_create(_buf_size, _data_lenght, BUFFER_CHARACTERS);
  for(int i=0; i< disk_r_count(disk); i++) {
    buffer_read_file_from_descriptor( disk_r_item(disk, i),  buf);
    buffer_dump(buf);
  }

  disk_r_destroy(disk);
  buffer_destroy(buf);
  return 0;
}
