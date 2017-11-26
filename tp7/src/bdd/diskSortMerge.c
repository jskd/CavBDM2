#include "buffer.h"
#include "diskManagerWriter.h"
#include "diskManagerReader.h"
#include "diskWriter.h"
#include "diskReader.h"
#include <limits.h>
#include <sys/stat.h>
#include "rmrf.h"

static const char* _folder_step= "steps";
static const char* _step_prefix= "step-";
static const char* _dir_sort_prefix= "block";
static const char* _dir_sort_suffixe= "";
static const char* _file_prefixe= "";
static const char* _file_suffixe= ".txt";

static void _make_folder_step(const char* path_output) {
  char dirname[PATH_MAX];
  sprintf(dirname, "%s-%s", path_output, _folder_step);
  rmrf(dirname);
  mkdir(dirname, 0777);
}

static void _make_output_dir(const char* path_output) {
  rmrf(path_output);
  mkdir(path_output, 0777);
}

static void _sprint_pathname_step(const char* path_step, int step, char* output) {
  sprintf(output, "%s-%s/%s%03d", path_step, _folder_step, _step_prefix, step);
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


static void _disk_manager_r_dump_step(struct diskManagerReader* dmr, const char* path_step, int step) {
  char dirname[PATH_MAX];
  sprintf(dirname, "%s-%s/%s%03d/dump.txt", path_step, _folder_step, _step_prefix, step);
  FILE* outfile= fopen(dirname, "w+");
  disk_manager_r_dump(outfile, dmr);
}

static void _disk_explode_and_sort_to_disk_manager(struct diskReader* dr, struct buffer* buf, struct diskManagerWriter* dmw) {
  for(int index=0; index < disk_r_count(dr); index++) {
      buffer_read_file_from_descriptor(disk_r_item(dr, index), buf);
      buffer_quicksort(buf);
      if(index > 0)
        disk_manager_w_next_dw(dmw);
      disk_w_new_f(disk_manager_w_get_current_dw(dmw));
      buffer_write_file_from_descriptor(disk_w_get_current_f(disk_manager_w_get_current_dw(dmw)), buf);
  }
}

// Fait un merge de deux disk
static void _disk_merge(struct diskReader* dr_a, struct diskReader* dr_b,
  struct buffer* buf_a, struct buffer* buf_b, struct buffer* buf_out,
  struct diskWriter* disk_output) {

  int index_dr_a=0;
  int index_dr_b=0;
  int index_buf_a=0;
  int index_buf_b=0;

  buffer_flush(buf_a);
  buffer_flush(buf_b);
  buffer_flush(buf_out);

  if(index_dr_a < disk_r_count(dr_a))
    buffer_read_file_from_descriptor(disk_r_item(dr_a, index_dr_a), buf_a);

  if(index_dr_b < disk_r_count(dr_b))
    buffer_read_file_from_descriptor(disk_r_item(dr_b, index_dr_b), buf_b);

  // Tant que l'on a pas parcourut tout les disque enntiérement
  while( index_dr_b < disk_r_count(dr_b) || index_dr_a < disk_r_count(dr_a))
  {

    // Les deux disque ne sont pas entiérement parcourut
    if( index_dr_a < disk_r_count(dr_a) && index_dr_b < disk_r_count(dr_b))
    {
      if( buffer_cmp(buf_a, index_buf_a, buf_b, index_buf_b) < 0) {
        buffer_put_cpy(buf_out, buf_a, index_buf_a);
        index_buf_a++;
      } else {
        buffer_put_cpy(buf_out, buf_b, index_buf_b);
        index_buf_b++;
      }
    }
    // Il reste des element non parcourut dans disque a
    else if( index_dr_a < disk_r_count(dr_a))
    {
      buffer_put_cpy(buf_out, buf_a, index_buf_a);
      index_buf_a++;
    }
    // Il reste des element non parcourut dans disque b
    else if( index_dr_b < disk_r_count(dr_b))
    {
      buffer_put_cpy(buf_out, buf_b, index_buf_b);
      index_buf_b++;
    }

    // Le buffer a à été entirément parcout on charge le prochain bloque
    if(index_buf_a >= buffer_count(buf_a)) {
      index_dr_a++;
      if(index_dr_a < disk_r_count(dr_a)) {
        buffer_read_file_from_descriptor(disk_r_item(dr_a, index_dr_a), buf_a);
        index_buf_a= 0;
      }
    }

    // Le buffer b à été entirément parcout on charge le prochain bloque
    if(index_buf_b >= buffer_count(buf_b)) {
      index_dr_b++;
      if(index_dr_b < disk_r_count(dr_b)) {
        buffer_read_file_from_descriptor(disk_r_item(dr_b, index_dr_b), buf_b);
        index_buf_b= 0;
      }
    }

    // Si le buffer d'ecriture est plein, on le vide dans un bloque
    if(buffer_isFull(buf_out)) {
      disk_w_new_f(disk_output);
      buffer_write_file_from_descriptor( disk_w_get_current_f(disk_output), buf_out);
      buffer_flush(buf_out);
    }
  }

  // s'il reste des elements dans le buffer de sortie
  if(!buffer_isEmpty(buf_out)) {
    disk_w_new_f(disk_output);
    buffer_write_file_from_descriptor( disk_w_get_current_f(disk_output), buf_out);
    buffer_flush(buf_out);
  }
}

// Fait une step de merge
static void _disk_manager_merge_step(struct diskManagerReader* dmr, struct diskManagerWriter* dmw,
  struct buffer*buf_a, struct buffer*buf_b, struct buffer*buf_out) {

  int index=0;

  // Merge deux par deux (parralelisable)
  while( index+1 < disk_manager_r_count(dmr)) {

    if(index > 0)
      disk_manager_w_next_dw(dmw);

    struct diskReader* disk_a= disk_manager_r_item(dmr, index);
    struct diskReader* disk_b= disk_manager_r_item(dmr, index+1);
    struct diskWriter* disk_output= disk_manager_w_get_current_dw(dmw);

    _disk_merge(disk_a, disk_b, buf_a, buf_b, buf_out, disk_output);

    index+=2;
  }

  // S'il reste un bloque
  if(index < disk_manager_r_count(dmr)) {
    struct diskReader* disk= disk_manager_r_item(dmr, index);
    if(index > 0)
      disk_manager_w_next_dw(dmw);
    disk_w_copy(disk, disk_manager_w_get_current_dw(dmw), buf_out);
  }

}


void disk_sort_merge(struct diskReader* dr, struct buffer*buf_a, struct buffer*buf_b, struct buffer*buf_out, const char* path_output) {

  _make_output_dir(path_output);
  _make_folder_step(path_output);

  int step=0;
  int nb_block=0;

  struct diskManagerWriter* dmw= NULL;
  struct diskManagerReader* dmr= NULL;

  dmw= _create_step_dmw(path_output, step);

  _disk_explode_and_sort_to_disk_manager(dr, buf_a, dmw);

  step++;

  nb_block= disk_manager_w_count(dmw);

  disk_manager_w_destroy(dmw);

  while(nb_block > 2)
  {
    dmr= _create_step_dmr(path_output, step-1);

    _disk_manager_r_dump_step(dmr, path_output, step-1);

    dmw= _create_step_dmw(path_output, step);

    _disk_manager_merge_step(dmr, dmw, buf_a, buf_b, buf_out);

    nb_block= disk_manager_w_count(dmw);

    disk_manager_w_destroy(dmw);
    disk_manager_r_destroy(dmr);

    step++;
  }

  // Dernier step dans l'ouput dir cette fois
  if(nb_block == 2)
  {
    dmr= _create_step_dmr(path_output, step-1);

    _disk_manager_r_dump_step(dmr, path_output, step-1);

    struct diskReader* disk_a= disk_manager_r_item(dmr, 0);
    struct diskReader* disk_b= disk_manager_r_item(dmr, 1);
    struct diskWriter* disk_output= disk_w_create(path_output, _file_prefixe, _file_suffixe);

    _disk_merge(disk_a, disk_b, buf_a, buf_b, buf_out, disk_output);

    struct diskReader* disk_output_r= disk_r_create(path_output);

    char dirname[PATH_MAX];
    sprintf(dirname, "%s-dump.txt", path_output);

    FILE* f_dump= fopen(dirname ,"w+");
    disk_r_dump( f_dump,  disk_output_r);
    fclose(f_dump);
  }
}
