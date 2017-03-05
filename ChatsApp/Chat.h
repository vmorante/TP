#ifndef Chat_h
#define Chat_h

#include <string>
using namespace std;
#include "ListaMensajes.h"
#include "Mensaje.h"
#include "Servidor.h"

typedef struct{
	string nombreChat;
	string dueñoChat;
	tListaMensajes listaMensajes;
}tChat;

//inicializamos el nombre chat,dueño chat y la cola de mensajes
void inicializarChat(string nombreChat,string dueñoChat,tChat &chat);
//carga un chat
bool cargarChat(string dueñoChat,ifstream& archivo,tChat &chat);
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
//añade un mensaje nuevo al chat recibido
void añadirMensajeNuevo(const tMensaje &mensaje,tChat &chat,bool &ok);
//operador relacional para comparar chat
//basado en el campo nombreChat
bool operator>(tChat opIzq, tChat opDer);

#endif