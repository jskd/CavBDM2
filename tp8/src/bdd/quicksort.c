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

/*
* Remarques : Ce fichier a été récuprer du site:
*   http://www.zentut.com/c-tutorial/c-quicksort-algorithm/
*   il a été réadapté dans le cadre du projet
*/

#include <stdio.h>
#include <stdlib.h>

void char_swap(char *x, char *y)
{
  char temp;
  temp = *x;
  *x = *y;
  *y = temp;
}

void short_swap(short *x, short *y)
{
  short temp;
  temp = *x;
  *x = *y;
  *y = temp;
}


int char_choose_pivot(char i,char j)
{
  return((i+j) /2);
}

int short_choose_pivot(short i, short j)
{
  return((i+j) /2);
}

void char_quicksort(char* list, int m, int n)
{
  int key,i,j,k;
  if( m < n)
  {
    k = char_choose_pivot(m,n);
    char_swap(&list[m],&list[k]);
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
        char_swap(&list[i],&list[j]);
    }
    /* swap two elements */
    char_swap(&list[m],&list[j]);

    /* recursively sort the lesser list */
    char_quicksort(list,m,j-1);
    char_quicksort(list,j+1,n);
  }
}


void short_quicksort(short* list, int m, int n)
{
  int key,i,j,k;
  if( m < n)
  {
    k = short_choose_pivot(m,n);
    short_swap(&list[m],&list[k]);
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
        short_swap(&list[i],&list[j]);
    }
    /* swap two elements */
    short_swap(&list[m],&list[j]);

    /* recursively sort the lesser list */
    short_quicksort(list,m,j-1);
    short_quicksort(list,j+1,n);
  }
}
