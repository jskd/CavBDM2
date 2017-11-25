#include "../bdd/bufferExtended.h"
#include "../bdd/table.h"
#include "../bdd/diskReader.h"
#include "../bdd/nestedLoopJoin.h"

static const size_t _buf_size=   10;
static const size_t _out_size= 10;
static const size_t _data_lenght= sizeof(short);
static const char* _file_r= "res/test/21/R";
static const char* _file_s= "res/test/21/S";

static const char* _file_table_r= "res/test/21/tableR";
static const char* _file_table_s= "res/test/21/tableS";

int main(int argc, char** argv){

  struct diskReader* disk_r= disk_r_create(_file_r);
  if(disk_r == NULL) {
    printf("Erreur lors de la lecture de %s.\n", _file_r);
    return -1;
  }

  struct diskReader* disk_s= disk_r_create(_file_s);
  if(disk_s == NULL) {
    printf("Erreur lors de la lecture de %s.\n", _file_s);
    return -1;
  }

  struct table* tab_r= table_create(4, _file_table_r);
  struct table* tab_s= table_create(4, _file_table_s);

  struct buffer* buf_r  = buffer_create(_buf_size, _data_lenght, BUFFER_DECIMALS);
  struct buffer* buf_s  = buffer_create(_buf_size, _data_lenght, BUFFER_DECIMALS);
  struct buffer* buf_out= buffer_create(_out_size, _data_lenght, BUFFER_DECIMALS);

  disk_r_storeContentInTable(disk_s, buf_s, tab_s);
  disk_r_storeContentInTable(disk_r, buf_r, tab_r);

  table_bucket_join(tab_s, buf_s, tab_r, buf_r, buf_out, 0);

  buffer_printValue(buf_out);

  buffer_destroy(buf_r);
  buffer_destroy(buf_s);
  buffer_destroy(buf_out);

  disk_r_destroy(disk_r);
  disk_r_destroy(disk_s);

  table_destroy(tab_r);
  table_destroy(tab_s);
}
