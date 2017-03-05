#ifndef Chat_h
#define Chat_h

#include <string>
using namespace std;
#include "ListaMensajes.h"
#include "Mensaje.h"
#include "Servidor.h"

const int LINEA=80;

typedef struct{
	string nombreChat;
	string due�oChat;
	tListaMensajes listaMensajes;
}tChat;

typedef tChat *tChatPtr;

//inicializamos el nombre chat,due�o chat y la cola de mensajes
void inicializarChat(string nombreChat,string due�oChat,tChat &chat);
//carga un chat
bool cargarChat(string due�oChat,ifstream& archivo,tChat &chat);
//guarda un chat en el archivo
void guardarChat(const tChat &chat,ofstream &archivo);
//muestra por pantalla el indice,el nombre del chat y el ultimo mensaje
void mostrarCabercera(const tChat &chat);
//devuelve el nombre del chat para poder alinear el mensaje en listaChat.cpp
string nombreChat(const tChat &chat);
//devuelve la fecha del ultimo mensajes del chat para ordenarlos
tFecha getFecha(const tChat &chat);
//lee el texto introducido por el usuario y hace las funciones correspondientes
void gestionarChat(tServidor &servidor,tChat &chat,bool &enviado);
//a�ade un mensaje nuevo al chat recibido
void anadirMensajeNuevo(const tMensaje &mensaje,tChat &chat);
//operador relacional para comparar chat
//basado en el campo nombreChat
bool operator>(tChat opIzq, tChat opDer);
//accede al array de mensajes de cada chat para destruirlo
void accederListaMensajes(tChat &chat);

#endif