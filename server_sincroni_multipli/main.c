#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main()
{

    /* Coda "OK TO SEND" */

    key_t ok_key = ftok(".", 'a');/* TBD: Definire una chiave per "OK TO SEND" */

    int ok_id = msgget(ok_key, IPC_CREAT | 0644); /* TBD: Ottenere la coda per i messaggi "OK TO SEND" */

    if (ok_id < 0)
    {
        perror("Errore creazione coda messaggi");
        exit(1);
    }

    /* Coda "REQUEST TO SEND" */

    key_t req_key = ftok(".", 'b'); /* TBD: Definire una chiave per "REQUEST TO SEND" */

    int req_id = msgget(req_key, IPC_CREAT | 0644); /* TBD: Ottenere la coda per i messaggi "REQUEST TO SEND" */

    if (req_id < 0)
    {
        perror("Errore creazione coda messaggi");
        exit(1);
    }

    //server
    for (int i = 0; i < 2; i++)
    {
     
     pid_t pid = fork();

    printf("[%d] Attivazione server \n", getpid());

     if(pid == 0){

         execl("./server", "server", NULL);

         perror("Errore attivazione server");
         exit(1);
     }
        /* TBD: Avviare 2 processi server */
    }

    //client
    for (int i = 0; i < 4; i++)
    {
        pid_t pid = fork();

        printf(" [%d] Attivazione client \n", getpid());

        if(pid == 0){

            execl("./client", "client", NULL);

            perror("Errore attivazione client");
            exit(1);
        }
        /* TBD: Avviare 4 processi client */
    }



    printf("[%d] In attesa di terminazione...\n", getpid());

    /* TBD: Attendere la terminazione di tutti i processi */

    for(int i = 0; i < 6; i++){

        wait(NULL);
    }



    printf("[%d] Deallocazione code\n", getpid());

    msgctl(ok_id, IPC_RMID, NULL);
    msgctl(req_id,IPC_RMID, NULL);
    /* TBD: Deallocazione delle code */


    return 0;
}