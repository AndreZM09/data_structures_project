using namespace std;

//Variables Globales

int Contador=0;

struct Contribuyentes{
    char rfc[LongLlavePrimaria]; // mascara (formato de captura) CCCCDDDDDDDCD
    char nombre[32];
    char apellido[2][32];
    char telefono[12];
    char direccion[45];
    char ciudad[LongLlaveSecundaria];
    char fechaNacimiento[10]; // formato AAAA/MM/DD: Año,mes y dia
    int VariableNula;	//Por alguna razon que desconosco la varible que esta debajo de la fecha nunca funciona, esta es la solucion que encontre :(
    int dependientes;
    char EstadoCivil;
}contribuyente;

struct stIndiceRfc{
    char rfc[LongLlavePrimaria];
    short int indice; // 2 bytes (NRR)
}IndicePrimario[LimiteRegistros];


