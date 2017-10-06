/**
* TP n°: 1
*
* Titre du TP : Join Array
*
* Date : 06/10/17
*
* Nom : Lefranc
* Prenom : Joaquim
* email : lefrancjoaquim@gmail.com
*
* Nom : Skoda
* Prenom : Jérôme
* email : contact@jeromeskoda.fr
*
* Remarques : Code Block -> Trash. Makefile <3
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
TODO: struct

 buffer 
   v : value
   s : size
   c : count


  put_buffer ( struct buffer, value) 

    si c < s  add value return 0
    sinon return -1


  change storefilebuffer ( fp, buffer)
  write buffer in file (fp, buffer)
  natural join (buffer a, buffer b, buffer c)

*/



/**
 * @brief Store the first letter of each line intro buffer
 * @param[in]  reading file
 * @param[out] output buffer adress
 * @param[in]  output buffer max size
 * @return     size of output buffer
 */
size_t storeFileBuffer(FILE* fp, char* buffer, size_t buffer_s) {
  char* line = NULL;
  size_t len = 0;
  size_t wcount= 0;

  while((getline(&line, &len, fp)) != -1) {
    buffer[wcount]= line[0];
    wcount++;

    if(wcount >= buffer_s)
      break;
  }
  return wcount;
}

/**
 * Write buffer in file
 * TODO: La flemme
 */
void writeBufferInFile(FILE* fp, char* buffer, size_t size) {
  for(int i=0; i<size; i++)
    fprintf(fp, "%c\n", buffer[i]);
}

/**
 * Natual join
 * TODO: La flemme
 */
size_t natural_join(char* buf_a, size_t size_a, char* buf_b, size_t size_b, char* buf_out, size_t size_out) {
  size_t count=0;
  for(int a=0; a<size_a; a++) {
    for(int b=0; b<size_b; b++) {
      if(buf_a[a] == buf_b[b]) {
        buf_out[count]= buf_a[a];
        count++;
        if(count >= buf_out)
          return count;
        else
          break; // pass to next a
      }
    }
  }
  return count;
}


int main(int argc, char** argv){

  FILE* r_file;
  FILE* s_file;
  FILE* rs_file;

  r_file = fopen("R.txt", "r");
  if (r_file == NULL)
    exit(1);


  s_file = fopen("S.txt", "r");
  if (s_file == NULL)
    exit(1);

  rs_file = fopen("RS.txt", "w");
  if (rs_file == NULL)
    exit(1);


  char* a_buf = (char*) malloc( 10 * sizeof(char) );
  char* b_buf = (char*) malloc( 10 * sizeof(char) );

  size_t a_count= storeFileBuffer(r_file, a_buf, 10);
  size_t b_count= storeFileBuffer(s_file, b_buf, 10);


  char* join_buf = (char*) malloc( 10 * sizeof(char) );

  size_t join_count= natural_join(a_buf, a_count, b_buf, b_count, join_buf, 10);

  writeBufferInFile(rs_file, join_buf, join_count);

  fclose(r_file);
  fclose(s_file);
  fclose(rs_file);

  exit(0);
}
