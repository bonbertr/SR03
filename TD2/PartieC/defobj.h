#include "include.h"

typedef struct {
	char id[12];
	char desc[24];
	int ii;
	int jj;
	double dd;
} obj;

obj* tabObjet;  // objets à transférer

int init_tab(obj * tab) {
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

	strcpy(tab[3].id,"Fin");
	strcpy(tab[3].desc,"Objet de fin");
	tab[3].ii = -1;
	tab[3].jj = -1;
	tab[3].dd = -1;

	return 0;
}

int display_object(obj object) {
	printf("<<<<<<< Objet modifié reçu par le client\n");
	printf("Identifiant de l'objet: %s\n", object.id);
	printf("Description de l'objet: %s\n", object.desc);
	printf("informations complémentaires sur l'objet: %d / %d / %f\n", object.ii,object.jj,object.dd);
	printf(">>>>>>>\n\n");
	return 0;
}

int display_object2(obj object) {
	printf("<<<<<<< Objet reçu par le serveur\n");
	printf("Identifiant de l'objet: %s\n", object.id);
	printf("Description de l'objet: %s\n", object.desc);
	printf("informations complémentaires sur l'objet: %d / %d / %f\n", object.ii,object.jj,object.dd);
	printf(">>>>>>>\n\n");
	return 0;
}







