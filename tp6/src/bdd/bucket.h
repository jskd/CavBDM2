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
#ifndef SRC_BDD_BUCKET_H
#define SRC_BDD_BUCKET_H

#include <stdio.h>

struct bucket;

struct bucket* bucket_create(const char* filename);

void bucket_puts( struct bucket* bucket, const char* str);

#endif
