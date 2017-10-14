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
*/

/*
* Remarques : Ce fichier a été récuprer du site:
*   http://www.zentut.com/c-tutorial/c-quicksort-algorithm/
*   il a été réadapté dans le cadre du projet
*/

#include <stdio.h>
#include <stdlib.h>

void swap(char *x, char *y)
{
  char temp;
  temp = *x;
  *x = *y;
  *y = temp;
}

int choose_pivot(char i,char j)
{
  return((i+j) /2);
}

void quicksort(char* list, int m, int n)
{
  int key,i,j,k;
  if( m < n)
  {
    k = choose_pivot(m,n);
    swap(&list[m],&list[k]);
    key = list[m];
    i = m+1;
    j = n;
    while(i <= j)
    {
      while((i <= n) && (list[i] <= key))
        i++;
      while((j >= m) && (list[j] > key))
        j--;
      if( i < j)
        swap(&list[i],&list[j]);
    }
    /* swap two elements */
    swap(&list[m],&list[j]);

    /* recursively sort the lesser list */
    quicksort(list,m,j-1);
    quicksort(list,j+1,n);
  }
}
