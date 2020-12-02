#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>

#include "p.h"


int main() {

	printf("Processo P3 avviato\n");



	key_t queue_operandi_1  = ftok(".", 'a'); /* TBD: Definire la chiave per la coda 1 per gli operandi */
	key_t queue_risultati_1 = ftok(".", 'b'); /* TBD: Definire la chiave per la coda 1 per le risposte */
	key_t queue_operandi_2  = ftok(".", 'c'); /* TBD: Definire la chiave per la coda 2 per gli operandi */
	key_t queue_risultati_2 = ftok(".", 'd'); /* TBD: Definire la chiave per la coda 2 per le risposte */



	int id_operandi_1 = msgget(queue_operandi_1, 0644);/* TBD: Ottenere la coda 1 per gli operandi */

	if(id_operandi_1 < 0) {
		perror("Msgget fallita");
		exit(1);
	}




	int id_risultati_1 = msgget(queue_risultati_1, 0644);/* TBD: Ottenere la coda 1 per le risposte */

	if(id_risultati_1 < 0) {
		perror("Msgget fallita");
		exit(1);
	}




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

		int c, d, e, f, r2, r4, r5;

		struct msg_operandi op;
		struct msg_risposta ris;


		/* TBD: Ricevere gli operandi "c", "d", "e" e "f" dal processo P1 sulla coda 1 degli operandi */

		printf("[P3] RECEIVE P1\n");

		ret = msgrcv(id_operandi_1, &op, sizeof(struct msg_operandi) - sizeof(long), P3, 0); /* TBD */

		if(ret<0) {
			perror("Msgrcv fallita");
			exit(1);
		}

		c = op.operandi[0];/* TBD */
		d = op.operandi[1];/* TBD */
		e = op.operandi[2];/* TBD */
		f = op.operandi[3];/* TBD */

		printf("[P3] OPERANDI: c=%d, d=%d, e=%d, f=%d\n", c, d, e, f);





		/* TBD: Inviare gli operandi "c" e "d" al processo P5 sulla coda 2 degli operandi */

		printf("[P3] SEND P5\n");

		op.processo = P5;
		op.operandi[0] = c;
		op.operandi[1] = d;

		ret = msgsnd(id_operandi_2, &op, sizeof(struct msg_operandi)-sizeof(long), 0); /* TBD */

		if(ret<0) {
			perror("Msgsnd fallita");
			exit(1);
		}




		/* TBD: Inviare gli operandi "e" e "f" al processo P6 sulla coda 2 degli operandi */

		printf("[P3] SEND P6\n");

		op.processo = P6;
		op.operandi[0] = e;
		op.operandi[1] = f;

		ret = msgsnd(id_operandi_2, &op, sizeof(struct msg_operandi) - sizeof(long), 0);/* TBD */

		if(ret<0) {
			perror("Msgsnd fallita");
			exit(1);
		}




		/* TBD: Ricevere la risposta "r4" dal processo P5 sulla coda 2 delle risposte */

		printf("[P3] RECEIVE P5\n");

		ret = msgrcv(id_risultati_2, &ris, sizeof(struct msg_risposta)-sizeof(long), P5, 0); /* TBD */

		if(ret<0) {
			perror("Msgrcv fallita");
			exit(1);
		}

		r4 = ris.risposta;/* TBD */




		/* TBD: Ricevere la risposta "r5" dal processo P6 sulla coda 2 delle risposte */

		printf("[P3] RECEIVE P6\n");

		ret =  msgrcv(id_risultati_2, &ris, sizeof(struct msg_risposta)-sizeof(long), P6, 0); /* TBD */

		if(ret<0) {
			perror("Msgrcv fallita");
			exit(1);
		}

		r5 = ris.risposta; /* TBD */





		printf("[P3] RISULTATI INTERMEDI: r4=%d, r5=%d\n", r4, r5);





		r2 = r4 * r5;

		printf("[P3] RISULTATO: %d\n", r2);


		ris.processo = P3;
		ris.risposta = r2;



		/* TBD: Inviare la risposta "r2" al processo P1 sulla coda 1 dei risultati */



		printf("[P3] SEND P1\n");

		ret = msgsnd(id_risultati_1, &ris, sizeof(struct msg_risposta) - sizeof(long), 0);/* TBD */

		if(ret<0) {
			perror("Msgsnd fallita");
			exit(1);
		}


	}


	return 0;
}


