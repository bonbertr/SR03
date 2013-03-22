#include "include.h"
#include "defobj.h"

obj* init_tab();

int main(int argc, char **argv)
{
	int idSockCli, lengthCli;
	int lengthServ;
	int etat_connexion;
	char * servName;
	int servPort;

	char *buffer = (char *) malloc(10);
	buffer = "coucou";

	struct sockaddr_in saddrServ; // Adresse serveur
	struct hostent * hid;

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
	saddrServ.sin_port = htons(servPort); 			// Local port
	//servAddr.sin_addr.s_addr = inet_addr(servName); // Convertion de l'adresse en binaire. Il faut donner l'adresse IP
	bcopy(hid->h_addr,&(saddrServ.sin_addr.s_addr), hid->h_length);

	if ((connect(idSockCli, (struct sockaddr *) &saddrServ, lengthServ)) < 0) {
		perror("connect() failed\n");
		exit(0);
	}

	printf("Connexion réussie\n");
	send(idSockCli, buffer, sizeof(char)*10, 0);
	printf("Message envoyé\n");
}

obj* init_tab() {
	obj *tab= (obj *)malloc(TABLEN);

	strcpy(tab[0].id,"ident_o1");
	strcpy(tab[0].desc,"description_o1");
	tab[0].ii = 11;
	tab[0].jj = 12;
	tab[0].dd = 10.2345;

	strcpy(tab[1].id,"ident_o2");
	strcpy(tab[1].desc,"description_o2");
	tab[1].ii = 21;
	tab[1].jj = 22;
	tab[1].dd = 20.2345;

	strcpy(tab[2].id,"ident_o3");
	strcpy(tab[2].desc,"description_o3");
	tab[2].ii = 31;
	tab[2].jj = 32;
	tab[2].dd = 30.2345;

	strcpy(tab[3].id,NULL);
	return tab;
}
