class NodoSublista{
	private:
		char rfc[LongLlavePrimaria];
		NodoSublista* siguiente;
		void InsertarAdenlante(char[]);
		friend class Sublista;
};

void NodoSublista::InsertarAdenlante(char LlavePrimaria[]){
	//Se crea un nodo de la sublista.
	NodoSublista* NuevoNodo = new NodoSublista;
	//Se actualizan los punteros para acomodar el nodo en el lugar deseado y mantener la relacion en la lista.
	NuevoNodo->siguiente=this->siguiente;
	this->siguiente=NuevoNodo;
	//Se carga el nodo con la informacion que almacenara.
	CopiarArreglo(LlavePrimaria,NuevoNodo->rfc,LongLlavePrimaria);
}

/////////////////////////////////////////////////////////////////////////

class Sublista{
	private:
		NodoSublista Inicio;
		void BuscarIndP(char[]);
	public:
		Sublista();
		bool IsEmpty();
		void Insertar(char[]);
		NodoSublista* GetAnterior(NodoSublista*);
		void Imprimir();
		void Salvar(ofstream &out);
};

Sublista::Sublista(){
	//Se relacionan el Inicio y Fin de la lista al momento de crearse.
	Inicio.siguiente=NULL;
}

bool Sublista::IsEmpty(){
	//Esta funcion evalua si la lista esta vacia.
	return Inicio.siguiente==NULL;
}

void Sublista::BuscarIndP(char rfc_a_buscar[]){
	//Esta funcion busca un rfc en el indice primario.
	for(int i(0);i<=Contador;i++){
		if(CompararArreglo(IndicePrimario[i].rfc,rfc_a_buscar,LongLlavePrimaria)){
			//Si lo encuentra obtenemos el NRR y lo buscamos en el archivo de indices secundarios para mostrarlo en pantalla.
			string basura;
			ifstream Archivo("Reg_Datos.txt", ios::in);
			for(int j(0);j<IndicePrimario[i].indice;j++)
				getline(Archivo,basura,'\n');
			ImprimirRegistro(Archivo);
			Archivo.close();
			return;
		}
	}
}

void Sublista::Imprimir(){
	//Creamos un nodo auxiliar que apunta al primer elemnto de la lista.
	NodoSublista* aux = Inicio.siguiente;
	//Recorremos la lista de manera lineal hasta llegar al final.
	int cont=1;
	//Buscamos todos los RFC de la sublista en el indice primario.
	while(aux!=NULL){
		cout<<"\n\tContrubuyente: "<<cont++;
		BuscarIndP(aux->rfc);
		aux=aux->siguiente;
	}
}

NodoSublista* Sublista::GetAnterior(NodoSublista* aux){
	//Esta funcion nos regresa el nodo anterior de la posicion en la que nos encontremos.
	NodoSublista* anterior = &Inicio;
	while(anterior->siguiente!=aux)
		anterior=anterior->siguiente;
	return anterior;
}

void Sublista::Insertar(char LlavePrimaria[]){
	//Verificamos si la sublista esta vacia para crear un primer nodo el cual no se necesita acomodar.
	if(IsEmpty()){
		Inicio.InsertarAdenlante(LlavePrimaria);
		return;
	}
	//Si la sublista no esta vacia se crea un nodo auxiliar que apunta al primer elemnto de la sublista.
	NodoSublista* aux = Inicio.siguiente;
	//Recorremos la lista de manera lineal hasta llegar al final, en el peor de los casos.
	while(aux!=NULL){
		//Se busca el lugar donde deberia de ir la llave primaria para mantener la sublista ordenada
		if(MenorQue(LlavePrimaria,aux->rfc,LongLlavePrimaria)){
			aux=GetAnterior(aux);
			aux->InsertarAdenlante(LlavePrimaria);
			return;
		}
		//En caso de no estar en el lugar correcto avanzamos al siguiente nodo
		aux=aux->siguiente;
	}
	//En el caso de que se termino de recorrer toda la sublista y no se insertaron los datos
	//se insertan al final de la sublista para mantenerla ordenada
	aux=GetAnterior(aux);
	aux->InsertarAdenlante(LlavePrimaria);
}

void Sublista::Salvar(ofstream &out){
	//Creamos un nodo auxiliar que apunta al primer elemnto de la lista.
	NodoSublista* aux = Inicio.siguiente;
	//Recorremos la lista de manera lineal hasta llegar al final.
	while(aux!=NULL){
		//Guardamos un Delimitador.
		out<<Delimitador;
		//Guardamos el RFC.
		Guardar(out,aux->rfc,LongLlavePrimaria,false);
		//Avanzamos al siguiente nodo.
		aux=aux->siguiente;
	}
	out<<endl;
}

