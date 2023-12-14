class NodoLista{
	private:
		char ciudad[LongLlaveSecundaria];
		Sublista* sublista;
		NodoLista* siguiente;
		void InsertarAdenlante(char[],char[],Sublista*);
		friend class Lista;
};

void NodoLista::InsertarAdenlante(char LlavePrimaria[],char LlaveSecundaria[], Sublista* sublista_){
	//Se crea un nodo de la lista.
	NodoLista* NuevoNodo = new NodoLista;
	//Se actualizan los punteros para acomodar el nodo en el lugar deseado y mantener la relacion en la lista.
	NuevoNodo->siguiente=this->siguiente;
	this->siguiente=NuevoNodo;
	//Se carga el nodo con la informacion que almacenara.
	CopiarArreglo(LlaveSecundaria,NuevoNodo->ciudad,LongLlaveSecundaria);
	NuevoNodo->sublista=sublista_;
	NuevoNodo->sublista->Insertar(LlavePrimaria);
}

//////////////////////////////////////////////////////////////////////////////////////

class Lista{
	private:
		NodoLista Inicio;
	public:
		Lista();
		bool IsEmpty();
		void Insertar(char[],char[]);
		NodoLista* GetAnterior(NodoLista* aux);
		void Buscar(char[]);
		void Salvar();
};

Lista::Lista(){
	//Se relacionan el Inicio y Fin de la lista al momento de crearse.
	Inicio.siguiente=NULL;
}

bool Lista::IsEmpty(){
	//Esta funcion evalua si la lista esta vacia.
	return Inicio.siguiente==NULL;
}

NodoLista* Lista::GetAnterior(NodoLista* aux){
	//Esta funcion nos regresa el nodo anterior de la posicion en la que nos encontremos.
	NodoLista* anterior = &Inicio;
	while(anterior->siguiente!=aux)
		anterior=anterior->siguiente;
	return anterior;
}

void Lista::Insertar(char LlavePrimaria[],char LlaveSecundaria[]){
	//Verificamos si la lista esta vacia para crear un primer nodo el cual no se necesita acomodar.
	if(IsEmpty()){
		Sublista* sublista = new Sublista;
		Inicio.InsertarAdenlante(LlavePrimaria,LlaveSecundaria,sublista);
		Salvar();
		return;
	}
	//Si la lista no esta vacia se crea un nodo auxiliar que apunta al primer elemnto de la lista.
	NodoLista* aux = Inicio.siguiente;
	//Recorremos la lista de manera lineal hasta llegar al final, en el peor de los casos.
	while(aux!=NULL){
		//Si la sublista de la llave secundaria ya existe solo se inserta la llave primaria.
		if(CompararArreglo(aux->ciudad,LlaveSecundaria,LongLlaveSecundaria)){
			aux->sublista->Insertar(LlavePrimaria);
			Salvar();
			return;
		}
		//Sino, se busca el lugar donde deberia de ir la llave secundaria para mantener la lista ordenada.
		if(MenorQue(LlaveSecundaria,aux->ciudad,LongLlaveSecundaria)){
			Sublista* sublista = new Sublista;
			aux=GetAnterior(aux);
			aux->InsertarAdenlante(LlavePrimaria,LlaveSecundaria,sublista);
			Salvar();
			return;
		}
		//En caso de no escontrar la sublista o lugar correcto avanzamos al siguiente nodo.
		aux=aux->siguiente;
	}
	//En el caso de que se termino de recorrer toda la lista y no se insertaron los datos
	//se insertan al final de la lista para mantenerla ordenada.
	Sublista* sublista = new Sublista;
	aux=GetAnterior(aux);
	aux->InsertarAdenlante(LlavePrimaria,LlaveSecundaria,sublista);
	Salvar();
}

void Lista::Buscar(char LlaveSecundaria[]){
	//Creamos un nodo auxiliar que apunta al primer elemnto de la lista.
	NodoLista* aux = Inicio.siguiente;
	//Recorremos la lista de manera lineal hasta llegar al final, en el peor de los casos.
	while(aux!=NULL){
		//Si la llave secundaria ya existe solo le decimos a su sublista que se imprima.
		if(CompararArreglo(LlaveSecundaria,aux->ciudad,LongLlaveSecundaria)){
			cout<<"\n\tEstos los datos de los contrubuyestes de la ciudad: ";
			ImprimirTexto(aux->ciudad,sizeof(aux->ciudad));
			cout<<endl;
			aux->sublista->Imprimir();
			return;
		}
		//En caso de no escontrar la llave secundaria avanzamos al siguiente nodo.
		aux=aux->siguiente;
	}
	//Si no se encontro la llave secundaria mandamos un error en pantalla.
	cout<<"\n\t\tNo se encontro la ciudad: ";
	ImprimirTexto(LlaveSecundaria,LongLlaveSecundaria);
}

void Lista::Salvar(){
	ofstream Archivo("IndS.txt", ios::out);
	//Creamos un nodo auxiliar que apunta al primer elemnto de la lista.
	NodoLista* aux = Inicio.siguiente;
	//Recorremos la lista de manera lineal hasta llegar al final.
	while(aux!=NULL){
		//Guardamos la llave secundaria.
		Guardar(Archivo,aux->ciudad,LongLlaveSecundaria,false);
		//Guardamos la sublista que contiene
		aux->sublista->Salvar(Archivo);
		//Avanzamos al siguiente nodo.
		aux=aux->siguiente;
	}
    Archivo.close();
}


