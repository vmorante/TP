#include <iostream>
#include <cstdlib> // srand(), rand()
#include <ctime>    // time()
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

const int NumColores = 6;
const int Longitud = 4;
const int MaxIntentos = 30;
const bool Repeticion = false;
const string HelpFile = "ayuda.txt";


typedef enum { rojo, azul, verde, negro, granate, marron } tColores;

typedef tColores tCodigo[Longitud];
const int MAX = 100;
typedef struct {
   string nombre;
   int juegos;
   int ganados;
   int puntos;
} tJugador;
typedef tJugador tArray[MAX];
typedef struct {
   tArray elementos;
   int contador;
} tLista;

// funciones definidas por el programador

void generar(tCodigo codigo);
tColores letraAColor(char c);
char colorALetra(tColores color); 
void jugar(int& numintentos,int& puntostotales); // Devuelve el numero de intentos (0 si el jugador abandona el juego)
void leerCodigo(tCodigo codigo, bool& cancelar,bool& pista);
void chequear(const tCodigo secreto, const tCodigo jugador, int& correctos, int& descolocados);
void mostrarMovimiento(const tCodigo jugador, int intento, int correctos, int descolocados,int puntostotales);
void mostrarAyuda();
void puntuacion(int& puntostotales,int correctos, int descolocados );
bool Error(int , int,int );//verifica si un numero esta repetido para generar el codigo
void solicitarpista(const tCodigo secreto);
bool codigovalido(string cadena);
string colorNombredecolor(tColores color);

//funciones version 3
int menu(); // Menú del programa - devuelve la opción elegida
void cargar(tLista &lista, bool &ok); // Carga el archivo en la lista
void guardar(const tLista &lista); // Guarda la lista en el archivo
void leerJugador(tJugador &jugador,string &nombrejugador); // Lee los datos
void insertarJugador(tLista &lista, tJugador jugador, bool &ok); // Inserta un nuevo Jugador en la lista
void partida(tLista &lista,tJugador jugador,int puntostotales,int numintentos,int pos);//modifica los puntos,ganados y partidas
void mostrarJugador(tJugador jugador); 
void listado(const tLista &lista); // Lista de la clase
void jugadorRepetido(const tLista lista,tJugador jugador,bool& encontrado,int& pos,string nombrejugador);//comprueba si un jugador esta e indicas su posicion


bool Error(int n, int num[],int i){  
	if(!Repeticion) {
		for(int j=i; j>=0; j--){//comprobacion de los valores anteriores del array
			if(n == num[j]){//el numero esta repetido
				return true;
			}
		}
		return false;
	}//if
	return false;//no comprueba si los numeros son repetidos
}

void generar(tCodigo codigo) {
	int n, num[Longitud];
    for(int i=0; i<Longitud; i++){
		do{
			n= rand() % NumColores;
		}while(Error(n, num,i));
		num[i] = n;
		tColores color;
		color = tColores(num[i]);
        codigo[i]=color;
    }
};

tColores letraAColor(char c){
	tColores color;

	switch (c) {
		case 'R':
			color = rojo;
			break;
		case 'A':
			color = azul;
			break;
		case 'V':
			color = verde;
			break;
		case 'N':
			color = negro;
			break;
		case 'G':
			color = granate;
			break;
		case 'M':
			color = marron;
	}
	return color;
}
char colorALetra(tColores color){
  char letra;
	switch (color) {
	case  rojo:
		letra = 'R'; 
		break;
	case azul:
		letra ='A';
		break;
	case verde:
		letra = 'V';
		break;
	case negro:
		letra ='N';
		break;
	case granate:
		letra ='G';
		break;
	case marron:
		letra ='M';
		break;
	}
	return letra;
}
 
void jugar(int& numintentos,int& puntostotales) {
	int correctos,descolocados,intento=0,contadordepistas=0,pistaporintento=0;
	tCodigo secreto,jugador;
	bool cancelar,pista;
	puntostotales=0;	
	generar( secreto);
	numintentos=0;
	
	do{ 
		leerCodigo(jugador,cancelar,pista);
		if(cancelar){
			numintentos=0;
		}else{
			if(pista) {
				if(pistaporintento<5)//pista cada 5 intentos
				cout<<"Lo siento! Puedes conseguir una pista cada 5 intentos"<<endl;
			else{
				if(contadordepistas>=2){//maximo de pistas 2
					cout<<"Lo siento! El numero maximo de pistas es 2"<<endl;
					}
				else{
					solicitarpista(secreto);
					contadordepistas++;
					pistaporintento=0;
				}
			}
			}else{
				numintentos++;
				intento++;	
				pistaporintento++;
				chequear(secreto,jugador,correctos,descolocados);
				puntuacion(puntostotales,correctos,descolocados );
				mostrarMovimiento( jugador,intento,correctos,descolocados,puntostotales);
			}
			
		}//else
     
	}while((!cancelar) && (numintentos<MaxIntentos) && (correctos!=Longitud)); 
	if((numintentos==MaxIntentos)&&(correctos!=Longitud)){
		numintentos=MaxIntentos + 1;
	}//el jugador no ha acertado en el maximo de intentos

	
}
  
