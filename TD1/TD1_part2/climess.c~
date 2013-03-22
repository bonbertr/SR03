#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "include.h"

int main() {
	key_t clef;
	int id_msg;
	msg message;

	clef = ftok("./sr03p012.txt", 0);
	id_msg = msgget(clef, 0); // Récupération de la file de messages

	int id;
	int choice;

	if(id_msg == -1)
		perror("File inexistante - msgget()");
	else
	{	
		// Demande de connexion au serveur
		printf("Demande de connexion\n");
		message.type = SERVER_TYPE;
		message.operation = REQ_NUM_CLIENT;
		msgsnd(id_msg, (void *) &message, LONG_MESSAGE, 0);
		printf("Attente de réponse\n");
		msgrcv(id_msg, (void *) &message, LONG_MESSAGE, ID_REQUEST_TYPE, 0);
		switch(message.operation) {
			// Connexion rejetée
			case REJECT_NUM_CLIENT:
				printf("Connexion au serveur refusée\n");
				break;
			// Connexion acceptée
			case RESP_NUM_CLIENT:
				id = message.num_client;
				printf("Connecté au serveur, reçu identifiant: %d\n", id);
				
				// Menu
				do {
					printf("Sélectionnez une option:\n");
					printf("1 - Demander la liste des produits\n");
					printf("2 - Fin de connexion\n");
					printf("Numéro du choix:");
					scanf("%d", &choice);
					switch (choice) {
						case 1:
							printf("Demande de liste de produits\n");
							message.type = SERVER_TYPE;
							message.operation = REQ_LISTE_PRODUITS;
							message.num_client = id;
							msgsnd(id_msg, (void *) &message, LONG_MESSAGE, 0);
							printf("Attente de réponse\n");
							msgrcv(id_msg, (void *) &message, LONG_MESSAGE, id, 0);
							printf("%s\n", message.content);
							break;
						case 2:
							printf("Fin de connexion\n");
							message.type = SERVER_TYPE;
							message.operation = CONNEXION_ENDS;
							message.num_client = id;
							msgsnd(id_msg, (void *) &message, LONG_MESSAGE, 0);
							break;
					}
				} while (choice != 2);
				break;
		}
	}
	printf("Fin du programme client \n");
	return 0;
}
