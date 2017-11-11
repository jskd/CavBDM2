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

#ifndef SRC_BDD_NESTEDLOOPJOIN_H
#define SRC_BDD_NESTEDLOOPJOIN_H

#include "bufferExtended.h"
#include "disk.h"

/**
 * Natual join (TP 1) Ne supporte pas les overflow
 *
 * @param[in]  buf_a   relation externe
 * @param[in]  buf_b   relation interne
 * @param[out] buf_out resultat du natural join de buf_a et buf_b
 */
void natural_join(const struct buffer* buf_a, const struct buffer* buf_b,
    struct buffer* buf_out);

/**
 * nested_loop_join (TP5) Supporte les overflow (ecrit dans un fichier)
 *
 * @param[in]  buf_a   relation externe
 * @param[in]  buf_b   relation interne
 * @param[out] buf_out resultat du nested_loop_join de buf_a et buf_b
 * @param[out] file    fichier de vidage de buf_out si overflow
 *                     (autorisation d'ecriture necessaire)
 */
void nested_loop_join(const struct buffer* buf_a, const struct buffer* buf_b,
    struct buffer* buf_out, FILE* overflow_file);

/**
 * nested_loop_join sur disk (TP5)
 * Supporte les overflow (ecrit dans un fichier)
 *
 * @param[in]  disk_a  relation externe
 * @param[in]  buf_a   buffer de sauvegarde utilisé par le disk a
 * @param[in]  disk_b  relation interne
 * @param[in]  buf_b   buffer de sauvegarde utilisé par le disk b
 * @param[out] buf_out resultat du nested_loop_join du disk_a et disk_b
 * @param[out] file    fichier de vidage de buf_out si overflow
 *                     (autorisation d'ecriture necessaire)
 */
void nested_loop_join_disk( const struct disk* disk_a, struct buffer* buf_a,
    const struct disk* disk_b, struct buffer* buf_b, struct buffer* buf_out,
    FILE* overflow_file);

#endif
