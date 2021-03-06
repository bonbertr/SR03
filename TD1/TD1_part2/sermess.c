#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "include.h"

// Retourne un id unique pour un client
int numeroUniqueClient(int * cpt);

int main() {
	key_t clef;
	int id_msg;
	msg message;

	clef = ftok("./sr03p012.txt", 0);
	id_msg = msgget(clef, IPC_CREAT|IPC_EXCL|0666);

	int next_client_id = CLIENT_TYPE; // Compteur d'ids clients
	int current_served_clients = 0; // Nombre de clients actuellement servis
	int total_served_clients = 0;	// Nombre total de clients servis
	int last_client_served = 0; // Booléen pour indiquer si on a servi ou non 4 clients

	if (id_msg == -1) {
		perror("File deja existante - msgget()");
	}
	else
	{
		while (!last_client_served) { // Le serveur tourne tant qu'il n'a pas servi 4 clients
			printf("En attente de messages\n");
			msgrcv(id_msg, (void*) &message, LONG_MESSAGE, SERVER_TYPE, 0);
			switch(message.operation)
			{
				// Demande de connexion client
				case REQ_NUM_CLIENT:
					printf("Reçu demande de connexion\n");
					message.type = ID_REQUEST_TYPE;
					if (current_served_clients < 2) {
						// Acceptation de connexion
						message.operation = RESP_NUM_CLIENT;
						message.num_client = numeroUniqueClient(&next_client_id);
						current_served_clients++;
						printf("current served: %d\n", current_served_clients);
						total_served_clients++;
					}
					else {
						// Rejet de connexion
						message.operation = REJECT_NUM_CLIENT;
						message.num_client = -1;
					}
					msgsnd(id_msg, (void*) &message, LONG_MESSAGE, 0);
					break;
				// Demande de consultation de la liste des produits
				case REQ_LISTE_PRODUITS:
					printf("Reçu demande de liste de produits du client numero: %d\n", message.num_client);
					message.type = message.num_client;
					message.operation = RESP_LISTE_PRODUITS;
					strcpy(message.content, "Liste des produits:\n-P1\n-P2\n-P3\n");
					msgsnd(id_msg, (void*) &message, LONG_MESSAGE, 0);
					break;
				// Notification de fin de connexion
				case CONNEXION_ENDS:
					printf("Fin de connexion du client numero: %d\n", message.num_client);
					current_served_clients--;
					// Contrôle du nombre de clients servis
					if (total_served_clients >= 4) {
						last_client_served = 1;
					}
					break;
				default:
					printf("default\n");
			}
		}
		printf("4 clients servis, arrêt du serveur\n");
		msgctl(id_msg, IPC_RMID, 0);
	}
	return 0;
}

int numeroUniqueClient(int * cpt) {
	*cpt = *cpt + 1;
	return *cpt;
}
