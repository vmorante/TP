#ifndef ListaChats_h
#define ListaChats_h

using namespace std;
const int DIMENSIONCHAT=10;
#include "Chat.h"
#include "Servidor.h"

typedef struct{
	tChatPtr chat;
	int contadorChats;
	int tamano;
}tListaChats;


//cargamos una lista de chat de un usuario
void cargarListaChats(string idUsuario,tListaChats &listaChats);
//guardamos la lista de chats en el archivo
void guardarListaChats(const tListaChats &listaChats,string idUsuario);
//busqueda lineal de un chat
int buscarChat(const tListaChats &listaChats,string idUsuario);
//eliminamos el chat de la posicion dada
void eliminarChat(int pos,tListaChats &listaChats,bool &ok);
//añadimos un chat al final de  la lista
void anadirChat(tListaChats &listaChats, tChat chat);
//movemos un chat a final
void moverFinal(tListaChats &listaChats, int pos,bool &ok);
//ordena una lista de chats por nombre
void ordenarPorNombre(tListaChats &listaChats);
//ordena una lista de chats por fecha
void ordenarPorFecha(tListaChats &listaChats);
//delvuelve el numero de chats creados por un usuario para mostrar la interfaz en el modulo cliente
int numeroDeChats(const tListaChats &listaChats);
//recibe una lista de chats y la posicion y llama a  mostrarCabecera del modulo chat
void mostrarCabercerachats(const tListaChats &listaChats,int i);
//llama a la funcion añadirMensajeNuevo del modulo chat para insertar el mensaje en un chat
void anadirMensajeChat(const tMensaje &mensaje,int pos,tListaChats &listaChat);
//permite llamar a la funcion gestionarChat 
void accederAchat(int num,tServidor &servidor,tListaChats &listaChats);
//destruye el array de chats
void destruirChats(tListaChats &listaChats);
//inicializa una lista de chat de tamaño 10
void iniListaChats(tListaChats &listaChats);


#endif