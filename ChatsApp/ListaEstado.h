#ifndef ListaEstado_h
#define ListaEstado_h

#include "Estado.h"
using namespace std;
const int MAXESTADOS=10;
//PARTE OPCIONAL

typedef struct{
	tEstado estado[MAXESTADOS];
	int contador;
}tListaEstados;

//carga estados de un archivo
void cargarEstados(tListaEstados &listaEstados,bool &ok);
//guarda un alista de estados en un archivo
void guardarEstados(const tListaEstados &listaEstados);
//muestra una lista de estados por pantalla
void mostrarListaDeEstado(const tListaEstados &listaEstados);
//actualiza la ultima conexion
void actualizarUltConexion(string idUsuario,tListaEstados &listaEstados);
//actualiza un estado
void actualizarEstado(string idUsuario,tListaEstados &listaEstados);

#endif