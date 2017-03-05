#ifndef Servidor_h
#define Servidor_h

#include "ListaUsuarios.h"
#include"Mensaje.h"
#include"ListaMensajes.h"
using namespace std;

typedef struct{
	tListaUsuarios usuarios;
}tServidor;


//buscamos al usuario y añadimos el mensaje a lista de mensajes del usuario
void enviarMensaje(const tMensaje &mensaje,tServidor &servidor,bool &error);
//devuelve una lista de mensajes con los mensajes pendientes y los elimina del servidor
void obtenerNuevosMensajes(tServidor &servidor,string idUsuario,tListaMensajes &listaMensajes);


#endif