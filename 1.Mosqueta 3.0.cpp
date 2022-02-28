#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>
#define MAX_JUG 20

int opcionMenuI; //Opcion Menu Inicial
int opcionMenuC; //Opcion Menu de Cuenta
char Nickname[20];
char copa[20];
int copas = 0;
bool perdida201;
int cantAciertos = 0;
int perdidas = 0;
char entrada[100];
int saldo=0;
bool esPrimera;

void ordenarAtributos(int);
void top5(int);
void imprimirTop5(int);
void ordenamientoDeMejoresPuntajes(int);
void cargaJugadores();
void menuInicio();
void registrarse();
void iniciarSesion();
void menuDeCuenta(int); //RECIBE POSICION DONDE SE ENCUENTRA GUARDADA LA INFO DE DICHO USUARIO EN EL ARREGLO DE JUGADORES
//int jugar(int);
void jugar(int);
int leerEntradaGenerica();
bool trampa();
void imprimirCopas();
void imprimirJugada(int, char);
void acertoCopa(int);
int copaSalirMano(int&);
int leerEntrada();
void perdio(int,int,char);
void razonOrgullo(int);
bool apuestaValida(int);
void ultimasTres(int);
void cerrarSesion();


struct registroDePartidasGlobal{ //SOLO LO USO PARA TENER EL DISE�O DEL STRUCT Y USARLO DESPUES DENTRO DE OTRO STRUCT
    char nickname[20]; //CON UN STRCPY COPIO EL NICKNAME DEL JUGADOR QUE ESTE JUGANDO EN ESA PARTIDA
    int saldoInicial;
    int saldoFinal;
    int puntaje;
};
struct registroGlobal{ //HISTORIAL GLOBAL
    registroDePartidasGlobal historialGlobal[50];
    int ultIndiceUsado = -1;
};
registroGlobal histoGlobal; //DEFINICION HISTOGLOBAL
 

struct regPersonal{
	int saldoI;
	int saldoF;
};


struct usuario{
	char nickname[20];
	int edad;
	char nombre[20];
	int saldo;
    regPersonal regPartidas[32];
    int cantPartidas = -1; //NINGUN JUGADOR TIENE PARTIDAS JUGADAS AUN
};

usuario jugador[20];

void cargaJugadores(){ //JUGADORES DE PRUEBA
	strcpy(jugador[0].nickname,"Player01");
	strcpy(jugador[0].nombre,"TestPlayer");
	jugador[0].saldo=5000;
	jugador[0].edad=52;
}

void menuInicio(){ //MENU INICIO
	printf("1-Iniciar sesion\n2-Registrarse\n\n");
	scanf("%d",&opcionMenuI);
	while((opcionMenuI!=1)&&(opcionMenuI!=2)){
		printf("ERROR:La opcion seleccionada no existe en el menu inicio\n");
		scanf("%d",&opcionMenuI);
	}
	if(opcionMenuI==1)
		iniciarSesion();
	if(opcionMenuI==2)
		registrarse();
}

void registrarse(){ //REGISTRARSE
	printf("Ingrese nickname: ");
	scanf("%s",Nickname);
	bool existeNick = false;
	int i=0;

	while((!existeNick)&&(i<MAX_JUG)){
		if(strcmp(Nickname,jugador[i].nickname)==0)
		existeNick = true;
		i++;
	}
	if(!existeNick){ //SI NO EXISTE EL NICK INGRESADO BUSCO LA PRIMERA POSICION VACIA DEL ARREGLO DE JUGADORES PARA GUARDAR ALLI EL NICKNAME
		int i=0;
		int posvacia=0;
		bool vacioEncontrado = false;
		while((!vacioEncontrado)&&(i<20)){ //ENCUENTRO PRIMER LUGAR VACIO
			if(jugador[i].nickname[0]=='\0'){
				posvacia = i;
				vacioEncontrado = true;
			}
			i++;
		}
		/*for(int j=0;j<20;j++){
			jugador[posvacia].nickname[j]=Nickname[j];
		}*/
		strcpy(jugador[posvacia].nickname,Nickname);
		printf("Edad: "); scanf("%d",&jugador[posvacia].edad);
		printf("Nombre: "); scanf("%s",jugador[posvacia].nombre); // CAMBIO POR WARNING
		jugador[posvacia].saldo=5000;
		printf("Registro exitoso\n\n");
		menuInicio();

	}else{
		printf("ERROR: Nickname ya existente\n\n");
		registrarse();
	}

}

