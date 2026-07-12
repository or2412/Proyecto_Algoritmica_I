#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <windows.h>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <algorithm> // Para std::sort (ordenar padrones e historial)
#include <cctype> // Para isdigit/isalpha (validacion de datos ingresados)
#include <climits> // Para INT_MIN/INT_MAX (limites por defecto de leerEntero)

using namespace std;

// === CLASES ===
class Unidad{
  private:
   string placa{};
   int cod{};
   int capacidad{};
   string estado{}; 
 
   public:
   //constructor
   Unidad(string _placa, int _cod, int _capacidad, string _estado){
      placa=_placa;
      cod=_cod;
      capacidad=_capacidad;
      estado=_estado;
   }
   //getters
   string getPlaca() {return placa;}
   int getCodigo() {return cod;}
   int getCapacidad() {return capacidad;}
   string getEstado() {return estado;}
   //setters
   void setEstado(string newEstado) {estado=newEstado;}
};

class Operador{
  private:
   int cod{};
   int dni{};
   string nombres{};
   string apellidos{};
   string estado{};

  public:
   //constructor
   Operador(int _cod, int _dni, string _nombres, string _apellidos, string _estado){
      cod=_cod; 
      dni=_dni;
      nombres=_nombres;
      apellidos=_apellidos;
      estado=_estado;
   }
   //getters
   int getCodigo() {return cod;}
   int getDNI() {return dni;}
   string getNombres() {return nombres;}
   string getApellidos() {return apellidos;}
   string getNombreCompleto(){
      string fullName=nombres+" "+apellidos;
      return fullName;
   }
   string getEstado() {return estado;}
   //setters
   void setEstado(string newEstado) {estado=newEstado;}
};

class Servicio{
 private:
   int id{};
   int codUnid{};
   int codOp{};
   int pasajeros{};
   string destino{};
   string estado{};

 public:
   //constructor
   Servicio(int _id, int _codUnid, int _codOp, int _pasajeros, string _destino, string _estado){
      id=_id;
      codUnid=_codUnid;
      codOp=_codOp;
      pasajeros=_pasajeros;
      destino=_destino;
      estado=_estado;
   }
   //getters
   int getID() {return id;}
   int getCodigoUnid() {return codUnid;}
   int getCodigoOp() {return codOp;}
   int getNumPasajeros() {return pasajeros;}
   string getDestino() {return destino;}
   string getEstado() {return estado;}
   //setters
   void setEstado(string newEstado) {estado=newEstado;}
};

// === UTILIDADES DE CONSOLA (TUI) ===
void limpiarPantalla(){
   #ifdef _WIN32
      system("cls");
   #else
      system("clear");
   #endif
}

string llenar(int extension, const string &simbolo){
	string relleno{};
	for (int i=1; i<=extension; i++) relleno+=simbolo;
	return relleno;
}

void titulo(const string &title, int cat){
	int tamReal{};
	for (size_t i=0; i<title.size(); i++){
		unsigned char c=(unsigned char)(title[i]);
		if (c<128 || c>191) tamReal++;
	}
	int anchoBorde=(int)((tamReal*1.618034)+0.5); //0.5 para que al perder su parte entera sea le aproximado perfecto :D
	string centros{};
	//categorías
	switch (cat){
		case 0:{
			string temp{},newTitle{};
			for (size_t i=0; i<title.size(); i++){
				unsigned char c=(unsigned char)title[i];
				if ((c<128 || c>191) && newTitle.empty()==false){
					newTitle+=" ";
				}
				newTitle+=title[i];
			}
			tamReal=2*(tamReal)-1;
			anchoBorde=(int)((tamReal*1.618034)+0.5);
			if ((((anchoBorde-tamReal)/2)-1)<4 ||
				(((anchoBorde-1-tamReal)/2.0)-0.5)<4){
				anchoBorde=tamReal+8;
				string relleno(1, ' ');
				centros=relleno;
			}
			else{
				if ((anchoBorde-tamReal)%2==0){
					string relleno(((anchoBorde-tamReal)/2)-3,' ');
					centros=relleno;
				}
				else{
					anchoBorde--;
					string relleno(((anchoBorde-tamReal)/2)-3,' ');
					centros=relleno;
				}
			}
			cout<<"\033[96m  ╔"<<llenar(anchoBorde-6, "═")   <<"╗  \033[0m\n";
			cout<<"\033[96m╔═╝ "<<llenar(anchoBorde-8, "─") <<" ╚═╗\033[0m\n";
			cout<<"\033[96m║ │"<<centros<<"\033[0m"<<newTitle<<"\033[96m"<<centros<<"│ ║\033[0m\n";
			cout<<"\033[96m╚═╗ "<<llenar(anchoBorde-8, "─") <<" ╔═╝\033[0m\n";
			cout<<"\033[96m  ╚"<<llenar(anchoBorde-6, "═")   <<"╝  \033[0m\n";
			break;
		}
		case 1:{
			if ((((anchoBorde-tamReal)/2)-1)<2 ||
				(((anchoBorde-1-tamReal)/2.0)-0.5)<2){
				anchoBorde=tamReal+4;
				string relleno(1, ' ');
				centros=relleno;
			}
			else{
				if ((anchoBorde-tamReal)%2==0){
					string relleno(((anchoBorde-tamReal)/2)-1,' ');
					centros=relleno;
				}
				else{
					anchoBorde--;
					string relleno(((anchoBorde-tamReal)/2)-1,' ');
					centros=relleno;
				}
			}
			cout<<"\033[36m╔"<<llenar(anchoBorde-2, "═")<<"╗\033[0m\n";
			cout<<"\033[36m║"<<centros<<"\033[0m"<<title<<"\033[36m"<<centros<<"║\033[0m\n";
			cout<<"\033[36m╚"<<llenar(anchoBorde-2, "═")<<"╝\033[0m\n";
			break;
		}
		case 2:{
			if ((((anchoBorde-tamReal)/2)-1)<2 ||
				(((anchoBorde-1-tamReal)/2.0)-0.5)<2){
				anchoBorde=tamReal+4;
				string relleno(1, ' ');
				centros=relleno;
			}
			else{
				if ((anchoBorde-tamReal)%2==0){
					string relleno(((anchoBorde-tamReal)/2)-1,' ');
					centros=relleno;
				}
				else{
					anchoBorde--;
					string relleno(((anchoBorde-tamReal)/2)-1,' ');
					centros=relleno;
				}
			}
			cout<<"\033[34m┌"<<llenar(anchoBorde-2, "─")<<"┐\033[0m\n";
			cout<<"\033[34m│"<<centros<<"\033[0m"<<title<<"\033[34m"<<centros<<"│\033[0m\n";
			cout<<"\033[34m└"<<llenar(anchoBorde-2, "─")<<"┘\033[0m\n";
			break;
		}
		case 3:{
			if ((((anchoBorde-tamReal)/2)-1)<2 ||
				(((anchoBorde-1-tamReal)/2.0)-0.5)<2){
				anchoBorde=tamReal+4;
				string relleno(2,'=');
				centros=relleno;
			}
			else{
				if ((anchoBorde-tamReal)%2==0){
					string relleno(((anchoBorde-tamReal)/2)-1,'=');
					centros=relleno;
				}
				else{
					anchoBorde--;
					string relleno(((anchoBorde-tamReal)/2)-1,'=');
					centros=relleno;
				}
			}
			cout<<"\033[35m"<<centros<<" \033[0m"<<title<<"\033[35m "<<centros<<"\033[0m"<<endl;
			break;
		}
		case 4:{
			if ((((anchoBorde-tamReal)/2)-1)<2 ||
				(((anchoBorde-1-tamReal)/2.0)-0.5)<2){
				anchoBorde=tamReal+4;
				string relleno(2,'-');
				centros=relleno;
			}
			else{
				if ((anchoBorde-tamReal)%2==0){
					string relleno(((anchoBorde-tamReal)/2)-1,'-');
					centros=relleno;
				}
				else{
					anchoBorde--;
					string relleno(((anchoBorde-tamReal)/2)-1,'-');
					centros=relleno;
				}
			}
			cout<<"\033[90m"<<centros<<" \033[0m"<<title<<"\033[90m "<<centros<<"\033[0m"<<endl;
			break;
		}
	}
}

