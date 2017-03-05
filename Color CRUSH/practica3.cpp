#include <iostream>
#include <ctime>
#include <cstdlib>
#include <Windows.h>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include <string>
using namespace std;
//solicitar movimiento para pedirlos con comas,quitar inicializar grupo de fichas,comentar funciones del principio
const int COLUMNA=8;
const int FILA=8;
const int INTENTOS=15;
const int NumColores = 4;
const bool Debug=false;
const int  SLEEP=300;
typedef enum {magenta,amarillo,azul,verde,none} tFicha;
	
typedef enum {arriba, abajo, izquierda, derecha,error}tDireccion;	

typedef bool tGrupoDeFichas[FILA][COLUMNA];

typedef enum { // Screen colors
black, // 0
dark_blue, // 1
dark_green, // 2
dark_cyan, // 3
dark_red, // 4
dark_magenta, // 5
dark_yellow, // 6
light_gray, // 7
dark_gray, // 8
light_blue, // 9
light_green, // 10
light_cyan, // 11
light_red, // 12
light_magenta, // 13
light_yellow, // 14
white // 15
} tColor;	

typedef struct {
	int fila;
	int columna;
	tDireccion direccion;
}tMovimiento;
	
typedef tFicha tTablero[FILA][COLUMNA];

typedef struct {
	tTablero tablero;
	int intentosRestantes;
	int puntuacion;
}tJuego;

const int MAX = 100;//maximo de jugadores
typedef struct {
   string nombre;
   int juegos;
   int puntos;
} tJugador;
typedef tJugador tArray[MAX];
typedef struct {
   tArray elementos;
   int contador;
} tLista;


void inicializarJuego(tJuego & juego);
void inicializarGrupoDeFichas(tGrupoDeFichas grupoDeFichas);
void puntuar(tJuego &juego,int cont);
void comprobacionFilas( tJuego&juego, tGrupoDeFichas grupoDeFichas);
void comprobacionColumnas( tJuego&juego, tGrupoDeFichas grupoDeFichas);
void eliminarFichas(tJuego& juego, tGrupoDeFichas grupoDeFichas,bool &cambio);
void generarTablero(tTablero tablero);
void setColor(tColor color);
void mostrarTablero(const tJuego&juego);
void tableroParteSuperior(const tJuego &juego);
void TableroParteMedia (const tTablero tablero);
void TableroParteInferior();
void caidaDeFichas(tTablero  tablero,bool &caida);
void procesarTablero(tJuego &juego);
void bucleDeCaida (tJuego &juego);
void crearMovimiento(tMovimiento &movimiento, int fila,int columna,char direccionFicha);
tDireccion letraADireccion(char c);
void calcularDirecccion(int & incrementoFila,int& incrementoColumna,const tDireccion& direccion);
void ejecucionDeMovimiento(tTablero tablero,tMovimiento& movimiento,bool & movimientoValido);
void intercambio(const tMovimiento &movimiento,tTablero tablero,bool &exito);
bool creacionDeGrupo(const tTablero tablero,int fila,int columna);
void jugar(tJuego &juego);
void guardarPartida(const tJuego& juego);
void recuperarPartida(tJuego & juego);
int elegirTablero();
void cargarTablero(tTablero tablero);
int menu(); // Menú del programa - devuelve la opción elegida
void cargar(tLista &lista, bool &ok); // Carga el archivo en la lista
void guardar(const tLista &lista); // Guarda la lista en el archivo
void leerJugador(tJugador &jugador,string &nombrejugador); // Lee los datos
void insertarJugador(tLista &lista, tJugador jugador, bool &ok); // Inserta un nuevo Jugador en la lista
void partida(tLista &lista,int puntostotales,int pos);//modifica los puntos y partidas
void mostrarJugador(tJugador jugador); 
void listado(const tLista &lista); // Lista de la clase
void jugadorRepetido(const tLista lista,bool& encontrado,int& pos,string nombrejugador);//comprueba si un jugador esta e indicas su posicion



