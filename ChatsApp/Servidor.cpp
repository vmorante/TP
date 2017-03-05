#include <iostream>
#include <string>
using namespace std;
#include "Servidor.h"

void enviarMensaje(const tMensaje &mensaje,tServidor &servidor,bool &error){
	int pos;
	bool encontrado;
	error=false;
	//buscamos la posicion del destinatario
	pos=buscarUsuario(servidor.usuarios,mensaje.receptor,encontrado);
	if(!encontrado)
		//no esta en la lista
		error=true;
	else
		//añadimos el mensaje a la cola del servidor
		añadirMensajePendientes(mensaje,pos,servidor.usuarios);
}

void obtenerNuevosMensajes(tServidor &servidor,string idUsuario,tListaMensajes &listaMensajes){
	int pos;
	bool encontrado;
	//buscamos la posicion del usuario en la lista de usuarios
	pos=buscarUsuario(servidor.usuarios,idUsuario,encontrado);
	if(!encontrado)
		cout<<"El usuario no ha sido encontrado"<<endl;
	else{
		//devuelve una lista de mensajes pendientes de leer
		obtenerMensaje(servidor.usuarios,pos,listaMensajes);
		//accedemos al usuario para borrar los mensajes pendientes ya leidos
		accederAUsuario(pos,servidor.usuarios);
	}
}
