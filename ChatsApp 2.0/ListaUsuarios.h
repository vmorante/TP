#ifndef ListaUsuarios_h
#define ListaUsuarios_h

#include "Usuario.h"
#include "ListaMensajes.h"
using namespace std;
const int MAXUSUARIOS=50;

typedef tUsuarioPtr tArray[MAXUSUARIOS];

typedef struct{
	tArray usuarios;
	int contadorUsuarios;
}tListaUsuarios;

//carga usuarios de un archivo
void cargarUsuarios(tListaUsuarios &listaUsuarios,bool &ok);
//guarda una lista de usuarios en un archivo
void guardarUsuarios(const tListaUsuarios &listaUsuarios);
//busqueda binaria de un usuario,delvuelve la posicion en la que deberia estar o en la que esta y un booleano si no lo encuentra
int buscarUsuario(const tListaUsuarios &listaUsuarios,string identificadorUsuario,bool &encontrado);
//busca el usuario en la lista de usuarios y recibe el mensaje
void añadirMensajePendientes(const tMensaje &mensaje,int pos,tListaUsuarios& listaUsuarios);
//devuelve una lista mensajes pendientes de leer para el modulo servidor
void obtenerMensaje(const tListaUsuarios &listaUsuarios,int pos,tListaMensajes &ListaMensajes);
//permite accder al usuario para poder eliminar los mensajes ya puestos en el chat
void borrarMensajesLeidos(int pos, tListaUsuarios &listaUsuarios);
//destruye el array de susuarios
void destruirUsuarios(tListaUsuarios &listaUsuarios);

#endif