void inicializarJuego(tJuego & juego){

	int tipoDePartida;
    tipoDePartida=elegirTablero();
	if(tipoDePartida==3){
		recuperarPartida( juego);
	}else{
		//inicializacion de intentos
		juego.intentosRestantes=INTENTOS;
		//inicializacion de la puntuacion
		juego.puntuacion=0;
		if(tipoDePartida==1)
			//tablero aleatorio
			generarTablero(juego.tablero);
		else
			//tablero de archivo
			cargarTablero(juego.tablero);
	
	
	}
}
	
void inicializarGrupoDeFichas(tGrupoDeFichas grupoDeFichas){
	//no hay grupos de fichas,todo a false
	for(int fila = 0; fila < FILA; fila++){
		for(int columna = 0; columna < COLUMNA; columna++){
			grupoDeFichas[fila][columna] = false;
		}
	}
}

void puntuar(tJuego &juego,int cont){
	int puntos=0;
	if (cont=3)
		puntos=3;
	if(cont=4)
		puntos=8;
	if(cont>=5)
		puntos=15;
		
	juego.puntuacion=juego.puntuacion+puntos;
}

	
void comprobacionFilas( tJuego&juego, tGrupoDeFichas grupoDeFichas){
	
	int cont = 1, posicion;
	//ficha auxiliar
	tFicha tmp = none, fichaActual;
	//inicializacion del boleano a false
	inicializarGrupoDeFichas( grupoDeFichas);
	//Comprobacion de Filas
	for(int fila = 0; fila < FILA; fila++){
		for(int columna = 0; columna < COLUMNA; columna++){
			fichaActual = juego.tablero[fila][columna];
			//comprobacion si la ficha anterior es igual a la actual
			if(fichaActual == tmp)
				cont++;				
			else{
				tmp = fichaActual;
				//si el contador es mayor que se ha generado un grupo de fichas y hay que poner el booleano a true
				if(cont >= 3){
					posicion = columna;
					//sumamos la puntuacion
					puntuar( juego, cont);
					for(int k = cont; k > 0; k--){
						grupoDeFichas[fila][posicion-1] = true;
						posicion--;
					}
				}
				cont = 1;
			}
			//comprobacion de la ultima columna por si se ha formado un grupo
			if (columna == COLUMNA-1){
				if (cont >= 3){
					posicion = columna;
					//sumamos la puntuacion
					puntuar( juego, cont);
					for (int k = cont; k > 0; k--){
						grupoDeFichas[fila][posicion] = true;
						posicion--;
					}
				}
			}
		}
		cont = 1;
		tmp = none;
	}
}

void comprobacionColumnas( tJuego&juego, tGrupoDeFichas grupoDeFichas){
	int cont = 1, posicion;
	//ficha auxiliar
	tFicha tmp = none, fichaActual;
	//comprobacion de columnas
	for(int columna = 0; columna < COLUMNA; columna++){
		for(int fila = 0; fila < FILA; fila++){
			fichaActual = juego.tablero[fila][columna];
			//comprobacion de la ficha actual con la anterior
			if(fichaActual == tmp)
				cont++;				
			else{
				//la ficha anterior es distinta a la actual
				tmp = fichaActual;
				//si el contador es mayor que 3 se ha fomado un grupo
				if(cont >= 3){
					posicion = fila;
					//sumar puntuaciones
					puntuar( juego, cont);
					//ponemos el booleano a true
					for(int k = cont; k > 0; k--){
						grupoDeFichas[posicion-1][columna] = true;
						posicion--;
					}
				}
				cont = 1;
			}
			//comprobacion de la ultima fila por si se ha formado un grupo
			if (fila == FILA-1){
				if (cont >= 3){
					posicion = fila;
					puntuar( juego, cont);
					for (int k = cont; k > 0; k--){
						grupoDeFichas[posicion][columna] = true;
						posicion--;
					}
				}
			}
		}
		cont = 1;
		tmp = none;
	}
}



