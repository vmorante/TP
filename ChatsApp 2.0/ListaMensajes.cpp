#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "ListaMensajes.h"

void redimensionarLista(tListaMensajes &listaMensajes,int nuevaDimension);
//inicializamos el contador y creamos el array
void inicializarListaMensajes(tListaMensajes &listaMensajes,int dimension);

void iniListaMensajes(tListaMensajes &listaMensajes){
	listaMensajes.cont=0;
	listaMensajes.tamano=DIMENSION;
	listaMensajes.mensaje=new tMensaje[listaMensajes.tamano];
	
}
void inicializarListaMensajes(tListaMensajes &listaMensajes,int dimension){
	listaMensajes.cont=0;
	listaMensajes.tamano=dimension;
	listaMensajes.mensaje=new tMensaje[listaMensajes.tamano];
}
bool cargarColaMensajes(ifstream &archivo ,tListaMensajes &listaMensajes){ 
	tMensaje mensaje;
	int nMensajes;
	//leemos el numero de mensajes 
	archivo>>nMensajes;		
	//inicializamos el contador y el tamaño del array a la decena mas proxima
	inicializarListaMensajes(listaMensajes,(nMensajes/DIMENSION+1)*DIMENSION);
	//mientras el mensaje no tenga errores
	while ((listaMensajes.cont<nMensajes)&&(cargarMensaje(archivo, mensaje))){
		anadirMensaje(listaMensajes,mensaje);		
	}
	return !archivo.fail();
}

void guardarColaMensajes(const tListaMensajes &listaMensajes,ofstream &archivo){ 
	//guardamos el numero de mensajes
	archivo<<listaMensajes.cont<<endl;
	//guardamos los mensajes
	for (int i = 0; i < listaMensajes.cont; i++){
		guardarMensaje(listaMensajes.mensaje[i],archivo);		
	}
}

int nMensajesIntercambiados(const tListaMensajes &listaMensajes){
	return listaMensajes.cont;
}


tMensaje getUltimoMensaje(const tListaMensajes& cola){
	return cola.mensaje[cola.cont-1];
}
tMensaje getMensaje(const tListaMensajes& cola,int contador){
	return cola.mensaje[contador];
}

void anadirMensaje(tListaMensajes &listaMensajes,const tMensaje &mensaje) {	
	if (listaMensajes.cont == listaMensajes.tamano) 
		redimensionarLista(listaMensajes,(listaMensajes.tamano*3)/2+1);

	listaMensajes.mensaje[listaMensajes.cont] = mensaje;
	// Insertamos al final
	listaMensajes.cont++;
   
}

void redimensionarLista(tListaMensajes &listaMensajes,int nuevaDimension){
	tMensajePtr mensajes=new tMensaje[nuevaDimension];
	for(int i=0;i<listaMensajes.cont;i++){
		mensajes[i]=listaMensajes.mensaje[i];
	}
	delete[]listaMensajes.mensaje;
	listaMensajes.tamano=nuevaDimension;
	listaMensajes.mensaje=mensajes;
}

void destruir(tListaMensajes &listaMensaje){
	delete[]listaMensaje.mensaje;
	listaMensaje.cont=0;
	listaMensaje.tamano=DIMENSION;
}