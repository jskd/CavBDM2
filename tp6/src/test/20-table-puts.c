#include "../bdd/bufferExtended.h"
#include "../bdd/table.h"

static const size_t _buf_size= 10;
static const size_t _data_lenght= sizeof(short);
static const char* _file_r= "res/test/20/R.txt";
static const char* _file_table_r= "res/test/20/tableR";

int main(int argc, char** argv){

  struct buffer* buf= buffer_read_file(_file_r, _buf_size, _data_lenght, BUFFER_DECIMALS);
  if(buf == NULL) {
    printf("Erreur lors de la lecture de %s.\n", _file_r);
    return -1;
  }

  struct table* tab= table_create(2, _file_table_r);
  if(tab == NULL) {
    printf("Erreur lors de la creation de %s.\n", _file_table_r);
    return -1;
  }

  table_putBuffer(tab, buf);

  table_storeBucketInBuffer(tab, 0, buf);

  printf("bucket 0\n");
  buffer_printValue(buf);

  table_storeBucketInBuffer(tab, 1, buf);

  printf("bucket 1\n");
  buffer_printValue(buf);

  buffer_destroy(buf);

}
