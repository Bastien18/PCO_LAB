# Rapport labo03 PCO
## Loïc Brasey & Bastien Pillonel

### Introduction:
Ce laboratoire a pour but de gérer la simulation d'achat/fabrication d'item entre trois différents acteurs (mine, usine et grossiste). Il nous était donc demandé de faire l'implémentation de certaines méthodes des classes mine, factory et wholeseller ainsi que de gérer l'accès aux sections critiques.

### Conception:
La gestion des variables communes est le point clefs de ce labo. Nous avons décidé d'ajouter un attribut mutex à la superclasse seller. Ainsi les classes mine, factory et wholeseller ont chacune leur propre mutex qui sera utiliser pour éviter la mauvaise modification des variables money et stock[item] qui sont partagées.

Ci-dessous se trouve le détails de nos implémentation.

#### Mine
- Buy: 
    - Check de la validité de quantité demander ( > 0) et check du stock donc quantité de l'item à acheter > quantité demandé.
    - Determinbation du prix
    - Section critique (car accès au stock et argent => ressources communes):
      - mutex.lock
      - Encaisse l'achat
      - Retire du stock
      - mutex.unlock
    - Fin section critique
    - Si transaction ok retourne le prix payé sinon retourne 0
    
- Run:
  - Ajout de mutex autour lors du payement de l'employé et de l'incrémentation du stock
  - Ajout de la condition d'arrêt grâce au boolean working de la superclasse seller (donc de chaque mine/factory/wholeseller) => mis à false si endService appelé       (touche enter pressé dans console).


#### Wholeseller
- Buy:
    - Check si item différent de Spectacles && quantité demandé ok (dans les stocks et > 0)
        - Seciton critique:
            - mutex.lock
            - Encaisse l'achat
            - Retire du stock
            - mutex.unlock
        - Fin section critique
        - Retourne le prix ou 0 si transaction KO

- Buy_ressource:
    - Si pas assez d'argent pour achat
        - N'achète rien
    - Si assez d'argent
        - Seciton critique:
          - mutex.lock
          - Encaisse l'achat
          - Retire du stock
          - mutex.unlock
        - Fin section critique

- Run
    Ajout de la condition d'arrêt grâce au boolean working de la superclasse seller (donc de chaque mine/factory/wholeseller) => mis à false si endService appelé       (touche enter pressé dans console).


#### Factory
- Buy:
    - Contrôle item == item construit par la factory en question && quantité demandé est valide (dans les stocks et > 0)
    - Seciton critique:
      - mutex.lock
      - Encaisse l'achat
      - Retire du stock
      - mutex.unlock
    - Fin section critique
    - Retourne le prix ou 0 si transaction KO
    
- Order_ressource:
    - Itère sur les ressources necessaires pour build l'item :
        - Si pas assez d'item pour construire:
            - Détermine combien d'item acheter => tous ce qu'on peut la moitié de l'argent de la factory (max 5 items)   
            - Itére sur tous les wholeseller:
                - tentaive d'achat pour chaque wholeseller (prend le premier qui peut fournir)
                - Si bon pour l'achat :
                  - Seciton critique:
                      - mutex.lock
                      - Encaisse l'achat
                      - Retire du stock
                      - mutex.unlock
                  - Fin section critique

- Build_item:
    - Determine le prix de l'employé
    - Si pas assez d'argent pour payer l'employé où pas assez de ressource pour build l'item
        - Seciton critique:
          - mutex.lock
          - Paie l'employé
          - mutex.unlock
         - Fin section critique 
     - Construction de l'item (temps random)
     - Incrémente le compteur d'item (=> sert au stat)
        - Seciton critique:
          - mutex.lock
          - Incrémente stock d'item construit
          - Décrémente stock des ressources
          - mutex.unlock
         - Fin section critique 

- Run:
    Ajout de la condition d'arrêt grâce au boolean working de la superclasse seller (donc de chaque mine/factory/wholeseller) => mis à false si endService appelé       (touche enter pressé dans console).

### Test:
Après avoir laisser tourner le programme assez longtemps pour qu'au moins un item spectacles soit fabriqué nous avons arrêter le programme et bien constater un score de 1800/1800 comme attendu.
