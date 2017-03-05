#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
#include <fstream>
#include "Chat.h"


void mostrarInterfazChat(const tChat &chat);

void inicializarChat(string nombreChat,string dueñoChat,tChat &chat){
	chat.nombreChat=nombreChat;
	chat.dueñoChat=dueñoChat;
	iniListaMensajes(chat.listaMensajes);
}

bool cargarChat(string dueñoChat,ifstream& archivo,tChat &chat){
	string  nombreChat;
	//leemos el nombre del chat
	archivo>>nombreChat;
	//inicializamos dueño chat,nombre chat y la cola de mensajes
	inicializarChat(nombreChat,dueñoChat,chat);
	//carga la lista de mensajes
	cargarColaMensajes(archivo,chat.listaMensajes);
	
	return !archivo.fail();
}


void guardarChat(const tChat &chat,ofstream &archivo){
	archivo<<chat.nombreChat<<endl;
	guardarColaMensajes(chat.listaMensajes,archivo) ;
}
 

void mostrarCabercera(const tChat &chat){
	//mostramos el nombre del chat
	cout<<chat.nombreChat<<endl;
	//mostramos el ultimo mensaje del chat
	cout<<"       "<<mostrarMensaje(getUltimoMensaje(chat.listaMensajes));
}
void mostrarInterfazChat(const tChat &chat){
	string nombre;
	//linea
	for(int i=0;i<LINEA;i++)
		cout<<char(196);
	//mostramos el nombre del chat
	cout<<right<<setw(40)<<"CHAT CON " <<chat.nombreChat<<endl;
	//linea
	for(int i=0;i<LINEA;i++)
		cout<<char(196);
	cout<<endl;
	//lista de mensajes intercambiados
	for(int i=0;i<nMensajesIntercambiados(chat.listaMensajes);i++){
		//nombre del que ha escrito el mensaje
		nombre=personaMensaje(getMensaje(chat.listaMensajes,i));
		//alineamos segun corresponda y mostramos el mensaje
		if(nombre==chat.nombreChat)
			cout<<mostrarMensaje(getMensaje(chat.listaMensajes,i));
		else
			cout<<right<<setw(LINEA)<<mostrarMensaje(getMensaje(chat.listaMensajes,i));
		//linea
		for(int i=0;i<LINEA;i++)
			cout<<char(196);
	}
	cout<<endl;
	//linea
	for(int i=0;i<LINEA;i++)
		cout<<char(196);
	cout<<"Escribe aqui ("<<char(36)<<"salir"<<char(36)<<") para salir: ";

}


void gestionarChat(tServidor &servidor,tChat &chat,bool &enviado){
	bool error,salir=false;
	tMensaje mensaje;
	enviado=false;
	string texto,simbolo;
	simbolo=char(36);
	while(!salir){
		cin.sync();
		mostrarInterfazChat(chat);
		//leemos el texto introducido por el usuario
		getline(cin,texto);
		cin.sync();
		if(texto==(simbolo+"salir"+simbolo))
			salir=true;
		else{
			//creamos el mensaje
			crearMensaje(chat.dueñoChat,chat.nombreChat,texto,mensaje);
			//añadimos el mensaje al chat
			anadirMensaje(chat.listaMensajes,mensaje);
				enviado=true;
				//enviamos el mensaje al servidor para que lo reciba el remitente
				enviarMensaje(mensaje,servidor,error);
				if(error)
					cout<<"No se ha podido mandar el mensaje al servidor"<<endl;
			
		}
		system("cls");
	}
}



tFecha getFecha(const tChat &chat){
	return fechaMensaje(getUltimoMensaje(chat.listaMensajes));
}


string nombreChat(const tChat &chat){
	return chat.nombreChat;
}

void anadirMensajeNuevo(const tMensaje &mensaje,tChat &chat){
	anadirMensaje(chat.listaMensajes,mensaje);
}

bool operator>(tChat opIzq, tChat opDer) {
    return opIzq.nombreChat > opDer.nombreChat;
}

 void accederListaMensajes(tChat &chat){
	 destruir(chat.listaMensajes);
 }