void iniciarSesion(){ //INICIAR SESION
    esPrimera=true;
	printf("Ingrese nickname: ");
	scanf("%s",Nickname); // CAMBIO POR WARNING
	//printf("%s\n",Nickname);

	bool existeNick = false;
	int i=0;
	int posUsu = 0;
	while((!existeNick)&&(i<MAX_JUG)){
		if(strcmp(Nickname,jugador[i].nickname)==0){
			existeNick = true;
			posUsu = i; //POSICION DONDE SE ENCUENTRA GUARDADA LA INFO DE DICHO USUARIO EN EL ARREGLO DE JUGADORES
		//	printf("POS USUARIO: %d\n",posUsu);
		}
		i++;
	}
	if(existeNick){
		menuDeCuenta(posUsu);

		//printf("usuario encontrado\n");
		//printf("Posicion en arreglo de jugadores del jugador %s = %d",jugador[posUsuario].nickname,posUsuario);
	}else{
		printf("ERROR: El usuario indicado no existe\n\n");
		menuInicio();
	}

}

int convertirCharAInt(char letra){
	int numero = letra - '0';
	return numero;
}

void menuDeCuenta(int posUsuario){
    //printf("%d\n",posUsuario);
	if(esPrimera){
    printf("\n-------- Bienvenido %s --------\n",jugador[posUsuario].nombre);
	printf("Saldo Actual: %d\n\n",jugador[posUsuario].saldo);
    }
	printf("1-Jugar\n2-Ultimas 3 Personales\n3-Top 5\n4-Cerrar Sesion\n\n");
	//scanf("%d",&opcionMenuC);
	char opcionMenuCuentaChar;
	scanf("%s",&opcionMenuCuentaChar);
	opcionMenuC = convertirCharAInt(opcionMenuCuentaChar);
	while((opcionMenuC!=1)&&(opcionMenuC!=2)&&(opcionMenuC!=3)&&(opcionMenuC!=4)){
		printf("ERROR: La opcion indicada no existe en el menu\n");
		scanf("%s",&opcionMenuCuentaChar);
		opcionMenuC = convertirCharAInt(opcionMenuCuentaChar);
	}
	switch(opcionMenuC){
		case 1:{
		    esPrimera=false;
			jugar(posUsuario);
			break;
		}
		case 2:{
			esPrimera=false;
			ultimasTres(posUsuario);
			break;
		}
		case 3:{
			esPrimera=false;
			top5(posUsuario); //SOLO LO MANDO PARA NO PERDER EL VALOR
			break;
		}
		case 4:{
			esPrimera=false;
			cerrarSesion();
			break;
		}
	}
}
int leerEntradaGenerica(){
	int i = -1;
	do{
		i++;
		entrada[i]= getchar();
	}while(entrada[i] != '\n');
		entrada[i] = '\0';
	char a;

	bool sonEnteros = true;
	int j=0;

	while((j<i)&&(sonEnteros)){
		a=entrada[j];
		if((a-'0'>9)||(a-'0'<0))
			sonEnteros = false;
		j++;
	}

	if(!sonEnteros){
		return -1;
	}else{
		int sumaDeEnteros=0;
		int numero = 0;
		for(int k=0;k<i;k++){
			a = entrada[k];
			numero = a - '0';
			sumaDeEnteros =sumaDeEnteros +(numero * (pow(10,i-k-1)));
		}
		return sumaDeEnteros;
	}
		//EN EL MAIN VOY A IR LLAMANDO A ESTA FUNCION Y IGUALANDOLA A SALDO,COPAS Y APUESTA, DEPENDIENDO DE LO QUE SE TRATE y haciendo whiles de acuerdo a
		//las condiciones que se tienen que cumplir(apuesta<=saldo)etc...
}

