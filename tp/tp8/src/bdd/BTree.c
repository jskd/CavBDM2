/**
* TP n°: 8
*
* Titre du TP : B+Tree
*
* Date : 5 Nec 2017
*
* Nom : Lefranc
* Prenom : Joaquim
* email : lefrancjoaquim@gmail.com
*
* Nom : Skoda
* Prenom : Jérôme
* email : contact@jeromeskoda.fr
*
* Nom : Bitout
* Prenom : Cécilia
* email : bitout.cecelia@gmail.com
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

/**
 * @brief Permet de forcer l'écriture sur le disque
 */
static void _ffsync(FILE* file) {
  fflush(file);
  int fd= fileno(file);
  fsync(fd);
}

/**
 * @brief Test si l'insertion est possible
 */
char btreenode_can_insert_value_in_node(const struct btree_node* node) {
  return node->n_value < NODE_MAX;
}

/**
 * @brief Test si c'est le node root
 */
char btreenode_node_is_root(const struct btree_node* node) {
  return (strcmp(node->parent, "") == 0);
}

/**
 * @brief Affiche un noeud
 */
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

/**
 * @brief Ecrit dans le fichier
 */
static void _btreenode_store(const struct btree_node* node) {
  FILE * pFile= fopen(node->savefile, "w");
  _btreenode_print(pFile, node);
  fclose(pFile);
}

/**
 * @brief Ouvre l'arbre contenu dans un fichier
 */
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

/**
 * @brief Affiche un noeud
 */
void print_btreenode(FILE* stream, const struct btree_node* node, int tab, char last, char parent_last) {
  node= _btreenode_read_file(node->savefile);

  for(int i=0; i< tab; i++) {
    if(i == tab -1)
      if(last)
        fprintf(stream, "└── ");
      else
        fprintf(stream, "├── ");
    else if(parent_last && i == tab -2)
    fprintf(stream, "│   ");
    else
    fprintf(stream, "    ");
  }

  for(int i=0; i< node->n_value; i++) {
    if(i > 0)
      fprintf(stream, "%.*s ", BUF_DATA_LENGHT, node->key[i]);
    fprintf(stream, "%.*s ", PATH_MAX, node->value[i]);
  }
  fprintf(stream, "\n");

  if(!node->isLeaf) {
    for(int i=0; i< node->n_value; i++) {
      struct btree_node* current= _btreenode_read_file(node->value[i]);
        print_btreenode(stream ,current, tab+1, i ==  node->n_value-1, !last );
    }
  }
}

/**
 * @brief  Affiche l'arbre
 */
void print_btree(FILE* stream, const struct btree_node* node) {

fprintf(stream, "%.*s (root)\n", PATH_MAX, node->savefile);
  print_btreenode(stream, node, 1, 1, 1);

}

/**
 * @brief Création d'un nouveau noeud
 */
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

/**
 * @brief Deplace une valeur
 */
void btreenode_move_value(struct btree_node* dst, int idx_dst, struct btree_node* source, int idx_source) {
  strncpy(dst->key[idx_dst],   source->key[idx_source]  , BUF_DATA_LENGHT);
  strncpy(dst->value[idx_dst], source->value[idx_source], PATH_MAX       );
  dst->n_value++;

  strncpy(source->key[idx_source], "", BUF_DATA_LENGHT);
  strncpy(source->value[idx_source], "", PATH_MAX       );
  source->n_value--;

  _btreenode_store(source);
  _btreenode_store(dst);
}

/**
 * @brief Ajoute un enfant
 */
void btreenode_add_child(struct btree_node* parent, struct btree_node* child) {
  strncpy(parent->key[parent->n_value],   child->key[0]  , BUF_DATA_LENGHT);
  strncpy(parent->value[parent->n_value], child->savefile, PATH_MAX       );
  strncpy(child->parent, parent->savefile, PATH_MAX );
  parent->n_value++;
  parent->isLeaf= 0;

  _btreenode_store(parent);
  _btreenode_store(child);
}

/**
 * @brief Return right node
 */
struct btree_node* btreenode_slit_leaf(struct btree_node* left, struct diskWriter* dw) {

  struct btree_node* right= btreenode_create( dw );