void puntosCarga(int repeticion, unsigned int retraso){
   for(int i=1; i<=repeticion; i++){
      for (int j=1; j<=3; j++){
         cout<<".";
         Sleep(retraso);
      }
      cout<<llenar(3,"\b")<<llenar(3," ")<<llenar(3,"\b");
      Sleep(retraso);
   }
}

void menuPrincipal(){
   limpiarPantalla();
   titulo("SISTEMA DE GESTIÓN DE TRANSPORTE", 0);
   cout<<"\033[96m"<<"  ├╴["<<"\033[0m"<<"1"<<"\033[96m"<<"] "<<"\033[0m"<<"PADRÓN GENERAL\n";
   cout<<"\033[96m"<<"  ├╴["<<"\033[0m"<<"2"<<"\033[96m"<<"] "<<"\033[0m"<<"HISTORIAL DE SERVICIOS\n";
   cout<<"\033[96m"<<"  ├╴["<<"\033[0m"<<"3"<<"\033[96m"<<"] "<<"\033[0m"<<"OPERACIONES\n";
   cout<<"\033[96m"<<"  ├╴["<<"\033[0m"<<"4"<<"\033[96m"<<"] "<<"\033[0m"<<"NUEVOS REGISTROS\n";
   cout<<"\033[96m"<<"  └╴["<<"\033[0m"<<"0"<<"\033[96m"<<"] "<<"\033[0m"<<"GUARDAR Y SALIR\n";
   cout<<"\n\033[96m►► \033[0m"<<"Ingresar opción "<<"\033[96m-→ \033[0m";
}

void menuPadron(){
   limpiarPantalla();
   titulo("PADRÓN GENERAL", 1);
   cout<<"  ├╴[1] PADRÓN DE UNIDADES\n";
   cout<<"  ├╴[2] PADRÓN DE OPERADORES\n";
   cout<<"  └╴[0] REGRESAR AL MENÚ PRINCIPAL\n";
   cout<<"\n►► Ingresar opción -→ ";
}

void menuOperaciones(){
   limpiarPantalla();
   titulo("MÓDULO DE OPERACIONES", 1);
   cout<<"  ├╴[1] PROGRAMAR NUEVO SERVICIO\n";
   cout<<"  ├╴[2] PROCESAR SALIDA DE UNIDAD\n";
   cout<<"  ├╴[3] PROCESAR ARRIBO DE UNIDAD\n";
   cout<<"  ├╴[4] MARCAR FIN DE DESCANSO\n";
   cout<<"  └╴[0] REGRESAR AL MENÚ PRINCIPAL\n";
   cout<<"\n►► Ingresar opción -→ ";
}

void menuRegistros(){
   limpiarPantalla();
   titulo("MÓDULO DE REGISTROS", 1);
   cout<<"  ├╴[1] REGISTRAR NUEVA UNIDAD\n";
   cout<<"  ├╴[2] REGISTRAR NUEVO OPERADOR\n";
   cout<<"  └╴[0] REGRESAR AL MENÚ PRINCIPAL\n";
   cout<<"\n►► Ingresar opción -→ ";
}

void menuFinDescansos(){
   limpiarPantalla();
   titulo("FIN DE DESCANSO", 2);
   cout<<"  ├╴[1] UNIDAD\n";
   cout<<"  ├╴[2] OPERADOR\n";
   cout<<"  └╴[0] REGRESAR AL MENÚ DE OPERACIONES\n";
   cout<<"\n►► Ingresar opción -→ ";
}

void pausar(){
   cout<<"\n\033[2;37mPresione ENTER para continuar...\033[0m";
   //cin.ignore();
   cin.get();
}

bool esCancelacion(const string &entrada){
   string t=entrada;
   for (size_t i=0; i<t.size(); i++) t[i]=(char)toupper((unsigned char)t[i]);
   return (t=="Q" || t=="CANCELAR");
}

bool esSoloDigitos(const string &texto, size_t desde=0){
   if (desde>=texto.size()) return false;
   return all_of(texto.begin()+desde, texto.end(), [](unsigned char c){
      return isdigit(c);
   });
}

// Convierte un texto a mayusculas y le quita las tildes (acentos), para que
// todo lo que el usuario escribe se guarde de forma uniforme en los archivos.
// La letra "Ñ"/"ñ" NO se considera una tilde, por lo que se conserva (solo
// se pasa a mayuscula si vino en minuscula). El atributo Estado nunca pasa
// por esta funcion, ya que sus valores ("Disponible", "Activo", etc.) son
// asignados internamente por el programa y no son texto libre del usuario.
string normalizarTexto(const string &texto){
   string resultado{};
   for (size_t i=0; i<texto.size(); i++){
      unsigned char c=(unsigned char)texto[i];
      // Caracteres UTF-8 de 2 bytes (tildes y diéresis): 0xC3 0x??
      if (c==0xC3 && i+1<texto.size()){
         unsigned char c2=(unsigned char)texto[i+1];
         switch (c2){
            case 0x81: case 0xA1: resultado+='A'; i++; continue; // Á á -> A
            case 0x89: case 0xA9: resultado+='E'; i++; continue; // É é -> E
            case 0x8D: case 0xAD: resultado+='I'; i++; continue; // Í í -> I
            case 0x93: case 0xB3: resultado+='O'; i++; continue; // Ó ó -> O
            case 0x9A: case 0xBA: resultado+='U'; i++; continue; // Ú ú -> U
            case 0x9C: case 0xBC: resultado+='U'; i++; continue; // Ü ü -> U
            case 0x91: case 0xB1: resultado+="\xC3\x91"; i++; continue; // Ñ/ñ -> Ñ (se conserva)
            default: break; // Otro caracter UTF-8 no contemplado: se deja tal cual
         }
      }
      resultado+=(char)toupper(c);
   }
   return resultado;
}

