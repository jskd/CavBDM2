
/**
* TP n°: 3
*
* Titre du TP : Merge Join Duplicate
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
#include "hashtable.h"
#include "hexdump.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_EMPTY -1
#define NOT_IN_HASHTABLE -1

struct hashset {
  char key;
  char val;
};

/**
 * @brief Structure de donnée repésentant un buffer
 */
struct hashtable {
  /// Value: Valeur
  struct hashset* v;
  /// M: Nombre de bucket
  size_t m;
  /// Count: Nombre de valeur entrée
  size_t c;
};

/**
 * Creation d'une hashtable
 * @param[in] m Nombre de bucket
 */
struct hashtable* hashtable_create( size_t m ) {
  struct hashtable* hashtable= (struct hashtable*) malloc(sizeof(struct hashtable));
  hashtable->v= (struct hashset*) malloc(m * sizeof(struct hashset));
  // Set all set value as HASH_EMPTY
  for(size_t index=0; index < m; index++)
    hashtable->v[index].key= HASH_EMPTY;
  hashtable->m= m;
  hashtable->c=0;
  return hashtable;
}

/**
 * Hash fonction (linear)
 * @param[in] ht table de hash cible
 * @param[in] key clef
 */
static int _hash(struct hashtable* ht,char key) {
  return key % ht->m;
}

/**
 * Détruit le buffer
 * @param[in] buf buffer à détruire
 */
void hashtable_destroy(struct hashtable* ht) {
  free(ht->v);
  free(ht);
}

char hashtable_is_full(struct hashtable* ht) {
  return ht->c >= ht->m-1;
}


void hashtable_put(struct hashtable* ht, char key, char val) {
  // Erreur table remplie
  if(hashtable_is_full(ht))
    return;

  int index= _hash(ht, key);
  while(ht->v[index].key != HASH_EMPTY) {
    index= (index+1) % ht->m;
  }
  ht->v[index].val = val;
  ht->v[index].key = key;
  ht->c++;
}

char hashtable_get(struct hashtable* ht, char key) {
  int index= _hash(ht, key);
  while(ht->v[index].key != HASH_EMPTY && ht->v[index].key != key) {
    index= (index+1) % ht->m;
  }
  if(ht->v[index].key == key)
    return ht->v[index].val;
  else
    return NOT_IN_HASHTABLE;
}

//void hashtable_remove(struct hashtable* ht, char key) {
//}
