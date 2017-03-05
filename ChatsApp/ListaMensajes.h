#ifndef ListaMensaje_h
#define ListaMensaje_h

using namespace std;
#include "Mensaje.h"
const int MAX = 6;

typedef struct{
	tMensaje mensaje[MAX];
	int cont;
}tListaMensajes;

//inicializamos el contador
void inicializarListaMensajes(tListaMensajes &listaMensajes);
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
 void añadirMensaje(tListaMensajes &listaMensajes,const tMensaje &mensaje, bool &ok);

#endif