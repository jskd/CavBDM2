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
#ifndef SRC_BDD_HASHTABLE_H
#define SRC_BDD_HASHTABLE_H

extern const char VAL_NOT_IN_HASHTABLE;

#include <stdio.h>
#include "buffer.h"
/**
 * @brief Structure de donnée repésentant une table de hash
 * Remarque: Structure caché! Ne pas initilialiser autrement
 * qu'avec les fonctions prévu à cet effet!
 */
struct hashtable;

/**
 * Creation d'une hashtable
 * @param[in] m Nombre de bucket
 */
struct hashtable* hashtable_create( size_t m );

/**
 * Suppression d'une hashtable
 * @param[in] hashtable
 */
void hashtable_destroy( struct hashtable* ht );

char hashtable_is_full(struct hashtable* ht);

char hashtable_put(struct hashtable* ht, char key, char val);

char hashtable_get(const struct hashtable* ht, char key);

void hashtable_remove(struct hashtable* ht, char key);

void hashtable_print(struct hashtable* ht);

char storeBufferToHashtable(struct buffer* buf, struct hashtable* ht);

/**
 * Hash fonction (linear)
 * @param[in] ht table de hash cible
 * @param[in] key clef
 */
int hash(const struct hashtable* ht,char key);

struct hashtable* storeFileInHashtable(const char* filename, size_t m);

#endif
