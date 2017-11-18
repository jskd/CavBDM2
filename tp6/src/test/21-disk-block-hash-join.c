#include "../bdd/bufferExtended.h"
#include "../bdd/table.h"
#include "../bdd/disk.h"
#include "../bdd/nestedLoopJoin.h"

static const size_t _buf_size=   10;
static const size_t _out_size= 10;
static const size_t _data_lenght= sizeof(short);

int main(int argc, char** argv){

  struct disk* disk_r= disk_create("res/test/disk-short/R", "r");
  if(disk_r == NULL) {
    printf("Erreur lors de la lecture de res/test/disk-short/R.\n");
    return -1;
  }

  struct disk* disk_s= disk_create("res/test/disk-short/S", "r");
  if(disk_s == NULL) {
    printf("Erreur lors de la lecture de res/test/disk-short/S.\n");
    return -1;
  }

  struct table* tab_r= table_create(4, "res/test/21-bucket-r-4");
  struct table* tab_s= table_create(4, "res/test/21-bucket-s-4");

  struct buffer* buf_r  = buffer_create(_buf_size, _data_lenght, BUFFER_DECIMALS);
  struct buffer* buf_s  = buffer_create(_buf_size, _data_lenght, BUFFER_DECIMALS);
  struct buffer* buf_out= buffer_create(_out_size, _data_lenght, BUFFER_DECIMALS);

  disk_storeContentInTable(disk_s, buf_s, tab_s);
  disk_storeContentInTable(disk_r, buf_r, tab_r);

  table_bucket_join(tab_s, buf_s, tab_r, buf_r, buf_out, 0);

  buffer_printValue(buf_out);

  buffer_destroy(buf_r);
  buffer_destroy(buf_s);
  buffer_destroy(buf_out);

  disk_destroy(disk_r);
  disk_destroy(disk_s);

  table_destroy(tab_r);
  table_destroy(tab_s);
}
