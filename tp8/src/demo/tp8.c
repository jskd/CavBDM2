/**
* TP n°: 5
*
* Titre du TP : Nested loop join disk
*
* Date : 10 Nov 2017
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

#include "../bdd/diskSortMerge.h"
#include "../bdd/BTree.h"
#include <limits.h>

// input disk config
static const char* _file_r= "res/demo/tp8/R";
static const char* _path_output="res/demo/tp8/R-btree";

static void _search_demo(struct btree_node* root, const char* key) {
  char search[PATH_MAX];
  btreenode_search(root, key, search) ;
  printf("Search %s: %s\n", key, search);

}

int main(int argc, char** argv){

 struct diskReader* dr= disk_r_create(_file_r);
  if(dr == NULL) {
    printf("Erreur lors de la lecture de %s.\n", _file_r);
    return -1;
  }

  struct diskWriter* dw= disk_w_create(_path_output, "", ".node");
  if(dw == NULL) {
    printf("Erreur lors de la lecture de %s.\n", _path_output);
    return -1;
  }

  struct btree_node* root= btreenode_create(dw);

  for(int i=0; i< disk_r_count(dr); i++) {
    printf("Insertion de %s.\n", disk_r_item_path(dr, i));
    btreenode_insert( root, disk_r_item_path(dr, i) , dw );
    printf("B+tree:\n");
    print_btree(stdout, root);
    printf("\n");
  }

  printf("Génération de l'arbre %s terminé.\n", _path_output);

  printf("\nExemple de recherche dans l'index:\n");
  _search_demo(root, "LE");
  _search_demo(root, "ZE");
  _search_demo(root, "BH");
  _search_demo(root, "NB");

}
