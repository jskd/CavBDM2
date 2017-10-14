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
#include "bdd.h"

int main(int argc, char** argv){

  // Store R.txt file in buf_r
  FILE* r_file = fopen("R.txt", "r");
  if (r_file == NULL)
    exit(1);
  struct buf* buf_r= buf_create(16);
  storeFileBuffer(r_file, buf_r);
  fclose(r_file);

  // Store S.txt file in buf_s
  FILE* s_file = fopen("S.txt", "r");
  if (s_file == NULL)
    exit(1);
  struct buf* buf_s= buf_create(16);
  storeFileBuffer(s_file, buf_s);
  fclose(s_file);

  buf_quicksort(buf_r);
  buf_quicksort(buf_s);

  // Store natural join of buf_r and buf_s in buf_rs
  struct buf* buf_rs= buf_create(16);
  merge_join(buf_r, buf_s, buf_rs);

  // Write buf_rs in RS.txt file
  FILE* rs_file = fopen("RS.txt", "w");
  if (rs_file == NULL)
    exit(1);
  writeBufferInFile(rs_file, buf_rs);
  fclose(rs_file);

  buf_dump(buf_rs);

  // Remove buf
  buf_destroy(buf_r);
  buf_destroy(buf_s);
  buf_destroy(buf_rs);

  exit(0);
}
