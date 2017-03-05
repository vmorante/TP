#include <iostream>
using namespace std;
#include "ListaUsuarios.h"
#include "Servidor.h"
#include "Cliente.h"


int main(){
	tDatosCliente cliente;
	string idUsuario;
	bool ok,salir=false,encontrado;
	tServidor servidor;	
	cargarUsuarios(servidor.usuarios,ok);	
	if(!ok)
		cout<<"No se ha podido cargar la lista de usuarios"<<endl;
	else{
		do{
			cout<<"Introduca id usuario(0 para salir): ";
			cin>>idUsuario;
			if(idUsuario=="0"){
				salir=true;
				guardarUsuarios(servidor.usuarios);
				destruirUsuarios(servidor.usuarios);				
			}
			else{
				buscarUsuario(servidor.usuarios,idUsuario,encontrado);
				if(!encontrado)
					cout<<"No eres un usuario valido!!!"<<endl;
				else{
					ejecutarApp( idUsuario,servidor,cliente);
					system("cls");
				}
			}
			
		}while(!salir);
	}
	system("pause");
	
	return 0;
}