void eliminarFichas(tJuego& juego, tGrupoDeFichas grupoDeFichas,bool &cambio){
	bool  comp;
	cambio=false;
	//recorrido por el tablero
	for(int fila = 0; fila < FILA; fila++){
		for(int columna = 0; columna < COLUMNA; columna++){
			comp = grupoDeFichas[fila][columna];
			//si se ha formado un grupo de fichas,las eliminamos
			if(comp){
				juego.tablero[fila][columna] = none;
				cambio=true;
			}
		}
	}
}

void generarTablero(tTablero tablero) {	
		//generacion de tablero con fichas aleatorias
		for(int fila=0;fila<FILA;fila++){		
			for(int j=0;j<COLUMNA;j++){
				tablero[fila][j]=(tFicha)(rand() % NumColores) ;
			}
		}
}
void setColor(tColor color) {
HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleTextAttribute(handle, color);
}

void mostrarTablero(const tJuego&juego){
	if(!Debug){
		//se borra el tablero cada vez que se muestra
		system("cls");
		tableroParteSuperior(juego);
		TableroParteMedia(juego.tablero);
		TableroParteInferior();
		Sleep(SLEEP);
	}else{
		//pide al usuario que introduzca una tecla para mostrar el tablero
		tableroParteSuperior(juego);
		TableroParteMedia(juego.tablero);
		TableroParteInferior();
		system("pause");
	}
}

void tableroParteSuperior(const tJuego &juego) {	
	//muestra los intentos restantes y los puntos acumulados
	cout <<"  Intentos:"<< juego.intentosRestantes<<"  Puntos: "<<juego.puntuacion<<endl;
	cout <<" "<< char(218);
	for(int columna = 0; columna < COLUMNA; columna++){
		for(int j = 0; j < 3; j++)
			cout << char(196);
		if(columna!=COLUMNA-1)
			cout << char (194);
		else
			cout << char (191)<<endl;
	}
}
void TableroParteMedia (const tTablero tablero){
	cout<<FILA;
	for (int fila = FILA-1; fila >= 0; fila--){		
		cout << char(179);
		for(int columna = 0; columna < COLUMNA; columna++){
			//rellena la ficha del color que le corresponde
			if(tablero[fila][columna]==magenta)
				setColor(light_magenta);
			if(tablero[fila][columna]==azul)
				setColor(light_blue);
			if(tablero[fila][columna]==amarillo)
				setColor(light_yellow);
			if(tablero[fila][columna]==verde)
				setColor(light_green);
			if(tablero[fila][columna]==none)
				setColor(black);
			cout<< char(219)<< char(219) << char(219);		
				setColor(white);
				cout<< char(179);
		}
		if(fila>0){
			cout <<endl<<" "<< char(195);
			for(int v=0;v<COLUMNA;v++){
				for(int k = 0; k < 3; k++)
					cout << char(196);	
				if(v<COLUMNA-1)
					cout << char (197);
				else{
					cout << char(180)<<endl;
					cout<<fila;
				}
			}
		}
	}
}
void TableroParteInferior(){
	cout <<endl<<" "<< char(192);
	for(int columna = 0; columna< COLUMNA; columna++){
		for(int j = 0; j < 3; j++)
			cout << char(196);
		if(columna!=COLUMNA-1)
			cout << char (193);
		else
			cout << char (217)<<endl<<setw(4);
	}
	//numero de columnas
	for (int columna = 1; columna <= COLUMNA; columna++){
		cout << columna << setw(4);
	}
	cout << " " << endl;
	cout << endl;
}

