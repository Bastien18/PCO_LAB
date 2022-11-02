# Rapport labo03 PCO
## Loïc Brasey & Bastien Pillonel

### Introduction:

### Conception:

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

- Run:



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

- Run:

### Test:

### Conclusion:
