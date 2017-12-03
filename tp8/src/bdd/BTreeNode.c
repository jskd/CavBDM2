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
  int  isLeaf;
  char  parent   [PATH_MAX];
  int   n_value;
  char  key      [NODE_MAX][BUF_DATA_LENGHT];
  char  value    [NODE_MAX][PATH_MAX];
  char  savefile [PATH_MAX];
};

static void _btreenode_print(FILE* stream, const struct btree_node* node) {
rewind (stream);
  fprintf(stream, "Leaf: %d\n", node->isLeaf);
  fprintf(stream, "N_Value: %d\n", node->n_value);
  fprintf(stream, "Key:\n");
  for(int i=0; i< NODE_MAX; i++){
    fprintf(stream, "%.*s\n", BUF_DATA_LENGHT, node->key[i]);
  }
  fprintf(stream, "Value:\n");
  for(int i=0; i< NODE_MAX; i++){
    fprintf(stream, "%.*s\n", PATH_MAX, node->value[i]);
  }
  fprintf(stream, "Parent: \n");
  fprintf(stream, "%.*s\n", PATH_MAX, node->parent);
  fflush(stream);
}

static void _btreenode_store(const struct btree_node* node) {
  FILE * pFile= fopen(node->savefile, "w+");
  _btreenode_print(pFile, node);
  fclose(pFile);
}



static struct btree_node* _btreenode_read_file(const char* file) {
  FILE * pFile= fopen(file, "r");
  rewind (pFile);

  struct btree_node* node= (struct btree_node*) malloc( sizeof(struct btree_node));

  fscanf(pFile, "Leaf: %d\n", &node->isLeaf);
  fscanf(pFile, "N_Value: %d\n", &node->n_value);
  fscanf(pFile, "Key:\n");
  for(int i=0; i< NODE_MAX; i++){
    fscanf(pFile, "%s\n", node->key[i]);
  }
  fscanf(pFile, "Value:\n");
  for(int i=0; i< NODE_MAX; i++){
    fscanf(pFile, "%s\n", node->value[i]);
  }
  fscanf(pFile, "Parent: \n");
  fscanf(pFile, "%s\n", node->parent);
  fclose(pFile);
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











void btreenode_insert(struct btree_node* root, const char* filepath, struct diskWriter* dw)
{

  struct buffer* buf= buffer_read_file(filepath, _buf_size, _buf_data_lenght, _buf_mode);
  if(buf == NULL) {
    printf("Erreur lors de la lecture de %s.\n", filepath);
    return;
  }


  struct btree_node* current= root;

   _btreenode_print(stdout, current);

  while(current->isLeaf == 0) {
      current= _btreenode_read_file(current->value[ current->n_value-1 ] );
  }



   _btreenode_print(stdout, current);



  if(current->n_value < NODE_MAX)
  {
    buffer_get(buf, 0, current->key[current->n_value]);
    strcpy( current->value[current->n_value], filepath);
    current->n_value++;


             _btreenode_store(current);

  }
  else
  {
     if(strcmp(current->parent, "") != 0) {


       struct btree_node* parent= _btreenode_read_file( current->parent);


       if(strcmp(parent->savefile, root->savefile) ==0){
         parent= root;
       }







       if(parent->isLeaf == 0) {


         // Creation de right
         struct btree_node* right= btreenode_create( dw);

         memcpy(right->parent,   parent->savefile, PATH_MAX);
         memcpy(right->key[0],   current->key[2]  , BUF_DATA_LENGHT);
         memcpy(right->value[0], current->value[2], PATH_MAX);
         right->n_value++;

         buffer_get(buf, 0, right->key[right->n_value]);
         strcpy( right->value[right->n_value], filepath);
         right->n_value++;

         _btreenode_store(right);

         // Supression des valeur de left

         memset(current->key[2],   0  , BUF_DATA_LENGHT);
         memset(current->value[2], 0, PATH_MAX);
         current->n_value--;

         _btreenode_store(current);

        //    parent
        //  current   right
        //


        memcpy(parent->key[ 2],   right->key[0]  , BUF_DATA_LENGHT);
        memcpy(parent->value[ 2], right->savefile, PATH_MAX);


        parent->n_value= 3;




        _btreenode_store(parent);




       }
     }
     else
     {
       struct btree_node* left= btreenode_create( dw );

       memcpy(left->key[0],   current->key[0]  , BUF_DATA_LENGHT*2);
       memcpy(left->value[0], current->value[0], PATH_MAX*2       );
       left->n_value+=2;
       memcpy(left->parent, current->savefile, PATH_MAX);
       _btreenode_store(left);


       struct btree_node* right= btreenode_create( dw);
       memcpy(right->parent, current->savefile, PATH_MAX);
       memcpy(right->key[0],   current->key[2]  , BUF_DATA_LENGHT);
       memcpy(right->value[0], current->value[2], PATH_MAX);
       right->n_value++;

       buffer_get(buf, 0, right->key[right->n_value]);
       strcpy( right->value[right->n_value], filepath);
       right->n_value++;

       _btreenode_store(right);

      //    current
      //  left   right
      //
      memset(current->key[1],  0, BUF_DATA_LENGHT * 2);
      memset(current->value[1],0, PATH_MAX * 2);

      memcpy(current->key[0],   left->key[0]  , BUF_DATA_LENGHT);
      memcpy(current->value[0], left->savefile, PATH_MAX);

      memcpy(current->key[1],   right->key[0]  , BUF_DATA_LENGHT);
      memcpy(current->value[1], right->savefile, PATH_MAX);
      current->n_value= 2;

      current->isLeaf= 0;


      _btreenode_store(current);

     }

  }


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
