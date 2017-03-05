#include "ListaChats.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;


void inicializarListaChats(tListaChats &listaChats){
	listaChats.contadorChats=0;
}

void cargarListaChats(string idUsuario,tListaChats &listaChats,bool &ok){
	ifstream archivo;
	tChat chat;
	archivo.open(idUsuario+"_chats.txt");
	if(!archivo.is_open()){
		ok=false;
	}else{
		ok=true;
		//inicializamos el contador
		inicializarListaChats(listaChats);
		while((cargarChat(idUsuario,archivo,chat)) && (listaChats.contadorChats<NCHAT) &&(nombreChat(chat)!="XXX")){
			//añadimos el chat a la ultima posicion
			listaChats.chat[listaChats.contadorChats]=chat;			
			listaChats.contadorChats++;
		}
	}	
	archivo.close();
}

void guardarListaChats(const tListaChats &listaChats,string idUsuario){
	ofstream archivo;
	string nombreArchivo;
	archivo.open(idUsuario+"_chats.txt");	
	for(int i=0;i<listaChats.contadorChats;i++){
		guardarChat(listaChats.chat[i],archivo);
	}
	archivo<<"XXX"<<endl;
	archivo.close();
}

int buscarChat(const tListaChats &listaChats,string idUsuario){
	//devuelve -1 si el chat no esta
	bool encontrado=false;
	int pos=0;
	while((!encontrado) &&(pos<listaChats.contadorChats)){
		if(nombreChat(listaChats.chat[pos])==idUsuario)
			encontrado=true;
		else
			pos++;
	}
	if(!encontrado)
		pos=-1;
	return pos;
}

void eliminarChat(int pos,tListaChats &listaChats, bool &ok) {
	if((pos < 0)||(pos > listaChats.contadorChats -1)){
		ok = false; // Elemento inexistente
	}
	else{
		ok = true;
		//desplazamos la lista de chats
		for (int i = pos; i < listaChats.contadorChats-1; i++) {
			listaChats.chat[i] = listaChats.chat[i + 1];
		}
		//disminuimos el contador
		listaChats.contadorChats--;
   }
}


void añadirChat(tListaChats &listaChats, tChat chat, bool &ok) {
	ok = true;
	//lista llena
	if(listaChats.contadorChats==NCHAT) {
		ok = false;
    }
    else{
		listaChats.chat[listaChats.contadorChats]=chat;
		// Insertamos al final
		listaChats.contadorChats++;
	}
}

void moverFinal(tListaChats &listaChats, int pos,bool &ok){
	tChat chat;	
    if((pos < 0)||(pos > listaChats.contadorChats-1 )) {
      ok = false; // Elemento inexistente
    }
    else{
		ok = true;
		//guardamos el chat
		chat=listaChats.chat[pos];
		//desplazamos a partir de la posicion dada
		for(int i=pos;i<listaChats.contadorChats-1;i++)
			listaChats.chat[i]=listaChats.chat[i+1];
		//movemos al final
		listaChats.chat[listaChats.contadorChats-1]=chat;
   }
}


void ordenarPorNombre(tListaChats &listaChats){
	for (int i = 1; i < listaChats.contadorChats; i++) {
      // Desde el segundo elemento hasta el último
         int pos = i;
         while ((pos > 0) && (listaChats.chat[pos - 1] > listaChats.chat[pos])) {
         // Mientras no se llegue al principio y el anterior sea mayor
            tChat tmp;
            tmp = listaChats.chat[pos];
            listaChats.chat[pos] = listaChats.chat[pos - 1];
            listaChats.chat[pos - 1] = tmp;
            pos--;
         }
      }
}



void ordenarPorFecha(tListaChats &listaChats){
	for (int i = 1; i < listaChats.contadorChats; i++) {
      // Desde el segundo elemento hasta el último
         int pos = i;
         while ((pos > 0) && (getFecha(listaChats.chat[pos - 1]) > getFecha(listaChats.chat[pos]))) {
         // Mientras no se llegue al principio y el anterior sea mayor
            tChat tmp;
            tmp = listaChats.chat[pos];
            listaChats.chat[pos] = listaChats.chat[pos - 1];
            listaChats.chat[pos - 1] = tmp;
            pos--;
         }
      }
}


int numeroDeChats(const tListaChats &listaChats){
	return listaChats.contadorChats;
}

void mostrarCabercerachats(const tListaChats &listaChats,int i){
	mostrarCabercera(listaChats.chat[i]);
}

void añadirMensajeChat(const tMensaje &mensaje,int pos,tListaChats &listaChat,bool &ok){
	añadirMensajeNuevo(mensaje,listaChat.chat[pos],ok);
}

void accederAchat(int num,tServidor &servidor,tListaChats &listaChats){
	bool enviado,movido;
	gestionarChat(servidor,listaChats.chat[num],enviado);
	//Si se ha enviado algun mensaje se mueve ese chat al final
	if(enviado){
		moverFinal(listaChats,num,movido);
			if(!movido)
				cout<<"El chat no se ha movido al final"<<endl;
	}
}

