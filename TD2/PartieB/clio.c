#include "include.h"
#include "defobj.h"

int main(int argc, char **argv)
{
	int idSockCli, lengthCli;
	int idSockServ,lengthServ;
	int etat_connexion;
	char * servName;
	int servPort;
	int i;
	char* Buffer;
	int cb;

	struct sockaddr_in saddrServ; // Adresse serveur
	struct hostent * hid;
	obj* tab;

	tab = (obj *)malloc(sizeof(obj) * TABLEN);
	init_tab(tab);

	printf("Connexion au serveur %s sur le port %s\n", argv[1], argv[2]);
	servPort = atoi(argv[2]);
	servName = argv[1];

	// Création de l'identifiant de la socket client
 	if ((idSockCli = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		perror("socket() failed\n");
		exit(0);
	}

	// Initialisation à zéro
	lengthServ = sizeof(saddrServ);
	bzero(&saddrServ, lengthServ);

	hid = gethostbyname(servName);

	saddrServ.sin_family = AF_INET; 				// Internet addresse
	saddrServ.sin_port = htons(servPort); 		// Local port
	bcopy(hid->h_addr,&(saddrServ.sin_addr.s_addr), hid->h_length);

	if ((connect(idSockCli, (struct sockaddr *) &saddrServ, lengthServ)) < 0) {
		perror("connect() failed\n");
		exit(0);
	}
	printf("Connexion réussie\n");

	for (i=0; i<TABLEN; i++) {
		printf("Envoi de l'objet: %s\n", tab[i].id);
		send(idSockCli, &tab[i], sizeof(tab[0]), 0); // transmission des données grace a la socket de service idsockcli
	}
	free(tab);
	printf("Envoi terminé, fin de la connexion\n");
	close(idSockCli);
	return 0;
}
