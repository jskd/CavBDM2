/**
* TP n°: 8
*
* Titre du TP : B+Tree
*
* Date : 5 Nec 2017
*
* Nom : Lefranc
* Prenom : Joaquim
* email : lefrancjoaquim@gmail.com
*
* Nom : Skoda
* Prenom : Jérôme
* email : contact@jeromeskoda.fr
*
* Nom : Bitout
* Prenom : Cécilia
* email : bitout.cecelia@gmail.com
*
* Remarques :
*/
#ifndef SRC_BDD_BTREE_H
#define SRC_BDD_BTREE_H

#include "diskReader.h"
#include "diskWriter.h"

struct btree_node;

/**
 * @brief Creation d'un B+tree
 */
struct btree_node* btreenode_create(struct diskWriter* dw);

/**
 * @brief Insertion d'un block
 */
void btreenode_insert(struct btree_node* root, const char* filepath, struct diskWriter* dw);

/**
 * @brief Recherche d'un noeud dans l'arbre
 */
void btreenode_search(struct btree_node* root, const char* value, char* file);

/**
 * @brief Chargement d'un B+tree (La racine est uniquement chargé en mémoire)
 */
struct btree_node* btree_load(struct diskReader* dw);

/**
 * @brief Impression d'un B+tree
 */
void print_btree(FILE* stream, const struct btree_node* node);

#endif
