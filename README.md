## Analyseur de Fréquence de Lettres avec Fils et Sémaphores

Ce programme en C est conçu pour analyser la fréquence d'apparition des lettres dans un fichier texte. Il utilise une approche basée sur des processus fils pour gérer le traitement des données, permettant ainsi une meilleure gestion des ressources et un traitement simultané des informations.

### Fonctionnalités principales

- **Lecture de Fichiers** : Le programme lit un fichier texte spécifié par l'utilisateur.
- **Traitement par Lignes** : Il traite un nombre spécifique de lignes à partir d'une ligne de départ donnée, facilitant le traitement de grands fichiers.
- **Histogramme de Fréquence** : Il génère un histogramme des occurrences des lettres de l'alphabet (minuscules) et crée des fichiers de sortie périodiques avec ces informations.
- **Gestion d'Erreurs** : Des vérifications sont effectuées pour s'assurer que les fichiers sont correctement ouverts et traités.

### Utilisation

Pour compiler et lancer, utiliser le makefile

- taper : " make " pour supprimer les fichiers

- taper : " lancer1 " pour lancer le fichier avec 1 processus et cela compilera avant

- taper : " compil " pour compiler tous les fichiers dont vous avez besoin pour lancer le code
- pour lancer le code taper : "./pere nomDuFichier.txt nomFichierGénéré nbProcessus"