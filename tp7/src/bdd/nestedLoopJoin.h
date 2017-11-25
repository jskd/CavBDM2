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

#ifndef SRC_BDD_NESTEDLOOPJOIN_H
#define SRC_BDD_NESTEDLOOPJOIN_H

#include "bufferExtended.h"
#include "diskReader.h"
#include "diskWriter.h"

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
  struct buffer* buf_out, struct disk_output* overflow_disk);

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
void nested_loop_join_disk( const struct diskReader* disk_a, struct buffer* buf_a,
  const struct diskReader* disk_b, struct buffer* buf_b, struct buffer* buf_out,
  struct disk_output* overflow_disk);

/**
 * table_bucket_join (TP6)
 * Fait la jointure de deux table
 *
 * @param[in]  tab_a   table a
 * @param[in]  buf_a   buffer de sauvegarde utilisé par la table a
 * @param[in]  tab_b   table b
 * @param[in]  buf_b   buffer de sauvegarde utilisé par le table b
 * @param[out] buf_out resultat du nested_loop_join du tab_a et tab_b
 * @param[out] file    fichier de vidage de buf_out si overflow
 *                     (autorisation d'ecriture necessaire)
 */
void table_bucket_join(const struct table* tab_a, struct buffer* buf_a,
  const struct table* tab_b, struct buffer* buf_b,
  struct buffer* buf_out, struct disk_output* overflow_disk);

#endif
