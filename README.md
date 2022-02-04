# Bring Back Money v1.0

## Présentation

Bring Back Money est un jeu où vous interprétez le joueur correspondant au caractère ‘J’ dans une carte en 2 dimensions.  
Le but est de ramasser le plus de pièces tant que c’est possible, car des pièges ou encore des monstres sont présents dans vos alentours.  
Cachez-vous dans les buissons et certains monstres ne vous poursuivront plus. N'oubliez pas aussi de passer par votre cabane afin d’y déposer un maximum de pièces.   
  

Si vous finissez par perdre tous vos points de vie, le jeu s’arrête, vous demande votre nom d’aventurier et sauvegarde votre score afin d’être affiché sur le leaderboard local.   


## Compilation
Il n'y a pas encore de Makefile pour compiler automatiquement le projet
Munissez vous d'un compilateur et faites : 
```go
gcc -W -Wall src/main.c -o BringBackMoney.exe
```

## Jouer
Télécharger et éxecuter le programme BringBackMoney.exe


---

## Road Map :

### A faire :

- Finaliser et optimiser les monstres
- Développer une page leaderboard
- Checker le makefile
- Optimiser le menu

### Finit :

- Développer les monstres et leur déplacement :white_check_mark:

- Faire le menu (check ce qu'on peut faire avec curses) :white_check_mark:

- Finaliser l'apparation random de tout :white_check_mark:

- Developper les pièges :white_check_mark:

- Créer le systeme de dossier pour delivrable :white_check_mark:

- Remplacer l'init.h pour nouveau terminal avec curses :white_check_mark:

- Intégrer les déplacements dynamique avec curses :white_check_mark:

- Programmer de façon événementiel :white_check_mark:

- fetch avec le develop :white_check_mark:

- Refonte de l'init carte avec buissons :white_check_mark:

- Faire spawner aléatoirement joueur et sa cabane :white_check_mark:

- Définir la structure player sans global :white_check_mark:

- Revérifier certains détails sur les buissons :white_check_mark:

- mettre en place l'interface cabane :white_check_mark:

