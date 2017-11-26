#include "buffer.h"
#include "diskManagerWriter.h"
#include "diskManagerReader.h"
#include "diskWriter.h"
#include "diskReader.h"
#include <limits.h>
#include <sys/stat.h>
#include "rmrf.h"

static const char* folder_step= "steps";
static const char* _step_prefix= "step-";
static const char* _dir_sort_prefix= "block";
static const char* _dir_sort_suffixe= "";
static const char* _file_prefixe= "";
static const char* _file_suffixe= ".txt";

static void _make_folder_step(const char* path_output) {
  char dirname[PATH_MAX];
  sprintf(dirname, "%s-%s", path_output, folder_step);
  mkdir(dirname, 0777);
}

static void _make_output_dir(const char* path_output) {
  rmrf(path_output);
  mkdir(path_output, 0777);
}

static void _sprint_pathname_step(const char* path_step, int step, char* output) {
  sprintf(output, "%s-%s/%s%d", path_step, folder_step, _step_prefix, step);
}

static struct diskManagerWriter* _create_step_dmw(const char* path_output, int step) {
  char dirname[PATH_MAX];
  _sprint_pathname_step(path_output, step, dirname);
  return disk_manager_w_create(dirname, _dir_sort_prefix, _dir_sort_suffixe, _file_prefixe, _file_suffixe);
}

static struct diskManagerReader* _create_step_dmr(const char* path_output, int step) {
  char dirname[PATH_MAX];
  _sprint_pathname_step(path_output, step, dirname);
  return disk_manager_r_create(dirname);
}
void disk_explode_and_sort_to_disk_manager(struct diskReader* dr, struct buffer* buf, struct diskManagerWriter* dmw) {
  for(int index=0; index < disk_r_count(dr); index++) {
      buffer_read_file_from_descriptor(disk_r_item(dr, index), buf);
      buffer_quicksort(buf);
      if(index > 0)
        disk_manager_w_next_dw(dmw);
      disk_w_new_f(disk_manager_w_get_current_dw(dmw));
      buffer_write_file_from_descriptor(disk_w_get_current_f(disk_manager_w_get_current_dw(dmw)), buf);
  }
}


#define IF_BUFFER_A_ENTIRELY_READ_LOAD_NEXT_FILE \
  if(index_buf_a >= buffer_count(buf_a)) { \
    buffer_read_file_from_descriptor(disk_r_item(dr_a, index_dr_a), buf_a); \
    index_buf_a= 0; \
  } \

#define IF_BUFFER_B_ENTIRELY_READ_LOAD_NEXT_FILE \
  if(index_buf_b >= buffer_count(buf_b)) { \
    buffer_read_file_from_descriptor(disk_r_item(dr_b, index_dr_b), buf_b); \
    index_buf_b= 0; \
  } \

static void _if_buffer_is_full_flush_buffer_in_disk(struct buffer* buf_out, struct diskWriter* disk_output) {
  if(buffer_isFull(buf_out)) {
    disk_w_new_f(disk_output);
    buffer_write_file_from_descriptor( disk_w_get_current_f(disk_output), buf_out);
    buffer_flush(buf_out);
  }
}

