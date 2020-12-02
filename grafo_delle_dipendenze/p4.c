#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>

#include "p.h"


int main() {

	printf("Processo P4 avviato\n");



	key_t queue_operandi_1  = ftok(".", 'a');/* TBD: Definire la chiave per la coda 1 per gli operandi */
	key_t queue_risultati_1 = ftok(".", 'b');/* TBD: Definire la chiave per la coda 1 per le risposte */



	int id_operandi_1 = msgget(queue_operandi_1, 0644); /* TBD: Ottenere la coda 1 per gli operandi */

	if(id_operandi_1 < 0) {
		perror("Msgget fallita");
		exit(1);
	}



	int id_risultati_1 = msgget(queue_risultati_1, 0644); /* TBD: Ottenere la coda 1 per le risposte */

	if(id_risultati_1 < 0) {
		perror("Msgget fallita");
		exit(1);
	}



	int i;

	for(i=0; i<3; i++) {


		int ret;

		int g, h, r3;

		struct msg_operandi op;
		struct msg_risposta ris;



		/* TBD: Ricevere gli operandi "g" e "h" dal processo P1 sulla coda 1 degli operandi */

		printf("[P4] RECEIVE P1\n");

		ret = msgrcv(id_operandi_1, &op, sizeof(struct msg_operandi) - sizeof(long), P4, 0); /* TBD */

		if(ret<0) {
			perror("Msgrcv fallita");
			exit(1);
		}

		g = op.operandi[0];/* TBD */
		h = op.operandi[1];/* TBD */

		printf("[P4] OPERANDI: g=%d, h=%d\n", g, h);




		r3 = g * h;

		printf("[P4] RISULTATO: %d\n", r3);

		ris.processo = P4;
		ris.risposta = r3;


		/* TBD: Inviare la risposta "r3" al processo P1 sulla coda 1 dei risultati */

		printf("[P4] SEND P1\n");

		ret = msgsnd(id_risultati_1, &ris, sizeof(struct msg_risposta) - sizeof(long), 0);/* TBD */
			  
		if(ret<0) {
			perror("Msgsnd fallita");
			exit(1);
		}


	}


	return 0;
}
