
#include <iostream>
#include <string>
using namespace std;
#include <fstream>
#include "ListaUsuarios.h"
//recibe un usuario y lo inserta en la posicion que le corresponde
void insertarUsuarios(tListaUsuarios &listaUsuarios, const tUsuario &usuario,bool &listaLlena);


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
			listaUsuarios.usuarios[pos] = usuario;
			listaUsuarios.contadorUsuarios++;
		}
	}
}

void cargarUsuarios(tListaUsuarios &listaUsuarios,bool &ok){
	tUsuario usuario;
	bool listaLlena=false;
	ifstream archivo;
	archivo.open("usuarios.txt");
	if(!archivo.is_open()){
		ok=false;
	}else{
		ok=true;
		listaUsuarios.contadorUsuarios = 0;
		while((cargarUsuario(archivo,usuario)) && (!listaLlena) &&(identificadorUsuario(usuario)!="XXX")){
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
		guardarUsuario(listaUsuarios.usuarios[i],archivo);
	}
	archivo<<"XXX"<<endl;
	archivo.close();
}

int buscarUsuario(const tListaUsuarios &listaUsuarios,string idUsuario,bool &encontrado){
	int pos , ini = 0, fin = listaUsuarios.contadorUsuarios - 1, mitad;
	encontrado = false;   
	while((ini <= fin) && !encontrado) {
		mitad = (ini + fin) / 2; // División entera
		if (idUsuario ==identificadorUsuario(listaUsuarios.usuarios[mitad])) {
			encontrado = true;
		}
		else if (idUsuario < (identificadorUsuario(listaUsuarios.usuarios[mitad]))){
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
	enviarMensajeALista(mensaje,listaUsuarios.usuarios[pos]);
}

void obtenerMensaje(const tListaUsuarios &listaUsuarios,int pos,tListaMensajes &listaMensajes){
	mensajesRecibidos(listaUsuarios.usuarios[pos],listaMensajes);
}

void accederAUsuario(int pos, tListaUsuarios &listaUsuarios){
	eliminarMensajes(listaUsuarios.usuarios[pos]);
}

