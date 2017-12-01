#include "../bdd/buffer.h"

int main(int argc, char** argv){

  struct buffer* buf= buffer_read_file("res/test/19-buffer-short.txt", 10, sizeof(short), BUFFER_DECIMALS);

  buffer_printValue(buf);
}
