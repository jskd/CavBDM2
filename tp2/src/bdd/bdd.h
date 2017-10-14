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
*/
#include <stdio.h>
#include "quicksort.h"

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
void writeBufferInFile(FILE* fp, const struct buf* buf);

/**
 * Natual join
 *
 * @param[in]  buf_a   relation externe
 * @param[in]  buf_b   relation interne
 * @param[out] buf_out resultat du natural join de buf_a et buf_b
 */
void natural_join(const struct buf* buf_a, const struct buf* buf_b, struct buf* buf_out);

/**
 * @brief Merge join
 *
 * @param[in]  buf_a   relation externe
 * @param[in]  buf_b   relation interne
 * @param[out] buf_out resultat du merge_join
 */
void merge_join(const struct buf* buf_a, const struct buf* buf_b, struct buf* buf_out);

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
struct buf* storeFileBufferOC(const char* file_name, size_t buffer_size);


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
char writeBufferInFileOC(const char* file_name, const struct buf*);
