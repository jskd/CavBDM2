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
static const size_t _n_bucket= 64;

static const char* _dir_rs= "res/demo/tp6/RS-join";
static const char* _prefix_rs= "RS";
static const char* _ext_rs= ".txt";
static const int   _offset_rs= 0;

int main(int argc, char** argv){

  struct disk* disk_r= disk_create(_file_r, "r");
  if(disk_r == NULL) {
    printf("Erreur lors de la lecture de %s.\n", _file_r);
    return -1;
  }

  struct disk* disk_s= disk_create(_file_s, "r");
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

  printf("Creation de la table: stat Buffer R:\n");
  buffer_fprint_stat(stdout, buf_r);
  printf("Creation de la table: stat Buffer S:\n");
  buffer_fprint_stat(stdout, buf_s);
  printf("Creation de la table: stat Buffer RS:\n");
  buffer_fprint_stat(stdout, buf_rs);



  printf("\nRemive à zero des compteurs\n\n");
  buffer_stat_reset(buf_r);
  buffer_stat_reset(buf_s);
  buffer_stat_reset(buf_rs);

  struct disk_output* disk_o= disk_output_create(_dir_rs, _prefix_rs, _ext_rs, _offset_rs);

  table_bucket_join(tab_s, buf_s, tab_r, buf_r, buf_rs, disk_o);

  // Si n'est pas vide alors ecriture
  if(!buffer_isEmpty(buf_rs))
    buffer_write_file_from_descriptor(
      disk_output_get_current_file_descriptor(disk_o), buf_rs);

  printf("Jointure: stat Buffer R:\n");
  buffer_fprint_stat(stdout, buf_r);
  printf("Jointure: stat Buffer S:\n");
  buffer_fprint_stat(stdout, buf_s);
  printf("Jointure: stat Buffer RS:\n");
  buffer_fprint_stat(stdout, buf_rs);

  buffer_destroy(buf_r);
  buffer_destroy(buf_s);
  buffer_destroy(buf_rs);

  disk_destroy(disk_r);
  disk_destroy(disk_s);

  table_destroy(tab_r);
  table_destroy(tab_s);
}
