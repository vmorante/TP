#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
#include "Cliente.h"
//inicializamos la estructura cliente
void inicializarApp(string id,tDatosCliente &cliente);
//creamos un nuevo chat
void crearNuevoChat( tServidor &servidor, tDatosCliente &cliente);
//obtenemos los mensajes pendiente de leer del servidor y los introduce en los chat del usuario
void obtenerMensajesNuevos(const tServidor &servidor,tDatosCliente &cliente);
//gestiona la opcion introducida por el usuario
void menuDeOpciones(char opcion,tDatosCliente &cliente,tServidor &servidor,bool &salir);
void menuDeOpciones2(char opcion,tDatosCliente &cliente);
//muestra la interfaz del chatssap
void mostrarInterfaz(const tDatosCliente &cliente);

void mostrarInterfaz(const tDatosCliente &cliente){
	//linea
	for(int i=0;i<LINEA;i++)
		cout<<char(196);
	cout<<right<<setw(50)<<"CHATSAPP 1.0: Chat de " <<cliente.id<<endl;
	for(int i=0;i<LINEA;i++)
		cout<<char(196);
	for(int i=0;i<numeroDeChats(cliente.chats);i++){
		cout<<i<<": ";
		mostrarCabercerachats(cliente.chats,i);
		for(int i=0;i<LINEA;i++)
			cout<<char(196);
	}
	cout<<endl;
	for(int i=0;i<LINEA;i++)
		cout<<char(196);
	cout<<right<<setw(33)<<"Entrar al chat N: c N <intro>";
	cout<<right<<setw(44)<<"Crear nuevo chat: n <intro>"<<endl;
	cout<<right<<setw(35)<<"Eliminar el chat N: e N <intro>";
	cout<<right<<setw(42)<<"Ordenar chats por nombre: o n <intro>"<<endl;
	cout<<right<<setw(40)<<"Ordenar chats por fecha: o f <intro>";
	cout<<right<<setw(37)<<"Salir: s <intro>"<<endl;
	for(int i=0;i<LINEA;i++)
		cout<<char(196);
}

void obtenerMensajesNuevos(tServidor &servidor,tDatosCliente &cliente){
	string nombreChat;
	int pos;
	tChat chat;
	bool movido;
	tListaMensajes listaMensajes;
	//obtenemos los mensajes pendientes de leer
	obtenerNuevosMensajes(servidor,cliente.id,listaMensajes);
	for(int i=0;i<listaMensajes.cont;i++){
		//se obtiene el nombre del chat a traves del emisor del mensaje
		nombreChat=personaMensaje(listaMensajes.mensaje[i]);
		//se busca el chat
		pos=buscarChat(cliente.chats,nombreChat);
		//si no se encuentra lo creamos
		if(pos==-1){
			//se crea un chat y se añade el mensaje
			inicializarChat(nombreChat,cliente.id,chat);
			anadirMensaje(chat.listaMensajes,listaMensajes.mensaje[i]);
			//se añade el chat a la lista de chats
			anadirChat(cliente.chats,chat);
					
		}
		else{
			//añadimos el mensaje al chat existente
			anadirMensajeChat(listaMensajes.mensaje[i],pos,cliente.chats);
			moverFinal(cliente.chats,pos,movido);
				if(!movido)
					cout<<"El chat no se ha movido al final"<<endl;
			
		}
	}
}

void inicializarApp(string id,tDatosCliente &cliente){
	cliente.id=id;
	iniListaChats(cliente.chats);
}

void crearNuevoChat( tServidor &servidor, tDatosCliente &cliente){
	string nombreChat,mensajeInicial;
	int pos;
	bool error,encontrado;
	tMensaje mensaje;
	tChat chat;
	//solicitamos la persona con la que se quiere crear el chat
	cout<<"Indique la persona con la que quiere crear el chat: ";
	cin>>nombreChat;
	//se busca si el chat existe
	pos=buscarChat(cliente.chats,nombreChat);
	if(pos!=-1)
		cout<<"El chat ya existe"<<endl;
	else{
		//si no existe se comprueba si el usuario es  valido
		pos=buscarUsuario(servidor.usuarios,nombreChat,encontrado);
		if(!encontrado)
			cout<<"La persona con la que quiere crear el chat no esta en la lista de usuarios"<<endl;
		else{
			//si esta en la lista de usuarios,creamos un chat nuevo y añadimos el mensaje inicial
			inicializarChat(nombreChat,cliente.id,chat);
			mensajeInicial="Nuevo chat iniciado por "+cliente.id;
			crearMensaje(cliente.id,nombreChat,mensajeInicial,mensaje);
			anadirMensaje(chat.listaMensajes,mensaje);
			//añadimos el chat a lista de chat
			anadirChat(cliente.chats,chat);
			//enviamos el mensaje al servidor para que lo gestione
			enviarMensaje(mensaje,servidor,error);
			if(error)
				cout<<"el mensaje no se ha enviado al servidor"<<endl;
			else
				cout<<"Chat creado con exito"<<endl;
			
		}
	}
}


void ejecutarApp(string id,tServidor &servidor,tDatosCliente &cliente){
	bool salir=false;
	char opcion;
	inicializarApp(id,cliente);
	cargarListaChats(id,cliente.chats);
	obtenerMensajesNuevos(servidor,cliente);
	while(!salir){
		system("cls");
		//mostramos la interfaz y recogemos la opcion
		mostrarInterfaz(cliente);
		cin>>opcion;
		opcion=toupper(opcion);
		menuDeOpciones(opcion,cliente,servidor,salir);
	}
	
}


void menuDeOpciones(char opcion,tDatosCliente &cliente,tServidor &servidor,bool &salir){
	int num,numChats;
	salir=false;
	numChats=numeroDeChats(cliente.chats);
	switch(opcion){
		case 'C':
			{
				cin>>num;
				if((num<0) || (num>numChats-1)){
					cout<<"Indice no valido"<<endl;
					system("pause");
				}else{
					system("cls");
					accederAchat(num,servidor,cliente.chats);					
				}
		    }
			break;
		
		case 'N':
			{
				crearNuevoChat(servidor,cliente);
				system("pause");
			}
			break;			
		case 'S':
			{
				salir=true;
				guardarListaChats(cliente.chats,cliente.id);
				destruirChats(cliente.chats);
			}
			break;	
			
		default:
			{
				menuDeOpciones2(opcion,cliente);
			}
			break;
	}
}

void menuDeOpciones2(char opcion,tDatosCliente &cliente){
	int num;
	char orden;
	bool ok;
	switch(opcion){
		case 'E':
			{
				cin>>num;
				eliminarChat(num,cliente.chats,ok);
				if(!ok){
					cout<<"Indice no valido"<<endl;
					system("pause");
				 }
			 }
			break;
		case 'O':
			{
				cin>>orden;
				orden=toupper(orden);
				if(orden=='F')
					ordenarPorFecha(cliente.chats);
				else if(orden=='N')
					ordenarPorNombre(cliente.chats);
				else{
					cout<<"ordenacion no valida"<<endl;
					system("pause");
				}
			}
			break;
			default:
				{
					cout<<"Opcion no valida"<<endl;
					system("pause");
				}
				break;
	}
}