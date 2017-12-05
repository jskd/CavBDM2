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

#include <unistd.h>
static const size_t _buf_size=   10;
static const size_t _buf_data_lenght= 2;
static const size_t _buf_mode= BUFFER_CHARACTERS;

#define NODE_MAX 3
#define BUF_DATA_LENGHT 3

struct btree_node {
  int   isLeaf;
  char  parent   [PATH_MAX];
  int   n_value;
  char  key      [NODE_MAX][BUF_DATA_LENGHT];
  char  value    [NODE_MAX][PATH_MAX];
  char  savefile [PATH_MAX];
};

static void _ffsync(FILE* file) {
  fflush(file);
  int fd= fileno(file);
  fsync(fd);
}

char btreenode_can_insert_value_in_node(const struct btree_node* node) {
  return node->n_value < NODE_MAX;
}
char btreenode_node_is_root(const struct btree_node* node) {
  return strcmp(node->parent, "") == 0;
}

void _btreenode_print(FILE* stream, const struct btree_node* node) {

  _ffsync(stream);
  rewind (stream);

  fprintf(stream, "leaf: %d\n", node->isLeaf);
  fprintf(stream, "n_value: %d\n", node->n_value);
  fprintf(stream, "key: [\n");
  for(int i=0; i< NODE_MAX; i++){
    fprintf(stream, "\t%.*s\n", BUF_DATA_LENGHT, node->key[i]);
  }
  fprintf(stream, "]\n");
  fprintf(stream, "value: [\n");
  for(int i=0; i< NODE_MAX; i++){
    fprintf(stream, "\t%.*s\n", PATH_MAX, node->value[i]);
  }
  fprintf(stream, "]\n");
  fprintf(stream, "root: %d\n", btreenode_node_is_root(node));
  fprintf(stream, "parent: %.*s\n", PATH_MAX, node->parent);

  _ffsync(stream);
}

static void _btreenode_store(const struct btree_node* node) {
  FILE * pFile= fopen(node->savefile, "w");
  _btreenode_print(pFile, node);
  fclose(pFile);
}

struct btree_node* _btreenode_read_file(const char* file) {

  struct btree_node* node= (struct btree_node*) malloc( sizeof(struct btree_node));

  FILE * stream= fopen(file, "r");

  _ffsync(stream);

  int isRoot =0;
  fscanf(stream, "leaf: %d\n", &node->isLeaf);
  fscanf(stream, "n_value: %d\n", &node->n_value);
  fscanf(stream, "key: [\n");
  for(int i=0; i< NODE_MAX; i++){
    if(i < node->n_value) fscanf(stream, "\t%s\n", node->key[i]);
    else                  fscanf(stream, "\t\n");
  }
  fscanf(stream, "]\n");
  fscanf(stream, "value: [\n");
  for(int i=0; i< NODE_MAX; i++){
    if(i < node->n_value) fscanf(stream, "\t%s\n", node->value[i]);
    else                  fscanf(stream, "\t\n");
  }
  fscanf(stream, "]\n");
  fscanf(stream, "root: %d\n", &isRoot);
  if(!isRoot)
    fscanf(stream, "parent: %s\n", node->parent);
  else {
    fscanf(stream, "parent: \n");
    strncpy(node->parent, "", PATH_MAX       );
  }

  _ffsync(stream);
  fclose(stream);

  strcpy(node->savefile, file);

  return node;
}


struct btree_node* btreenode_create(struct diskWriter* dw) {

  struct btree_node* node= (struct btree_node*) malloc( sizeof(struct btree_node));

  disk_w_new_f(dw);
  strcpy(node->savefile, disk_w_get_current_path(dw));

  node->isLeaf= 1;
  strcpy(node->parent, "");
  node->n_value= 0;
  for(int i=0; i<NODE_MAX; i++) {
    strcpy(node->key[i], "");
    strcpy(node->value[i], "");
  }
  _btreenode_store(node);
  return node;
}