  btreenode_move_value(right, 0, left, 2);

  right->isLeaf= left->isLeaf;

  _btreenode_store(left);
  _btreenode_store(right);

  return right;
}

/**
 * @brief Divise le noeud racine en deux et retourne le noeud de droite
 */
struct btree_node* btreenode_slit_root(struct btree_node* root, struct diskWriter* dw) {

  struct btree_node* left= btreenode_create( dw );
  struct btree_node* right= btreenode_create( dw );

  right->isLeaf= root->isLeaf;
  left->isLeaf= root->isLeaf;
  root->isLeaf= 0;

  btreenode_move_value(left, 0, root, 0);
  btreenode_move_value(left, 1, root, 1);
  btreenode_move_value(right, 0, root, 2);

  btreenode_add_child(root, left);
  btreenode_add_child(root, right);

  _btreenode_store(root);
  _btreenode_store(left);
  _btreenode_store(right);

  return right;
}

/**
 * @brief Insertion d'une valeure dans un noeud
 */
void btreenode_insert_value_in_node(struct btree_node* node, const char* key, const char* value) {
  strncpy(node->key[node->n_value], key, BUF_DATA_LENGHT);
  strncpy(node->value[node->n_value], value, PATH_MAX);
  node->n_value++;
  _btreenode_store(node);
}

/**
 * @brief Insertion d'un  noeud
 */
void btreenode_insert(struct btree_node* root, const char* filepath, struct diskWriter* dw)
{
  // Lecture de la 1ére valeur du fichier
  struct buffer* buf= buffer_read_file(filepath, _buf_size, _buf_data_lenght, _buf_mode);
  if(buf == NULL) {
    printf("Erreur lors de la lecture de %s.\n", filepath);
    return;
  }
  char key[BUF_DATA_LENGHT+1];
  buffer_get(buf, 0, key);
  buffer_destroy(buf);

  // Relecture de la racine et deplacement jusqu'à la feuille la plus à droite
  root= _btreenode_read_file(root->savefile);
  struct btree_node* current= root;
  while(current->isLeaf != 1) {
      current= _btreenode_read_file(current->value[ current->n_value-1 ] );
  }

  // Il reste de la place dans la feuille
  if(btreenode_can_insert_value_in_node(current)) {
    btreenode_insert_value_in_node(current, key, filepath);
  }
  // Pas de place et le noeud courrant est la racine
  else if(btreenode_node_is_root(current))
  {
    // Division et ajout à droite
    struct btree_node* right= btreenode_slit_root(current, dw);
    btreenode_insert_value_in_node(right, key, filepath);
  }
  // Pas de place et le noeud courrant n'est pas la racine
  else if(!btreenode_node_is_root(current))
  {
    // On divise la feuille
    struct btree_node* right= btreenode_slit_leaf(current, dw);
    btreenode_insert_value_in_node(right, key, filepath);

    // La racine n'est pas pleinne
    if(btreenode_can_insert_value_in_node(root))
    {
      btreenode_add_child(root, right);
    }
    // La racine est pleinne
    else
    {
      struct btree_node* right_root= btreenode_slit_root(root, dw);
      btreenode_add_child(right_root, right);
    }
  }
}

/**
 * @brief Recherche d'un noeud dans l'arbre
 */
void btreenode_search(struct btree_node* root, const char* value, char* file) {

  root= _btreenode_read_file(root->savefile);
  struct btree_node* current= root;


  int index=0;

  while(1)
  {
    // Parcour les noeuds jusqu'à dépassement de la clef
    for(index=0; index < current->n_value; index++)
      if(strcmp(value, current->key[ index ] ) < 0)
        break;

    // Decrement de l'index pour avoir la derniere key inferieur
    if(index > 0)
      index--;

    // Si ce n'est pas une feuille on retitére l'operation sur le noeuf fils
    if(current->isLeaf == 0)
      current= _btreenode_read_file(current->value[ index ]);
    else
    {
      strncpy(file, current->value[ index ], PATH_MAX );
      return;
    }
  }

}

struct btree_node* btree_load(struct diskReader* dr) {
   return _btreenode_read_file(disk_r_item_path(dr, 0));
}