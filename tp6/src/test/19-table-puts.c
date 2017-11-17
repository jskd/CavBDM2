#include "../bdd/table.h"



int main(int argc, char** argv){

  struct table* tab= table_create(10, "test");

  struct buffer* buf= buffer_read_file("test.num", 10, sizeof(int), BUFFER_DECIMALS);

  buffer_printValue(buf);
}
