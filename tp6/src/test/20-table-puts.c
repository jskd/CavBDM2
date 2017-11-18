#include "../bdd/bufferExtended.h"
#include "../bdd/table.h"

int main(int argc, char** argv){

  struct buffer* buf= buffer_read_file("res/test/20-buffer-pair-impaire.txt",
    10, sizeof(short), BUFFER_DECIMALS);

  struct table* tab= table_create(2, "res/test/20-bucket");

  table_putBuffer(tab, buf);

  table_storeBucketInBuffer(tab, 0, buf);

  printf("bucket 0\n");
  buffer_printValue(buf);

  table_storeBucketInBuffer(tab, 1, buf);

  printf("bucket 1\n");
  buffer_printValue(buf);

  buffer_destroy(buf);

}
