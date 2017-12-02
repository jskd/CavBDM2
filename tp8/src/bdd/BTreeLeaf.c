/**
* TP n°: 6
*
* Titre du TP :
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
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>


#include <stdlib.h>
#include <stdio.h>
#include "diskWriter.h"
#include "diskReader.h"
#include <string.h>
#include "buffer.h"

static const size_t _buf_size=   10;
static const size_t _buf_data_lenght= 2;
static const size_t _buf_mode= BUFFER_CHARACTERS;

struct BTreeLeaf {
  char* label;
  char* filepath;
  char* savefile;
};

static void _btreeleaf_store(const struct BTreeLeaf* node) {
  FILE * pFile= fopen(node->savefile, "w+");
  fprintf(pFile, "L\n");
  fprintf(pFile, "%s\n", node->label);
  fprintf(pFile, "%s\n", node->filepath);
  fclose(pFile);
}

struct BTreeLeaf* btreeleaf_create(const char* filepath, const char* savefile) {

  struct buffer* buf= buffer_read_file(filepath, _buf_size, _buf_data_lenght, _buf_mode);
  if(buf == NULL) {
    printf("Erreur lors de la lecture de %s.\n", filepath);
    return NULL;
  }

  struct BTreeLeaf* node= (struct BTreeLeaf*) malloc( sizeof(struct BTreeLeaf));

  node->filepath= strdup(filepath);
  node->savefile= strdup(savefile);
  node->label = (char*) calloc(0, _buf_data_lenght+1);

  buffer_get(buf, 0, node->label);
  buffer_destroy(buf);

  _btreeleaf_store(node);

  return node;
}

void btreeleaf_print(FILE* stream, const struct BTreeLeaf* node) {
  fprintf(stream, "Type: Leaf\n");
  fprintf(stream, "Label: %s\n", node->label);
  fprintf(stream, "FilePath: %s\n", node->filepath);
  fprintf(stream, "NodePath: %s\n", node->savefile);
}
