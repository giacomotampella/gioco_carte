/*
	GIOCO CON LE CARTE
	
	-\ Si ha a disposizione un mazzo di carte con quattro gruppi di numeri da 1 a 10.
	-\ Dopo aver mescolato le carte, due giocatori giocano a turno con le carte coperte.
	-\ Un giocatore sceglie una carta e l’altro giocatore cerca di indovinarla. 
	-\ Se ci riesce ottiene zero punti altrimenti ottiene tanti punti pari alla differenza tra il valore della carta e il valore indicato dal giocatore. 
		Questi punti si sommano ai precedenti.
	-\ Il gioco termina quando finiscono le carte e vince il giocatore con meno punti.
*/
#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

const int NMAX = 40;
const int N_SCAMBI = 40;

int mazzo[NMAX];
int n;

int pti_com;
int pti_usr;

void init_mazzo(int mazzo[], int n) {
	for (int i = 0; i<10; i++) {
		mazzo[i] = i + 1;
		mazzo[i+10] = i + 1;
		mazzo[i+20] = i + 1;
		mazzo[i+30] = i + 1;
	}
}

void mescola_carte(int mazzo[], int n, int n_scambi) {
	int a, b, app;
	for (int i = 0; i < n_scambi; i++) {
		a = rand() % n;
		b = rand() % n;
		app = mazzo[a];
		mazzo[a] = mazzo[b];
		mazzo[b] = app;
	}
}

int estrai_carta(int mazzo[], int n, int p) {
	int carta = mazzo[p];
	for (int i = p; i < n-1; i++) {
		mazzo[i] = mazzo[i+1];
	}
	n--;
	return carta;
}

void stampa_info(int pti_usr, int pti_com, int n) {
	cout << endl;
	cout << "Punti Giocatore: " << pti_usr << endl;
	cout << "Punti Computer: " << pti_com << endl;
	cout << "Carte Rimaste: " << n << endl;
}

bool fine_gioco(int n) {
	return (n <= 0);
}

int main () {
	int p;
	
	int carta_usr;
	int carta_com;
		
	int carta_guess_com;
	int carta_guess_usr;
	
	srand(time(NULL));
	n = NMAX;
	cout << "Creo il mazzo da 40 carte..." << endl;
	init_mazzo(mazzo, n);
	cout << "Mescolo mazzo..." << endl;
	mescola_carte(mazzo, n, N_SCAMBI);
	
	do {
		// turno COMPUTER
		cout << "Estraggo una carta dal mazzo." << endl;
		carta_com = estrai_carta(mazzo, n, rand()%n);
		do {
			cout << "Indovina la mia carta: ";
			cin >> carta_guess_usr;
		} while (carta_guess_usr <= 0);
		cout << "La mia carta e': " << carta_com << endl;
		
		// turno UTENTE
		cout << "Ora e' il tuo turno, ";
		do {
			cout << "scegli una posizione nel mazzo con " << n << " carte: ";
			cin >> p;
		} while (p <= 0 || p > n);
		carta_usr = estrai_carta(mazzo, n, p-1);
		carta_guess_com = 1+rand()%10;
		cout << "CPU: Secondo me la tua carta vale " << carta_guess_com << endl;
		cout << "La tua carta vale: " << carta_usr << endl;
		
		// SCORE
		pti_com += abs(carta_guess_com - carta_usr);
		pti_usr += abs(carta_guess_usr - carta_com);
		
		stampa_info(pti_usr, pti_com, n);
		
	} while (! fine_gioco(n));

	cout << "GAME OVER!" << endl;
	
	if (pti_com < pti_usr) {
		cout << "L'utente ha vinto!" << endl;
	} else if (pti_com > pti_usr) {
		cout << "La CPU ha vinto!" << endl;
	} else {
		cout << "Parita'!" << endl;
	}
}
