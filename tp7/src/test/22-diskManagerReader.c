#include "../bdd/buffer.h"
#include "../bdd/diskManagerReader.h"
#include "../bdd/diskReader.h"

static const size_t _buf_size= 10;
static const size_t _buf_data_lenght= sizeof(char);
static const int _buf_mode= BUFFER_CHARACTERS;

static const char* _main_disk= "res/test/22/MainDisk/";

int main(int argc, char** argv){

  struct diskManagerReader* dmr= disk_manager_r_create(_main_disk);
  if(dmr == NULL) {
    printf("Erreur lors de la lecture de %s.\n", _main_disk);
    return -1;
  }

  struct buffer* buf= buffer_create(_buf_size, _buf_data_lenght, _buf_mode);

  for(int index_disk=0; index_disk<disk_manager_r_count(dmr); index_disk++) {
    struct diskReader* dr= disk_manager_r_get_item(dmr, index_disk);
    if(dr != NULL)
    for(int index_block=0; index_block<disk_r_count(dr); index_block++) {
      buffer_read_file_from_descriptor( disk_r_item(dr, index_block),  buf);
      buffer_printValue(buf);
    }
  }
}