void disk_merge(struct diskReader* dr_a, struct diskReader* dr_b,
  struct buffer* buf_a, struct buffer* buf_b, struct buffer* buf_out,
  struct diskWriter* disk_output) {

  int index_dr_a=0;
  int index_dr_b=0;
  int index_buf_a=0;
  int index_buf_b=0;


  // Si y a des elment dans les deux disque
  if(disk_r_count(dr_a) > 0 && disk_r_count(dr_b) > 0)
  {
    buffer_read_file_from_descriptor(disk_r_item(dr_a, index_dr_a), buf_a);
    buffer_read_file_from_descriptor(disk_r_item(dr_b, index_dr_b), buf_b);

    // Comparaison s'il y a des elements dans les deux listes
    while(index_dr_a < disk_r_count(dr_a) && index_dr_b < disk_r_count(dr_b))
    {

      IF_BUFFER_A_ENTIRELY_READ_LOAD_NEXT_FILE
      IF_BUFFER_B_ENTIRELY_READ_LOAD_NEXT_FILE

      // Merge buffer (comparaison et sauvergade dans buffer_out)
      while( index_buf_a < buffer_count(buf_a) && index_buf_b < buffer_count(buf_b))
      {
        if( buffer_cmp(buf_a, index_buf_a, buf_b, index_buf_b) < 0) {
          buffer_put_cpy(buf_out, buf_a, index_buf_a);
          index_buf_a++;
        } else {
          buffer_put_cpy(buf_out, buf_b, index_buf_b);
          index_buf_b++;
        }
        _if_buffer_is_full_flush_buffer_in_disk(buf_out, disk_output);
      }

      if(index_buf_a >= buffer_count(buf_a))
        index_dr_a++;

      if(index_buf_b >= buffer_count(buf_b))
        index_dr_b++;
    }
  }

  // Vidage du disk_a s'il reste des elements
  while(index_dr_a < disk_r_count(dr_a))
  {
    IF_BUFFER_A_ENTIRELY_READ_LOAD_NEXT_FILE

    while(index_buf_a < buffer_count(buf_a) ) {
      buffer_put_cpy(buf_out, buf_a, index_buf_a);
      index_buf_a++;
      _if_buffer_is_full_flush_buffer_in_disk(buf_out, disk_output);
    }

    index_dr_a++;
  }

  // Vidage du disk_b s'il reste des elements
  while( index_dr_b < disk_r_count(dr_b) )
  {
    IF_BUFFER_B_ENTIRELY_READ_LOAD_NEXT_FILE

    while(index_buf_b < buffer_count(buf_b) ) {
      buffer_put_cpy(buf_out, buf_b, index_buf_b);
      index_buf_b++;
      _if_buffer_is_full_flush_buffer_in_disk(buf_out, disk_output);
    }
    index_dr_b++;
  }

  // S'il reste des element dans le buffer de sortie
  if(!buffer_isEmpty(buf_out)) {

      disk_w_new_f(disk_output);
        buffer_write_file_from_descriptor( disk_w_get_current_f(disk_output), buf_out);
  }

}


void disk_manager_merge_step(struct diskManagerReader* dmr, struct diskManagerWriter* dmw,
  struct buffer*buf_a, struct buffer*buf_b, struct buffer*buf_out) {

  int index_a=0;
  int index_b=disk_manager_r_count(dmr)-1;

  // Merge les premier avec les derniers
  while( index_a < index_b) {

    if(index_a > 0)
      disk_manager_w_next_dw(dmw);

    struct diskReader* disk_a= disk_manager_r_item(dmr, index_a);
    struct diskReader* disk_b= disk_manager_r_item(dmr, index_b);
    struct diskWriter* disk_output= disk_manager_w_get_current_dw(dmw);

    disk_merge(disk_a, disk_b, buf_a, buf_b, buf_out, disk_output);

    index_a++;
    index_b--;
  }
}


void disk_sort_merge(struct diskReader* dr, struct buffer*buf_a, struct buffer*buf_b, struct buffer*buf_out, const char* path_output) {

  _make_output_dir(path_output);
  _make_folder_step(path_output);

  int step=0;

  struct diskManagerWriter* dmw= NULL;
  struct diskManagerReader* dmr= NULL;

  dmw= _create_step_dmw(path_output, step);

  disk_explode_and_sort_to_disk_manager(dr, buf_a, dmw);

  disk_manager_w_destroy(dmw);


  dmr= _create_step_dmr(path_output, step);
  step++;
  dmw= _create_step_dmw(path_output, step);

  disk_manager_merge_step(dmr, dmw, buf_a, buf_b, buf_out);
}
