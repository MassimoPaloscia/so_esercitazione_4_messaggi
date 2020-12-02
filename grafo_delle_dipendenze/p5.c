#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>

#include "p.h"


int main() {

	printf("Processo P5 avviato\n");



	key_t queue_operandi_2  = ftok(".", 'c'); /* TBD: Definire la chiave per la coda 2 per gli operandi */
	key_t queue_risultati_2 = ftok(".", 'd'); /* TBD: Definire la chiave per la coda 2 per le risposte */



	int id_operandi_2 = msgget(queue_operandi_2, 0644);/* TBD: Ottenere la coda 2 per gli operandi */

	if(id_operandi_2 < 0) {
		perror("Msgget fallita");
		exit(1);
	}



	int id_risultati_2 = msgget(queue_risultati_2, 0644); /* TBD: Ottenere la coda 2 per le risposte */

	if(id_risultati_2 < 0) {
		perror("Msgget fallita");
		exit(1);
	}



	int i;

	for(i=0; i<3; i++) {


		int ret;

		int c, d, r4;

		struct msg_operandi op;
		struct msg_risposta ris;



		/* TBD: Ricevere gli operandi "c" e "d" dal processo P3 sulla coda 2 degli operandi */

		printf("[P5] RECEIVE P3\n");

		ret =  msgrcv(id_operandi_2, &op, sizeof(struct msg_operandi) - sizeof(long), P5, 0);/* TBD */

		if(ret<0) {
			perror("Msgrcv fallita");
			exit(1);
		}

		c = op.operandi[0]; /* TBD */
		d = op.operandi[1]; /* TBD */

		printf("[P5] OPERANDI: c=%d, d=%d\n", c, d);




		r4 = c + d;

		printf("[P5] RISULTATO: %d\n", r4);




		/* TBD: Inviare la risposta "r4" al processo P3 sulla coda 2 dei risultati */

		ris.processo = P5;
		ris.risposta = r4;

		printf("[P5] SEND P3\n");

		ret = msgsnd(id_risultati_2, &ris, sizeof(struct msg_risposta) - sizeof(long), 0); /* TBD */

		if(ret<0) {
			perror("Msgsnd fallita");
			exit(1);
		}


	}


	return 0;
}
