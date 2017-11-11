/**
* TP n°: 3
*
* Titre du TP : Merge Join Duplicate
*
* Date : 21/10/17
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
#include "naturalJoin.h"
#include "buffer.h"

/**
 * nested_loop_join
 *
 * @param[in]  buf_a   relation externe
 * @param[in]  buf_b   relation interne
 * @param[out] buf_out resultat du nested_loop_join de buf_a et buf_b
 * @param[out] file    fichier de vidage de buf_out si overflow
 */
void nested_loop_join(const struct buffer* buf_a, const struct buffer* buf_b, struct buffer* buf_out, FILE* overflow_file) {
  for(int a=0; a< buffer_count(buf_a); a++) {
    for(int b=0; b< buffer_count(buf_b); b++) {
      if(buffer_cmp(buf_a, a, buf_b, b) == 0) {
        // Overflow vidage dans overflow_file
	if(buffer_count(buf_out) == buffer_size(buf_out) && overflow_file != NULL) {
          buffer_write_file_from_descriptor(overflow_file, buf_out);
          buffer_flush(buf_out);
	}
        buffer_put_cpy(buf_out, buf_a, a);
        break; // pass to next a
      }
    }
  }
}

void disk_nested_loop_join(const struct disk* disk_a, , const struct buffer* buf_b, struct buffer* buf_out, FILE* overflow_file) {

 char incr= 1;
 int b=0;
 int skip_reading=0; 

 buffer_read_file_from_descriptor( disk_item(disk, b),  buf_b);

 for(int a=0; a<disk_count(disk); a++) {
    // Lecture en va-et-vient de disk b
    while( b < disk_count(buf_b) && b > -1 ) {
      // Saut de lecture si le contenu est déjà dans le buffer
      if(skip_reading) 
        skip_reading= 0;
      else 
	buffer_read_file_from_descriptor( disk_item(disk, b),  buf_b);
      nested_loop_join(buf_a, buf_b, buf_out, overflow_file);
      b+= incr;
    }
    incr= incr == 1 ? -1 : 1; // va-et-vient
    skip_reading= 1; // activate skip
  }
}
