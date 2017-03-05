#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "Usuario.h"

void inicializarUsuario(string id,tUsuario &usuario);

void inicializarUsuario(string id,tUsuario &usuario){
	usuario.idUsuario=id;
	inicializarListaMensajes(usuario.listaMensajes);
}


bool cargarUsuario(ifstream &archivo,tUsuario &usuario){
	string id;
	archivo>>id;
	//inicializamos el nombre del usuario y la cola de mensajes
	inicializarUsuario(id,usuario);
	//cargamos lista de mensajes
	cargarColaMensajes(archivo,usuario.listaMensajes);
	
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
	bool ok;
	añadirMensaje(usuario.listaMensajes,mensaje, ok);
	if(!ok){
		cout<<"No se ha podido enviar el mensaje a "<< usuario.idUsuario<<" su buzon esta lleno"<<endl;
		system("pause");
	}
}

void mensajesRecibidos(const tUsuario &usuario,tListaMensajes &listaMensaje){
	listaMensaje=usuario.listaMensajes;
}

void eliminarMensajes(tUsuario &usuario){
	inicializarUsuario(usuario.idUsuario,usuario);
}