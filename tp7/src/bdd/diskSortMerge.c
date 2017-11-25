#include "buffer.h"
#include "diskManagerWriter.h"
#include "diskManagerReader.h"
#include "diskWriter.h"
#include "diskReader.h"


void disk_explode_and_sort_to_disk_manager(struct diskReader* dr, struct buffer* buf, struct diskManagerWriter* dmw) {

  for(int index=0; index < disk_r_count(dr); index++) {

      buffer_read_file_from_descriptor(disk_r_item(dr, index), buf);

      buffer_quicksort(buf);

      if(index > 0)
        disk_manager_w_next_dw(dmw);

      buffer_write_file_from_descriptor(disk_w_get_current_f(disk_manager_w_get_current_dw(dmw)), buf);

  }
}

void disk_manager_merge_step(struct diskManagerReader* in, struct diskManagerWriter* out) {





}
