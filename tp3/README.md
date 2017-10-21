# Attention

Ce projet a été conçu pour fonctionner avec make

Il est recommandé pour les utilisateurs n'aimant pas le terminal 
de manipuler le projet uniquement avec **eclipse** 

Des *builds targets* sont configurés, il suffit de double cliquer dessus
pour lancer la commande make correspondante (voir rapport)

# Commandes

* __make all__  : Compile tout les fichiers
* __make test__ : Lancement de la série de tests automatiques
* __make doc__  : Génération de la documentation (doxygen)
* __make rapport__ : Génération du rapport (latex)
* __make clean__ : Nettoyage du projet (supression des objets et binaires)
* __make demo-tp1__: Lancer la démo tp1
* __make demo-tp2__: Lancer la démo tp2
* __make rm-rs__: Supprime le fichier res/RS.txt

# Arborescence

* __bin__ : Binaire exécutable
  * __demo__ : Exécutable de démonstration
  * __test__ : Exécutable de test
* __doc__ : Documentation doxygen sous differents formats
* __rapport__ : Source du rapport
* __res__ : Ressources necessaire au projet (fichier de bdd)
* __script__  : Script utilisé pour les test
* __src__ : Source du projet
  * __bdd__   : Source de la bibliothéque
  * __demo__  : Sources des differentes démonstrations d'utilisation
  * __test__  : Sources des dufferents tests

* *sujet.pdf*  : Sujet du projet
* *README.md*  : C'est moi
* *rappot.pdf* : Le rapport du projet 


# Démonstration disponibles

Les sources de demosntration sont diponible dans: src/demo
Les exécutables de test sont généré dans: bin/demo
La commande make pour lancer les demo sont: make demo-tp1, make demo-tp2, make demo-tp3

* tp1-natural-join: Natural join R et S
* tp2-merge-join-without-duplicate: Merge join sans duplication 
* tp3-merge-join-with-duplicate: Merge join avec duplication 

# Tests disponibles

Les sources de test sont diponible dans: src/test
Les exécutables de test sont généré dans: bin/test
Le script de test est dans script/test.sh
La commande make pour lancer les test est: make test

* 0-storeFileBuffer: Ecriture d'un buffer dans un fichier
* 1-natural-join-1: Natural join R et S
* 2-natural-join-2: Natural join S et R
* 3-buf-quick-sort: Fonction de trie d'un buffer
* 4-merge-join-without-duplicate-1: Merge join sans duplication R et S
* 5-merge-join-without-duplicate-2: Merge join sans duplication S et R
* 6-merge-join-with-duplicate-1: Merge join avec duplication R et S
* 7-merge-join-with-duplicate-2: Merge join avec duplication S et R