// Return right node
struct btree_node* btreenode_slit_leaf(struct btree_node* left, struct diskWriter* dw) {

  struct btree_node* right= btreenode_create( dw );

  // copy last value in right
  memcpy(right->key[0],   left->key[2]  , BUF_DATA_LENGHT);
  memcpy(right->value[0], left->value[2], PATH_MAX       );
  right->n_value++;

  // Remove last item of left
  strncpy(left->key[2], "", BUF_DATA_LENGHT);
  strncpy(left->value[2], "", PATH_MAX);
  left->n_value--;

  right->isLeaf= left->isLeaf;

  _btreenode_store(left);
  _btreenode_store(right);

  return right;
}





struct btree_node* btreenode_slit_root(struct btree_node* root, struct diskWriter* dw) {

  struct btree_node* left= btreenode_create( dw );
  struct btree_node* right= btreenode_create( dw );



  // copy 1er et 2eme value in right
  strncpy(left->key[0],   root->key[0]  , BUF_DATA_LENGHT);
  strncpy(left->value[0], root->value[0], PATH_MAX       );

  strncpy(left->key[1],   root->key[1]  , BUF_DATA_LENGHT);
  strncpy(left->value[1], root->value[1], PATH_MAX       );
  left->n_value= 2;

  // copy last value in right
  strncpy(right->key[0],   root->key[2]  , BUF_DATA_LENGHT);
  strncpy(right->value[0], root->value[2], PATH_MAX       );
  right->n_value= 1;

  // Vidage de root
  for(int i=0; i<NODE_MAX; i++) {
    strncpy(root->key[i], "", BUF_DATA_LENGHT);
    strncpy(root->value[i], "", PATH_MAX);
  }
  root->n_value= 0;

  // Add left in root
  strncpy(root->key[0],   left->key[0]  , BUF_DATA_LENGHT);
  strncpy(root->value[0], left->savefile, PATH_MAX       );
  strncpy(left->parent,  root->savefile,  PATH_MAX );
  root->n_value++;

  // Add right in root
  strncpy(root->key[1],   right->key[0]  , BUF_DATA_LENGHT);
  strncpy(root->value[1], right->savefile, PATH_MAX       );
  strncpy(right->parent, root->savefile, PATH_MAX );
  root->n_value++;
  root->isLeaf= 0;


  _btreenode_store(root);
  _btreenode_store(left);
  _btreenode_store(right);

  return root;
}



void btreenode_insert_value_in_node(struct btree_node* node, const char* key, const char* value) {
  strncpy(node->key[node->n_value], key, BUF_DATA_LENGHT);
  strncpy(node->value[node->n_value], value, PATH_MAX);
  node->n_value++;
  _btreenode_store(node);
}




void btreenode_insert_node(struct btree_node* root, struct btree_node* child) {

  btreenode_insert_value_in_node(root, child->key[0], child->savefile);
}


void btreenode_insert(struct btree_node* root, const char* filepath, struct diskWriter* dw)
{

  struct buffer* buf= buffer_read_file(filepath, _buf_size, _buf_data_lenght, _buf_mode);
  if(buf == NULL) {
    printf("Erreur lors de la lecture de %s.\n", filepath);
    return;
  }

  char key[BUF_DATA_LENGHT+1];
  buffer_get(buf, 0, key);
  buffer_destroy(buf);


  while(1) {

    struct btree_node* current= root;

    while(current->isLeaf != 1) {
        current= _btreenode_read_file(current->value[ current->n_value-1 ] );
    }

    // Il reste de la place dans la feuille
    if(btreenode_can_insert_value_in_node(current)) {
      btreenode_insert_value_in_node(current, key, filepath);
      break;
    }
    else
    {
      // La feuille est la racine : slit root
      if(btreenode_node_is_root(current)) {
        btreenode_slit_root(current, dw);
      }
      else
      {
        struct btree_node* right= btreenode_slit_leaf(current, dw);
        btreenode_insert_node(root, right);
        break;

      }
    }

  }

}
