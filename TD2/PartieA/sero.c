#include "include.h"
#include "defobj.h"

int display_object(obj object);

int main(int argc, char **argv)
{
	int idSockServ, lengthServ; // Identifiant socket serveur et taille structure
	int idSockCli, lengthCli; // Identifiant socket client et taille structure
	struct sockaddr_in saddrServ; // Adresse serveur
	struct sockaddr_in saddrCli; // Adresse client
	int servPort;
	int status;
	pid_t pid;
	obj objet;

	printf("Le serveur fonctionne sur le port %s\n", argv[1]);
	servPort = atoi(argv[1]);

	// Création du socket
	if ((idSockServ = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) { // SOCK_STREAM: TCP, PF_INET: IPv4
		perror("socket() failed\n");
		exit(0);
	}

	// Initialisation à zéro
	lengthServ = sizeof(saddrServ);
	bzero(&saddrServ, lengthServ);

	// Affectation des champs utiles du socket
	saddrServ.sin_family = AF_INET; 				// IPv4
	saddrServ.sin_addr.s_addr = htonl(INADDR_ANY); 	// Converts unsigned int arg from host byte order to network byte order
	saddrServ.sin_port = htons(servPort); 			// Récupère le port passé en argument

	// Association de la socket à l'adresse créée
	if ((bind(idSockServ, (const struct sockaddr *) &saddrServ, lengthServ)) < 0) {
		perror("bind() failed\n");
		exit(0);
	}

	// Le serveur écoute sur le socket, la file d'attente a une longueur MAXBINDING
	if (listen(idSockServ, MAXBINDING) < 0) {
		perror("listen() failed\n");
		exit(0);
	}
	
	while (1) {
		printf("En attente de messages\n");
		lengthCli = sizeof(saddrCli);
		// Création d'une socket de service
		if ((idSockCli = accept(idSockServ, (struct sockaddr *) &saddrCli, &lengthCli)) < 0) {
			perror("accept() failed\n");
			exit(0);
		}

		pid = fork();
		switch(pid) {
			case 0:
        		printf ("Traitement du client par le fils\n");
				do {
					if((recv(idSockCli, &objet, sizeof(objet), 0)) < 0) {
						perror("rcv() Failed");
						exit(0);
					}
					if (objet.ii != -1)
						display_object(objet);
				} while (objet.ii != -1);
				return FIN_SERVEUR;
				break;
			case -1:
				perror("Erreur");
				break;
			default:
				waitpid(pid, &status, 0);
				if (status == FIN_SERVEUR) {
					printf("Fin du traitement par le fils, terminaison du serveur\n");
					return 0;
				} else {
					printf("Fin du traitement par le fils, attente d'un nouveau client\n");
				}
		}
	}
	return 0;
}

int display_object(obj object) {
	printf("Objet reçu:\n");
	printf("%s\n", object.id);
	printf("%s\n", object.desc);
	printf("%d\n", object.ii);
	printf("%d\n", object.jj);
	printf("%f\n", object.dd);
	return 0;
}
