#include <iostream>
#include <string>
using namespace std;
#include <fstream>
#include "ListaEstado.h"

//PARTE OPCIONAL

//inserta un estado en la posicion que le corresponde
void insertarEstados(tListaEstados &listaEstados ,const tEstado &estado,bool &listaLlena);
//devuelve la posicion que esta o en la que tendria que estar
int buscarEstado(const tListaEstados &listaEstados,string idUsuario,bool &encontrado);

void insertarEstados(tListaEstados &listaEstados, const tEstado &estado,bool &listaLlena){
	listaLlena=false;
	bool encontrado;
	if(listaEstados.contador == MAXESTADOS)
		listaLlena=true;
	else{
		int pos;
		pos=buscarEstado(listaEstados,nombreUsuario(estado),encontrado);
		if(!encontrado){
			for(int j = listaEstados.contador; j > pos; j--){
				listaEstados.estado[j] = listaEstados.estado[j-1];
			}
			listaEstados.estado[pos] = estado;
			listaEstados.contador++;
		}
	}
}

void cargarEstados(tListaEstados &listaEstados,bool &ok){
	tEstado estado;
	bool listaLlena=false;
	ifstream archivo;
	archivo.open("estados.txt");
	if(!archivo.is_open()){
		ok=false;
	}else{
		ok=true;
		listaEstados.contador = 0;
		while((cargarEstado(archivo,estado)) && (!listaLlena)&& (nombreUsuario(estado)!="XXX")){
			insertarEstados(listaEstados, estado,listaLlena);
			if(listaLlena)
				cout<<"La lista esta llena"<<endl;

		}
	}
	archivo.close();
}

void guardarEstados(const tListaEstados &listaEstados){
	ofstream archivo;
	archivo.open("estados.txt");
	for(int i=0;i<listaEstados.contador;i++){
		guardarEstado(listaEstados.estado[i],archivo);
	}
	archivo<< "XXX"<<endl;
	archivo.close();
}

int buscarEstado(const tListaEstados &listaEstados,string idUsuario,bool &encontrado){
	int pos , ini = 0, fin = listaEstados.contador - 1, mitad;
	encontrado = false;   
	while ((ini <= fin) && !encontrado) {
		 mitad = (ini + fin) / 2; // División entera
		 if (idUsuario ==nombreUsuario(listaEstados.estado[mitad])) {
			encontrado = true;
		 }
		 else if (idUsuario < (nombreUsuario(listaEstados.estado[mitad]))) {
				fin = mitad - 1;
		 }
		 else {
			ini = mitad + 1;
		 }
   }
   if (encontrado) 
      pos = mitad;
   else
	   pos=ini;
   
  return pos;
}

void mostrarListaDeEstado(const tListaEstados &listaEstados){
	for(int i=0;i<listaEstados.contador;i++){
		mostrarEstado(listaEstados.estado[i]);
	}

}
void actualizarUltConexion(string idUsuario,tListaEstados &listaEstados){
	int pos;
	bool encontrado;
	pos=buscarEstado(listaEstados,idUsuario,encontrado);
	if(encontrado)
		accederFecha(listaEstados.estado[pos]);
}

void actualizarEstado(string idUsuario,tListaEstados &listaEstados){
	string texto;
	int pos;
	bool encontrado;
	cin.sync();
	pos=buscarEstado(listaEstados,idUsuario,encontrado);
	if(encontrado){
		 cout<<"Introduza su nuevo estado : ";
		 getline(cin,texto);
		 cin.sync();
		 accederEstado( listaEstados.estado[pos],texto);
	 }
}



