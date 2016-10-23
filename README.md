# Graphic_motor
Notre petit moteur graphique chérie



Tutorials qui peuvent être intéressant à lire :

http://loulou.developpez.com/tutoriels/moteur3d/partie1/ : Explication du fonctionnement d'OpenGL et de GLUT
http://www-evasion.imag.fr/Membres/Antoine.Bouthors/teaching/opengl/opengl1.html : Tutorial complet d'un moteur graphique. Peut être une bonne inspiration mais attention de ne pas tomber dans le copier/coller.

TODO List:
- Définir une norme de codage : Nom d'un objet commence à par une majuscule, nom d'une variable de classe commence par _ (?) etc... Possibilité d'utiliser la norme de codage de QT https://wiki.qt.io/Qt_Coding_Style
- Ecrire un fichier type.h : Je pense qu'il peut être intéressant de définir nos propres type avec un typedef. 
- Ecrire un objet Mesh : Ça risque d'être l'objet le plus complexe du moteur. Donc vaut mieux commencer simple puis ensuite le complexifier.
- Ecrire un objet Camera : Au début juste un truc simple pour pouvoir se déplacer et explorer l'unique triangle présent dans l'environnement.
- Ecrire un objet Renderer : J'avoue que je ne sais pas exactement quoi mettre dedans. C'est lui qui initialisera la scène et appelera les différentes fonctions de rafraichissement. (Mieux lire tutos).
