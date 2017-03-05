#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <sstream>
using namespace std;
#include "Mensaje.h"

//muestra la fecha por pantalla
string mostrarFecha(tFecha fecha);
	

string mostrarMensaje(tMensaje mensaje){
	stringstream resultado;
	resultado << mensaje.origen << " (" << mostrarFecha(mensaje.fecha)<<"): " << mensaje.cadena << endl;
	return resultado.str();
}

void crearMensaje(string emisor,string receptor,string texto,tMensaje &mensaje){	
    mensaje.origen=emisor;
	mensaje.fecha = time(0);
	mensaje.receptor=receptor;
	mensaje.cadena=texto;
	
}

bool cargarMensaje(ifstream &archivo, tMensaje &mensaje){
	char aux;
	archivo >> mensaje.origen;
	archivo >> mensaje.fecha;
	//saltamos el espacio
	archivo.get(aux);
	getline(archivo, mensaje.cadena);
	
	return !archivo.fail();
}

void guardarMensaje(const tMensaje& mensaje,ofstream &archivo){
	archivo << mensaje.origen << " ";
	archivo << mensaje.fecha<<" ";
	archivo << mensaje.cadena << endl;	
}

string mostrarFecha(tFecha fecha){
	stringstream resultado;
	tm* ltm = localtime (&fecha);
	resultado << 1900 + ltm->tm_year << "/" << 1 + ltm->tm_mon << "/" << ltm->tm_mday;
	resultado << ", " << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec;
	return resultado.str();
}

tFecha fechaMensaje(const tMensaje &mensaje){
	return mensaje.fecha;
}


string personaMensaje(const tMensaje& mensaje){
	return mensaje.origen;
}

