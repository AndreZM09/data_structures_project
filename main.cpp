/*//////////////////////////////////////////////////////////

	Practica 1

Materia: Estructuras de Datos II
Seccion: D12
Profesor: GRACIELA LARA LOPEZ
Integrantes: 217564323 - CASTAÑEDA PEREZ SAUL ALEJANDRO
			 220286539 - ZURITA MURILLO ANDRE CONRADO
			 
NOTA: Poner esta info en todos los archivos cuando este terminado
			 
*///////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <string>
#define LongLlavePrimaria 13
#define LongLlaveSecundaria 32
#define Delimitador '|'
#define CaracterNulo '\0'
#define LimiteRegistros 100
#include "Estructura.h"
#include "Funciones.h"
#include "Sublista.h"
#include "Lista.h"

void BusquedaLlaveSecundaria(Lista &ListaInvertida){
	char LlaveSecundaria[LongLlaveSecundaria];
	cout<<"\n\t\tIngresa el nombre de la ciudad: ";
	cin.ignore();
    cin.getline(LlaveSecundaria,LongLlaveSecundaria+1,'\n');
    RellenarConEspacios(LlaveSecundaria,sizeof(LlaveSecundaria));
    aMayusculas(LlaveSecundaria,sizeof(LlaveSecundaria));
    ListaInvertida.Buscar(LlaveSecundaria);
}

void BusquedaLlavePrimaria(){
	char LlavePrimaria[LongLlavePrimaria];
	cout<<"\n\t\tIngresa el RFC: ";
	cin.ignore();
    cin.getline(LlavePrimaria,LongLlavePrimaria+1,'\n');
    aMayusculas(LlavePrimaria,LongLlavePrimaria);
    BuscarLlavePrimaria(LlavePrimaria);
}

void SubMenu(Lista &ListaInvertida){
	int opc;
	do{
		cout<<"\n\t\t- - - - - S U B - M E N U - - - - -"<<endl
		<<"\t\t 1.- Busqueda por llave primaria"<<endl
		<<"\t\t 2.- Busqueda por llave Secundaria"<<endl
		<<"\t\t 3.- Salir"<<endl
		<<"\t\t- - - - - - - - - - - - - - - - - -"<<endl
		<<"\t\tQue deseas hacer: ";
		cin>>opc;
		switch(opc){
			case 1:{
				BusquedaLlavePrimaria();
				break;
			}
			case 2:{
				BusquedaLlaveSecundaria(ListaInvertida);
				break;
			}
			case 3:break;
			default:{
				cout<<"\n\t\tSolo puedes ingresar numeros del 1 al 3."<<endl;
				break;
			}
		}
	}while(opc!=3);
}

void AgregarRegistro(Lista &ListaInvertida){
	if(Contador<LimiteRegistros){
		//Pedimos los datos.
		cout<<"\n\tBinevenido!\n";
	    cout<<"Ingresa los datos solicitados\n\n";
	    cout<<"Ingresa tu nombre: ";
	    cin.ignore();
	    cin.getline(contribuyente.nombre,32+1,'\n');
	    cout<<"Ingresa tu apellido paterno: ";
	    cin.getline(contribuyente.apellido[0],32+1,'\n');
	    cout<<"Ingresa tu apellido materno: ";
	    cin.getline(contribuyente.apellido[1],32+1,'\n');
	    cout<<"Ciudad: ";
		cin.getline(contribuyente.ciudad,LongLlaveSecundaria+1,'\n');
	    cout<<"Dependientes: ";
	    cin>>contribuyente.dependientes;
	    cout<<"Estado civil: ";
	    cin>>contribuyente.EstadoCivil;
	    cout<<"Telefono: ";
	    cin.ignore();
	    cin.getline(contribuyente.telefono,12+1,'\n');
	    cout<<"Direccion: ";
	    cin.getline(contribuyente.direccion,45+1,'\n');
	    cout<<"Ingresa tu fecha de nacimiento con el formato AAAA/MM/DD"
	    <<endl<<"Ejemplo 1997/09/07 : ";
	    cin.getline(contribuyente.fechaNacimiento,10+1,'\n');
	    //Acomodamos la informacion.
		PonerEnMayusculas();
	    PonerEspacios();
	    //Generamos un RFC.
	    GenerarRFC();
	    //Agregamos el registro al archivo.
	    AgregarAlArchivo();
	    cout<<"\nRegristro guardado con exito."<<endl;
	    //Mostramos el RFC.
		cout<<"\n\tSu RFC es: ";
		ImprimirTexto(contribuyente.rfc,sizeof(contribuyente.rfc));
		//Cargamos el registro al indice primario.
		InsertarIndiceP(contribuyente.rfc);
	    //Cargamos el registro al indice secundario.
	    ListaInvertida.Insertar(contribuyente.rfc,contribuyente.ciudad);
	}
	else
		cout<<"\n\tSe a alcanzado el maximo de registros en el sistema."<<endl;
}

void RecuperarIndices(Lista &ListaInvertida){
	ifstream Archivo("Reg_Datos.txt", ios::in);
	if(Archivo.is_open()){
		string Texto;
		while(!Archivo.eof()){
			getline(Archivo,Texto,Delimitador);
			if(Archivo.eof())
				break;
			getline(Archivo,Texto,Delimitador);
			//Cargamos un RFC al contrubuyente.
			StringToChar(Texto,contribuyente.rfc,Texto.size());
			for(int i(0);i<6;i++)
				getline(Archivo,Texto,Delimitador);
			//Cargamos un RFC al contrubuyente.
			StringToChar(Texto,contribuyente.ciudad,Texto.size());
			getline(Archivo,Texto,'\n');
			//Cargamos el registro al indice primario.
			InsertarIndiceP(contribuyente.rfc);
		    //Cargamos el registro al indice secundario.
		    ListaInvertida.Insertar(contribuyente.rfc,contribuyente.ciudad);
		}
	}
	Archivo.close();
}

int main(){
	srand(time(NULL));
	Lista ListaInvertida;
	RecuperarIndices(ListaInvertida);
	int opc;
	do{
		cout<<"\n\t- - - - - M E N U - - - - -"<<endl
		<<"\t   1.- Agregar Registro"<<endl
		<<"\t   2.- Buscar Registro"<<endl
		<<"\t   3.- Salir"<<endl
		<<"\t- - - - - - - - - - - - - -"<<endl
		<<"\tQue deseas hacer: ";
		cin>>opc;
		switch(opc){
			case 1:{
				AgregarRegistro(ListaInvertida);
				break;
			}
			case 2:{
				SubMenu(ListaInvertida);
				break;
			}
			case 3:{
				cout<<"\n\tAdios :)"<<endl;
				break;
			}
			default:{
				cout<<"\n\tSolo puedes ingresar numeros del 1 al 3."<<endl;
				break;
			}
		}
	}while(opc!=3);
	return 0;
}

