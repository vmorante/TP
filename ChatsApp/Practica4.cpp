#include <iostream>
using namespace std;
#include "ListaUsuarios.h"
#include "Servidor.h"
#include "Cliente.h"
#include "ListaEstado.h"
//parte opcional muestra el estado de una persona y su ultima conexion estados.txt,modulo estado y listaEstado

int main(){
	tDatosCliente cliente;
	string idUsuario;
	bool ok,salir=false,cargado,encontrado;
	tServidor servidor;
	tListaEstados listaEstados;
	cargarUsuarios(servidor.usuarios,ok);
	cargarEstados(listaEstados,cargado);
	if(!ok)
		cout<<"No se ha podido cargar la lista de usuarios"<<endl;
	else{
		do{
			cout<<"Introduca id usuario(0 para salir): ";
			cin>>idUsuario;
			if(idUsuario=="0"){
				salir=true;
				guardarUsuarios(servidor.usuarios);
				guardarEstados(listaEstados);
			}
			else{
				buscarUsuario(servidor.usuarios,idUsuario,encontrado);
				if(!encontrado)
					cout<<"No eres un usuario valido!!!"<<endl;
				else{
					ejecutarApp( idUsuario,servidor,cliente,listaEstados,cargado);
					system("cls");
				}
			}
			actualizarUltConexion(idUsuario,listaEstados);
		}while(!salir);
	}
	system("pause");
	
	return 0;
}