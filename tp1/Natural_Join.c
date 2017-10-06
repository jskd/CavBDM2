/**
* TP n°: 1
*
* Titre du TP : Join Array
*
* Date : 06/10/17
*
* Nom : Lefranc
* Prenom : Joaquim
* email : lefrancjoaquim@gmail.com
* 
* Nom : Skoda
* Prenom : Jérôme
* email : contact@jeromeskoda.fr
*
* Remarques : Code Block -> Trash. Makefile <3
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv){

	FILE* r_file;
	FILE* s_file;
	FILE* rs_file;

	r_file = fopen("R.txt", "r");
	if (r_file == NULL)
		exit(1);


	s_file = fopen("S.txt", "r");
	if (s_file == NULL)
		exit(1);

	rs_file = fopen("RS.txt", "w");
	if (rs_file == NULL)
		exit(1);

	char* r_line = NULL;
	char* s_line = NULL;
	size_t r_len = 0;
	size_t s_len = 0;

	// Parcours de R
	while (getline(&r_line, &r_len, r_file) != -1) {

		// Parcours de S
		while (getline(&s_line, &s_len, s_file) != -1) {

			// Si attribut identique
			if(strcmp(r_line, s_line) == 0){
				fprintf(rs_file, "%s", r_line);
			}
		}

		rewind(s_file); // Replace le curseur du fichier à 0
	}

	fclose(r_file);
	fclose(s_file);
	fclose(rs_file);

	exit(0);
}