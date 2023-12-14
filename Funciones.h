void CopiarArreglo(char Copiar[],char Pegar[],int Tamanio){
	//Esta funcion copia los datos de un arreglo a otro del mismo tamaño.
	for(int i(0);i<Tamanio;i++)
		Pegar[i]=Copiar[i];
}

bool CompararArreglo(char Arreglo1[],char Arreglo2[],int Tamanio){
	//Esta funcion compara los datos de un arreglo con otro del mismo tamaño.
	for(int i(0);i<Tamanio;i++)
		if(Arreglo1[i]!=Arreglo2[i])
			return false;
	return true;
}

bool MenorQue(char Arreglo1[],char Arreglo2[],int Tamanio){
	//Esta funcion retorna un booleano dependiendo si el arreglo1 es menor al arreglo2 con ayuda del codigo ASCII.
	for(int i(0);i<Tamanio;i++){
		if(Arreglo1[i]<Arreglo2[i])
			return true;
		if(Arreglo2[i]<Arreglo1[i])
			return false;
	}
}

char NumRandom(){
	//Esta funcion genera un caracter aleatorio entre los numeros 0 y 9 con ayuda del codigo ASCII.
	return 48 + rand() % 9 + 1;
}

char LetraRandom(){
	//Esta funcion genera una letra aleatoria mayuscula con ayuda del codigo ASCII.
	return 65 + rand() % 25 + 1;
}

char PrimeraVocal(char texto[],int tamanio){
	//Esta funcion retorna la primera vocal de un texto, sino retorna un espacio.
	for(int i(0);i<tamanio;i++)
		if(texto[i]=='A' or texto[i]=='E' or texto[i]=='I' or texto[i]=='O' or texto[i]=='U')
			return texto[i];
	return 32;
}

void aMayusculas(char texto[],int tamanio){
	//Esta funcion convierte letras minusculas a mayusculas con ayuda del codigo ASCII.
	for(int i(0);i<tamanio;i++)
		if(texto[i]>='a' and texto[i]<='z')
			texto[i]-=32;
}

void RellenarConEspacios(char texto[],int tamanio){
	//Esta funcion rellena con espacios los caracteres que no se ocuparon.
	for(int i(0);i<tamanio;i++)
		if(texto[i]==CaracterNulo){
			for(int j=i;j<tamanio;j++)
				texto[j]=' ';
			return;
		}
}

void ImprimirTexto(char texto[],int tamanio){
	//Esta funcion simplemente imprime un texto en pantalla.
	for(int i(0);i<tamanio;i++)
		cout<<texto[i];
	cout<<endl;
}

void PonerEspacios(){
	//Esta funcion reune en una sola instruccion la orden de rellenar todos los espacios no utilizados con espacios
	RellenarConEspacios(contribuyente.nombre,sizeof(contribuyente.nombre));
	RellenarConEspacios(contribuyente.apellido[0],sizeof(contribuyente.apellido[0]));
	RellenarConEspacios(contribuyente.apellido[1],sizeof(contribuyente.apellido[1]));
	RellenarConEspacios(contribuyente.telefono,sizeof(contribuyente.telefono));
	RellenarConEspacios(contribuyente.direccion,sizeof(contribuyente.direccion));
	RellenarConEspacios(contribuyente.ciudad,sizeof(contribuyente.ciudad));
	RellenarConEspacios(contribuyente.fechaNacimiento,sizeof(contribuyente.fechaNacimiento));
}

void PonerEnMayusculas(){
	//Esta funcion reune en una sola instruccion la orden de convertir a mayusculas los
	//atributos importantes de un Contribuyente que tenga sus datos ya cargados en la estructura.
	aMayusculas(contribuyente.nombre,sizeof(contribuyente.nombre));
	aMayusculas(contribuyente.apellido[0],sizeof(contribuyente.apellido[0]));
	aMayusculas(contribuyente.apellido[1],sizeof(contribuyente.apellido[1]));
	aMayusculas(contribuyente.direccion,sizeof(contribuyente.direccion));
	aMayusculas(contribuyente.ciudad,sizeof(contribuyente.ciudad));
}

