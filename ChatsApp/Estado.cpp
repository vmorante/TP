#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;
#include "Estado.h"

//PARTE OPCIONAL

bool cargarEstado(ifstream &archivo,tEstado &estado){
	char aux;
	archivo>>estado.nombreUsuario;	
	archivo>>estado.fecha;
	archivo.get(aux);
	getline(archivo,estado.mensajeDeEstado);
	
	
	return !archivo.fail();
}

void guardarEstado(const tEstado &estado,ofstream &archivo){
	archivo<<estado.nombreUsuario<<endl;
	archivo<<estado.fecha<<" ";
	archivo<<estado.mensajeDeEstado<<endl;
	
}

void mostrarEstado(const tEstado &estado){
	cout<<estado.nombreUsuario<<endl;
	if(estado.fecha==0)
		cout<<"No se ha conectado todavia"<<endl;
	else
		cout<<"ult.vez:"<<mostrarFecha(estado.fecha)<<endl;
	cout<<estado.mensajeDeEstado<<endl;
	for(int i=0;i<80;i++)
		cout<<char(196);
}

void accederEstado(tEstado &estado,string texto){
	estado.mensajeDeEstado=texto;
}

void accederFecha(tEstado &estado){
	estado.fecha=time(0);
}

string nombreUsuario(const tEstado &estado){
	return estado.nombreUsuario;
}

bool operator<(tEstado opIzq, tEstado opDer){
	 return opIzq.nombreUsuario < opDer.nombreUsuario;
}