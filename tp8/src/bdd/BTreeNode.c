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
#include <limits.h>




static const size_t _buf_size=   10;
static const size_t _buf_data_lenght= 2;
static const size_t _buf_mode= BUFFER_CHARACTERS;

#define NODE_MAX 3
#define BUF_DATA_LENGHT 2

struct btree_node {
  char  isLeaf;
  char  parent   [PATH_MAX];
  int   n_value;
  char  key      [NODE_MAX][BUF_DATA_LENGHT];
  char  value    [NODE_MAX][PATH_MAX];
  char* savefile;
};

static void _btreenode_store(const struct btree_node* node) {
  FILE * pFile= fopen(node->savefile, "w+");
  fprintf(pFile, "Leaf: %d\n", node->isLeaf);
  fprintf(pFile, "N_Value: %d\n", node->n_value);
  fprintf(pFile, "Key:\n");
  for(int i=0; i< NODE_MAX; i++){
    fprintf(pFile, "%.*s\n", BUF_DATA_LENGHT, node->key[i]);
  }
  fprintf(pFile, "Value:\n");
  for(int i=0; i< NODE_MAX; i++){
    fprintf(pFile, "%.*s\n", PATH_MAX, node->value[i]);
  }
  fprintf(pFile, "Parent: \n");
  fprintf(pFile, "%s\n", node->parent);
  fclose(pFile);
}

struct btree_node* btreenode_create(const char* savefile) {

  struct btree_node* node= (struct btree_node*) malloc( sizeof(struct btree_node));

  node->isLeaf= 1;
  strcpy(node->parent, "");
  node->n_value= 0;
  node->savefile= strdup(savefile);
  for(int i=0; i<NODE_MAX; i++) {
    strcpy(node->key[i], "");
    strcpy(node->value[i], "");
  }
  _btreenode_store(node);
  return node;
}











void btreenode_insert(struct btree_node* root, const char* filepath)
{

  struct buffer* buf= buffer_read_file(filepath, _buf_size, _buf_data_lenght, _buf_mode);
  if(buf == NULL) {
    printf("Erreur lors de la lecture de %s.\n", filepath);
    return;
  }

  if(root->n_value < NODE_MAX)
  {
    buffer_get(buf, 0, root->key[root->n_value]);
    strcpy( root->value[root->n_value], filepath);
    root->n_value++;
  }
  else
  {





     struct btree_node* slit1= btreenode_create("res/demo/tp8/R-slit2");

     memcpy(slit1->key[0],   root->key[0]  , BUF_DATA_LENGHT*2);
     memcpy(slit1->value[0], root->value[0], PATH_MAX*2       );
     slit1->n_value+=2;
     memcpy(slit1->parent, root->savefile, PATH_MAX);
     _btreenode_store(slit1);


     struct btree_node* slit2= btreenode_create("res/demo/tp8/R-slit3");
     memcpy(slit2->parent, root->savefile, PATH_MAX);
     memcpy(slit2->key[0],   root->key[2]  , BUF_DATA_LENGHT);
     memcpy(slit2->value[0], root->value[2], PATH_MAX);
     slit2->n_value++;

     buffer_get(buf, 0, slit2->key[slit2->n_value]);
     strcpy( slit2->value[slit2->n_value], filepath);
     slit2->n_value++;

     _btreenode_store(slit2);







    //       root
    //  slit1   slit2
    //
    memset(root->key[1],  0, BUF_DATA_LENGHT * 2);
    memset(root->value[1],0, PATH_MAX * 2);

    memcpy(root->key[0],   slit1->key[0]  , BUF_DATA_LENGHT);
    memcpy(root->value[0], slit1->savefile, PATH_MAX);

    memcpy(root->key[1],   slit2->key[0]  , BUF_DATA_LENGHT);
    memcpy(root->value[1], slit2->savefile, PATH_MAX);
    root->n_value= 2;

    root->isLeaf= 0;


  }


  _btreenode_store(root);

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
