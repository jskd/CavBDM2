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


  struct hashtable* ht= hashtable_create( 10 );

  hashtable_put(ht, 8, 0);
  hashtable_put(ht, 18, 1);
  hashtable_put(ht, 29, 2);
  hashtable_put(ht, 39, 3);
  hashtable_put(ht, 49, 4);

  hashtable_print(ht);

  hashtable_destroy(ht);
}