void leerCodigo(tCodigo codigo, bool& cancelar,bool& pista) {
	tColores color;
	string cadena;
	bool valido;
	pista=false;
	cancelar=false;
		cout<<"Codigo(? para ayuda,! para pista , 0 para cancelar): " ;
		cin>> cadena;
	do{	
		while(cadena[0]=='?'){
			mostrarAyuda();
			cout<<"Codigo(? para ayuda,! para pista ,0 para cancelar): " ;
			cin>> cadena;		
			}//whilw
			if(cadena[0]=='!') 
					pista=true;
			else{
				if(cadena[1]==0) 
					cancelar=true;			
				else{
					valido = codigovalido(cadena);
					if(valido==true){
						for (int i = 0; i < Longitud; i++){
						cadena[i]= toupper(cadena[i]) ;//convierte la cadena a mayuscula 
						color=letraAColor( cadena[i]);
						codigo[i]=color;
						}				
					}else{
					cout<<"Codigo(? para ayuda,! para pista ,0 para cancelar): " ;
					cin>> cadena;//el codigo no ha sido valido y te pide introducir otro codigo
					}
				}
					
			}
		}while((!cancelar) && (!valido) &&(!pista));
};
void chequear(const tCodigo secreto, const tCodigo jugador, int& correctos, int& descolocados) {
	int cont,j;
	correctos=0;
	descolocados=0;
	bool correcto[Longitud]={false} ,descolocado[Longitud]={false} ;
	
	for (int i = 0; i < Longitud; i++) {
		if ( secreto[i]==jugador[i])
			correcto[i] = true;	//misma posicion	 
	}

    for (int i =0 ; i < Longitud; i++) { 
		if(correcto[i]==0){//solo mira las posiciones donde no estan en la misma posicion
		j=i+1;//mira la posicion posterior a i,cuando llega al maximo vuelve al principio
		cont=0;
		do{
			if(j>=Longitud)
			j=0;//mira los numeros iniciales para ver si coinciden		
			if (secreto[i] == jugador[j]) {		  
				descolocado[i] =true;						
			}else{
				j++;
				cont++;
			} 
	    }while((cont<(Longitud-1))&& (!descolocado[i]));
		}//if
    }//for
	for (int i = 0; i < Longitud; i++){
		correctos=correctos +correcto[i];
		descolocados=descolocados + descolocado[i];
	}  //for
			
        
}
void mostrarMovimiento(const tCodigo jugador, int intento, int correctos, int descolocados,int puntostotales) {
  char letra;
	cout<<setw(3)<<intento<<": ";
	for (int i = 0; i < Longitud; i++){
		letra=colorALetra(jugador[i]);
		cout<<letra<<setw(2);
	}//for
    cout<<setw(6);
	cout<< correctos <<"ø"<<setw(8);
	cout<< descolocados <<"¤"<<setw(8);
	cout<<puntostotales<<"puntos"<<endl;
	
}
	
