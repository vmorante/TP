#ifndef Cliente_h
#define Cliente_h

#include "ListaChats.h"
#include "Servidor.h"
#include "Chat.h"
#include "Mensaje.h"
#include "ListaMensajes.h"
#include "ListaEstado.h"
#include <string>
using namespace std;

typedef struct{
	string id;
	tListaChats chats;
}tDatosCliente;

//dirige el funcionamiento de chatssap
void ejecutarApp(string id,tServidor &servidor,tDatosCliente &cliente,tListaEstados &listaEstados,bool abierto);


#endif