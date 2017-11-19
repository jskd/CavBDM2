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

#include "../bdd/bufferExtended.h"
#include "../bdd/table.h"
#include "../bdd/disk.h"
#include "../bdd/nestedLoopJoin.h"

static const size_t _buf_size= 10;
static const size_t _data_lenght= sizeof(short);
static const char* _file_r= "res/demo/tp6/R";
static const char* _file_s= "res/demo/tp6/S";

static const char* _file_table_r= "res/demo/tp6/tableR";
static const char* _file_table_s= "res/demo/tp6/tableS";
static const size_t _n_bucket= 10;

static const char* _dir_rs= "res/demo/tp6/RS";
static const char* _prefix_rs= "RS";
static const char* _ext_rs= ".txt";
static const int   _offset_rs= 0;

int main(int argc, char** argv){

  struct disk* disk_r= disk_create(_file_r);
  if(disk_r == NULL) {
    printf("Erreur lors de la lecture de %s.\n", _file_r);
    return -1;
  }

  struct disk* disk_s= disk_create(_file_s);
  if(disk_s == NULL) {
    printf("Erreur lors de la lecture de %s.\n", _file_s);
    return -1;
  }

  struct table* tab_r= table_create(_n_bucket, _file_table_r);
  struct table* tab_s= table_create(_n_bucket, _file_table_s);

  struct buffer* buf_r  = buffer_create(_buf_size, _data_lenght, BUFFER_DECIMALS);
  struct buffer* buf_s  = buffer_create(_buf_size, _data_lenght, BUFFER_DECIMALS);
  struct buffer* buf_rs = buffer_create(_buf_size, _data_lenght, BUFFER_DECIMALS);

  disk_storeContentInTable(disk_s, buf_s, tab_s);
  disk_storeContentInTable(disk_r, buf_r, tab_r);

  printf("Creation de la table\n");
  printf("Buffer R:\n");
  buffer_fprint_stat(stdout, buf_r);
  printf("Buffer S:\n");
  buffer_fprint_stat(stdout, buf_s);
  printf("Buffer RS:\n");
  buffer_fprint_stat(stdout, buf_rs);
  printf("Table R:\n");
  table_fprint_stat(stdout, tab_r);
  printf("Table S:\n");
  table_fprint_stat(stdout, tab_s);
  printf("\n");

  printf("Remise à zero des compteurs\n");
  buffer_stat_reset(buf_r);
  buffer_stat_reset(buf_s);
  buffer_stat_reset(buf_rs);
  printf("\n");

  struct disk_output* disk_o= disk_output_create(_dir_rs, _prefix_rs, _ext_rs, _offset_rs);
  table_bucket_join(tab_r, buf_r, tab_s, buf_s, buf_rs, disk_o);

  // Si n'est pas vide alors ecriture
  if(!buffer_isEmpty(buf_rs))
    buffer_write_file_from_descriptor(
      disk_output_get_current_file_descriptor(disk_o), buf_rs);

  printf("Jointure\n");
  printf("Buffer R:\n");
  buffer_fprint_stat(stdout, buf_r);
  printf("Buffer S:\n");
  buffer_fprint_stat(stdout, buf_s);
  printf("Buffer RS:\n");
  buffer_fprint_stat(stdout, buf_rs);
  printf("\n");

  printf("Terminé, fichier dans %s.\n", _dir_rs);

  buffer_destroy(buf_r);
  buffer_destroy(buf_s);
  buffer_destroy(buf_rs);

  disk_destroy(disk_r);
  disk_destroy(disk_s);

  table_destroy(tab_r);
  table_destroy(tab_s);
}
