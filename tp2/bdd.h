/**
* TP n°: 2
*
* Titre du TP : Merge Join
*
* Date : 13/10/17
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
*
* History: 146488d PASS (avec struct)
*          7d1b9de PASS (sans struct)
*/
#include <stdio.h>

/**
 * @brief Structure de donnée repésentant un buffer
 * Remarque: Structure caché! Ne pas initilialiser autrement
 * qu'avec les fonctions prévu à cet effet!
 */
struct buf;

/**
 * Creation d'un buffer
 * @param[in] size Taille du buffer
 */
struct buf* buf_create( size_t size );

/**
 * Détruit le buffer
 * @param[in] buf buffer à détruire
 */
void buf_destroy(struct buf* buf);

/**
 * Ajoute un caractere dans le buffer s'il reste de la place
 * @param[in] buf   buffer d'entrée
 * @param[in] value valeur à entrer
 * @return    0   succès
 *            -1  erreur: buffer plein
 */
char buf_put(struct buf* buf, char value);

/**
 * @brief Enregistre un le 1er caractére de chaque
 *        ligne d'un fichier dans un buffer
 *
 * @param[in]  Fichier d'entrée
 * @param[out] Buffer de sortie
 */
void storeFileBuffer(FILE* fp, struct buf* buf);

/**
 * Ecrit un buffer dans un fichier
 *
 * @param[out] fp  fichier de sortie
 * @param[in]  buf fichier d'entrée
 */
void writeBufferInFile(FILE* fp, struct buf* buf);

/**
 * Natual join
 *
 * @param[in]  buf_a   relation externe
 * @param[in]  buf_b   relation interne
 * @param[out] buf_out resultat du natural join de buf_a et buf_b
 */
void natural_join(struct buf* buf_a, struct buf* buf_b, struct buf* buf_out);

/**
 * @brief Merge join
 *
 * @param[in]  buf_a   relation externe
 * @param[in]  buf_b   relation interne
 * @param[out] buf_out resultat du merge_join
 */
void merge_join(struct buf* buf_a, struct buf* buf_b, struct buf* buf_out);
