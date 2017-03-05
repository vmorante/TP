#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "Usuario.h"

void inicializarUsuario(string id,tUsuario &usuario);

void inicializarUsuario(string id,tUsuario &usuario){
	usuario.idUsuario=id;
	iniListaMensajes(usuario.listaMensajes);
}


bool cargarUsuario(ifstream &archivo,tUsuario &usuario,bool &fin){
	string id;
	fin=false;
	archivo>>id;
	if(id!="XXX"){
		//inicializamos el nombre del usuario y la cola de mensajes
		inicializarUsuario(id,usuario);
		//cargamos lista de mensajes
		cargarColaMensajes(archivo,usuario.listaMensajes);
	}else
		fin=true;
	
	return !archivo.fail();
}

void guardarUsuario(const tUsuario &usuario,ofstream &archivo){
	archivo<<usuario.idUsuario<<endl;
	guardarColaMensajes(usuario.listaMensajes,archivo);
}

string identificadorUsuario(const tUsuario &usuario){
	return usuario.idUsuario;
}


void enviarMensajeALista(const tMensaje &mensaje,tUsuario &usuario){
	
	anadirMensaje(usuario.listaMensajes,mensaje);
	
}

void mensajesRecibidos(const tUsuario &usuario,tListaMensajes &listaMensaje){
	listaMensaje=usuario.listaMensajes;
}

void eliminarMensajes(tUsuario &usuario){
	inicializarUsuario(usuario.idUsuario,usuario);
}

void borrarArrayMensajes(tUsuario &usuario){
	destruir(usuario.listaMensajes);
}