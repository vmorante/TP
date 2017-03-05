
#include <iostream>
#include <string>
using namespace std;
#include <fstream>
#include "ListaUsuarios.h"
//recibe un usuario y lo inserta en la posicion que le corresponde
void insertarUsuarios(tListaUsuarios &listaUsuarios, const tUsuario &usuario,bool &listaLlena);
//inicializa el contador de la lista a 0
void inicializarListaUsuarios(tListaUsuarios &listaUsuarios);


void inicializarListaUsuarios(tListaUsuarios &listaUsuarios){
	listaUsuarios.contadorUsuarios=0;
}
void insertarUsuarios(tListaUsuarios &listaUsuarios, const tUsuario &usuario,bool &listaLlena){
	listaLlena=false;
	bool encontrado;
	if(listaUsuarios.contadorUsuarios == MAXUSUARIOS)
		listaLlena=true;
	else{
		int pos;
		//buscamos la posicion que le corresponderia al usuario
		pos= buscarUsuario(listaUsuarios,identificadorUsuario(usuario),encontrado);
		if(encontrado)
			cout<<"El usuario ya existe"<<endl;
		else{
		//desplazamos
			for(int j = listaUsuarios.contadorUsuarios; j > pos; j--){
				listaUsuarios.usuarios[j] = listaUsuarios.usuarios[j-1];
			}
			listaUsuarios.usuarios[pos] = new tUsuario(usuario);
			listaUsuarios.contadorUsuarios++;
		}
	}
}

void cargarUsuarios(tListaUsuarios &listaUsuarios, bool &ok){
	bool listaLlena=false,fin;
	ifstream archivo;
	archivo.open("usuarios.txt");
	if(!archivo.is_open()){
		ok=false;
	}else{
		tUsuario usuario;
		ok=true;
		inicializarListaUsuarios(listaUsuarios);
		while((cargarUsuario(archivo,usuario,fin)) && (!listaLlena) &&(!fin)){
			insertarUsuarios(listaUsuarios, usuario,listaLlena);
			if(listaLlena)
				cout<<"La lista esta llena"<<endl;
		}
	}
	archivo.close();
}

void guardarUsuarios(const tListaUsuarios &listaUsuarios){
	ofstream archivo;
	archivo.open("usuarios.txt");
	for(int i=0;i<listaUsuarios.contadorUsuarios;i++){
		guardarUsuario(*listaUsuarios.usuarios[i],archivo);
	}
	archivo<<"XXX"<<endl;
	archivo.close();
}

int buscarUsuario(const tListaUsuarios &listaUsuarios,string idUsuario,bool &encontrado){
	int pos , ini = 0, fin = listaUsuarios.contadorUsuarios - 1, mitad;
	encontrado = false;   
	while((ini <= fin) && !encontrado) {
		mitad = (ini + fin) / 2; // División entera
		if (idUsuario == identificadorUsuario(*listaUsuarios.usuarios[mitad])) {
			encontrado = true;
		}
		else if (idUsuario < (identificadorUsuario(*listaUsuarios.usuarios[mitad]))){
				fin = mitad - 1;
		}
		else{
			ini = mitad + 1;
		}
   }
   if (encontrado) 
      pos = mitad;   
   else
	   pos=ini;
   
  return pos;
}



void añadirMensajePendientes(const tMensaje &mensaje,int pos,tListaUsuarios& listaUsuarios){
	enviarMensajeALista(mensaje,*listaUsuarios.usuarios[pos]);
}

void obtenerMensaje(const tListaUsuarios &listaUsuarios,int pos,tListaMensajes &listaMensajes){
	mensajesRecibidos(*listaUsuarios.usuarios[pos],listaMensajes);
}

void borrarMensajesLeidos(int pos, tListaUsuarios &listaUsuarios){
	eliminarMensajes(*listaUsuarios.usuarios[pos]);
}

void destruirUsuarios(tListaUsuarios &listaUsuarios){
	for (int i = 0; i < listaUsuarios.contadorUsuarios; i++){
		borrarArrayMensajes(*listaUsuarios.usuarios[i]);
		delete listaUsuarios.usuarios[i];
	}	
	listaUsuarios.contadorUsuarios = 0;
}
