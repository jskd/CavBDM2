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
#ifndef SRC_BDD_HASHTABLE_H
#define SRC_BDD_HASHTABLE_H

#include <stdio.h>

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

#endif
