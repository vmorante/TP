#ifndef Mensaje_h
#define Mensaje_h

#include <string>
using namespace std;

typedef time_t tFecha;

typedef struct{
	string origen;
	string receptor;
	tFecha fecha;
	string cadena;
}tMensaje;


//devuelve una cadena con un mensaje
string mostrarMensaje(tMensaje mensaje);
//crea un mensaje nuevo
void crearMensaje(string emisor,string receptor,string texto,tMensaje &mensaje);
//carga el emisor,la fecha y el texto y devuelve un tMensaje
bool cargarMensaje(ifstream &archivo, tMensaje &mensaje);
//guarda emisor,fechay mensaje
void guardarMensaje(const tMensaje& mensaje,ofstream &archivo);
//devuelve la fecha del mensaje para poder ordenar la lista de chats
tFecha fechaMensaje(const tMensaje &mensaje);
//devuelve la persona emisora del mensaje
string personaMensaje(const tMensaje& mensaje);
//muestra la fecha por pantalla,tambien se utiliza en el modulo listaEstados
string mostrarFecha(tFecha fecha);
	

#endif