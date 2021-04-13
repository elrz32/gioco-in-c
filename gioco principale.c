#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define R 25
#define C 4

#define VUOTO 0
#define PERSONAGGIO 1
#define MURO 2
#define NEM1 3
#define NEM2 4
#define TRAPPOLA 5

#define MOSSE_TOTALI 60

#define FRECCIA_SU 72
#define FRECCIA_GIU 80
#define FRECCIA_DX 77
#define FRECCIA_SX 75



/*
		IMPORTANTE PRIMA DI LEGGERE IL CODICE:
		ho aggiunto la possibiltà di giocare con colori, ma, siccome non mi piacevano, li ho "tolti" mettendoli come commenti.
		se si vuole, si può giocare con i colori togliendo i cmmenti.
		L'unico elemento a cui non può essere tolto il colore è il personaggio per via delle regole
*/


void regole(){
	HANDLE  setup_colore;
	setup_colore = GetStdHandle(STD_OUTPUT_HANDLE);
	printf(" BENVENUTO/A ALLA CORSA !!!\n");
	printf("LA CORSA prevede che il personaggio arrivi alla fine di uno stretto corridoio superando i nemici \n\n");
	printf("Regole e appunti:\n");
	printf(" 1) tu sei questo --> ");
	SetConsoleTextAttribute(setup_colore, 2);
	printf("%c\n",219);
	SetConsoleTextAttribute(setup_colore, 7);
	printf(" 2) hai a disposizione ");
	SetConsoleTextAttribute(setup_colore, 15);
	printf("60");
	SetConsoleTextAttribute(setup_colore, 7);
	printf(" mosse per finire la partita, altrimenti perderai (quando il tuo personaggio da verde dicenta rosso, vuol dire che stai per finire le mosse)\n");
	printf(" 3) ti muovi con le freccettine, altri tasti non saranno ammessi\n");
	printf(" 4) il muro e questo --> %c , non puoi oltrepassarlo\n",186);
	printf(" 5) il nemico mortale e questo --> ");
	SetConsoleTextAttribute(setup_colore, 11);
	printf("%c",64);
	SetConsoleTextAttribute(setup_colore, 7);
	printf(", toccalo e perderai\n");
	printf(" 6) il nemico non mortale e questo --> ");
	SetConsoleTextAttribute(setup_colore, 5);
	printf("%c",245);
	SetConsoleTextAttribute(setup_colore, 7);
	printf(" , toccalo e ricomincerai da capo\n");
	printf(" 7) questa casella (--> ");
	SetConsoleTextAttribute(setup_colore, 12);
	printf("%c",176);
	SetConsoleTextAttribute(setup_colore, 7);
	printf(") sara la trappola, e se la toccherai perderai\n");
	printf(" 7.5) nella terza riga, ogni turno, ci sara una trappola che si posizionera randomicamente \n");
	printf(" 8) i dettagli della partita saranno comunicati tramite file txt esterno al programma (consultare directory sulla quale  si ha salvato questo gioco)\n");	
	printf("\n   premi invio per iniziare");
	char tasto;
	do{
	tasto=getch();		
	}while(tasto!=13);
	
	printf("\n\n\n Elon Musk approva");
}
void stampaCampo(int campo[R][C],int mosse_fatte){
	//per i colori
	HANDLE  setup_colore;
	setup_colore = GetStdHandle(STD_OUTPUT_HANDLE);
	int colore;
	int r,c;
	
	for(r=0; r<R; r++){
		for(c=-1; c<C+1; c++){
			if(c==0 || c==C){
				campo[r][c]=MURO;
			}
			if(campo[r][c] == VUOTO){
				printf(" ");
			} else if(campo[r][c]==	PERSONAGGIO){
				if(mosse_fatte<(MOSSE_TOTALI-10)){
					SetConsoleTextAttribute(setup_colore, 2);
					printf("%c",219);
					SetConsoleTextAttribute(setup_colore, 7);		
				}
				else{
					SetConsoleTextAttribute(setup_colore, 4);
					printf("%c",219);
					SetConsoleTextAttribute(setup_colore, 7);	
				}	
			}
			else if(campo[r][c]== MURO){
				printf("%c",186);
			}
			else if(campo[r][c]==NEM1){
				SetConsoleTextAttribute(setup_colore, 11);
				printf("%c",64);
				SetConsoleTextAttribute(setup_colore, 7);
			}
			else if(campo[r][c]==NEM2){
				SetConsoleTextAttribute(setup_colore, 5);
				printf("%c",245);
				SetConsoleTextAttribute(setup_colore, 7);
			}
			else if(campo[r][c]==TRAPPOLA){
				SetConsoleTextAttribute(setup_colore, 12);
				printf("%c",176);
				SetConsoleTextAttribute(setup_colore, 7);
			}
		}
		printf("\n");
	}
}