// Lee texto libre. Devuelve false si el usuario cancela (escribe 'C').
// Por defecto no permite campos vacios. El texto valido se guarda en
// mayusculas y sin tildes.
bool leerTexto(const string &prompt, string &valor, bool permitirVacio=false){
   string entrada{};
   while (true){
      cout<<prompt;
      getline(cin, entrada);
      if (esCancelacion(entrada)) return false;
      if (entrada.empty() && !permitirVacio){
         cout<<"\033[31m[ERROR] Este campo no puede estar vacio. (Escriba 'C' para cancelar)\033[0m\n";
         continue;
      }
      valor=normalizarTexto(entrada);
      return true;
   }
}

// Lee un entero dentro de un rango opcional [minimo, maximo].
// Devuelve false si el usuario cancela (escribe 'C').
bool leerEntero(const string &prompt, int &valor, int minimo=INT_MIN, int maximo=INT_MAX){
   string entrada{};
   while (true){
      cout<<prompt;
      getline(cin, entrada);
      if (esCancelacion(entrada)) return false;

      size_t desdeDigitos=0;
      if (!entrada.empty() && (entrada[0]=='-' || entrada[0]=='+')) desdeDigitos=1;
      if (!esSoloDigitos(entrada, desdeDigitos)){
         cout<<"\033[31m[ERROR] Debe ingresar un numero valido. (Escriba 'C' para cancelar)\033[0m\n";
         continue;
      }

      int numero{};
      try{
         numero=stoi(entrada);
      } catch(...){
         cout<<"\033[31m[ERROR] El numero ingresado es demasiado grande. (Escriba 'C' para cancelar)\033[0m\n";
         continue;
      }
      if (numero<minimo || numero>maximo){
         cout<<"\033[31m[ERROR] El valor debe estar entre "<<minimo<<" y "<<maximo<<". (Escriba 'C' para cancelar)\033[0m\n";
         continue;
      }
      valor=numero;
      return true;
   }
}

// Lee un DNI/C.E.: solo digitos, entre 8 y 12 caracteres (cubre DNI peruano
// de 8 digitos y Carnet de Extranjeria, que puede tener mas digitos).
bool leerDNI(const string &prompt, int &valor){
   string entrada{};
   while (true){
      cout<<prompt;
      getline(cin, entrada);
      if (esCancelacion(entrada)) return false;
      if (!esSoloDigitos(entrada) || entrada.size()<8 || entrada.size()>12){
         cout<<"\033[31m[ERROR] El DNI/C.E. debe tener entre 8 y 12 digitos numericos. (Escriba 'C' para cancelar)\033[0m\n";
         continue;
      }
      try{
         valor=stoi(entrada);
      } catch(...){
         cout<<"\033[31m[ERROR] El DNI/C.E. ingresado no es valido. (Escriba 'C' para cancelar)\033[0m\n";
         continue;
      }
      return true;
   }
}

// Valida el formato de placa esperado: 3 letras + guion + 3 numeros (ej. ABC-123)
bool tieneFormatoPlaca(const string &placa){
   if (placa.size()!=7) return false;
   for (int i=0; i<3; i++) if (!isalpha((unsigned char)placa[i])) return false;
   if (placa[3]!='-') return false;
   for (int i=4; i<7; i++) if (!isdigit((unsigned char)placa[i])) return false;
   return true;
}

// Lee una placa vehicular validando su formato (ej. ABC-123). Se guarda en mayusculas.
bool leerPlaca(const string &prompt, string &valor){
   string entrada{};
   while (true){
      cout<<prompt;
      getline(cin, entrada);
      if (esCancelacion(entrada)) return false;
      if (!tieneFormatoPlaca(entrada)){
         cout<<"\033[31m[ERROR] Formato de placa no valido. Use el formato ABC-123. (Escriba 'C' para cancelar)\033[0m\n";
         continue;
      }
      valor=normalizarTexto(entrada);
      return true;
   }
}

// === PERSISTENCIA DE DATOS (ARCHIVOS) ===
const string UNIDADES="unidades.txt";
const string OPERADORES="operadores.txt";
const string SERVICIOS="historial_serv.txt";

// Carga los datos del disco duro a la RAM al iniciar
void cargarUNIDADES(vector<Unidad>& padron){
   ifstream archivo(UNIDADES); //ios::in es su modo por defecto
   string linea{}, placa{}, strCod{}, strCap{}, estado{};
   int cod{}, capacidad{};
   cout<<"\nCargando datos de UNIDADES"; puntosCarga(3, 150);

   if (archivo.is_open()){
      while (getline(archivo, linea)){
         stringstream datoLinea(linea);
         // Formato esperado: PLACA,CÓDIGO,CAPACIDAD,ESTADO
         getline(datoLinea, placa, ',');
         getline(datoLinea, strCod, ',');
         getline(datoLinea, strCap, ',');
         getline(datoLinea, estado);
         
         cod=stoi(strCod); // Convertir string a entero
         capacidad=stoi(strCap); // Convertir string a entero
         padron.push_back(Unidad(placa, cod, capacidad, estado));
      }
      cout<<"\r[OK] Datos de UNIDADES cargados exitosamente."<<endl;
      archivo.close();
   }
   else cout<<"\rError al leer el archivo. No se pueden cargar los datos."<<endl;
}

void cargarOPERADORES(vector<Operador>& padron){
   ifstream archivo(OPERADORES); //ios::in es su modo por defecto
   string linea{}, strCod{}, strDNI{}, nombres{}, apellidos{}, estado{};
   int cod{}, dni{};
   cout<<"\nCargando datos de OPERADORES"; puntosCarga(3, 150);

   if (archivo.is_open()){
      while (getline(archivo, linea)){
         stringstream datoLinea(linea);
         // Formato esperado: CÓDIGO,DNI,NOMBRES,APELLIDOS,ESTADO
         getline(datoLinea, strCod, ',');
         getline(datoLinea, strDNI, ',');
         getline(datoLinea, nombres, ',');
         getline(datoLinea, apellidos, ',');
         getline(datoLinea, estado);
         
         cod=stoi(strCod);
         dni=stoi(strDNI);
         padron.push_back(Operador(cod, dni, nombres, apellidos, estado));
      }
      cout<<"\r[OK] Datos de OPERADORES cargados exitosamente."<<endl;
      archivo.close();
   }
   else cout<<"\rError al leer el archivo. No se pueden cargar los datos."<<endl;
}

void cargarSERVICIOS(vector<Servicio>& padron){
   ifstream archivo(SERVICIOS); //ios::in es su modo por defecto
   string linea{}, strID{}, strCodUnid{}, strCodOp{}, strPasaj{}, destino{}, estado{};
   int id{}, codUnid{}, codOp{}, pasajeros{};
   cout<<"\nCargando datos de SERVICIOS"; puntosCarga(3, 150);

   if (archivo.is_open()){
      while (getline(archivo, linea)){
         stringstream datoLinea(linea);
         // Formato esperado: ID,COD_UNIDAD,COD_OPERADOR,PASAJEROS,DESTINO,ESTADO
         getline(datoLinea, strID, ',');
         getline(datoLinea, strCodUnid, ',');
         getline(datoLinea, strCodOp, ',');
         getline(datoLinea, strPasaj, ',');
         getline(datoLinea, destino, ',');
         getline(datoLinea, estado);
         
         id=stoi(strID);
         codUnid=stoi(strCodUnid);
         codOp=stoi(strCodOp);
         pasajeros=stoi(strPasaj);
         padron.push_back(Servicio(id, codUnid, codOp, pasajeros, destino, estado));
      }
      cout<<"\r[OK] Datos de SERVICIOS cargados exitosamente."<<endl;
      archivo.close();
   }
   else cout<<"\rError al leer el archivo. No se pueden cargar los datos."<<endl;
}

