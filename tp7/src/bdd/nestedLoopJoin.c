/**
* TP n°: 5
*
* Titre du TP : Nested loop join disk
*
* Date : 10 Nov 2017
*
* Nom : Lefranc
* Prenom : Joaquim
* email : lefrancjoaquim@gmail.com
*
* Nom : Skoda
* Prenom : Jérôme
* email : contact@jeromeskoda.fr
*
* Remarques :
*/
#include "nestedLoopJoin.h"
#include "bufferExtended.h"
#include "table.h"
#include "diskReader.h"
#include "diskWriter.h"

// See header
void natural_join(const struct buffer* buf_a, const struct buffer* buf_b, struct buffer* buf_out) {
  nested_loop_join(buf_a, buf_b, buf_out, NULL);
}

// See header
void nested_loop_join(const struct buffer* buf_a, const struct buffer* buf_b, struct buffer* buf_out, struct disk_output* overflow_disk) {
  for(int a=0; a< buffer_count(buf_a); a++) {
    for(int b=0; b< buffer_count(buf_b); b++) {
      if(buffer_cmp(buf_a, a, buf_b, b) == 0) {
        // Overflow vidage dans overflow_file
        if(buffer_isFull(buf_out) && overflow_disk != NULL) {
          buffer_write_file_from_descriptor( disk_output_get_current_file_descriptor(overflow_disk), buf_out);
          disk_output_next_file(overflow_disk);
          buffer_flush(buf_out);
        }
        buffer_put_cpy(buf_out, buf_a, a);
        break; // pass to next a
      }
    }
  }
}

// See header
void nested_loop_join_disk( const struct diskReader* disk_a, struct buffer* buf_a,
    const struct diskReader* disk_b, struct buffer* buf_b,
    struct buffer* buf_out, struct disk_output* overflow_disk)
{
  char incr= 1;
  int b=0;
  int skip_reading=0;

  for(int a=0; a<disk_r_count(disk_a); a++) {
    buffer_read_file_from_descriptor( disk_r_item(disk_a, a),  buf_a);
    // Lecture en va-et-vient de disk b
    while( b < disk_r_count(disk_b) && b > -1 ) {
      // Saut de lecture si le contenu est déjà dans le buffer
      if(skip_reading)
        skip_reading= 0;
      else
        buffer_read_file_from_descriptor( disk_r_item(disk_b, b),  buf_b);

      nested_loop_join(buf_a, buf_b, buf_out, overflow_disk);
      b+= incr;
    }
    incr= incr == 1 ? -1 : 1; // va-et-vient
    b+= incr; // annule le dépacement
    skip_reading= 1; // activate skip
  }
}

void table_bucket_join(const struct table* tab_a, struct buffer* buf_a,
  const struct table* tab_b, struct buffer* buf_b,
  struct buffer* buf_out, struct disk_output* overflow_disk) {

    if(table_get_n_bucket(tab_a) != table_get_n_bucket(tab_b)) {
      printf("Impossible de faire le table join sur des table n'ayant pas\
        le même nombre de bucket\n");
      return;
    }

    for(int bucket_index=0; bucket_index< table_get_n_bucket(tab_a); bucket_index++) {

       struct diskReader* disk_a= create_disk_from_bucket(tab_a, bucket_index);
       struct diskReader* disk_b= create_disk_from_bucket(tab_b, bucket_index);

       nested_loop_join_disk( disk_a, buf_a, disk_b, buf_b, buf_out, overflow_disk);

       disk_r_destroy(disk_a);
       disk_r_destroy(disk_b);
    }
}