void caidaDeFichas(tTablero  tablero,bool &caida){
	tFicha tmp;
	caida=false;
		//recorrido por el tablero
		for (int columna = 0; columna < COLUMNA; columna++){
			for(int fila=0; fila<FILA-1;fila++){
				//si la en la posicion no hay fichas caen las de arriba
				if (tablero[fila][columna] == none){			
					caida=true;
					tmp = tablero[fila][columna];
					tablero[fila][columna] = tablero[fila+ 1][columna];					
					tablero[fila+1][columna] = tmp;			
				}	
			}
			//si la ultima fila esta vacia se genera una ficha aleatoria
			if(tablero[FILA - 1][columna]==none){
				tablero[FILA - 1][columna] = (tFicha)(rand() % NumColores);
				caida=true;
			}
		}	
}

void procesarTablero(tJuego &juego){
	bool cambio=true;
	tGrupoDeFichas grupoDeFichas;
	while(cambio){		
		//busca y destruye los grupos de fichas (notifica si hay cambios)
		comprobacionFilas(juego, grupoDeFichas);
		comprobacionColumnas(juego, grupoDeFichas);
		eliminarFichas(juego, grupoDeFichas,cambio);
		if(cambio){
			//muestra el tablero
			mostrarTablero(juego);
			//caída de fichas para ocupar las celdas vacías
			bucleDeCaida(juego);
		}
	}
}
 void bucleDeCaida (tJuego &juego){
	bool caida=true;
		while(caida){
			//dejamos caer las fichas
			caidaDeFichas(juego.tablero, caida);
				if(caida){
					//muestra el tablero
					mostrarTablero(juego);
					
				}
		}
}

void crearMovimiento(tMovimiento &movimiento, int fila,int columna,char direccionFicha){
	
	movimiento.fila=fila;
	movimiento.columna=columna;
	//convierte la letra a mayuscula 
	direccionFicha= toupper(direccionFicha) ; 
	//convierte el caracter a un tipo tDireccion
	movimiento.direccion=letraADireccion(direccionFicha);
}
	
	

tDireccion letraADireccion(char c){
	tDireccion direccion;

	switch (c) {
		case 'A':
			direccion= arriba;
			break;
		case 'B':
			direccion = abajo;
			break;
		case 'I':
			direccion = izquierda;
			break;
		case 'D':
			direccion = derecha;
			break;
		default:
			direccion=error;
			break;
	}
	return direccion;
}

void calcularDirecccion(int & incrementoFila,int& incrementoColumna,const tDireccion& direccion){
	incrementoFila=0;
	incrementoColumna=0;
	switch(direccion){
		case arriba:
			incrementoFila=1;
			break;
		case abajo:
			incrementoFila=-1;
			break;
		case izquierda:
			incrementoColumna=-1;
			break;
		case derecha:
			incrementoColumna=1;
			break;
	}
}

void ejecucionDeMovimiento(tTablero tablero,tMovimiento& movimiento,bool & movimientoValido){
	int  incrementoFila,incrementoColumna;
	bool exito;
	movimientoValido=false;
	//comprobacion si la fila y columna introducidas por el ususario son validas
	if((movimiento.fila<=8) && (movimiento.columna<=8) && (movimiento.fila>0) && (movimiento.columna>0)){
		//comprobacion si la direccion es valida
		if(movimiento.direccion!=error){
		//calcular direccion
		calcularDirecccion(incrementoFila, incrementoColumna, movimiento.direccion);
			//comprobacion si la ficha a intercambiar esta dentro del tablero
			if((movimiento.fila+incrementoFila<=8) && (movimiento.columna+incrementoColumna<=8) && (movimiento.fila+incrementoFila>0) && (movimiento.columna+incrementoColumna>0)){
				//intercambiamos las fichas y notificamos si el movimeinto ha sido valido
				intercambio(movimiento, tablero,exito);
				if(exito)
					movimientoValido=true;
			}
		}
	}
}
			