// Guarda los datos de la RAM al disco duro al salir
void guardarUNIDADES(vector<Unidad>& padron){
   ofstream archivo(UNIDADES, ios::out);
   cout<<"\nGuardando datos de UNIDADES"; puntosCarga(3, 150);
   
   if (archivo.is_open()){
      for (size_t i=0; i<padron.size(); i++){
         archivo<<padron[i].getPlaca()<<","
                <<padron[i].getCodigo()<<","
                <<padron[i].getCapacidad()<< ","
                <<padron[i].getEstado()<<"\n";
      }
      archivo.close();
      cout<<"\r[OK] Datos guardados exitosamente. Cierre seguro."<<endl;
   }
   else{
      cout<<"\r[ERROR CRITICO] No se pudo guardar en el disco."<<endl;
   }
}

void guardarOPERADORES(vector<Operador>& padron){
   ofstream archivo(OPERADORES, ios::out);
   cout<<"\nGuardando datos de OPERADORES"; puntosCarga(3, 150);
   
   if (archivo.is_open()){
      for (size_t i=0; i<padron.size(); i++){
         archivo<<padron[i].getCodigo()<<","
                <<padron[i].getDNI()<<","
                <<padron[i].getNombres()<<","
                <<padron[i].getApellidos()<<","
                <<padron[i].getEstado()<<"\n";
      }
      archivo.close();
      cout<<"\r[OK] Datos guardados exitosamente. Cierre seguro."<<endl;
   }
   else{
      cout<<"\r[ERROR CRITICO] No se pudo guardar en el disco."<<endl;
   }
}

void guardarSERVICIOS(vector<Servicio>& historial){
   ofstream archivo(SERVICIOS, ios::out);
   cout<<"\nGuardando datos de SERVICIOS"; puntosCarga(3, 150);
   
   if (archivo.is_open()){
      for (size_t i=0; i<historial.size(); i++){
         archivo<<historial[i].getID()<<","
                <<historial[i].getCodigoUnid()<<","
                <<historial[i].getCodigoOp()<< ","
                <<historial[i].getNumPasajeros()<< ","
                <<historial[i].getDestino()<< ","
                <<historial[i].getEstado()<<"\n";
      }
      archivo.close();
      cout<<"\r[OK] Datos guardados exitosamente. Cierre seguro."<<endl;
   }
   else{
      cout<<"\r[ERROR CRITICO] No se pudo guardar en el disco."<<endl;
   }
}

// === LOGICA DE NEGOCIO Y FUNCIONALIDADES ===
void mostrarPadronUnid(vector<Unidad>& padron){
   limpiarPantalla();
   titulo("PADRON DE UNIDADES", 2);
   cout<<endl;
   if (padron.empty()){
      cout<<"\033[33m[ALERTA] No hay unidades registradas en el padron.\033[0m"<<endl;
   }
   else{
      sort(padron.begin(), padron.end(), [](Unidad &a, Unidad &b){
         return a.getCodigo()<b.getCodigo();
      });
      cout<<"\033[1;36m"<<left<<setw(9)<<"CODIGO"<<setw(10)<<"PLACA"<<setw(12)<<"CAPACIDAD"<<setw(11)<<"ESTADO"<<"\033[0m"<<endl;
      cout<<"\033[36m"<<llenar(44, "-")<<"\033[0m\n";
      for (size_t i=0; i<padron.size(); i++){
         // Colores basicos ASCII  (Verde: "Disponible", Rojo: "Asignado", Amarillo: "En reposo")
         if(padron[i].getEstado()=="Disponible") cout<<"\033[32m";
         else if(padron[i].getEstado()=="Asignado") cout<<"\033[31m";
         else cout<<"\033[33m";
         //Información coloreada
         cout<<left
         <<setw(9)<<padron[i].getCodigo() 
         <<setw(10)<<padron[i].getPlaca() 
         <<setw(12)<<padron[i].getCapacidad() 
         <<setw(11)<<padron[i].getEstado()<<"\033[0m"<<endl;
      }
   }
   //no añadir
   pausar();
}

void mostrarPadronOp(vector<Operador>& padron){
   limpiarPantalla();
   titulo("PADRON DE OPERADORES", 2);
   cout<<endl;
   if (padron.empty()){
      cout<<"\033[33m[ALERTA] No hay operadores registrados en el padron.\033[0m"<<endl;
   }
   else{
      sort(padron.begin(), padron.end(), [](Operador &a, Operador &b){
         return a.getCodigo()<b.getCodigo();
      });
      cout<<"\033[1;36m"<<left<<setw(10)<<"CODIGO"<<setw(12)<<"DNI"<<setw(38)<<"NOMBRE COMPLETO"<<setw(20)<<"ESTADO"<<"\033[0m"<<endl;
      cout<<"\033[36m"<<llenar(75, "-")<<"\033[0m\n";
      for (size_t i=0; i<padron.size(); i++){
         // Colores basicos ASCII  (Verde: "Disponible", Rojo: "Asignado", Amarillo: "En reposo")
         if(padron[i].getEstado()=="Disponible") cout<<"\033[32m";
         else if(padron[i].getEstado()=="Asignado") cout<<"\033[31m";
         else cout<<"\033[33m";
         //Información coloreada
         cout<<left
         <<setw(10)<<padron[i].getCodigo() 
         <<setw(12)<<padron[i].getDNI() 
         <<setw(38)<<padron[i].getNombreCompleto() 
         <<setw(20)<<padron[i].getEstado()<<"\033[0m"<<endl;
      }
   }
   //no añadir nada
   pausar();
}

void mostrarHistorialServ(vector<Servicio>& historial){
   limpiarPantalla();
   titulo("HISTORIAL DE SERVICIOS", 1);
   cout<<endl;
   if (historial.empty()){
      cout<<"\033[33m[ALERTA] No hay servicios registrados en el historial.\033[0m"<<endl;
   }
   else{
      sort(historial.begin(), historial.end(), [](Servicio &a, Servicio &b){
         return a.getID()<b.getID();
      });
      cout<<"\033[1;36m"<<left<<setw(5)<<"ID"<<setw(11)<<"COD-UNID"<<setw(9)<<"COD-OP"<<setw(13)<<"N° PAS."<<setw(20)<<"DESTINO"<<setw(18)<<"ESTADO"<<"\033[0m"<<endl;
      cout<<"\033[36m"<<llenar(73, "-")<<"\033[0m\n";
      for (size_t i=0; i<historial.size(); i++){
         // Colores basicos ASCII  (Verde: "Completado", Rojo: "Activo", Amarillo: "Pendiente")
         if(historial[i].getEstado()=="Completado") cout<<"\033[32m";
         else if(historial[i].getEstado()=="Activo") cout<<"\033[31m";
         else cout<<"\033[33m";
         //Información coloreada
         cout<<left
         <<setw(5)<<historial[i].getID() 
         <<setw(11)<<historial[i].getCodigoUnid() 
         <<setw(9)<<historial[i].getCodigoOp() 
         <<setw(12)<<historial[i].getNumPasajeros() 
         <<setw(20)<<historial[i].getDestino() 
         <<setw(18)<<historial[i].getEstado()<<"\033[0m"<<endl;
      }
   }
   //no aañadir nada
   pausar();
}

