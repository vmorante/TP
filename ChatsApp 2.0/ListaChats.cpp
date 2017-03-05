#include "ListaChats.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

void redimensionar(tListaChats &listaChats,int nuevaDimension);
//inicializamos el contador,y creamos un array con la dimension recibida
void inicializarListaChats(tListaChats &listaChats,int dimension);

void iniListaChats(tListaChats &listaChats){
	listaChats.contadorChats=0;
	listaChats.tamano=DIMENSIONCHAT;
	listaChats.chat=new tChat[listaChats.tamano];
}
void inicializarListaChats(tListaChats &listaChats,int dimension){
	listaChats.contadorChats=0;
	listaChats.tamano=dimension;
	listaChats.chat=new tChat[listaChats.tamano];
}

void cargarListaChats(string idUsuario,tListaChats &listaChats){
	ifstream archivo;
	tChat chat;
	int nChat;
	archivo.open(idUsuario+"_chats.txt");
	if(!archivo.is_open()){
		//inicializamos el chat con una dimension de finida
		iniListaChats(listaChats);		
	}else{
		archivo>>nChat;
		//inicializamos el contador  creamos el array y aproximamos a la decena mas proxima
		inicializarListaChats(listaChats,(nChat/DIMENSIONCHAT+1)*DIMENSIONCHAT);		
		while((listaChats.contadorChats<nChat)&&(cargarChat(idUsuario,archivo,chat))) {
			//añadimos el chat a la ultima posicion
			anadirChat(listaChats, chat);
		}
	}	
	archivo.close();
}

void guardarListaChats(const tListaChats &listaChats,string idUsuario){
	ofstream archivo;
	string nombreArchivo;
	archivo.open(idUsuario+"_chats.txt");
	archivo<<listaChats.contadorChats<<endl;
	for(int i=0;i<listaChats.contadorChats;i++){
		guardarChat(listaChats.chat[i],archivo);
	}
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
		if((listaChats.tamano-listaChats.contadorChats)>(listaChats.tamano/2))
			redimensionar(listaChats,listaChats.tamano*2/3);
			
		
   }
}


void anadirChat(tListaChats &listaChats, tChat chat) {
	//si la lista esta llena redimensionamos
	if(listaChats.contadorChats==listaChats.tamano) 
		redimensionar(listaChats,(listaChats.tamano*3)/2+1); 
	listaChats.chat[listaChats.contadorChats]=chat;
	// Insertamos al final
	listaChats.contadorChats++;
	
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

void anadirMensajeChat(const tMensaje &mensaje,int pos,tListaChats &listaChat){
	anadirMensajeNuevo(mensaje,listaChat.chat[pos]);
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

void redimensionar(tListaChats &listaChats,int nuevaDimension){
	tChatPtr chats=new tChat [nuevaDimension];
	for(int i=0;i<listaChats.contadorChats;i++){
		chats[i]=listaChats.chat[i];
	}
	delete[]listaChats.chat;
	listaChats.tamano=nuevaDimension;
	listaChats.chat=chats;
}

void destruirChats(tListaChats &listaChats){
	for(int i=0;i<listaChats.contadorChats;i++)
		//accedemos a la lista de mensajes para borrar el array de mensajes
		accederListaMensajes(listaChats.chat[i]);
	delete[]listaChats.chat;  
	listaChats.contadorChats=0;
	listaChats.tamano=DIMENSIONCHAT;
}