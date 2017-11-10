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
#ifndef SRC_BDD_BUFFER_H
#define SRC_BDD_BUFFER_H

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
 * @brief Quick sort buffer
 *
 * @param buf Trie le buffer en entrée
 */
void buf_quicksort(struct buf* buf);

/**
 * @brief Hex dump buffer
 * @param[in] buf buffer à trier
 */
void buf_dump(const struct buf* buf);

/**
 * @brief Ouvre un fichier
 *        Stoque son contenu dans un buffer
 *        Ferme le fichier
 *
 * @param[in]  File_name Fichier
 * @param[in] buffer_size Taille du buffer,
 *             si trop petit pour contenir le fichier entirerement
 *             alors le reste du fichier est ignoré
 *
 * @return buffer si NULL alors erreur de lecture du fichier
 *
 */
struct buf* storeFileBuffer(const char* file_name, size_t buffer_size);


/**
 * @brief Ouvre un fichier
 *        Ecrit le contenu du buffer dans le fichier
 *        Ferme le fichier
 *
 * @param[in]  File_name Fichier
 * @param[in]  buf       Buffer à écrire dans le fichier
 *
 * @return -1 si erreur dans l'ouverture du fichier
 *
 */
char writeBufferInFile(const char* file_name, const struct buf*);

/**
 * @brief Retourne la valeur à la position d'un buffer
 *
 * @param[in]  buf   Buffer
 * @param[in]  index Index of value
 *
 * @return Value
 */
char buf_val(const struct buf* buf, int index);

/**
 * @brief Retourne le nombre de caractere enregistré dans le buffer
 *
 * @param[in]  buf       Buffer
 *
 * @return Nombre de caractere enregistré
 */
size_t buf_count(const struct buf* buf);

#endif
