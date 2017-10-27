/**
* TP n°: 4
*
* Titre du TP : Hash Merge
*
* Date : 27/10/17
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

#include "../bdd/hashtable.h"


int main(int argc, char** argv){


  struct hashtable* ht= hashtable_create(4);

  printf("hashtable_put 0 return: %d\n", hashtable_put(ht, 0, 0));
  printf("hashtable_put 1 return: %d\n", hashtable_put(ht, 1, 1));
  printf("hashtable_put 2 return: %d\n", hashtable_put(ht, 2, 2));
  printf("hashtable_put 3 return: %d\n", hashtable_put(ht, 3, 3));
  printf("hashtable_put 4 return: %d\n", hashtable_put(ht, 4, 4));

  hashtable_print(ht);
    
}
