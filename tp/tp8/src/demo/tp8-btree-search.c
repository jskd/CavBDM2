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
#include "../bdd/diskSortMerge.h"
#include "../bdd/BTree.h"
#include <limits.h>

// input disk config
static const char* _path_btree="res/demo/tp8/R-btree";

static void _search_demo(struct btree_node* root, const char* key) {
  char search[PATH_MAX];
  btreenode_search(root, key, search) ;
  printf("Search %s: %s\n", key, search);
}

int main(int argc, char** argv){

 struct diskReader* dr= disk_r_create(_path_btree);
  if(dr == NULL) {
    printf("Erreur lors de la lecture de %s.\n", _path_btree);
    return -1;
  }

  struct btree_node* tree = btree_load(dr);

  printf("Exemple de recherche dans l'index %s:\n", _path_btree);
  _search_demo(tree, "AG");
  _search_demo(tree, "DV");
  _search_demo(tree, "IF");
  _search_demo(tree, "LE");
  _search_demo(tree, "OO");
  _search_demo(tree, "RE");
  _search_demo(tree, "SS");
  _search_demo(tree, "XD");
  _search_demo(tree, "ZZ");
}
