/**
* TP n°: 4
*
* Titre du TP : Hash Join
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

  struct hashtable* ht= hashtable_create(10);
  printf("hashtable_put k:3  v:1 return: %d\n", hashtable_put(ht, 3 , 1));
  printf("hashtable_put k:13 v:2 return: %d\n", hashtable_put(ht, 13, 2));
  printf("hashtable_put k:26 v:3 return: %d\n", hashtable_put(ht, 26, 3));
  printf("hashtable_put k:15 v:4 return: %d\n", hashtable_put(ht, 15, 4));
  printf("hashtable_put k:25 v:5 return: %d\n", hashtable_put(ht, 25, 5));

  hashtable_print(ht);

  printf("hashtable_remove 15\n");
  hashtable_remove(ht, 15);
  printf("hashtable_remove 13\n");
  hashtable_remove(ht, 13);

  hashtable_print(ht);

  printf("hashtable_get  3 return: %d\n", hashtable_get(ht, 3));
  printf("hashtable_get 26 return: %d\n", hashtable_get(ht, 26));
  printf("hashtable_get 25 return: %d\n", hashtable_get(ht, 25));

  hashtable_destroy(ht);
}
