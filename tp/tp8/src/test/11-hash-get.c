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


  struct hashtable* ht= hashtable_create(5);
  printf("hashtable_put k:10 v:10 return: %d\n", hashtable_put(ht, 10, 10));
  printf("hashtable_put k:5  v:20 return: %d\n", hashtable_put(ht, 5, 20));
  printf("hashtable_put k:15 v:0  return: %d\n", hashtable_put(ht, 15, 0));

  hashtable_print(ht);

  printf("hashtable_get  5 return: %d\n", hashtable_get(ht, 5));
  printf("hashtable_get 10 return: %d\n", hashtable_get(ht, 10));
  printf("hashtable_get 15 return: %d\n", hashtable_get(ht, 15));
  printf("hashtable_get 20 return: %d\n", hashtable_get(ht, 20));

  hashtable_destroy(ht);
}
