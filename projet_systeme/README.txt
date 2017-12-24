Projet ASR5 de Naudion Melvin et Perie Arthur

Commencez par : make

Pour utiliser le client : ./projet_client.exx --ip ip_serveur --port port_serveur
sans parametre supplementaire, une interface gtk s'ouvre pour specifier
ce qu'il lui manque (Presente dans le dossier "log")
Bug si gtk/htk.h n'est pas disponible sur l'ordinateur.
Il faut donc utiliser la deuxieme méthode avec les parametres

Si on ne rempli pas tous les champs, alors l'invite de commande demandera
automatiquement de les remplir si besoin

Possibilité d'utiliser le client avec des parametres pour lui specifier 
le destinataire, le sujet, l'expediteur ainsi que le corps du message
en utilisant les options specifiées dans --usage. Sinon le client
demande automatiquement ce qui n'a pas été mentionné