void intercambio(const tMovimiento &movimiento,tTablero tablero,bool &exito){
	tFicha tmp;	
	int incrementoFila,incrementoColumna,filaFichaIntercambio,columnaFichaIntercambio;
	//calcular direccion
	calcularDirecccion(incrementoFila, incrementoColumna, movimiento.direccion);
	//se resta-1 porque el tablero va de 0 a 7 y se crea la fila y la columna de la ficha a intercambiar
	filaFichaIntercambio=movimiento.fila+incrementoFila-1;
	columnaFichaIntercambio=movimiento.columna+incrementoColumna-1;
	//intercambiamos las fichas
	tmp = tablero[movimiento.fila-1][movimiento.columna-1];
	tablero[movimiento.fila-1][movimiento.columna-1] = tablero[filaFichaIntercambio][columnaFichaIntercambio];					
	tablero[filaFichaIntercambio][columnaFichaIntercambio] = tmp;
	//notificamos si se ha formado un grupo al intercambiar		
	if((creacionDeGrupo(tablero,movimiento.fila-1,movimiento.columna-1)) ||( creacionDeGrupo(tablero,filaFichaIntercambio,columnaFichaIntercambio)))
		exito=true;
	else{
	//no ha tenido exito,cambiamos las fichas a su posicion inicial
		exito=false;
		tmp = tablero[filaFichaIntercambio][columnaFichaIntercambio];
		tablero[filaFichaIntercambio][columnaFichaIntercambio]=tablero[movimiento.fila-1][movimiento.columna-1]	;				
		tablero[movimiento.fila-1][movimiento.columna-1] = tmp;
	}
}
bool creacionDeGrupo(const tTablero tablero,int fila,int columna){
	bool ok=false;
	int cont=1,filaAnterior=fila+1,filaPosterior=fila-1,columnaDerecha=columna+1,columnaIzquierda=columna-1;
	//comprobamos si se ha creado un grupo con las fichas superiores
	while((tablero[fila][columna]==tablero[filaAnterior][columna]) && (cont!=3)){
		cont++;
		filaAnterior++;
	}
	//comprobamos si se ha creado un grupo con las fichas inferiores
	while((tablero[fila][columna]==tablero[filaPosterior][columna]) && (cont!=3)){
		cont++;
		filaPosterior--;
	}
	//si no se ha creado un grupo todavia lo comprobamos con las fichas de la derecha y de la izquierda
	if(cont>=3)
		ok=true;
	else{
		cont=1;
		while((tablero[fila][columna]==tablero[fila][columnaDerecha]) && (cont!=3)){
			cont++;
			columnaDerecha ++;
		}	
		while((tablero[fila][columna]==tablero[fila][columnaIzquierda]) && (cont!=3)){
			cont++;
			columnaIzquierda--;
		}
	}
	if(cont>=3)
		ok=true;
return ok;
}			

void jugar(tJuego &juego){
	bool end=false,movimientoValido,guardar=false;
	int fila,columna;
	tLista lista;
	char direccionFicha,c;
	tMovimiento movimiento;
	inicializarJuego(juego);
	mostrarTablero(juego);		
	procesarTablero(juego);
	while(!end ){
	    //miramos si todavia quedan intentos
		if(juego.intentosRestantes==0)			
			end=true;
		else{
			//solicitamos movimiento
			cout<<"Fila, columna y letra de direccion(A,B,I o D),0 para cancelar: ";
			cin >> fila;
			//si ha introducido un cero,el juego termina
			if(fila==0){
				//preguntamos al usuario si quiere guardar la partida
				cout<<"Desea guardar la partida (S/N)?:";
				cin >>c;
				guardar=toupper(c)=='S';
				if (guardar)
					guardarPartida( juego); 
				end=true;
			}else{
				cin>>columna;
				cin>>direccionFicha; 
				//creamos el movimiento
				crearMovimiento(movimiento, fila, columna,direccionFicha);
				//comprobamos si el movimiento es valido
				ejecucionDeMovimiento( juego.tablero, movimiento,movimientoValido);
				if(!movimientoValido)
					//si no es valido,volvemos a pedir otro al usuario
					cout<<"Movimiento incorrecto! intentelo otra vez..."<<endl;
				else{
					//restamos un intentos ,mostramos el tablero y lo procesamos
					juego.intentosRestantes=juego.intentosRestantes-1;
					mostrarTablero(juego);
					procesarTablero(juego);
				}
			}
		}
	}
}
void guardarPartida(const tJuego& juego){
	ofstream archivo;
	string nombrePartida;
	//solicitamos nombre para guardar la partida
	cout<<"indique un nombre para guardar la partida: ";
	cin>>nombrePartida;
	//añadimos al nombre el formato txt
	nombrePartida=nombrePartida+".txt";
	archivo.open(nombrePartida.c_str());
	//guardamos en el archivo el tablero,puntuaciones e intentos
    archivo << juego.intentosRestantes << endl;
    archivo << juego.puntuacion << endl;
    for(int fila = FILA-1; fila >= 0; fila--){
		for(int columna = 0; columna < COLUMNA; columna++){
			archivo<<juego.tablero[fila][columna]<<" ";
		}
		archivo<<endl;
	}
   
   archivo.close();
}

