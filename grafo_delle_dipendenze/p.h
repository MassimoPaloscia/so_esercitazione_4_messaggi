#ifndef _P_H_
#define _P_H_


#define P1 1 /*TBD*/
#define P2 2 /*TBD*/
#define P3 3 /*TBD*/
#define P4 4 /*TBD*/
#define P5 5 /*TBD*/
#define P6 6 /*TBD*/


struct msg_operandi {
	long processo;
	int operandi[4];
};
/* TBD: Definire una struct per i messaggi con gli operandi (vettore di interi) */

struct msg_risposta {
	long processo;
	int risposta;
};
/* TBD: Definire una struct per i messaggi con le risposte (un intero) */

#endif // _P_H_