void programarNuevoServ(vector<Unidad>& padronUnid, vector<Operador>& padronOp, vector<Servicio>& historial){
   limpiarPantalla();
   int pasajeros{};
   string destino{};
   titulo("PROGRAMAR NUEVO SERVICIO", 2);
   cout<<"\033[33m(Puede escribir 'C' en cualquier momento para cancelar la programacion)\033[0m\n\n";

   if (!leerTexto("DESTINO: ", destino)){
      cout<<"\n\033[33m[CANCELADO] Programacion de servicio cancelada. No se guardaron cambios.\033[0m\n";
      //no añadir nada
      pausar();
      return;
   }
   if (!leerEntero("N° PASAJEROS: ", pasajeros, 1, 999)){
      cout<<"\n\033[33m[CANCELADO] Programacion de servicio cancelada. No se guardaron cambios.\033[0m\n";
      //no añadir nada
      pausar();
      return;
   }

   //Validar si hay operadores disponibles primero
   vector<int> indexOp;
   for (size_t i=0; i<padronOp.size(); i++){
      if (padronOp[i].getEstado()=="Disponible"){
         indexOp.push_back((int)i);
      }
   }
   if (indexOp.empty()){
      cout<<"\n\033[31m[ERROR] No hay operadores DISPONIBLES en este momento. Intente nuevamente mas tarde.\033[0m\n";
      //no añadir nada
      pausar();
      return; // Corta la ejecución de la función aquí
   }

   //Validar si hay unidades con capacidad suficiente
   vector<int> indexUnid;
   for (size_t i=0; i<padronUnid.size(); i++){
      if (padronUnid[i].getEstado()=="Disponible" && padronUnid[i].getCapacidad()>=pasajeros){
         indexUnid.push_back((int)i);
      }
   }
   if (indexUnid.empty()){
      cout<<"\n\033[33m[ALERTA] No hay unidades disponibles con capacidad para "<<pasajeros<<" pasajeros.\033[0m\n";
      cout<<"Considere fraccionar el servicio asignando en multiples unidades mas pequeñas.\n";
      //no añadir nada
      pausar();
      return; 
   }

   //Mostrar y seleccionar Unidad
   cout<<endl; titulo("UNIDADES DISPONIBLES", 3); cout<<endl;
   cout<<"\033[1;36m"<<left<<setw(10)<<"CODIGO"<<setw(15)<<"PLACA"<<setw(11)<<"CAPACIDAD"<<"\033[0m"<<endl;
   cout<<"\033[36m"<<llenar(36, "-")<<"\033[0m\n";
   for (size_t i=0; i<indexUnid.size(); i++){
      cout<<left<<setw(10)<<padronUnid[indexUnid[i]].getCodigo()
                <<setw(15)<<padronUnid[indexUnid[i]].getPlaca()
                <<setw(11)<<padronUnid[indexUnid[i]].getCapacidad()<<endl;
   }
   int codUnidE{}, indexUnidE=-1;
   bool validUnid=false;
   do {
      if (!leerEntero("\nCODIGO de la UNIDAD por asignar: ", codUnidE)){
         cout<<"\n\033[33m[CANCELADO] Programacion de servicio cancelada. No se guardaron cambios.\033[0m\n";
         //no añadir nada
         pausar();
         return;
      }
      for (size_t i=0; i<indexUnid.size(); i++){
         if (padronUnid[indexUnid[i]].getCodigo()==codUnidE){
            indexUnidE=indexUnid[i];
            validUnid=true;
            break;
         }
      }
      if (!validUnid) cout<<"\033[31m[!] Codigo invalido o unidad no apta. (Escriba 'C' para cancelar)\033[0m\n";
   } while (!validUnid);

   //Mostrar y seleccionar Operador
   cout<<endl; titulo("OPERADORES DISPONIBLES", 3); cout<<endl;
   cout<<"\033[1;36m"<<left<<setw(10)<<"CODIGO"<<setw(12)<<"DNI"<<setw(40)<<"NOMBRE COMPLETO"<<"\033[0m"<<endl;
   cout<<"\033[36m"<<llenar(62, "-")<<"\033[0m\n";
   for (size_t i=0; i<indexOp.size(); i++){
      cout<<left<<setw(10)<<padronOp[indexOp[i]].getCodigo()
                <<setw(12)<<padronOp[indexOp[i]].getDNI()
                <<setw(40)<<padronOp[indexOp[i]].getNombreCompleto()<<endl;
   }
   int codOpE{}, indexOpE=-1;
   bool validOp=false;
   do {
      if (!leerEntero("\nCODIGO del OPERADOR por asignar: ", codOpE)){
         cout<<"\n\033[33m[CANCELADO] Programacion de servicio cancelada. No se guardaron cambios.\033[0m\n";
         //no añadir nada
         pausar();
         return;
      }
      for (size_t i=0; i<indexOp.size(); i++) {
         if (padronOp[indexOp[i]].getCodigo()==codOpE) {
            indexOpE=indexOp[i];
            validOp=true;
            break;
         }
      }
      if (!validOp) cout<<"\033[31m[!] Codigo invalido u operador no disponible. (Escriba 'C' para cancelar)\033[0m\n";
   } while (!validOp);

   //Creación del servicio y actualización de estados
   int id=(int)(historial.size())+1; 
   historial.push_back(Servicio(id, codUnidE, codOpE, pasajeros, destino, "Pendiente"));
   padronUnid[indexUnidE].setEstado("Asignado");
   padronOp[indexOpE].setEstado("Asignado");
   cout<<"\n\033[32m[EXITO] Servicio "<<id<<" programado correctamente.\033[0m\n";
   cout<<"Unidad asignada: " <<codUnidE<< " | Operador asignado: "<<codOpE<<endl;
   //no añadir nada
   pausar();
}

