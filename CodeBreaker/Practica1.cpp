//Verónica Morante Pindado y Jose Moreno Varillas L3-G8
#include <iostream>
#include <cstdlib> // srand(), rand()
#include <ctime>    // time()
#include <fstream>
#include <string>
#include <cmath> // pow
using namespace std;


int longitud = 4;
int intentos = 3;
int intervalo = 3; 
// funciones definidas por el programador

int invertir(int codigo);
int invertir(int clave);
int codeBreaker();
int menu();
int claveAleatoria(int longitud, int intervalo);
bool codigoValido(int codigo);
int numeroBips(int codigo, int clave);
bool mostrar(string NombArch);

int pedirIntentos(){
	do{
		cout << "Introduce el numero de intentos que desea: ";
		cin >> intentos;
		cout << "Numero de intentos modificado"<<endl;
	}while(intentos<0);
	return intentos;
};
int pedirLongitud (){
	do{
		cout << "Introduce la longitud que desea: ";
		cin >> longitud;
		cout << "Longitud modificada"<<endl;
		
	}while(longitud<0);
	return longitud;
};
int pedirIntervalo (){	
	do{
		cout << "Introduce el digito maximo: ";
		cin >> intervalo;
		cout << "Intervalo de digitos modificado"<<endl;
		
	}while(intervalo<0);
	return intervalo;
}; 

int menu(){
	int opcion = -1;// valor inicial de opcion para que entre en el while
	while ((opcion < 0) || (opcion > 5)) {
	cout << endl;
	cout << "1 - Jugar" << endl;
	cout << "2 - Cambiar el maximo de intentos" << endl;
	cout << "3 - Cambiar la longitud de los codigos" << endl;
	cout << "4 - Cambiar el intervalo de digitos" << endl;
	cout << "5 - Acerca de CodeBreaker" << endl;
	cout << "0 - Salir" << endl;
	cout << endl;
	cout << "Opcion: ";
	cin >> opcion;
	if ((opcion < 0) || (opcion > 5)) {
         cout << "opcion no valida!" << endl;
      }//opcion no valida
   }// vuelve a mostrar el menu si la opcion elegida no es valida
	return opcion;
};

int codeBreaker(){
	int clave, codigo, i=0, bips=0,intentos2;
	bool comp, comprobacion=false;
	clave = claveAleatoria(longitud, intervalo);
	do{
	cout << "Introduce un codigo(0 para abandonar): ";
		cin >> codigo;
		if(codigo!=0){	
		i++;		
		comp = codigoValido(codigo);
			if (comp==false){
				cout << "El codigo  excede la longitud o contiene digitos no validos" << endl;	
			}else{	
				bips=numeroBips(codigo,clave);
				if(bips==longitud){	
					for(int i = 1; i <= bips; i++){
						cout <<"Bip " ;
					}
					cout << "OK!" << endl;
					comprobacion=true;
				}else{
					for(int i = 1; i <= bips; i++){ 
						cout <<"Bip ";
					}
					cout <<"Bop -- Acceso denegado"<< endl;
				}
			}// comp=true
		};//codigo=0,abandona el juego
	}while ((i < intentos)&&(clave!=codigo)&&(codigo!=0) );//para cuando has acertado la clave o has llegado al maximo de intentos
	if(comprobacion==true){
		intentos2=i;
	} // Has adivinado la clave
	if(comprobacion==false && codigo!=0){
		intentos2=i+1;
	} // Has llegado al maximo de intentos y no lo has acertado
	if(codigo==0){
		intentos2=0;
	};	
	return intentos2;
};

int claveAleatoria(int longitud, int intervalo){
	int num, clave;
	clave = 0;
	do {
		num = rand() % intervalo + 1;
		clave = clave * 10 + num;
	}while (clave < (pow(10, (longitud - 1))));
	return clave;
};

int invertir(int numero){
	int numeroInvertido = 0;
	do{
		numeroInvertido = numeroInvertido*10 + numero % 10;
        numero = numero / 10;
	}while( numero > 0);
	return numeroInvertido;
};

bool codigoValido(int codigo){
	bool comp;
	int contador=0 ,resultado=0;
	do{
		resultado=codigo%10;
		codigo=codigo/10;
		if((resultado!=0) && (resultado <= intervalo)){
			contador++;
		}; // el contador suma cuando un digito del codigo es valido
	}while ((resultado <= intervalo) && (resultado != 0) && (codigo!=0));// sale cuando un resultado no es valido o cuando no puede dividir mas
		if(contador!=longitud){
			comp = false;
		}else{
			comp = true;
		};
	return comp;
};

int numeroBips(int codigo, int clave){
	int d1, d2, claveInvertida, codigoInvertido, i=0, bips = 0;
	codigoInvertido = invertir(codigo);
	claveInvertida = invertir(clave);
	do{
		d1 = codigoInvertido % 10;
		d2 = claveInvertida % 10;
		codigoInvertido = codigoInvertido / 10;
		claveInvertida = claveInvertida / 10;
		if (d1 == d2){
			bips++; 
			}//coinciden digito de la clave y del codigo
		
	}while((bips < longitud)&&(d1==d2));
	return bips;
};
 bool mostrar(string NombArch){
	bool compr;
	ifstream archivo2;
	archivo2.open("VersionCB.txt");
	if(!archivo2.is_open()) {
	compr=false;
	}else{
		compr=true;
	};//archivo abierto
	archivo2.close();
	return compr;
};

int main(){
	int intentos2,opcion;
	string NombArch;
	bool compr;//Declaraciones de variables
		srand(time(NULL));
	ifstream archivo1;
	archivo1.open("ConfigCB.txt");
	archivo1 >> intentos;
	archivo1 >> longitud;
	archivo1 >> intervalo;
	archivo1.close(); // lee del archivo los valores iniciales de las variable,si no toma los valores iniciales
	 
	opcion = menu();
    while (opcion != 0) {
		switch (opcion) {
			case 1: {
				cout << endl << "Let's play!" << endl;
				intentos2=codeBreaker();
                if(intentos2!=0){
					if(intentos2<=intentos){
						cout << "Has utilizado " << intentos2<< " intentos" << endl;
					}else{
						cout <<"Has llegado al maximo de intentos" << endl;
					}// intentos2 = intentos+1
				};//intentos2=0
			}//case1
			break;
			case 2: {
				pedirIntentos();
			} // case2
			break;
			case 3:{ 
				pedirLongitud();
			}//case3
			break;
			case 4:{ 
				pedirIntervalo();
			}//case4
			break;
			case 5: {
				compr = mostrar("VersionCB.txt");
				if(compr==true){
					ifstream archivo2;
					archivo2.open("VersionCB.txt");
					while(!archivo2.eof()){
						getline(archivo2,NombArch);
						cout<<NombArch<<endl; 
					}
					cout << endl;
					archivo2.close();					
				}else{
					cout << "Error al abrir el archivo versionCB.txt" << endl;
				}; // el archivo no esta abierto
			};//case5
		};// switch 
		ofstream archivo;
		archivo.open("configCB.txt");
		archivo <<intentos << endl;
		archivo <<longitud<< endl;
		archivo <<intervalo << endl;
		archivo.close(); // guarda intentos,longitud e intervalo tras modificarlo
		opcion = menu();//vuelve al menu tras haber finalizado una opcion
	};// while (opcion != 0)
 //codigo que implementa la practica
	return 0;
}; // main