void risultato(int mosse_fatte, int muri_toccati, int nemici_toccati, int trappola){
		FILE*fp;
		fp=fopen("risultati.txt","w");
		fprintf(fp,"RISULTATI:\n");
		fprintf(fp,"- Hai esguito un totale di %d mosse\n",mosse_fatte);
		fprintf(fp,"- Hai toccato %d muri\n",muri_toccati);
		fprintf(fp,"- Hai toccato %d nemici\n",nemici_toccati);
		if(trappola==1){
			fprintf(fp,"- Sei morto cadendo in una trappola\n");
		}
		else{
			fprintf(fp,"- Non sei caduto in una trappola\n");
		}			
		if(mosse_fatte>MOSSE_TOTALI){
			fprintf(fp,"-Sei morto perche hai finito le tue mosse massime possibili\n");
		}
		fclose(fp);			
}


int main(){
	regole();
	int r,c;	
	int campo[R][C];
	
	//Inizializzo la matrice
	for(r=-1; r<R; r++){
		for(c=-1; c<C; c++){
			campo[r][c] = VUOTO;
		}
	}
	//definisco le posizioni delle trappole
	campo[1][2]=TRAPPOLA;
	campo[3][1]=TRAPPOLA;
	campo[3][2]=TRAPPOLA;
	campo[21][1]=TRAPPOLA;
	campo[22][1]=TRAPPOLA;
	
	//posizione trappola randomica
	int trappola_random=1;
	srand(time(0));
	//definire posizione personaggio
	int posX = 2;
	int posY = 24;
	campo[posX][posY] = PERSONAGGIO;
	
	//definire posizione dei nemici
	int nem1x=C-1;
	int nem1y=R-3;
	int verso1=1;
	campo[nem1x][nem1y]=NEM1; 										//sfortunatamente le x e le y sono invertite per i nemici <-- IMPORTANTE	:(
	
	int nem1x_2=C-2;
	int nem1y_2=R+4;
	campo[nem1x_2][nem1y_2]=NEM1;	
	
	//questo nemico è dicerso per movimenti dai nemici prima
	int nem1x_3=20;
	int nem1y_3=2;
	int verso1_3=0;
	campo[nem1x_3][nem1y_3]=NEM1;
	//
	
	int nem1x_4=C-1;
	int nem1y_4=R+5;
	campo[nem1x_4][nem1y_4]=NEM1;
	
	//questo nemico funziona come il nem1_3
	int nem1x_5=2;
	int nem1y_5=2;
	int verso1_5=0;
	campo[nem1x_5][nem1y_5]=NEM1;
		
	//nemici 2
	int nem2x=C-4;
	int nem2y=R-5;
	int verso2;
	verso2=1;
	campo[nem2x][nem2y]=NEM2;
	
	int nem2x_2=C-2;
	int nem2y_2=R-4;
	int verso2_2=1;
	campo[nem2x_2][nem2y_2]=NEM2;
	
	int nem2x_3=C-3;
	int nem2y_3=R-3;
	int verso2_3=1;
	campo[nem2x_3][nem2y_3]=NEM2;
	
	//ora dichiaro il numero di mosse fatte, di muri toccati, di nemici toccati che verranno poi messi in un file di testo sotto forma di risultati
	
	int mosse_fatte;
	mosse_fatte=0;
	
	int muri_toccati;
	muri_toccati=0;
	
	int nemici_toccati;
	nemici_toccati=0;
	int trappola;
	trappola=0;
	
	while(1){
	
		system("cls");
		//Stampo il campo da gioco
		stampaCampo(campo,mosse_fatte);
		
		//Muovo il personaggio con le frecce
		getch();
		int tasto;
		do{
		tasto= getch();
		}while(tasto!=FRECCIA_SU && tasto!=FRECCIA_GIU && tasto!=FRECCIA_DX && tasto!=FRECCIA_SX);
		campo[posY][posX] = VUOTO;
		switch(tasto){
			case FRECCIA_SU:{
				posY--;
				if(posY<0){
					posY=0;
				}
				break;
			}
			case FRECCIA_GIU:{
				posY++;
				if(posY>=R){
					posY=R-1;
				}
				break;
			}
			case FRECCIA_SX:{
				posX--;
				if(posX<1){
					posX=1;
					muri_toccati++;
				}
				break;
			}
			case FRECCIA_DX:{
				posX++;
				if(posX>=C){
					posX=C-1;
					muri_toccati++;
				}
				break;
			}
		}
		//trappola random
		campo[trappola_random][3]=VUOTO;
		do{
		trappola_random=rand()%25;
		}while(trappola_random<9 || trappola_random>19);
		campo[trappola_random][3]=TRAPPOLA;
		//movimenti nemico 1 (e quindi pure 1_2)
		campo[nem1x][nem1y]=VUOTO;
		if(nem1x>11){
			verso1=0;
		}
		if(nem1x+1<5){
			verso1=1;
		}
		if(verso1==1){
			nem1x++;
		}
		else if(verso1==0){
			nem1x--;
		}
		campo[nem1x][nem1y]=NEM1;
		
		//movimenti nemico 1_2
		campo[nem1x_2][nem1y_2]=VUOTO;
		if(verso1==1){
			nem1x_2++;
		}
		else if(verso1==0){
			nem1x_2--;
		}
		campo[nem1x_2][nem1y_2]=NEM1;
				
		//movimenti nemico 1_3
		campo[nem1x_3][nem1y_3]=VUOTO;
		if(campo[nem1x_3][nem1y_3+1]==MURO)	{
			verso1_3=0;
		}	
		else if(campo[nem1x_3][nem1y_3-1]==MURO){
			verso1_3=1;
		}
		if(verso1_3==0){
			nem1y_3--;
		}
		else if(verso1_3==1){
			nem1y_3++;
		}
		campo[nem1x_3][nem1y_3]=NEM1;
		//movimenti nemico 1_4
			campo[nem1x_4][nem1y_4]=VUOTO;
		if(verso1==1){
			nem1x_4++;
		}
		else if(verso1==0){
			nem1x_4--;
		}
		campo[nem1x_4][nem1y_4]=NEM1;
		
		//movimenti nemico 1_5
		campo[nem1x_5][nem1y_5]=VUOTO;
		if(campo[nem1x_5][nem1y_5+1]==MURO)	{
			verso1_5=0;
		}	
		else if(campo[nem1x_5][nem1y_5-1]==MURO){
			verso1_5=1;
		}
		if(verso1_5==0){
			nem1y_5--;
		}
		else if(verso1_5==1){
			nem1y_5++;
		}
		campo[nem1x_5][nem1y_5]=NEM1;
				
		//movimenti nemico 2
		campo[nem2x][nem2y]=VUOTO;
		if(campo[nem2x][nem2y+1]==MURO){
			verso2=0;
		}
		else if(campo[nem2x][nem2y-1]==MURO){
			verso2=1;
		}
		if(verso2==1){
			nem2y++;
		}
		else if(verso2==0){
			nem2y--;
		}
		campo[nem2x][nem2y]=NEM2;		
		
		//movimenti nemico 2_2
		campo[nem2x_2][nem2y_2]=VUOTO;
		if(campo[nem2x_2][nem2y_2+1]==MURO){
			verso2_2=0;
		}
		else if(campo[nem2x_2][nem2y_2-1]==MURO){
			verso2_2=1;
		}
		if(verso2_2==1){
			nem2y_2++;
		}
		else if(verso2_2==0){
			nem2y_2--;
		}
		campo[nem2x_2][nem2y_2]=NEM2;
				
		//movimenti nemico 2_2
		campo[nem2x_3][nem2y_3]=VUOTO;
		if(campo[nem2x_3][nem2y_3+1]==MURO){
			verso2_3=0;
		}
		else if(campo[nem2x_3][nem2y_3-1]==MURO){
			verso2_3=1;
		}
		if(verso2_3==1){
			nem2y_3++;
		}
		else if(verso2_3==0){
			nem2y_3--;
		}
		campo[nem2x_3][nem2y_3]=NEM2;	
		
		//controlli
		if(mosse_fatte>MOSSE_TOTALI){
			system("cls");
			printf("\n hai finito le tue mosse");
			risultato(mosse_fatte,muri_toccati,nemici_toccati,trappola);
			return 0;
		}
		if(campo[posY][posX]==TRAPPOLA){
			trappola=1;
			mosse_fatte++;
			system("cls");
			printf("\n sei caduto in una trappola");
			risultato(mosse_fatte,muri_toccati,nemici_toccati,trappola);			
			return 0;			
		}
		
		if(campo[posY][posX]==NEM1){
			system("cls");
			nemici_toccati++;
			mosse_fatte++;
			printf("\n COLPITO, hai perso...");
			risultato(mosse_fatte,muri_toccati,nemici_toccati,trappola);		
			return 0;
		}
		else if(campo[posY][posX]==NEM2){
			nemici_toccati++;
			mosse_fatte++;
			posY=24;
			posX=2;
		}		
		campo[posY][posX] = PERSONAGGIO;
		mosse_fatte++;
		
		if(posY==0){
			stampaCampo(campo,mosse_fatte);
			printf("\n HAI VINTO!!!");
			risultato(mosse_fatte,muri_toccati,nemici_toccati,trappola);
			return 0;
		}
	}
}
