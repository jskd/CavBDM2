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

/* Remarques : Ce fichier a été récuprer du site:
*   https://stackoverflow.com/questions/7775991/how-to-get-hexdump-of-a-structure-data#7776146
*   il a été réadapté dans le cadre du projet
*/
#ifndef SRC_BDD_HEXDUMP_H
#define SRC_BDD_HEXDUMP_H

void hexDump (char *desc, const void *addr, int len);

char printable_or_dot(char c);

#endif