void procesarSalida(vector<Servicio>& historial){
   limpiarPantalla();
   titulo("PROCESAR SALIDA DE SERVICIO", 2);

   //Servicios pendientes
   vector<int> indexPend;
   for (size_t i=0; i<historial.size(); i++){
      if (historial[i].getEstado()=="Pendiente"){
         indexPend.push_back((int)i);
      }
   }
   if (indexPend.empty()){
      cout<<"\n\033[33m[ALERTA] No hay servicios PENDIENTES por procesar en este momento.\033[0m\n";
      //no añadir nada
      pausar();
      return; 
   }

   //Mostrar lista de servicios pendientes
   cout<<endl; titulo("SERVICIOS PENDIENTES DE SALIDA", 3); cout<<endl;
   cout<<"\033[1;36m"<<left<<setw(5)<<"ID"<<setw(11)<<"COD-UNID"<<setw(9)<<"COD-OP"<<setw(13)<<"N° PAS."<<setw(20)<<"DESTINO"<<"\033[0m"<<endl;
   cout<<"\033[36m"<<llenar(58, "-")<<"\033[0m\n";
   for (size_t i=0; i<indexPend.size(); i++){
      cout<<left<<setw(5)<<historial[indexPend[i]].getID()
                <<setw(11)<<historial[indexPend[i]].getCodigoUnid()
                <<setw(9)<<historial[indexPend[i]].getCodigoOp()
                <<setw(12)<<historial[indexPend[i]].getNumPasajeros()
                <<setw(20)<<historial[indexPend[i]].getDestino()<<endl;
   }

   //Selección y validación del usuario
   cout<<"\n\033[33m(Puede escribir 'C' para cancelar el proceso)\033[0m\n";
   int idServSalida{}, indexServE=-1;
   bool validID=false;
   do {
      if (!leerEntero("\nID del servicio ACTIVO: ", idServSalida)){
         cout<<"\n\033[33m[CANCELADO] Proceso de salida cancelado. No se guardaron cambios.\033[0m\n";
         //no añadir nada
         pausar();
         return;
      }
      for (size_t i=0; i<indexPend.size(); i++){
         if (historial[indexPend[i]].getID()==idServSalida){
            indexServE=indexPend[i];
            validID=true;
            break;
         }
      }
      if (!validID) cout<<"\033[31m[!] ID invalido o no esta en estado PENDIENTE. (Escriba 'C' para cancelar)\033[0m\n";
   } while (!validID);

   historial[indexServE].setEstado("Activo");
   cout<<"\n\033[32m[EXITO] El servicio "<<idServSalida<<" ha iniciado su ruta.\033[0m\n";
   //no añadir nada
   pausar();
}

void procesarArribo(vector<Unidad>& padronUnid, vector<Operador>& padronOp, vector<Servicio>& historial){
   limpiarPantalla();
   titulo("PROCESAR ARRIBO DE SERVICIO", 2);

   //Servicios activos
   vector<int> indexActivos;
   for (size_t i=0; i<historial.size(); i++){
      if (historial[i].getEstado()=="Activo"){ // Buscamos el estado que definiste en la salida
         indexActivos.push_back((int)i);
      }
   }
   if (indexActivos.empty()){
      cout<<"\n\033[33m[ALERTA] No hay servicios ACTIVOS en ruta en este momento.\033[0m\n";
      //no añadir nada
      pausar();
      return; 
   }

   //Mostrar lista de servicios activos
   cout<<endl; titulo("SERVICIOS ACTIVOS (EN RUTA)", 3); cout<<endl;
   cout<<"\033[1;36m"<<left<<setw(5)<<"ID"<<setw(11)<<"COD-UNID"<<setw(9)<<"COD-OP"<<setw(13)<<"N° PAS."<<setw(20)<<"DESTINO"<<"\033[0m"<<endl;
   cout<<"\033[36m"<<llenar(58, "-")<<"\033[0m\n";
   for (size_t i=0; i<indexActivos.size(); i++){
      cout<<left<<setw(5)<<historial[indexActivos[i]].getID()
                <<setw(11)<<historial[indexActivos[i]].getCodigoUnid()
                <<setw(9)<<historial[indexActivos[i]].getCodigoOp()
                <<setw(12)<<historial[indexActivos[i]].getNumPasajeros()
                <<setw(20)<<historial[indexActivos[i]].getDestino()<<endl;
   }

   //Selección y validación del usuario
   cout<<"\n\033[33m(Puede escribir 'C' para cancelar el proceso)\033[0m\n";
   int idServArribo{}, indexServE=-1;
   bool validID=false;
   do {
      if (!leerEntero("\nID del servicio COMPLETADO: ", idServArribo)){
         cout<<"\n\033[33m[CANCELADO] Proceso de arribo cancelado. No se guardaron cambios.\033[0m\n";
         //no añadir nada
         pausar();
         return;
      }
      for (size_t i=0; i<indexActivos.size(); i++){
         if (historial[indexActivos[i]].getID()==idServArribo){
            indexServE=indexActivos[i];
            validID=true;
            break;
         }
      }
      if (!validID) cout<<"\033[31m[!] ID invalido o no esta en estado ACTIVO. (Escriba 'C' para cancelar)\033[0m\n";
   } while (!validID);

   historial[indexServE].setEstado("Completado");
   int codUnidAsig=historial[indexServE].getCodigoUnid();
   for (size_t i=0; i<padronUnid.size(); i++){
      if (padronUnid[i].getCodigo()==codUnidAsig){
         padronUnid[i].setEstado("En reposo");
         break;
      }
   }
   int codOpAsig=historial[indexServE].getCodigoOp();
   for (size_t i=0; i<padronOp.size(); i++){
      if (padronOp[i].getCodigo()==codOpAsig){
         padronOp[i].setEstado("En reposo");
         break;
      }
   }

   cout<<"\n\033[32m[EXITO] El servicio "<<idServArribo<<" se ha completado.\033[0m\n";
   cout<<"La Unidad "<<codUnidAsig<<" y el Operador "<<codOpAsig<<" han pasado a estado EN REPOSO.\n";
   //no añadir nada
   pausar();
}

// Cantidad minima de turnos (ciclos de menu) que una unidad u operador debe
// esperar en estado "En reposo" antes de poder volver a "Disponible". Como
// el programa no tiene reloj real ni corre en segundo plano, el tiempo se
// simula pidiendole al usuario que confirme cuantos turnos ha esperado, en
// vez de llevar un contador persistente por cada unidad/operador.
const int TURNOS_MINIMOS_DESCANSO=2;

