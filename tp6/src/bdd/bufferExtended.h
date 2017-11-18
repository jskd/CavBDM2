/**
* TP n°: 5
*
* Titre du TP : Nested loop join disk
*
* Date : 10 Nov 2017
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

typedef enum {
  BUFFER_CHARACTERS,
  BUFFER_DECIMALS
} buffer_file_mode;


/**
 * Creation d'un buffer contigue
 * @param[in] size Taille du buffer
 * @param[in] num  Taille des données en octet
 * @param[in] mode Mode de fonctionnement des sortie fichier
 */
struct buffer* buffer_create( size_t size , size_t num, buffer_file_mode mode );

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
struct buffer* buffer_read_file(const char* file_name, size_t buffer_size, size_t data_lenght, buffer_file_mode mode);


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


/**
 * Ecrit le contenu d'un buffer dans un fichier
 */
void buffer_write_file_from_descriptor(FILE* file, const struct buffer* buf);

/**
 * @brief Copie la valeur d'une entrée d'un buffer dans le block memoire
 *        destination
 *
 * @param[in]  buf   Buffer
 * @param[in]  index Index of value
 * @param[out] destination
 */
void buffer_get(const struct buffer* buf, int index,  void* destination);

/**
 * @brief Retourne le nombre de caractere enregistré dans le buffer
 *
 * @param[in]  buf       Buffer
 *
 * @return Nombre de caractere enregistré
 */
size_t buffer_count(const struct buffer* buf);

/**
 * Retourne la taille du buffer
 */
size_t buffer_size(const struct buffer* buf);

/**
 * Copy la src_index valeur de buf_src et la stoque dans buf_dst (à la dernière position)
 *
 * @param[out] buf_dst  buffer de destination
 * @param[in] buf_src  buffer source
 * @param[in] src_index  index du buffer source à copier
 * @return    0   succès
 *            -1  erreur: buffer incompatible
 *            -2  erreur: buffer plein
 */
char buffer_put_cpy(struct buffer* buf_dst, const struct buffer* buf_src, int src_index);

/**
 * Vide le buffer
 */
void buffer_flush(struct buffer* buf);

/**
 *  Compares 2 buffer value:
 *  <0 lower value in buf_a than in buf_b
 *  0 equal
 *  >0 greater value in buf_a than in buf_b
 */
int buffer_cmp(const struct buffer* buf_a, int index_a, const struct buffer* buf_b, int index_b);

/**
 * Retourne si le buffer est complet
 * @return    1   complet
 *            0 non complet
 */
char buffer_isFull(const struct buffer* buf);

/**
 * Retourne si le buffer est vide
 * @return    0 vide
 *            1 contien des données
 */
char buffer_isEmpty(const struct buffer* buf);


/**
 * Affiche les valeurs
 */
void buffer_printValue(const struct buffer* buf);

/**
 * Retourne le mode de fonctionnement du buffer
 */
int buffer_mode(const struct buffer* buf);

/**
 * Retourne la taille en octet de chaque données
 */
size_t buffer_datasize(const struct buffer* buf);

#endif
