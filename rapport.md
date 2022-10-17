# Rapport Labo02_PCO_BRASEY_PILLONEL
## DESIGN
### PrimeNumberDetector::isPrime

  Pour le fonction simple thread nous faisons une boucle qui returne false si l'on trouve un nombre qui divise le nombre à examiner et qui retourne true si l'on a essayé tous les diviseurs jusqu'à la racine du nombre à examiner.
  
  ```
  if(number < 2) return 0;
    uint64_t denominator = 2;
    uint64_t root = (uint64_t) std::sqrt(number);
    while (true) {
        if(!(number % denominator))return 0;
        if(denominator > root)return 1;
        ++denominator;
    }
  ```
### PrimeNumberDetectorMultiThread::isPrime
Pour cette partie nous avons décider de séparer la fonction en deux:
La première partie sert à créer un vecteur de Pco_thread qui executent la fonction threadPrime(décrite un peu plus bas) et attend que tous les threads finissent leurs propre execution puis retourné le résultat stocké dans l'attribut finded.
``` 
bool PrimeNumberDetectorMultiThread::isPrime(uint64_t number) {
    std::vector<PcoThread> v;

    // Init. all threads
    for(size_t i =0 ; i < N_THREAD; ++i){
        v.emplace_back(&PrimeNumberDetectorMultiThread::threadPrime,this,number,i);
   }

    // Waiting all the threads
    for(auto&  thread : v)
        thread.join();
    // Return if all  the thread havent found a divider
    return !finded;

 }
```

La deuxième partie, la fonction threadPrime, sert à détecter un diviseur dans une range de taille = env. sqrt(nombre à examiner) / nombre de thread. Chaque thread examinera une range consécutive à un autre de 2 à sqrt(nombre à examiner). Lorsqu'un thread a trouvé un diviseur il met l'attribut finded à true ce qui fera automatiquement sortir les autres threads de leurs iteration car l'attribut est checker dans la condition de boucle. Une fois que le compteur de thread à atteint le nombre de thread on reset le compteur ainsi que le flag ready.

``` 
void PrimeNumberDetectorMultiThread::threadPrime(uint64_t number, size_t id){

    // init made by the first thread
    if(id == 0){
        finded = false;
        root = sqrt(number);
        ready = true;
    }
    // Waiting first thread has done the init
    while(!ready);

    // Calculating the range to process
    uint64_t start = (root-2) / (long double)N_THREAD * id +2;
    uint64_t end = (root-2) / (long double)N_THREAD * (id+1) +2;

    // Search for a divider
    for(uint64_t i = start; i < end and !finded; ++i){
        if(!(number % i))finded = true;
    }

    //counting wich thread is the last
    ++end_counter;

    //if last must dinit the program
    if(end_counter == N_THREAD){
        end_counter = 0;
        ready = false;
    }
}
```

## TEST
### 1) Mesurez le gain de temps produit par votre version multi-threadée en faisant varier le nombre de threads. Que remarquez-vous ?
  Simple test en prenant le nombre premier de base dans le fichier main.cpp (99194853094755497) afin de comparer le temps entre la méthode single thread et la méthode multi thread.

  | Nbr de thread | Temps single thread [ms] | Temps multi thread [ms] |
  |----------|:-------------:|:-------------:|
  | 2 | 2745 | 1479 |
  | 4 | 2778 | 1513 |
  | 8 | 2715 | 1594 |
  | 16 | 2743 | 1495 |
  | 32 | 2784 | 1508 |
  
  On a remarqué un gain de temps. Environ la moitié du temps par rapport a la version single thread du programme. Cependant l'augmentation du nombre de thread n'influence pas la vitesse d'execution.

### 2) Le gain de vitesse est-il linéaire avec le nombre de threads ? (Indiquez le nombre de threads alloués à la VM, il peut être changé dans les settings, ainsi que le nombre de threads de votre machine). Il y a-t-il une différence pour les nombre premiers et non premiers ?

Après quelques recherches afin de savoir où trouver le nombre de thread utilisés par notre VM, nous sommes arrivés à la conclusion qu'un seul thread était utiliser par core alloué à la machine. Ma machine ayant déjà énorement de peine à faire tourner virtual box en lui allouant un seul core sur les 4 à dispostion, nous décidons de ne pas allouer plus de core que necessaire. Toutefois nous avons vu qu'il était possible de demander plus de thread que le nombre disponible (utilise le timeslicing) nous changerons donc simplement la variable nthreads dans le main.cpp.

  - Multithread nombre premier:

  Nombre 433494437
  
  | Nbr de thread | Temps [us] |
  |----------|:-------------:|
  | 2 | 2918 |
  | 4 | 1426 |
  | 8 | 3733 |
  | 16 | 1631 |
  | 32 | 2236 |
  
  Nombre 68720001023
  
  | Nbr de thread | Temps [us] |
  |----------|:-------------:|
  | 2 | 4049 |
  | 4 | 3814 |
  | 8 | 28722 |
  | 16 | 19373 |
  | 32 | 4856 |

  Nombre 99194853094755497
  
  | Nbr de thread | Temps [ms] |
  |----------|:-------------:|
  | 2 | 1479 |
  | 4 | 1513 |
  | 8 | 1594 |
  | 16 | 1495 |
  | 32 | 1508 |
  
  Aucune véritable variation pertinente pour ce test. Cela fait sens en sachant que tout les thread devront itérer jusqu'a la fin donc augmenter le nombre de threads ne fait que diminuer un peu plus le temps de chaque thread mais en ayant plus de thread. Nous avons quand même eu deux valeur bien plus grande lors du second test que nous ne savons pas vraiment expliquer. Une raison possible est peut être ce timeslicing car nous avions vu que cela pouvait causer des problèmes lors de l'execution du code.
  
- MultiThread nombre non-premier 23986452839716232
  | Nbr de thread | Temps [us] |
  |----------|:-------------:|
  | 2 | 1032 |
  | 4 | 1653 |
  | 8 | 1902 |
  | 16 | 1735 |
  | 32 | 4483 | 
  
  Pour cette partie, on remarque une augmentation de la valeur de temps en augmentant le nombre de thread. Néanmois ces résultats ne nous semble pas significatifs car les temps mesurés sont très bas. 
