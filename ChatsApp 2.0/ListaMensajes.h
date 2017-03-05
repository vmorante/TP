#ifndef ListaMensaje_h
#define ListaMensaje_h

using namespace std;
#include "Mensaje.h"
const int DIMENSION=10;


typedef struct{
	tMensajePtr mensaje;
	int cont;
	int tamano;
}tListaMensajes;

//carga el numero de mensajes y devuelve una lista
bool cargarColaMensajes(ifstream &archivo, tListaMensajes &lista);
//recibe una lista de mensajes y lo guarda en el archivo
void  guardarColaMensajes(const tListaMensajes &lista,ofstream &archivo);
//devuelve el numero de mensajes que tiene un chat
int nMensajesIntercambiados(const tListaMensajes &listaMensajes);
//devuelve el ultimo mensaje de la lista
tMensaje getUltimoMensaje(const tListaMensajes& cola);
//devuelve el mensaje en la posicion del contador de la lista
tMensaje getMensaje(const tListaMensajes& cola,int contador);
//inserta un nuevo mensaje en la posicion ultima de la lista
 void anadirMensaje(tListaMensajes &listaMensajes,const tMensaje &mensaje);
 //destruye el array de mensajes
 void destruir(tListaMensajes &listaMensaje);
 //inicializa una lista de mensajes en tamaño 10
 void iniListaMensajes(tListaMensajes &listaMensajes);

#endif