void completarDescansoUnidad(vector<Unidad>& padron){
   limpiarPantalla();
   titulo("COMPLETAR DESCANSO DE UNIDAD", 3);
   cout<<endl;

   //Unidades en reposo
   vector<int> indexReposo;
   for (size_t i=0; i<padron.size(); i++){
      if (padron[i].getEstado()=="En reposo"){
         indexReposo.push_back((int)i);
      }
   }
   if (indexReposo.empty()){
      cout<<"\033[33m[ALERTA] No hay unidades en estado EN REPOSO en este momento.\033[0m\n";
      //no añadir nada
      pausar();
      return;
   }

   //Mostrar lista de unidades en reposo
   titulo("UNIDADES EN REPOSO", 4); cout<<endl;
   cout<<"\033[1;36m"<<left<<setw(10)<<"CODIGO"<<setw(15)<<"PLACA"<<setw(11)<<"CAPACIDAD"<<"\033[0m"<<endl;
   cout<<"\033[36m"<<llenar(36, "-")<<"\033[0m\n";
   for (size_t i=0; i<indexReposo.size(); i++){
      cout<<left<<setw(10)<<padron[indexReposo[i]].getCodigo()
                <<setw(15)<<padron[indexReposo[i]].getPlaca()
                <<setw(11)<<padron[indexReposo[i]].getCapacidad()<<endl;
   }

   //Selección y validación del usuario
   cout<<"\n\033[33m(Puede escribir 'C' para cancelar el proceso)\033[0m\n";
   int codUnidE{}, indexUnidE=-1;
   bool validCod=false;
   do {
      if (!leerEntero("\nCODIGO de la UNIDAD en reposo: ", codUnidE)){
         cout<<"\n\033[33m[CANCELADO] Proceso cancelado. No se guardaron cambios.\033[0m\n";
         //no añadir nada
         pausar();
         return;
      }
      for (size_t i=0; i<indexReposo.size(); i++){
         if (padron[indexReposo[i]].getCodigo()==codUnidE){
            indexUnidE=indexReposo[i];
            validCod=true;
            break;
         }
      }
      if (!validCod) cout<<"\033[31m[!] Codigo invalido o la unidad no esta en reposo. (Escriba 'C' para cancelar)\033[0m\n";
   } while (!validCod);

   //Confirmar turnos de descanso esperados antes de habilitar el cambio de estado
   int turnos{};
   bool cumpleDescanso=false;
   do {
      cout<<"\nEsta unidad requiere haber esperado al menos "<<TURNOS_MINIMOS_DESCANSO<<" turno(s) (ciclos de menu) en reposo.\n";
      if (!leerEntero("¿Cuantos turnos ha esperado en reposo?: ", turnos, 0, 999)){
         cout<<"\n\033[33m[CANCELADO] Proceso cancelado. No se guardaron cambios.\033[0m\n";
         //no añadir nada
         pausar();
         return;
      }
      if (turnos<TURNOS_MINIMOS_DESCANSO){
         cout<<"\033[31m[!] Aun no cumple el descanso minimo ("<<turnos<<"/"<<TURNOS_MINIMOS_DESCANSO<<" turnos). (Escriba 'C' para cancelar)\033[0m\n";
      }
      else{
         cumpleDescanso=true;
      }
   } while (!cumpleDescanso);

   padron[indexUnidE].setEstado("Disponible");
   cout<<"\n\033[32m[EXITO] La unidad "<<codUnidE<<" ha completado su descanso y vuelve a estar DISPONIBLE.\033[0m\n";
   //no añadir nada
   pausar();
}

void completarDescansoOperador(vector<Operador>& padron){
   limpiarPantalla();
   titulo("COMPLETAR DESCANSO DE OPERADOR", 3);
   cout<<endl;

   //Operadores en reposo
   vector<int> indexReposo;
   for (size_t i=0; i<padron.size(); i++){
      if (padron[i].getEstado()=="En reposo"){
         indexReposo.push_back((int)i);
      }
   }
   if (indexReposo.empty()){
      cout<<"\033[33m[ALERTA] No hay operadores en estado EN REPOSO en este momento.\033[0m\n";
      pausar();
      return;
   }

   //Mostrar lista de operadores en reposo
   titulo("OPERADORES EN REPOSO", 4); cout<<endl;
   cout<<"\033[1;36m"<<left<<setw(10)<<"CODIGO"<<setw(12)<<"DNI"<<setw(40)<<"NOMBRE COMPLETO"<<"\033[0m"<<endl;
   cout<<"\033[36m"<<llenar(62, "-")<<"\033[0m\n";
   for (size_t i=0; i<indexReposo.size(); i++){
      cout<<left<<setw(10)<<padron[indexReposo[i]].getCodigo()
                <<setw(12)<<padron[indexReposo[i]].getDNI()
                <<setw(40)<<padron[indexReposo[i]].getNombreCompleto()<<endl;
   }

   //Selección y validación del usuario
   cout<<"\n\033[33m(Puede escribir 'C' para cancelar el proceso)\033[0m\n";
   int codOpE{}, indexOpE=-1;
   bool validCod=false;
   do {
      if (!leerEntero("\nCODIGO del OPERADOR en reposo: ", codOpE)){
         cout<<"\n\033[33m[CANCELADO] Proceso cancelado. No se guardaron cambios.\033[0m\n";
         pausar();
         return;
      }
      for (size_t i=0; i<indexReposo.size(); i++){
         if (padron[indexReposo[i]].getCodigo()==codOpE){
            indexOpE=indexReposo[i];
            validCod=true;
            break;
         }
      }
      if (!validCod) cout<<"\033[31m[!] Codigo invalido o el operador no esta en reposo. (Escriba 'C' para cancelar)\033[0m\n";
   } while (!validCod);

   //Confirmar turnos de descanso esperados antes de habilitar el cambio de estado
   int turnos{};
   bool cumpleDescanso=false;
   do {
      cout<<"\nEste operador requiere haber esperado al menos "<<TURNOS_MINIMOS_DESCANSO<<" turno(s) (ciclos de menu) en reposo.\n";
      if (!leerEntero("¿Cuantos turnos ha esperado en reposo?: ", turnos, 0, 999)){
         cout<<"\n\033[33m[CANCELADO] Proceso cancelado. No se guardaron cambios.\033[0m\n";
         pausar();
         return;
      }
      if (turnos<TURNOS_MINIMOS_DESCANSO){
         cout<<"\033[31m[!] Aun no cumple el descanso minimo ("<<turnos<<"/"<<TURNOS_MINIMOS_DESCANSO<<" turnos). (Escriba 'C' para cancelar)\033[0m\n";
      }
      else{
         cumpleDescanso=true;
      }
   } while (!cumpleDescanso);

   padron[indexOpE].setEstado("Disponible");
   cout<<"\n\033[32m[EXITO] El operador "<<codOpE<<" ha completado su descanso y vuelve a estar DISPONIBLE.\033[0m\n";
   pausar();
}

// Submenu de la opcion [4] del Modulo de Operaciones: permite elegir si se
// va a completar el descanso de una Unidad o de un Operador.
void completarDescanso(vector<Unidad>& padronUnid, vector<Operador>& padronOp){
   string teclado{};
   char opc{};
   do {
      menuFinDescansos();
      getline(cin, teclado);
      opc='X';
      if (teclado.size()==1) opc=teclado[0];

      switch (opc){
         case '1': completarDescansoUnidad(padronUnid); break;
         case '2': completarDescansoOperador(padronOp); break;
         case '0': break; // Cancelar sin hacer nada
         default:
            cout<<"\n\033[31m[ERROR] Opcion no valida.\033[0m\n";
            pausar();
            break;
      }
   } while(opc!='0');
}
   
