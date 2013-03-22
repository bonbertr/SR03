#define LONG_MESSAGE (sizeof(msg) - sizeof( ((msg*)(0))->type))

#define REQ_NUM_CLIENT 0		// Demande de connexion
#define RESP_NUM_CLIENT 1		// Acceptation de connexion
#define REJECT_NUM_CLIENT -1	// Rejet de connexion
#define REQ_LISTE_PRODUITS 2	// Demande de la liste des produits
#define RESP_LISTE_PRODUITS 3 // Envoi de la liste des produits
#define CONNEXION_ENDS 4		// Notification de fin de connexion

#define CLIENT_TYPE 3		// Valeur de base du compteur d'ids clients
#define SERVER_TYPE 2 		// Message destiné au serveur
#define ID_REQUEST_TYPE 1 	// Message destiné à un client demandant une connexion

typedef struct {
	long type; 				// type du message
	int operation; 		//	operation demandée 
	int num_client; 		// numero du client
   char content[100];	// le contenu de la réponse du serveur
} msg;
