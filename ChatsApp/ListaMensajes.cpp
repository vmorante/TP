#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "ListaMensajes.h"

void inicializarListaMensajes(tListaMensajes &listaMensajes){
	listaMensajes.cont=0;
}
bool cargarColaMensajes(ifstream &archivo ,tListaMensajes &listaMensajes){ 
	tMensaje mensaje;
	int nMensajes;
	//inicializamos el contador
	inicializarListaMensajes(listaMensajes);
	//leemos el numero de mensajes 
	archivo>>nMensajes;	
	//mientras el mensaje no tenga errores,el nombre del chat no sea el centinela llamamos cargar mensaje
	while ((listaMensajes.cont<nMensajes)&&(cargarMensaje(archivo, mensaje)) && (listaMensajes.cont < MAX)){
		listaMensajes.mensaje[listaMensajes.cont]=mensaje;
		listaMensajes.cont++;					
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

void añadirMensaje(tListaMensajes &listaMensajes,const tMensaje &mensaje, bool &ok) {
	ok = true;
	if (listaMensajes.cont == MAX) {
		 ok = false;
	}
	else{
		listaMensajes.mensaje[listaMensajes.cont] = mensaje;
		// Insertamos al final
		listaMensajes.cont++;
   }
}