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
#include <stdlib.h>
#include <stdio.h>
#include "diskWriter.h"
#include "diskReader.h"
#include <string.h>

static const size_t _buf_size=   10;
static const size_t _buf_data_lenght= 2;
static const size_t _buf_mode= BUFFER_CHARACTERS;

#define NODE_MAX 3

struct btree_node {
  char  isLeaf;
  char* parent;
  int   n_value;
  char* key      [NODE_MAX];
  char* value    [NODE_MAX];
  char* savefile;
};

static void _btreenode_store(const struct btree_node* node) {
  FILE * pFile= fopen(node->savefile, "w+");
  fprintf(pFile, "Leaf: %d\n", node->isLeaf);
  fprintf(pFile, "N_Value: %d\n", node->n_value);
  fprintf(pFile, "Key:\n");
  for(int i=0; i< NODE_MAX; i++){
    fprintf(pFile, "%s\n", node->key[i]);
  }
  fprintf(pFile, "Value:\n");
  for(int i=0; i< NODE_MAX; i++){
    fprintf(pFile, "%s\n", node->value[i]);
  }
  fprintf(pFile, "Parent: \n");
  fprintf(pFile, "%s\n", node->parent);
  fclose(pFile);
}

struct btree_node* btreenode_create(const char* savefile) {

  struct btree_node* node= (struct btree_node*) malloc( sizeof(struct btree_node));

  node->isLeaf= 1;
  node->n_value= 0;
  node->parent= "";
  node->savefile= strdup(savefile);
  for(int i=0; i<NODE_MAX; i++) {
    node->key[i]= (char*) malloc( _buf_data_lenght + 1 );
    strcpy(node->key[i], "");
    node->value[i]= (char*) malloc( 255);
    strcpy(node->value[i], "");
  }
  _btreenode_store(node);
  return node;
}

struct btree_node* btreenode_insert(struct btree_node* node, const char* filepath)
{
  struct buffer* buf= buffer_read_file(filepath, _buf_size, _buf_data_lenght, _buf_mode);
  if(buf == NULL) {
    printf("Erreur lors de la lecture de %s.\n", filepath);
    return NULL;
  }

  if(node->n_value < NODE_MAX)
  {
    buffer_get(buf, 0, node->key[node->n_value]);
    node->key[node->n_value][2]= '\0';
    strcpy( node->value[node->n_value], filepath);
  }

  _btreenode_store(node);

  return node;
}



/*
struct btreenode* btreenode_create(const char* filepath, const char* savefile) {


}*/
/*
void btreenode_print(FILE* stream, const struct btreenode* node) {
  fprintf(stream, "Type: Leaf\n");
  fprintf(stream, "Label: %s\n", node->label);
  fprintf(stream, "FilePath: %s\n", node->filepath);
  fprintf(stream, "NodePath: %s\n", node->savefile);
}*/
