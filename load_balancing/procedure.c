#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "header.h"


void Client(int msg_id_balancer) {

	int i;
	int ret;

	for(i=0; i<TOTALE_MESSAGGI; i++) {

		/* TBD: Inviare il messaggio del client */

		struct mess m;

		m.tipo = 1;

		m.PID = getpid();

		printf("Client %d: invio messaggio numero %d\n", getpid(), i);

		ret = msgsnd(msg_id_balancer, &m, sizeof(struct mess) - sizeof(long), 0); /* TBD */

		if(ret < 0) {

			perror("Errore msgsnd() client");
			exit(1);
		}
	}
}


void Balancer(int msg_id_balancer, int msg_id_server[]) {

	int i;
	int ret;


	/*
	  La variabile "server" indica il prossimo server a cui
	  verrà inviato un messaggio. Il primo messaggio viene 
	  inviato al server n.0, il secondo messaggio al server n.1,
	  il terzo messaggio al server n.2, e poi si ripete a partire
	  da 0.
	*/

	int server = 0;


	for(i=0; i<TOTALE_MESSAGGI*TOTALE_CLIENT; i++) {

		/* TBD: Ricevere un messaggio dai client */

		struct mess m;

		ret = msgrcv(msg_id_balancer, &m, sizeof(struct mess) - sizeof(long), 0, 0);/* TBD */

		if(ret < 0) {

			perror("Errore msgrcv() balancer");
			exit(1);
		}



		printf("Balancer: ricezione messaggio dal processo %d, invio al server %d\n", m.PID, server+1);



	

		ret = msgsnd(msg_id_server[server], &m, sizeof(struct mess) - sizeof(long), 0); /* TBD */

		

		if(ret < 0) {

			perror("Errore msgsnd() balancer");
			exit(1);
		}



		/*
		  Aggiorna la variabile server con la divisione in modulo
		*/

		server = (server + 1) % TOTALE_SERVER;
	}

}


void Server(int msg_id_server) {

	int i;
	int ret;


	/*
	  Ciascun server effettua un numero di ricezioni prefissato
	  e poi termina.

	  Nota bene: il programma è scritto in modo che il numero totale di
	  messaggi sia esattamente un multiplo del numero di server
	*/

	for(i=0; i<TOTALE_MESSAGGI*TOTALE_CLIENT/TOTALE_SERVER; i++) {


		/* TBD: Ricevere un messaggio dal load balancer */

		struct mess m;

		ret = msgrcv(msg_id_server, &m, sizeof(struct mess) - sizeof(long), 0, 0);/* TBD */

		printf("Server %d: ricezione messaggio numero %d dal processo %d\n", getpid(), i, m.PID);

		if(ret < 0) {

			perror("Errore msgrcv() server");
			exit(1);
		}
	}
}

  