void GenerarRFC(){
	//Esta funcion genera un rfc para el Contribuyente que tenga sus datos ya cargados en la estructura.
	//Primera letra del apellido paterno.
	contribuyente.rfc[0]=contribuyente.apellido[0][0];
	//Siguiente vocal del apellido paterno.
	contribuyente.rfc[1]=PrimeraVocal(contribuyente.apellido[0],sizeof(contribuyente.apellido[0]));
	//Primera letra del apellido materno.
	contribuyente.rfc[2]=contribuyente.apellido[1][0];
	//Primera letra del nombre.
	contribuyente.rfc[3]=contribuyente.nombre[0];
	//Últimos dos dígitos del año de nacimiento.
	contribuyente.rfc[4]=contribuyente.fechaNacimiento[2];
	contribuyente.rfc[5]=contribuyente.fechaNacimiento[3];
	//Dos dígitos del mes de nacimiento.
	contribuyente.rfc[6]=contribuyente.fechaNacimiento[5];
	contribuyente.rfc[7]=contribuyente.fechaNacimiento[6];
	//Dos dígitos del día de nacimiento.
	contribuyente.rfc[8]=contribuyente.fechaNacimiento[8];
	contribuyente.rfc[9]=contribuyente.fechaNacimiento[9];
	//2 digitos y una letra aleatorios.
	contribuyente.rfc[10]=NumRandom();
	contribuyente.rfc[11]=LetraRandom();
	contribuyente.rfc[12]=NumRandom();
}

void Guardar(ofstream &out,char texto[],int tamanio,bool ImprimirDelmitador){
	//Esta funcion guarda carcater por caracter de un arreglo.
	for(int i(0);i<tamanio;i++)
		out<<texto[i];
	if(ImprimirDelmitador)
		out<<Delimitador;
}

void AgregarAlArchivo(){
	//Esta funcion agrega al archivo el contribuyente que este cargado en la estructura.
	ofstream Archivo("Reg_Datos.txt", ios::app);
	if(Contador<10)
		Archivo<<0;
	Archivo<<Contador<<Delimitador;	
	Guardar(Archivo,contribuyente.rfc,sizeof(contribuyente.rfc),true);
	Guardar(Archivo,contribuyente.nombre,sizeof(contribuyente.nombre),true);
	Guardar(Archivo,contribuyente.apellido[0],sizeof(contribuyente.apellido[0]),true);
	Guardar(Archivo,contribuyente.apellido[1],sizeof(contribuyente.apellido[1]),true);
	Guardar(Archivo,contribuyente.telefono,sizeof(contribuyente.telefono),true);
	Guardar(Archivo,contribuyente.direccion,sizeof(contribuyente.direccion),true);
	Guardar(Archivo,contribuyente.ciudad,sizeof(contribuyente.ciudad),true);
	Guardar(Archivo,contribuyente.fechaNacimiento,sizeof(contribuyente.fechaNacimiento),true);
	Archivo<<contribuyente.EstadoCivil<<Delimitador
	<<contribuyente.dependientes<<endl;  
    Archivo.close();
}

void SalvarIndiceP(){
	//Esta funcion guarda en un archivo el indice primario ya ordenado.
	ofstream Archivo("IndP.txt", ios::out);
	for(int i(0);i<Contador;i++){
		Guardar(Archivo,IndicePrimario[i].rfc,LongLlavePrimaria,true);
		if(i<10)
			Archivo<<0;
		Archivo<<IndicePrimario[i].indice<<endl;
	}
	Archivo.close();
}

