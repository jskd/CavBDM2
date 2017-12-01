#include "../bdd/buffer.h"
#include "../bdd/table.h"
#include "../bdd/diskReader.h"

// Buffer config
static const size_t _buf_size= 10;
static const size_t _data_lenght= sizeof(short);
static const int _buffer_type= BUFFER_DECIMALS;

// input disk config
static const char* _file_r= "res/test/20/R";

// table config
static const char* _file_table_r= "res/test/20/tableR";
static const size_t _n_bucket= 2;

int main(int argc, char** argv){

  struct diskReader* disk_r= disk_r_create(_file_r);
  if(disk_r == NULL) {
    printf("Erreur lors de la lecture de %s.\n", _file_r);
    return -1;
  }

  struct table* tab_r= table_create(_n_bucket, _file_table_r);
  if(tab_r == NULL) {
    printf("Erreur lors de la creation de %s.\n", _file_table_r);
    return -1;
  }

  struct buffer* buf_r  = buffer_create(_buf_size, _data_lenght, _buffer_type);

  disk_r_storeContentInTable(disk_r, buf_r, tab_r);

  for(int index_bucket=0; index_bucket < table_get_n_bucket(tab_r);  index_bucket++) {
    struct diskReader* disk_tab= create_disk_from_bucket(tab_r, index_bucket);
    disk_r_storeContentInTable(disk_tab, buf_r, tab_r);
    printf("Value bucket %d\n", index_bucket);
    buffer_printValue(buf_r);
    disk_r_destroy(disk_tab);
  }


  disk_r_destroy(disk_r);
  table_destroy(tab_r);
  buffer_destroy(buf_r);
}