void recuperarPartida(tJuego & juego){
	ifstream archivo;
	int n;
	bool abierto=false;
	string nombrePartida;
	do{
		cout<<"Indique la partida que quiere recuperar: ";
		cin >> nombrePartida;
		cout<<endl;
		nombrePartida=nombrePartida+".txt";
		archivo.open(nombrePartida.c_str());
		if (!archivo.is_open()) 
			cout << "Lo siento! No he podido encontrar la partida, pruebe con otro nombre.." << endl;
		else{
			abierto=true;
			archivo >> juego.intentosRestantes ;
			archivo >> juego.puntuacion ;
			for(int fila = FILA-1; fila >= 0; fila--){
				for(int columna = 0; columna < COLUMNA; columna++){
					//posicion en el enumerado
					archivo>>n;
					//transformacion a tipo tFicha
					juego.tablero[fila][columna]=tFicha(n);
				}
			}
		}
   }while(!abierto);
   archivo.close();
}
int elegirTablero() {
	int op;
	cout<<"Que opcion prefiere?"<<endl;
	do {
		cout << "1 - Generar tablero aleatoriamente" << endl;
		cout << "2 - Cargar tablero" << endl;
		cout << "3 - Recuperar una partida" << endl;
		cout << "Opcion: ";
		cin >> op;
		cout << endl;
	} while ((op < 1) || (op > 3));

   return op;
}
void cargarTablero(tTablero tablero){
	ifstream archivo;
	int n;
	bool abierto=false;
	string nombrePartida;
	do{
		cout<<"Indique el tablero que quiere cargar: ";
		cin >> nombrePartida;
		cout<<endl;
		nombrePartida=nombrePartida+".txt";
		archivo.open(nombrePartida.c_str());
		if (!archivo.is_open()) 
			cout << "Lo siento! No he podido encontrar el tablero, pruebe con otro nombre.." << endl;
		else{
			abierto=true;
			for(int fila = FILA-1; fila >= 0; fila--){
				for(int columna = 0; columna < COLUMNA; columna++){
					//posicion en el enumerado
					archivo>>n;
					//transformacion a tipo tFicha
					tablero[fila][columna]=tFicha(n);
				}
			}
		}
   }while(!abierto);
   archivo.close();
}
int menu() {
	int op;
	do {
		cout << "1 - Jugar" << endl;
		cout << "2 - Puntuaciones" << endl;
		cout << "0 - Salir" << endl;
		cout << "Opcion: ";
		cin >> op;
		cout << endl;
	} while ((op < 0) || (op > 2));

   return op;
}
void cargar(tLista &lista, bool &ok) {
	tJugador jugador;
	ifstream archivo;
	char aux;	
	lista.contador = 0; // Inicializamos la lista
	archivo.open("usuarios.txt");
	if (!archivo.is_open()) {
		ok = false;
	}else {
		ok = true;
		archivo >> jugador.nombre; // Leemos el primer nombre
		while ((jugador.nombre != "XXX") && (lista.contador < MAX)) {
			archivo >> jugador.juegos;
			archivo >> jugador.puntos;
			archivo.get(aux); // Saltamos el Intro
			lista.elementos[lista.contador] = jugador; // Al final
			lista.contador++; 
			archivo >> jugador.nombre; // Siguiente nombre
		} // Si hay más de MAX Jugadors, ignoramos el resto
		archivo.close();
	}
}

