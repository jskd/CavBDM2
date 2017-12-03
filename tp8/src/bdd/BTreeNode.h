/**
 * TP n°: 6
 *
 * Titre du TP :
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
#ifndef SRC_BDD_BTREENODE_H
#define SRC_BDD_BTREENODE_H

struct btree_node;

struct btree_node* btreenode_create(struct diskWriter* dw);

void btreenode_insert(struct btree_node* root, const char* filepath, struct diskWriter* dw);

#endif
