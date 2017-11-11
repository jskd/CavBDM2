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
#ifndef SRC_BDD_BUFFER_EXTENDED_H
#define SRC_BDD_BUFFER_EXTENDED_H

#include <stdio.h>

/**
 * @brief Structure de donnée repésentant un buffer
 * Remarque: Structure caché! Ne pas initilialiser autrement
 * qu'avec les fonctions prévu à cet effet!
 */
struct buffer;

/**
 * Creation d'un buffer contigue
 * @param[in] size      Taille du buffer
 * @param[in] data_size Taille des données
 */
struct buffer* buffer_create( size_t size , size_t data_size );

/**
 * Détruit le buffer
 * @param[in] buf buffer à détruire
 */
void buffer_destroy(struct buffer* buf);


char buffer_put(struct buffer* buf, const void * data);

/**
 * @brief Quick sort buffer
 *
 * @param buf Trie le buffer en entrée
 */
void buffer_quicksort(struct buffer* buf);

/**
 * @brief Hex dump buffer
 * @param[in] buf buffer à trier
 */
void buffer_dump(const struct buffer* buf);

/**
 * @brief Ouvre un fichier
 *        Stoque son contenu dans un buffer
 *        Ferme le fichier
 *
 * @param[in]  File_name Fichier
 * @param[in]  buffer_size Taille du buffer,
 *             si trop petit pour contenir le fichier entirerement
 *             alors le reste du fichier est ignoré
 * @param[in]  data_lenght Taille des données ajouté
 *
 * @return buffer si NULL alors erreur de lecture du fichier
 *
 */
struct buffer* buffer_read_file(const char* file_name, size_t buffer_size, size_t data_lenght);


/**
 * @brief Remplis le buffer du contenu du fichier
 *        N'alloue pas de buffer et vide de buffer avant d'effectuer l'operation
 *
 * @param[in]  File_name Fichier
 * @param[out] buffer
 */
void buffer_read_file_from_descriptor(FILE* fp, struct buffer* buf);

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
char buffer_write_file(const char* file_name, const struct buffer*);



void buffer_write_file_from_descriptor(FILE* file, const struct buffer* buf);

/**
 * @brief Retourne la valeur à la position d'un buffer
 *
 * @param[in]  buf   Buffer
 * @param[in]  index Index of value
 *
 * @return Value
 */
char buffer_val(const struct buffer* buf, int index);

/**
 * @brief Retourne le nombre de caractere enregistré dans le buffer
 *
 * @param[in]  buf       Buffer
 *
 * @return Nombre de caractere enregistré
 */
size_t buffer_count(const struct buffer* buf);

size_t buffer_size(const struct buffer* buf);
char buffer_put_cpy(struct buffer* buf_dst, const struct buffer* buf_src, int src_index);
void buffer_flush(struct buffer* buf);

int buffer_cmp(const struct buffer* buf_a, int index_a, const struct buffer* buf_b, int index_b);
#endif