void mostrarAyuda(){
	bool encontrado;
	ifstream inputFile;
	string line;
	inputFile.open(HelpFile.c_str());
	if (!inputFile.is_open()) {
		cout << "Lo siento! No he podido encontrar el archivo de ayuda..." << endl;
	}
	else {
		getline(inputFile,line);
		encontrado=line=="XXX";
		while(!encontrado){
			cout<<line<<endl;
			getline(inputFile,line);
			encontrado=line=="XXX";
		}
		cout << endl;
		inputFile.close();	
	};//archivo abierto
	
};
void puntuacion(int& puntostotales,int correctos, int descolocados ){
int puntosparciales=0;
	if(correctos!=Longitud){
		puntosparciales=correctos*5 + descolocados*1;
	}else{
		puntosparciales=100*correctos;
	}
puntostotales=puntostotales + puntosparciales;//suma de los puntos en cada intento
	  
};
string colorNombredecolor(tColores color){
  string nombrecolor;
	switch (color) {
	case  rojo:
		nombrecolor ="rojo"; 
		break;
	case azul:
		nombrecolor="azul";
		break;
	case verde:
		nombrecolor= "verde";
		break;
	case negro:
		nombrecolor="negro";
		break;
	case granate:
		nombrecolor ="granate";
		break;
	case marron:
		nombrecolor="marron";
		break;
	}
	return nombrecolor;
}
void solicitarpista(const tCodigo secreto){
	int n ;
	string nombrecolor;
	n = rand() % Longitud;	//genera un aposicion aleatoria
    nombrecolor= colorNombredecolor( secreto[n]);
	cout<<"El color de la posicion "<<n+1<<" es: "<<nombrecolor<<endl;
			
};
bool codigovalido(string cadena){
int num=0,i=0,j=0;
bool comp=true;
	for (int i = 0; i < Longitud; i++)
		cadena[i]= toupper(cadena[i]);
					
	num=cadena.length();//longitud de la cadena introducida

if(num!= Longitud){
	cout<<"La Longitud de la cadena no es valida"<<endl;
	comp = false;}
else{
	do{
		if((cadena[i])==('R')||(cadena[i])==('V')|| (cadena[i])==('A')||(cadena[i])==('N')||(cadena[i])==( 'G')||(cadena[i])==('M')){
				 j= i+1;				 
				if(!Repeticion){
					do{
						if( cadena[i]==cadena[j]){
							cout<<"El codigo contiene letras repetidas"<<endl;
							comp =  false;
						}else
							j++;
					}while((comp) && (j<Longitud));						
				};//if
				j=0;
				i++;
		}else{
			cout<<"El codigo contiene letras no validos"<<endl;
			comp = false;
			}
	}while((comp) &&(i<Longitud));
};
return comp;
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
			archivo >> jugador.ganados;
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
		archivo<< lista.elementos[i].ganados <<setw(8);
		archivo << lista.elementos[i].puntos <<endl;
	}
	archivo << "XXX" << endl; // Centinela final
	archivo.close();
}

void leerJugador(tJugador &jugador,string &nombrejugador) {
	cin.sync();
	cout << endl;
	cout << "Bienvenido a Mastermind! Por favor,introduce tu nombre: ";
	cin>> nombrejugador;
	jugador.nombre=nombrejugador;
	jugador.juegos=0;
	jugador.ganados=0;
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

void partida(tLista &lista,tJugador jugador,int puntostotales,int numintentos,int pos) {
 	
	if (numintentos<=MaxIntentos){
		lista.elementos[pos].ganados=(lista.elementos[pos].ganados+1);
		lista.elementos[pos].juegos=(lista.elementos[pos].juegos+1);
		lista.elementos[pos].puntos=(lista.elementos[pos].puntos+puntostotales);
	}else{	
		lista.elementos[pos].juegos=(lista.elementos[pos].juegos+1);
		lista.elementos[pos].puntos=(lista.elementos[pos].puntos+puntostotales);
	} 
}
void mostrarJugador(tJugador jugador) {
	cout << setw(28) << left << jugador.nombre ;
	cout << jugador.juegos << " ";
	cout << setw(10) << right << jugador.ganados << setw(14);
	cout << fixed << setprecision(1) << jugador.puntos;
}

void listado(const tLista &lista) {
	cout << right << setw(11) << "Nombre" << right << setw(25) << "Juegos" << right << setw(12) << "Ganados" << right << setw(15) << "Puntuacion" << endl;
	cout << endl;
	for (int i = 0; i < lista.contador; i++){
		cout << setw(3) << right << i + 1 << ": ";
		mostrarJugador(lista.elementos[i]);
		cout << endl;
	}	
	cout << endl;
}
void jugadorRepetido(const tLista lista,tJugador  jugador,bool& encontrado,int& pos,string nombrejugador) {
	encontrado=false;   
	for (int i = 0; i < lista.contador; i++){
		if (lista.elementos[i].nombre == nombrejugador) {
			encontrado=true;//esa persona ya ha jugado alguna vez
			pos = i;
		}
	}
	if(!encontrado){
		pos=lista.contador;
    }
}
   
int main() {
	bool encontrado,exito;
	tLista lista;
	tJugador jugador;  
	int op, pos,puntostotales=0,numintentos;
	string nombrejugador;
    srand(time(NULL));
	cargar(lista, exito);
	if (!exito) {
		cout << "No se ha podido cargar la lista!" << endl;
	}else{
		leerJugador(jugador,nombrejugador);
		jugadorRepetido(lista, jugador,encontrado, pos,nombrejugador);
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
					jugar( numintentos,puntostotales);   			
					if(numintentos!=0){
						if(numintentos<=MaxIntentos){
							cout<<"Enhorabuena! Has ganado en "<<numintentos<<" intento(s)"<<endl;
						}else{
							cout<<"No lo has logrado en el maximo de intentos"<<endl;
						}
						partida(lista, jugador, puntostotales, numintentos, pos);
					}
					break;
				case 2:
					listado(lista);       
			} 
		}while (op != 0);
		guardar(lista);
	}
	return 0;
};