bool trampa(){ //FUNCION PARA CONTROLAR LA TRAMPA
	if(cantAciertos==2)
		return true;
	else
		return false;
}

void imprimirCopas(){ //IMPRIME COPAS Y NUMEROS
	int i;

	for(i=0;i<copas;i++)
		printf("O ");
	printf("\n");
	for(i=0;i<copas;i++){
		printf("%d ",i+1);
	}
	printf("\n");
	printf("En que copa crees que esta escondida la piedra?: \n");
}

void imprimirJugada(int pos, char pies){ //pies= '.' o ' '		//FUNCION PARA IMPRIMIR LA JUGADA SI SE INGRESO UNA ENTRADA VALIDA
	int i;
	for(i=1;i<=copas;i++){
		if (i==pos)
			printf("%c ",pies);
		else
			printf("O ");
	}
	printf("\n");
}

void acertoCopa(int apuesta){//DARLE LA RECOMPENSA CORRESPONDIENTE
	if(copas<=5){
		saldo=saldo+apuesta;
	}
	if((copas>5) && (copas<=8)){
		saldo=saldo+(apuesta*2);
	}
	if(copas==9){
		saldo=saldo+(apuesta*3);
	}
}

int copaSalirMano(int& i){ //returna valor a la funcion leerEntrada
	switch(i){
		case 1:{
			char valorUnico = copa[0];
			int iValorUnico = valorUnico - '0';
				if((1<=iValorUnico)&&(iValorUnico<=copas)){
				return 1;
				break;
			}else{
				return -1;
				break;
			}
		}
		case 4:{
			char manoMay[4] = {'M','a','n','o'};
			char manoMin[4] = {'m','a','n','o'};
			if((strcasecmp(copa,manoMin)) ||(strcasecmp(copa,manoMay))){
				return 4;
				break;
			}else{
				return -1;
				break;
			}

		}
		case 5:{
			char salirMay[5] = {'S','a','l','i','r'};
			char salirMin[5] = {'s','a','l','i','r'};
			if((strcasecmp(copa,salirMay))||(strcasecmp(copa,salirMin))){
				return 5;
				break;
			}else{
				return -1;
				break;
			}
		}
		default: {
			return -1;
			break;
		}
	}
}

int leerEntrada(){
	int i = -1;
	do{
		i++;
		copa[i]= getchar();
	}while(copa[i] != '\n');
		copa[i] = '\0';

	int referencia;

	referencia = copaSalirMano(i);
	return referencia;  //returna a main lo que le retorno copaSalirMano
}

void perdio(int apuesta,int ubicacionPiedra,char pies,int posUsuario){
	saldo=saldo-apuesta;
		imprimirJugada(ubicacionPiedra,pies);
		printf("No ha acertado\nSaldo: %d\n\n",saldo);

		if(saldo>0){
			imprimirCopas();
			if(apuesta>200){ //SI PERDIO MAS DE 200
				perdida201 = true;
			}
			else{
				perdida201 = false;
			}
			cantAciertos = 0;
			perdidas = perdidas + apuesta;
		}
}

void razonOrgullo(int razon){
	switch(razon){
		case 1:{
			printf("Si vuelvo a casa sin plata me matan\n");
			break;
		}
		case 2:{
			printf("Esto no puede quedar asi\n");
			break;
		}
		case 3:{
			printf("Si perd� la anterior, de seguro ahora gano\n");
			break;
		}
	}
}

bool apuestaValida(int apuesta){

	//if((apuesta>saldo)||(apuesta<=0))
	//	return false;

	if(0<apuesta){
		if(apuesta<=saldo)
			return true;
		else
			return false;
	}else
		return false;
}

