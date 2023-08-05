# Projet Todo List en C++

Un projet simple de gestion de liste de tâches en C++, implémenté en utilisant des fichiers pour le stockage des tâches.

## Fonctionnalités

- Affichage de la liste des tâches avec un état de coche pour chaque tâche (cochée ou non cochée).
- Ajout de nouvelles tâches avec une description et une date.
- Cocher/Décocher une tâche pour marquer son état d'accomplissement.
- Supprimer une tâche de la liste en fonction de son numéro.


## Utilisation

1. Cloner le projet : `git clone https://github.com/Dr4ke-Sm0G/TODO-List.git`
2. Compiler le code : `g++ TODO-List.cpp -o todo_list`
3. Exécuter le programme : `./todo_list`

## Format de fichier de sauvegarde

Le programme stocke les tâches dans un fichier `todo.txt` sous le format suivant :

0 | Tâche 1 | 2023-08-05
1 | Tâche 2 | 2023-08-06
2 | Tâche 3 | 2023-08-07


Le premier chiffre (0 ou 1) représente l'état de coche de la tâche (non cochée ou cochée), suivi de la description de la tâche et de sa date d'échéance.

## Remarques

- Le programme utilise des codes de couleurs pour améliorer l'affichage dans le terminal. Assurez-vous d'exécuter le programme sur un terminal qui prend en charge les couleurs ANSI. ( Windows )

## Auteur

Yassine Chahid `https://github.com/Dr4ke-Sm0G`


