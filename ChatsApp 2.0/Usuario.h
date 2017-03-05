#ifndef Usuario_h
#define Usuario_h


#include <string>
#include "ListaMensajes.h"
using namespace std;

typedef struct{
	string idUsuario;
	tListaMensajes listaMensajes;
}tUsuario;

typedef tUsuario  *tUsuarioPtr;

//carga un usuario
bool cargarUsuario(ifstream &archivo,tUsuario &usuario,bool &fin);
//guarda un usuario en un archivo
void guardarUsuario(const tUsuario &usuario,ofstream &archivo);
//devuelve el id de un usuario
string identificadorUsuario(const tUsuario &usuario);
//le llega el usuario y el mensaje a insertar
void enviarMensajeALista(const tMensaje &mensaje,tUsuario &usuario);
//le llega un usuario y devuelve la lista de mensajes que le faltan por leer para el modulo servidor
void mensajesRecibidos(const tUsuario &usuario,tListaMensajes &listaMensaje);
//elimina los mensajes ya insertados en los chats
void eliminarMensajes(tUsuario &usuario);
//accede a la lista de mensajes para destruir el array
void borrarArrayMensajes(tUsuario &usuario);
#endif