void ultimasTres(int posUsuario){
    //printf("Saldo inicial		Saldo Final\n");
	//printf("%d",jugador[posUsuario].cantPartidas);
	switch(jugador[posUsuario].cantPartidas){
		case -1:{
			printf("ERROR: El usuario %s aun no ha jugado ninguna partida\n\n",jugador[posUsuario].nombre);
			menuDeCuenta(posUsuario);
			break;
		}
		case 0:{ //UNICAMENTE JUGO UNA PARTIDA
			printf("Partida Nro  |   Saldo inicial	|	Saldo Final\n");
			printf("------------------------------------------------------\n");
				printf("     %d       |     %d         |          %d        \n",1,jugador[posUsuario].regPartidas[0].saldoI,jugador[posUsuario].regPartidas[0].saldoF);
    		printf("\n");
			menuDeCuenta(posUsuario);
    		break;
		}
		case 1:{ //JUGO 2 PARTIDAS
			printf("Partida Nro  |   Saldo inicial	|	Saldo Final\n");
			printf("------------------------------------------------------\n");
			for(int i=jugador[posUsuario].cantPartidas;i>=0;i--){
				printf("     %d        |     %d        |          %d        \n",i+1,jugador[posUsuario].regPartidas[i].saldoI,jugador[posUsuario].regPartidas[i].saldoF);
			}
			printf("\n");
			menuDeCuenta(posUsuario);
			break;
		}
	}
	if(jugador[posUsuario].cantPartidas>=2){//JUGO 3 O MAS PARTIDAS
		printf("Partida Nro  |   Saldo inicial	|	Saldo Final\n");
		//printf("entre al for jejeje");
		printf("------------------------------------------------------\n");
		for(int i=jugador[posUsuario].cantPartidas;i>=jugador[posUsuario].cantPartidas-2;i--){
			printf("     %d        |     %d        |          %d        \n",i+1,jugador[posUsuario].regPartidas[i].saldoI,jugador[posUsuario].regPartidas[i].saldoF);
		}
		printf("\n");
		menuDeCuenta(posUsuario);
	}
}

void top5(int posUsuario){
	if(histoGlobal.ultIndiceUsado>=1){//existe un minimo de 2 partidas, osea necesidad de ordenar
		ordenamientoDeMejoresPuntajes(posUsuario);
	}
	
	if(histoGlobal.ultIndiceUsado>-1){ //se imprime solo si existen partidas
		imprimirTop5(posUsuario);
	}
	
	if(histoGlobal.ultIndiceUsado==-1){//si no existen partidas
		printf("ERROR: Aun no existen las partidas necesarias para mostrar el TOP 5\n");
	}
	menuDeCuenta(posUsuario);
}

void ordenamientoDeMejoresPuntajes(int posUsuario){
	int aux;
		for(int i=1;i<=histoGlobal.ultIndiceUsado;i++){
	        for(int j=1;j<=histoGlobal.ultIndiceUsado;j++){
	            if(histoGlobal.historialGlobal[j-1].puntaje>histoGlobal.historialGlobal[j].puntaje){
	                ordenarAtributos(j);
	            }
	       }
		}
	//printf("Se paso el FOR\n");
	
	//top5(posUsuario);
}

void ordenarAtributos(int j){
	int auxSaldoI = 0;
	int auxSaldoF = 0;
	int auxPuntaje = 0;
	char auxNickname[20];
	
	//GUARDO LOS DATOS DEL J-1 EN AUXILIARES
	auxSaldoI = histoGlobal.historialGlobal[j-1].saldoInicial ;
	auxSaldoF = histoGlobal.historialGlobal[j-1].saldoFinal;
 	auxPuntaje = histoGlobal.historialGlobal[j-1].puntaje;
	strcpy(auxNickname,histoGlobal.historialGlobal[j-1].nickname);
	//CAMBIO LOS ATT DE J A LA POSICION J-1
	histoGlobal.historialGlobal[j-1].saldoInicial = histoGlobal.historialGlobal[j].saldoInicial;
	histoGlobal.historialGlobal[j-1].saldoFinal = histoGlobal.historialGlobal[j].saldoFinal;
	histoGlobal.historialGlobal[j-1].puntaje = histoGlobal.historialGlobal[j].puntaje;
	strcpy(histoGlobal.historialGlobal[j-1].nickname,histoGlobal.historialGlobal[j].nickname);
	//CAMBIO LOS ATT DE J-1 A J
	histoGlobal.historialGlobal[j].saldoInicial = auxSaldoI;
	histoGlobal.historialGlobal[j].saldoFinal = auxSaldoF;
	histoGlobal.historialGlobal[j].puntaje = auxPuntaje;
	strcpy(histoGlobal.historialGlobal[j].nickname, auxNickname);
	
}

