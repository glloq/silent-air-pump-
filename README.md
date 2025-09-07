# silent air pump
on va faire une pompe air la plus silencieuse possible afin de simuler des poumons humain dans le but de jouer des instruments a vents 

## Contraintes 

- Il faut permette un aflux d'air autour de 20 litres / min.
- il faut permettre de faire varier le debit d'air le plus rapidement possible => a voir pour mettre ca coté instrument ?
- il faut un flux d'air le plus lisse possible.
- il faut ateindre une pression statique variable
- il faut permetre de mettre tout le systeme dans un boite en bois 


## choix techniques 

Nous utiliserons des systemes de pistons qui envoient l'air que dans la partie sans le bras du piston.
pour avoir un systeme qui envoi un air avec le moins de pulsation possible, et eviter l'utilisation de reservoir trop gros nous devrons utiliser entre 6 a 10 pistons.

pour des raisons economique, nous viserons 8 pistons pour avoir un flux d'air instantantané d'environ 20l ( en prenant en compte les fuites et pertes )
![courbe flux air](https://raw.githubusercontent.com/glloq/silent-air-pump-/refs/heads/main/courbe%208%20pistons.png)

il faudra limiter les vitesse de deplacement des pistons au maximum pour limiter les bruis d'air
on poura viser un moteur qui tourne autour de 30 rpm au maximum ( moteur avec reducteur et couple elevée ) on devra enssuite adapter la vitesse de rotation en fonction de l'etat de la reserve de lissage 

![courbe flux air](https://github.com/glloq/silent-air-pump-/blob/main/schemas%20principe.png)


Il faudra definir le volume minimal de la reserve de lissage pour permettre une atenuation des accouts entre pistons et aussi en fonction du temps de reaction du systeme de pompes =>  un volume autour de 0.5l a 1.5l devrais suffire mais un plus gors volmue permet de limiter les efforts sur le moteur 
Idealement on pourait viser autour de 2 litres au minimum 