void InsertarIndiceP(char Arreglo[]){
	//Si el indice primario esta vacio, insertamos el nuevo dato en la posicion 0 del arreglo ya que no existen datos para ordenar.
	if(Contador==0){
		IndicePrimario[Contador].indice = Contador;
		CopiarArreglo(Arreglo,IndicePrimario[Contador++].rfc,LongLlavePrimaria);
		SalvarIndiceP();
		return;
	}
	//Si no esta vacia, buscamos el lugar donde se deberian insertar los datos para mantener la lista ordenada.
	for(int i(0);i<Contador;i++){
		if(MenorQue(Arreglo,IndicePrimario[i].rfc,LongLlavePrimaria)){
			//Si encontramos el lugar para insertarlo recorremos todos los datos de la lista una posicion adelante apartir de donde se encontro el lugar.
			//Se recorren los datos una posicion adelante para liberar un espacion que sera el lugar donde vamos a insertar el dato nuevo y no perder los datos que ya teniamos.
			for(int j=Contador;j>=i;j--){
				IndicePrimario[j+1].indice = IndicePrimario[j].indice;
				CopiarArreglo(IndicePrimario[j].rfc,IndicePrimario[j+1].rfc,LongLlavePrimaria);
			}
			//Agregamos el nuevo registro al indice en el lugar que le reservamos para mantener la lista ordenada.
			IndicePrimario[i].indice = Contador;
			CopiarArreglo(Arreglo,IndicePrimario[i].rfc,LongLlavePrimaria);
			Contador++;
			SalvarIndiceP();
			return;
		}
	}
	//En caso de no encontrar un lugar, se insertaran los datos al final de la lista ya que ese es el lugar donde tienen que ir para mantener la lista ordenada.
	IndicePrimario[Contador].indice = Contador;
	CopiarArreglo(Arreglo,IndicePrimario[Contador++].rfc,LongLlavePrimaria);
	SalvarIndiceP();
}

void ImprimirRegistro(ifstream &in){
	//Esta funcion imprime en pantalla un registro obteniendo los datos desde el archivo.
	string texto;
	getline(in,texto,Delimitador);
	cout<<"\n\n\tEl NRR es: "<<texto;
	getline(in,texto,Delimitador);
	cout<<"\n\tEl RFC es: "<<texto;
	getline(in,texto,Delimitador);
	cout<<"\n\tEl Nombre es: "<<texto;
	getline(in,texto,Delimitador);
	cout<<"\n\tEl Apellido paterno es: "<<texto;
	getline(in,texto,Delimitador);
	cout<<"\n\tEl Apellido materno es: "<<texto;
	getline(in,texto,Delimitador);
	cout<<"\n\tEl Telefono es: "<<texto;
	getline(in,texto,Delimitador);
	cout<<"\n\tLa Direccion es: "<<texto;
	getline(in,texto,Delimitador);
	cout<<"\n\tLa Ciudad es: "<<texto;
	getline(in,texto,Delimitador);
	cout<<"\n\tLa Fecha es: "<<texto;
	getline(in,texto,Delimitador);
	cout<<"\n\tEl Estado Civil es: "<<texto;
	getline(in,texto,'\n');
	cout<<"\n\tEl Numero de Dependientes es: "<<texto<<endl;
}

void BuscarLlavePrimaria(char LlavePrimaria[]){
	//Esta funcion buscar una llave primaria en el indice primario.
	for(int i(0);i<=Contador;i++){
		if(CompararArreglo(IndicePrimario[i].rfc,LlavePrimaria,LongLlavePrimaria)){
			//Si la encuentra, abrimos el archivo y saltamos en la posicion del NRR del indice primario mostrando en pantalla el registro que se encuentra en esa posicion.
			string basura;
			ifstream Archivo("Reg_Datos.txt", ios::in);
			for(int j(0);j<IndicePrimario[i].indice;j++)
				getline(Archivo,basura,'\n');
			ImprimirRegistro(Archivo);
			Archivo.close();
			return;
		}
	}
	//Si no se encontro el RFC, mostramos en pantalla un error.
	cout<<"\n\tNo se encontro el RFC: ";
	ImprimirTexto(LlavePrimaria,LongLlavePrimaria);
}

void StringToChar(string Copiar,char Pegar[],int Tamanio){
	//Esta funcion almacena la informacion de un string en un arreglo de caracteres.
	for(int i(0);i<Tamanio;i++)
		Pegar[i]=Copiar[i];
}