void imprimirTop5(int posUsuario){
	//printf("Nickname     |       Saldo Inicial      |     Saldo Final\n");
	//printf("------------------------------------------------------------\n");
	
	if(histoGlobal.ultIndiceUsado>=4){ //SE JUGARON 5 O MAS PARTIDAS
		printf("Nickname     |       Saldo Inicial      |     Saldo Final\n");
		printf("------------------------------------------------------------\n");
			for(int i=histoGlobal.ultIndiceUsado;i>=histoGlobal.ultIndiceUsado-4;i--){
			printf("%s             %d                   %d        \n",histoGlobal.historialGlobal[i].nickname,histoGlobal.historialGlobal[i].saldoInicial,histoGlobal.historialGlobal[i].saldoFinal);
		}
	}
	
	switch(histoGlobal.ultIndiceUsado){
		case 0:{ //SE JUGO 1 PARTIDA
			printf("Nickname     |       Saldo Inicial      |     Saldo Final\n");
			printf("------------------------------------------------------------\n");
			printf("%s                       %d                        %d        \n",histoGlobal.historialGlobal[0].nickname,histoGlobal.historialGlobal[0].saldoInicial,histoGlobal.historialGlobal[0].saldoFinal);
			break;
		}
		case 1:{ //SE JUGARON 2 PARTIDAS
			printf("Nickname     |       Saldo Inicial      |     Saldo Final\n");
			printf("------------------------------------------------------------\n");
			for(int i=histoGlobal.ultIndiceUsado;i>=histoGlobal.ultIndiceUsado-1;i--){
				printf("%s                  %d                 %d        \n",histoGlobal.historialGlobal[i].nickname,histoGlobal.historialGlobal[i].saldoInicial,histoGlobal.historialGlobal[i].saldoFinal);
			}
			break;
		}
		case 2:{ //SE JUGADRON 3 PARTIDAS
			printf("Nickname     |       Saldo Inicial      |     Saldo Final\n");
			printf("------------------------------------------------------------\n");
			for(int i=histoGlobal.ultIndiceUsado;i>=histoGlobal.ultIndiceUsado-2;i--){
				printf("%s                     %d                      %d        \n",histoGlobal.historialGlobal[i].nickname,histoGlobal.historialGlobal[i].saldoInicial,histoGlobal.historialGlobal[i].saldoFinal);
			}
			break;
		}
		case 3:{ //SE JUGADRON 4 PARTIDAS
			printf("Nickname     |       Saldo Inicial      |     Saldo Final\n");
			printf("------------------------------------------------------------\n");
			for(int i=histoGlobal.ultIndiceUsado;i>=histoGlobal.ultIndiceUsado-3;i--){
				printf("%s                     %d                      %d        \n",histoGlobal.historialGlobal[i].nickname,histoGlobal.historialGlobal[i].saldoInicial,histoGlobal.historialGlobal[i].saldoFinal);
			}
			break;
		}
		top5(posUsuario);
	}
	
}


void cerrarSesion(){
	menuInicio();
}

