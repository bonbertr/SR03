#include "include.h"
#include "defobj.h"

int display_object(obj object);
void wait_handler();
int status;

int traiterClient(int idSockCli)
{
	obj objet;
	do {
		if((recv(idSockCli, &objet, sizeof(objet), 0)) < 0) {
			perror("rcv() Failed");
			exit(0);
		}
		
		if (objet.ii != -1) {
			display_object(objet);
		}	
	   } while (objet.ii != -1);
	
	printf(" -- Marqueur de fin reçu, fin de transmission --\n\n");
	sleep(1); //Pour avoir un dialogue un peu long entre le pere et le fils
	return 0;
}

int main(int argc, char **argv)
{
	int idSockServ, lengthServ; // Identifiant socket serveur et taille structure
	int idSockCli, lengthCli; // Identifiant socket client et taille structure
	struct sockaddr_in saddrCli; // Adresse client
	struct sockaddr_in saddrServ; // Adresse serveur
	int servPort;
	pid_t pid;
	obj objet;
	char* Buffer;
	int cb;

	// Changement du handler pour le signal SIGCHLD pour prevenir au processus pere la fin de son fils
	struct sigaction sig;
	sig.sa_handler = wait_handler; //signal envoyé au père qd le fils se termine
	sigaction(SIGCHLD, &sig, 0);//examiner action sigchild associé au sig

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
		again:
		printf("En attente de messages\n");
		lengthCli = sizeof(saddrCli);
		// Création d'une socket de service
		if ((idSockCli = accept(idSockServ, (struct sockaddr *) &saddrCli, &lengthCli)) < 0) {
			// Si l'appel système accept() est interrompu par le traitement du signal SIGCHLD, on se remet en attente
			if (errno == EINTR)
				goto again;
			perror("accept() failed\n");
			exit(0);
		}
		printf("Connexion client\n");

		pid = fork();
		switch(pid) {
			case 0: // Fils
        			printf ("Traitement du client par le fils\n");
				return traiterClient(idSockCli);
				break;
			case -1:
				perror("Erreur");
				break;
			default: // Père pid>0 se remet directement en accept
				printf("Délégation du traitement au fils\n");
		}
	}
	return 0;
}

void wait_handler() {
	printf("Reçu signal SIGCHLD\n");
	waitpid(-1, &status, 0); //Attendre n’importe lequel des processus fils.
	
	 if (WIFEXITED (status))
        printf("Fils terminé avec status %d\n", status);
    else
        printf ("Erreur lors du traitement du fils\n\n");
}