void guardar(const tLista &lista) {
	ofstream archivo;
	archivo.open("usuarios.txt");
	for (int i = 0; i < lista.contador; i++) {
		archivo<<lista.elementos[i].nombre<<setw(8);
		archivo << lista.elementos[i].juegos <<setw(8);
		archivo << lista.elementos[i].puntos <<endl;
	}
	archivo << "XXX" << endl; // Centinela final
	archivo.close();
}

void leerJugador(tJugador &jugador,string &nombrejugador) {
	cin.sync();
	cout << endl;
	cout << "Bienvenido a Color crush! Por favor,introduce tu nombre: ";
	cin>> nombrejugador;
	jugador.nombre=nombrejugador;
	jugador.juegos=0;
	jugador.puntos=0; 
	cin.sync(); // Descartamos cualquier entrada pendiente
}

void insertarJugador(tLista &lista, tJugador jugador,bool& ok){
	ok = true;
	if (lista.contador == MAX) {
		ok = false;
	}else {
		lista.elementos[lista.contador] = jugador;
		lista.contador++;
	}
}

void partida(tLista &lista,int puntostotales,int pos) {
 	
	lista.elementos[pos].juegos=(lista.elementos[pos].juegos+1);
	lista.elementos[pos].puntos=(lista.elementos[pos].puntos+puntostotales);
	
}
void mostrarJugador(tJugador jugador) {
	cout << setw(28) << left << jugador.nombre ;
	cout << jugador.juegos << " ";
	cout << setw(10) << right << jugador.puntos;
	
}

void listado(const tLista &lista) {
	cout << right << setw(11) << "Nombre" << right << setw(25) << "Partidas terminadas" << right << setw(12) << "Puntuacion" <<endl;
	cout << endl;
	for (int i = 0; i < lista.contador; i++){
		cout << setw(3) << right << i + 1 << ": ";
		mostrarJugador(lista.elementos[i]);
		cout << endl;
	}	
	cout << endl;
}
void jugadorRepetido(const tLista lista,bool& encontrado,int& pos,string nombrejugador) {
	encontrado=false; 
	int cont=0;
	while ((cont < lista.contador) && (!encontrado)){
		if (lista.elementos[cont].nombre == nombrejugador) {
			encontrado=true;//esa persona ya ha jugado alguna vez
			pos = cont;
		}
		cont++;
	}
	//si no ha jugado nunca,se le añade a la ultima posicion
	if(!encontrado){
		pos=lista.contador;
    }
}

int main(){	
	tJuego juego;	
	bool encontrado,exito;
	tLista lista;
	tJugador jugador;  
	int op, pos;
	string nombrejugador;
    srand(time(NULL));
	cargar(lista, exito);
	if (!exito) {
		cout << "No se ha podido cargar la lista!" << endl;
	}else{
		leerJugador(jugador,nombrejugador);
		jugadorRepetido(lista,encontrado, pos,nombrejugador);
		if(!encontrado){
			insertarJugador(lista, jugador, exito);
		}
		if (!exito){ 
			cout << "Lista llena: imposible insertar" << endl;
		}
		cout<<"Hola "<<nombrejugador<<" elige una opcion: "<<endl;
		do { 
			op = menu();
			switch (op) {
				case 1:
					jugar(juego);
					//si el jugador ha terminado el juego se le suma la puntuacion y el numero de partidas jugadas
					if(juego.intentosRestantes==0)
						partida(lista,juego.puntuacion,pos);
					
					break;
				case 2:
					listado(lista);       
			} 
		}while (op != 0);
		guardar(lista);
	}
	
	
return 0;	
}