void registrarUnidad(vector<Unidad>& padron){
   limpiarPantalla();
   string placa{};
   int cod{};
   int capacidad{};

   titulo("REGISTRO DE NUEVA UNIDAD", 2);
   cout<<"\n\033[33m(Puede escribir 'C' en cualquier momento para cancelar el registro)\033[0m\n\n";

   if (!leerPlaca("N° DE MATRICULA (ej. ABC-123): ", placa)){
      cout<<"\n\033[33m[CANCELADO] Registro de unidad cancelado. No se guardaron cambios.\033[0m\n";
      //no añadir nada
      pausar();
      return;
   }

   titulo("TIPOS DE UNIDADES", 3);
   cout<<"► (1NN) Unidad pequeña. CAPACIDAD: 8 asientos.\n"
       <<"► (2NN) Unidad grande. CAPACIDAD: 45 asientos.\n"
       <<"► (3NN) Unidad grande premium. CAPACIDAD: 39 asientos.\n";

   bool validCode=false;
   do {
      if (!leerEntero("\nCÓDIGO de la UNIDAD: ", cod)){
         cout<<"\n\033[33m[CANCELADO] Registro de unidad cancelado. No se guardaron cambios.\033[0m\n";
         //no añadir nada
         pausar();
         return;
      }
      validCode=false;
      if (cod>=100 && cod<200){
         capacidad=8;
         validCode=true;
      }
      else if (cod>=200 && cod<300) {
         capacidad=45;
         validCode=true;
      }
      else if (cod>=300 && cod<400) {
         capacidad=39;
         validCode=true;
      }
      else{
         cout<<"\033[31m[ERROR] Codigo de unidad no valido. Debe estar en el rango 100-399. (Escriba 'C' para cancelar)\033[0m\n";
         continue;
      }
      // Validar que el codigo no este ya asignado a otra unidad del padron
      for (size_t i=0; i<padron.size(); i++){
         if (padron[i].getCodigo()==cod){
            cout<<"\033[31m[ERROR] El codigo "<<cod<<" ya esta registrado en el padron. (Escriba 'C' para cancelar)\033[0m\n";
            validCode=false;
            break;
         }
      }
   } while (!validCode);

   padron.push_back(Unidad(placa, cod, capacidad, "Disponible"));
   cout<<"\n\033[32m[EXITO] Unidad registrada en memoria temporal.\033[0m"<<endl;
   pausar();
}

void registrarOperador(vector<Operador>& padron){
   limpiarPantalla();
   int cod{};
   int dni{};
   string nombres{};
   string apellidos{};

   titulo("REGISTRO DE NUEVO OPERADOR", 2);
   cout<<"\n\033[33m(Puede escribir 'C' en cualquier momento para cancelar el registro)\033[0m\n\n";

   bool validCode=false;
   do {
      if (!leerEntero("CODIGO DE OPERADOR (ej. 9NN): ", cod)){
         cout<<"\n\033[33m[CANCELADO] Registro de operador cancelado. No se guardaron cambios.\033[0m\n";
         //no añadir nada
         pausar();
         return;
      }
      validCode=true;
      for (size_t i=0; i<padron.size(); i++){
         if (padron[i].getCodigo()==cod){
            cout<<"\033[31m[ERROR] El codigo "<<cod<<" ya esta registrado en el padron. (Escriba 'C' para cancelar)\033[0m\n";
            validCode=false;
            break;
         }
      }
   } while (!validCode);

   if (!leerDNI("DNI / C.E.: ", dni)){
      cout<<"\n\033[33m[CANCELADO] Registro de operador cancelado. No se guardaron cambios.\033[0m\n";
      //no añadir nada
      pausar();
      return;
   }

   titulo("NOMBRE COMPLETO", 3);
   if (!leerTexto("NOMBRES: ", nombres)){
      cout<<"\n\033[33m[CANCELADO] Registro de operador cancelado. No se guardaron cambios.\033[0m\n";
      //no añadir nada
      pausar();
      return;
   }
   if (!leerTexto("APELLIDOS: ", apellidos)){
      cout<<"\n\033[33m[CANCELADO] Registro de operador cancelado. No se guardaron cambios.\033[0m\n";
      //no añadir nada
      pausar();
      return;
   }

   padron.push_back(Operador(cod, dni, nombres, apellidos, "Disponible"));
   cout<<"\n\033[32m[EXITO] Operador registrado en memoria temporal.\033[0m"<<endl;
   //no añadir nada
   pausar();
}

// === MENU PRINCIPAL ===
int main()
{
   SetConsoleOutputCP(CP_UTF8);
   SetConsoleCP(CP_UTF8);
   vector<Unidad> padronUnid;
   vector<Operador> padronOp;
   vector<Servicio> historialServ;
   
   titulo("CARGA INICIAL", 0);
   cargarUNIDADES(padronUnid);
   cargarOPERADORES(padronOp);
   cargarSERVICIOS(historialServ);
   //no añadir nada
   pausar();

   string teclado{}; 
   char opc{};

   // Bucle menú principal
   do {
      menuPrincipal();
      getline(cin, teclado);
      opc='X';
      if (teclado.size()==1) opc=teclado[0]; // Solo toma el caracter si escribieron exactamente 1 dígito

      switch (opc) {
         case '1':{
            string tecladoPad{};
            char opcPad{};
            do {
               menuPadron();
               getline(cin, tecladoPad);
               opcPad='X';
               if (tecladoPad.size()==1) opcPad=tecladoPad[0];

               switch(opcPad){
                  case '1': mostrarPadronUnid(padronUnid); break;
                  case '2': mostrarPadronOp(padronOp); break;
                  case '0': break; // Sale del sub-menu sin hacer nada
                  default:
                     cout<<"\n\033[31m[ERROR] Opcion no valida. Intente de nuevo...\033[0m\n";
                     pausar();
                     break;
               }
            } while(opcPad!='0');
            break;
         } 
         case '2':{
            mostrarHistorialServ(historialServ);
            break;
         }
         case '3':{
            string tecladoOps{};
            char opcOps{};
            do {
               menuOperaciones();
               getline(cin, tecladoOps);
               opcOps='X';
               if (tecladoOps.size()==1) opcOps=tecladoOps[0];

               switch(opcOps){
                  case '1': programarNuevoServ(padronUnid, padronOp, historialServ); break;
                  case '2': procesarSalida(historialServ); break;
                  case '3': procesarArribo(padronUnid, padronOp, historialServ); break;
                  case '4': completarDescanso(padronUnid, padronOp); break;
                  case '0': break; // Sale del sub-menú sin hacer nada
                  default: 
                     cout<<"\n\033[31m[ERROR] Opcion no valida. Intente de nuevo...\033[0m\n"; 
                     pausar(); 
                     break;
               }
            } while(opcOps!='0');
            break;
         }
         case '4':{
            string tecladoReg{};
            char opcReg{};
            do {
               menuRegistros();
               getline(cin, tecladoReg);
               opcReg='X';
               if (tecladoReg.size()==1) opcReg=tecladoReg[0];

               switch(opcReg){
                  case '1': registrarUnidad(padronUnid); break;
                  case '2': registrarOperador(padronOp); break;
                  case '0': break; // Sale del sub-menu sin hacer nada
                  default: 
                     cout<<"\n\033[31m[ERROR] Opcion no valida. Intente de nuevo...\033[0m\n"; 
                     pausar(); 
                     break;
               }
            } while(opcReg!='0');
            break;
         }
         case '0':{
            cout<<"\nIniciando rutina de apagado...\n";
            guardarUNIDADES(padronUnid);
            guardarOPERADORES(padronOp);
            guardarSERVICIOS(historialServ);
            Sleep(250); // Pausa dramática
            break;
         }
         default:{
            cout<<"\n\033[31m[ERROR] Opcion no valida. Intente de nuevo...\033[0m\n";
            pausar();
            break;
         }
      }
   } while(opc!='0');

   cout<<"\nFIN DEL PROGRAMA\n";
   return 0;
}