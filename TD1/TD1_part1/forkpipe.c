#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

char *str_sub (const char *s, unsigned int start, unsigned int end);

int main() {
	char str[100];
	char str2[100];
	char * buffer = (char *)malloc(21);
	char * line = (char *)malloc(100);
	char * txt = (char *)malloc(500);
	char * number = (char *)malloc(5);
	int nb;
	int p[2];
	pipe(p);
	pid_t pid = fork();
  	
	switch(pid) {
		case 0:
        	printf ("Je suis le fils 1 !\n");
			close(p[0]);
			FILE *fichier = NULL;
    		fichier = fopen ("input.txt", "r");
    		if (fichier == NULL)
        		printf ("Erreur a l'ouverture du fichier\n");
    		else {
				while(fgets(str, sizeof(char)*100, fichier)) {
					str[strlen(str)-1]='\0';
					sprintf(str2,"[%03d][%s]", strlen(str), str);
					write(p[1], str2, strlen(str2));
    			}
        		fclose(fichier);
    		}
			break;
		case -1:
			perror("erreur");
			break;
		default:
        	printf ("Je suis le père !\n");
			pid_t pid2 = fork();
			switch(pid2) {
				case 0:
					close(p[1]);
        			printf ("Je suis le fils 2 !\n");
					strcpy (txt, "");
					while (read(p[0], buffer, sizeof(char)*20)>0)
						strcat (txt, buffer);
					while (txt != NULL) {
						number = str_sub(txt, 1,3);
						nb = atoi(number);
						line = str_sub(txt, 6, nb+5);
						if (line != NULL) {
							printf("recu>>>>%s<<<<\n", line);
						} else {
							printf("recu>>>><<<<\n");
						}
						strcpy(txt, str_sub(txt, nb+7, strlen(txt)));
					}
					break;
				case -1:
					perror("error");
					break;
				default:
					close(p[0]);
					close(p[1]);
        			printf ("Je suis le père !\n");
					waitpid(pid, NULL, WUNTRACED);
					printf("fils 1 termine\n");
					waitpid(pid2, NULL, WUNTRACED);
					printf("fils 2 termine\n");
					printf("Terminaison du père\n");
    			}
    	}
	free(line);
	free(txt);
	free(number);
  	return 0;
}

char *str_sub (const char *s, unsigned int start, unsigned int end) {
   char *new_s = NULL;
   if (s != NULL && start < end) {
      new_s = malloc (sizeof (*new_s) * (end - start + 2));
      if (new_s != NULL) {
         int i;
         for (i = start; i <= end; i++) {
            new_s[i-start] = s[i];
         }
         new_s[i-start] = '\0';
      }
      else {
         fprintf (stderr, "Memoire insuffisante\n");
         exit (EXIT_FAILURE);
      }
   }
   return new_s;
}
