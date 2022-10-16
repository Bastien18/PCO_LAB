# Rapport Labo02_PCO_BRASEY_PILLONEL
1) Mesurez le gain de temps produit par votre version multi-threadée en faisant varier le nombre de threads. Que remarquez-vous ?

  | Nbr de thread | Temps [ms] |
  |----------|:-------------:|
  | 2 | 1479 |
  | 4 | 1513 |
  | 8 | 1594 |
  | 16 | 1495 |
  | 32 | 1508 |
  
  On a remarqué un gain de temps. Environ la moitié du temps par rapport a la version single thread du programme. Cependant l'augmentation du nombre de thread n'est pas facteur d'un temps d'execution plus court.

2) Le gain de vitesse est-il linéaire avec le nombre de threads ? (Indiquez le nombre de threads alloués à la VM, il peut être changé dans les settings, ainsi que le nombre de threads de votre machine). Il y a-t-il une différence pour les nombre premiers et non premiers ?

Aucune véritable variation pour le test avec nombre premier cela fait sens en sachant que tout les thread devront itérer jusqu'a la fin donc multiplier les threads ne fait que diviser le temps un peu plus le temps de chacun des threads 

- MultiThread nombre premier 99194853094755497
  | Nbr de thread | Temps [ms] |
  |----------|:-------------:|
  | 2 | 1479 |
  | 4 | 1513 |
  | 8 | 1594 |
  | 16 | 1495 |
  | 32 | 1508 |
  
- MultiThread nombre non-premier 23986452839716232
  | Nbr de thread | Temps [us] |
  |----------|:-------------:|
  | 2 | 1032 |
  | 4 | 1653 |
  | 8 | 1902 |
  | 16 | 1735 |
  | 32 | 4483 | 
