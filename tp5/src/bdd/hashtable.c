
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
// Pour getline (standard GNU)
#define _GNU_SOURCE

#include "buffer.h"
#include "hashtable.h"
#include "hexdump.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Set global
static const char _HASHSET_EMPTY= -1;
const char VAL_NOT_IN_HASHTABLE= -1;

struct hashset {
  char key;
  char val;
};

/**
 * @brief Structure de donnée repésentant une hashtable
 */
struct hashtable {
  /// Value: Valeur (liste de hashset)
  struct hashset* v;
  /// M: Nombre de bucket
  size_t m;
  /// Count: Nombre de valeur entrée
  size_t c;
};

/**
 * Hash fonction (linear)
 * @param[in] ht table de hash cible
 * @param[in] key clef
 */
int hash(const struct hashtable* ht,char key) {
  return key % ht->m;
}

/**
 * @brief Set hashset empty
 * @param[in] hs hashset
 */
static void _set_empty_hashset(struct hashset* hs) {
  memset(hs, _HASHSET_EMPTY, sizeof(struct hashset));
}

/**
 * Creation d'une hashtable
 * @param[in] m Nombre de bucket
 */
struct hashtable* hashtable_create( size_t m ) {
  struct hashtable* hashtable= (struct hashtable*) malloc(sizeof(struct hashtable));
  hashtable->v= (struct hashset*) malloc(m*sizeof(struct hashset));
  // Set all set value as HASH_EMPTY (pour le debug)
  memset(hashtable->v, _HASHSET_EMPTY, m*sizeof(struct hashset));
  hashtable->m= m;
  hashtable->c=0;
  return hashtable;
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


char hashtable_put(struct hashtable* ht, char key, char val) {

  // Erreur table remplie
  if(hashtable_is_full(ht))
    return -1;

  int index= hash(ht, key);
  while(ht->v[index].key != _HASHSET_EMPTY) {
    index= (index+1) % ht->m;
  }
  ht->v[index].val = val;
  ht->v[index].key = key;
  ht->c++;

  return 0;
}

char hashtable_get(const struct hashtable* ht, char key) {
  int index= hash(ht, key);
  while(ht->v[index].key != _HASHSET_EMPTY && ht->v[index].key != key) {
    index= (index+1) % ht->m;
  }
  if(ht->v[index].key == key)
    return ht->v[index].val;
  else
    return VAL_NOT_IN_HASHTABLE;
}



char storeBufferToHashtable(struct buf* buf, struct hashtable* ht) {
  if(buf_count(buf)+1 <= ht->m)
    return -1;

  for(int index=0; index< buf_count(buf); index++) {
    hashtable_put(ht, buf_val(buf, index), index);
  }
  return 0;
}

void hashtable_print(struct hashtable* ht) {
  printf("Hashtable c: %03lu, m: %03lu, v: [\n", ht->c, ht->m);
  for(int index=0; index < ht->m; index++) {
    printf("  [key:%03d(%c),val:%03d]\n", ht->v[index].key,
      printable_or_dot(ht->v[index].key), ht->v[index].val);
  }
  printf("]\n");
}

void hashtable_remove(struct hashtable* ht, char key) {
  // Remove hashset
  int index= hash(ht, key);
  while(ht->v[index].key != _HASHSET_EMPTY && ht->v[index].key != key) {
    index= (index+1) % ht->m;
  }

  // Key inexistante fin du remove
  if(ht->v[index].key == _HASHSET_EMPTY)
    return;

  _set_empty_hashset(&ht->v[index]);
  ht->c--;

  // Rehash
  index= (index+1) % ht->m;
  while(ht->v[index].key != _HASHSET_EMPTY) {
    struct hashset hs= ht->v[index];
    _set_empty_hashset(&ht->v[index]);
    hashtable_put(ht, hs.key, hs.val);
    index= (index+1)%ht->m;
  }
}



struct hashtable* storeFileInHashtable(const char* filename, size_t m) {

  FILE* file = fopen(filename, "r");
  if (file == NULL)
    return NULL;

  char* line = NULL;
  size_t len = 0;
  char rid   = 0;
  struct hashtable* ht= hashtable_create(m);
  while((getline(&line, &len, file)) != -1) {
    hashtable_put(ht, line[0], rid);
    rid++;
  }
  fclose(file);
  return ht;
}
