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
#include "../bdd/BTreeLeaf.h"
#include "../bdd/BTreeNode.h"

// input disk config
static const char* _file_r= "res/demo/tp8/R";
static const char* _path_output="res/demo/tp8/R-btree";

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
/*
  for(int i=0; i< disk_r_count(dr); i++) {
    disk_w_new_f(dw);
    btreeleaf_create( disk_r_item_path(dr, i) , disk_w_get_current_path(dw) );
  }


 struct btreeNode *root;


insertion(root, 12);
int ch=0;
searching(12,&ch, root);
printf("%d\n", ch );
*/

;
  struct btree_node* root= btreenode_create(dw);

  btreenode_insert( root, "res/demo/tp8/R/0.txt", dw);
  btreenode_insert( root, "res/demo/tp8/R/1.txt", dw);
  btreenode_insert( root, "res/demo/tp8/R/2.txt", dw);
  btreenode_insert( root, "res/demo/tp8/R/3.txt", dw);
  btreenode_insert( root, "res/demo/tp8/R/4.txt", dw);
  btreenode_insert( root, "res/demo/tp8/R/5.txt", dw);

  printf("insertion 6\n");
  btreenode_insert( root, "res/demo/tp8/R/6.txt", dw);
/*  disk_w_destroy(dw);
  disk_r_destroy(dr);*/

//  return 0;
}
