#ifndef Estado_h
#define Estado_h

//PARTE OPCIONAL
#include <string>
#include "Mensaje.h"
using namespace std;

typedef time_t tFecha;

typedef struct{
	string nombreUsuario;
	tFecha fecha;
	string mensajeDeEstado;
}tEstado;

//carga el nombre,el estado y la fecha y develve un estado
bool cargarEstado(ifstream &archivo,tEstado &estado);
//guarda un estado en el archivo
void guardarEstado(const tEstado &estado,ofstream &archivo);
//muestra un estado por pantalla
void mostrarEstado(const tEstado &estado);
//cambia el estado
void accederEstado( tEstado &estado,string texto);
//actualiza la ultima conexion
void accederFecha(tEstado &estado);
//devuelve el nombre de usuario
string nombreUsuario(const tEstado &estado);
//compara dos nombres
bool operator<(tEstado opIzq, tEstado opDer);

#endif