void jugar(int posUsuario){
	int saldoInicial = 0;
	int saldoFinal = 0;
	saldoInicial = jugador[posUsuario].saldo;
	//printf("%d\n",saldoInicial);
	perdidas = 0; //RESETEO PERDIDAS
	
	//regPartidas (PERSONALES)
	jugador[posUsuario].cantPartidas++; //aumento el indice en 1
	//printf("CANT PARTIDAS: %d\n",jugador[posUsuario].cantPartidas);
	jugador[posUsuario].regPartidas[jugador[posUsuario].cantPartidas].saldoI=jugador[posUsuario].saldo;
	//printf("SALDoI REG PARTIDAS: %d\n",jugador[posUsuario].regPartidas[jugador[posUsuario].cantPartidas].saldoI);
	//printf("%d\n",jugador[posUsuario].saldo);
	saldo=jugador[posUsuario].saldo;
	//printf("SALDO: %d\n",saldo);
	//jugador[posUsuario].regPartidas[jugador[posUsuario].cantPartidas].saldoI=saldo;
	srand(time(NULL));

	printf("Elige cuantas copas (de 3 a 9). Mas copas, mas ganas. Cuantas seran?\n");

	copas = leerEntradaGenerica();
	while((copas<3)||(copas>9)){ //Loop de cantidad de copas, solo se aceptara un valor entre 3 y 9
		copas = leerEntradaGenerica();
	}
	imprimirCopas();
	int razon = 0;
	char pies;
	int refmain = -1;
	int apuesta = 0;
	while(saldo>0){
		while(refmain==-1){
			refmain=leerEntrada(); //Loop de copa, hasta que se ingrese una entrada valida(numero de copa,salir,mano)
		}

		int ubicacionPiedra=rand()%copas + 1;

		switch(refmain){
			case 1: {  //COPA
				printf("Cuanto Apuestas?:\n"); //Se pide y escanea la apuesta
				apuesta = leerEntradaGenerica();
				while((!apuestaValida(apuesta)||(apuesta==-1))){ //Loop apuesta, hasta que se ingrese una apuesta <= saldo y apuesta>0
					apuesta = leerEntradaGenerica();
				}
				char valorUnico = copa[0];
				int copa = valorUnico - '0'; //Conversion de caracter a entero
				if(copa==ubicacionPiedra){ //Gano
					if(trampa()){ // Si la trampa esta activada
						pies = ' ';
						perdio(apuesta,ubicacionPiedra,pies,posUsuario); //imprime jugada e imprime copas
						refmain = -1;
					}else{ //si no esta activada
						acertoCopa(apuesta);
						imprimirJugada(ubicacionPiedra,'.');
						printf("Ha acertado.\nSaldo: %d\n\n",saldo);
						imprimirCopas();
						perdida201 = false;
						cantAciertos++;
						refmain = -1;
					}
				}else{ //Perdio
					pies = '.';
					perdio(apuesta,ubicacionPiedra,pies,posUsuario); //imprime jugada e imprime copas
					refmain = -1;
				}
				break;
			}

			case 4: { //MANO
				if(trampa()){ //Acusa de trampa y la misma SI esta activada
					saldo  = saldo + (perdidas*2);
					jugador[posUsuario].saldo = saldo;
					printf("Saldo: %d\nTu si que eres perceptivo, te animas a no contarle esto a nadie?\n",saldo);
					saldoFinal = saldo;
					printf("%d\n",saldoFinal);
					if(saldoFinal-saldoInicial>0){ //GUARDO EN HISTOGLOBAL UNICAMENTE SI EL PUNTAJE ES POSITIVO
							histoGlobal.ultIndiceUsado++; //aumento el indice en 1
							//printf("UltIndiceUsado: %d\n",histoGlobal.ultIndiceUsado);
							strcpy(histoGlobal.historialGlobal[histoGlobal.ultIndiceUsado].nickname,jugador[posUsuario].nickname); //COPIO EL NICKNAME 
							//printf("Nickname en HISTOGLOBAL: %s\n",histoGlobal.historialGlobal[histoGlobal.ultIndiceUsado].nickname);
							histoGlobal.historialGlobal[histoGlobal.ultIndiceUsado].saldoInicial = saldoInicial; //GUARDO SALDO INICIAL 
							histoGlobal.historialGlobal[histoGlobal.ultIndiceUsado].saldoFinal = jugador[posUsuario].saldo; // SALDO FINAL HISTO GLOBAL
							histoGlobal.historialGlobal[histoGlobal.ultIndiceUsado].puntaje = saldoFinal - saldoInicial; //PUNTAJE = SALDO FINAL - SALDO INNICIAL
					}
					
					
					jugador[posUsuario].regPartidas[jugador[posUsuario].cantPartidas].saldoF=jugador[posUsuario].saldo; //SALDO FINAL HISTO PERSONAL
					menuDeCuenta(posUsuario);
					
				}else{ //Acusa de trampa pero la misma NO esta activada
					printf("Qui�n te crees que soy? Vete de aqu�\n");

					jugador[posUsuario].saldo = saldo;
					saldoFinal = saldo;
					if(saldoFinal-saldoInicial>0){ //GUARDO EN HISTOGLOBAL UNICAMENTE SI EL PUNTAJE ES POSITIVO
						histoGlobal.ultIndiceUsado++; //aumento el indice en 1
						//printf("UltIndiceUsado: %d\n",histoGlobal.ultIndiceUsado);
						strcpy(histoGlobal.historialGlobal[histoGlobal.ultIndiceUsado].nickname,jugador[posUsuario].nickname); //COPIO EL NICKNAME 
						//printf("Nickname en HISTOGLOBAL: %s\n",histoGlobal.historialGlobal[histoGlobal.ultIndiceUsado].nickname);
						histoGlobal.historialGlobal[histoGlobal.ultIndiceUsado].saldoInicial = saldoInicial; //GUARDO SALDO INICIAL 
						histoGlobal.historialGlobal[histoGlobal.ultIndiceUsado].saldoFinal = jugador[posUsuario].saldo; // SALDO FINAL HISTO GLOBAL
						histoGlobal.historialGlobal[histoGlobal.ultIndiceUsado].puntaje = saldoFinal - saldoInicial; //PUNTAJE = SALDO FINAL - SALDO INNICIAL
					}
					jugador[posUsuario].regPartidas[jugador[posUsuario].cantPartidas].saldoF=jugador[posUsuario].saldo; //SALDO FINAL HISTO PERSONAL
					menuDeCuenta(posUsuario);
				}
				break;
			}

			case 5: { //SALIR
				if(perdida201){
					razon = rand()%3 + 1;
					razonOrgullo(razon);
					refmain=-1;
				}else{
					printf("Nos vemos la proxima\n");
					jugador[posUsuario].saldo = saldo;
					//printf("SALDO JUGADOR[POSUSUARIO].SALDO = %d",jugador[posUsuario].saldo);
					saldoFinal = saldo;
						if(saldoFinal-saldoInicial>0){ //GUARDO EN HISTOGLOBAL UNICAMENTE SI EL PUNTAJE ES POSITIVO
							histoGlobal.ultIndiceUsado++; //aumento el indice en 1
							//printf("UltIndiceUsado: %d\n",histoGlobal.ultIndiceUsado);
							strcpy(histoGlobal.historialGlobal[histoGlobal.ultIndiceUsado].nickname,jugador[posUsuario].nickname); //COPIO EL NICKNAME 
							//printf("Nickname en HISTOGLOBAL: %s\n",histoGlobal.historialGlobal[histoGlobal.ultIndiceUsado].nickname);
							histoGlobal.historialGlobal[histoGlobal.ultIndiceUsado].saldoInicial = saldoInicial; //GUARDO SALDO INICIAL 
							histoGlobal.historialGlobal[histoGlobal.ultIndiceUsado].saldoFinal = jugador[posUsuario].saldo; // SALDO FINAL HISTO GLOBAL
							histoGlobal.historialGlobal[histoGlobal.ultIndiceUsado].puntaje = saldoFinal - saldoInicial; //PUNTAJE = SALDO FINAL - SALDO INNICIAL
					}
					jugador[posUsuario].regPartidas[jugador[posUsuario].cantPartidas].saldoF=jugador[posUsuario].saldo; //SALDO FINAL HISTO PERSONAL
					//printf("SALDOI Y SALDOF: %d %d\n",jugador[posUsuario].regPartidas[jugador[posUsuario].cantPartidas].saldoI,jugador[posUsuario].regPartidas[jugador[posUsuario].cantPartidas].saldoF); //SOLO SIRVE PARA VER SI EL SALDO INICIAL Y FINAL SON CORRECTOS
                    menuDeCuenta(posUsuario);
				}
				break;
			}

		} //termina switch
	} //termina while(saldo>0)

	printf("Fin del juego");
}


int main(){
	printf("\n*--------------------------------------------------------------*\nBienvenido/a, a continuacion comenzaremos a jugar.\nPara cada jugada debes indicar en que copa se encuentra la bola.\nRecuerda que tambien puedes optar por retirarse marcando ''Salir''.\n\n");
	cargaJugadores();
	menuInicio();
}