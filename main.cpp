#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <windows.h>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <climits>

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
   void setPlaca(string newPlaca) {placa=newPlaca;}
   void setCodigo(int newCod) {cod=newCod;}
   void setCapacidad(int newCapacidad) {capacidad=newCapacidad;}
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
   void setDNI(int newDNI) {dni=newDNI;}
   void setNombres(string newNombres) {nombres=newNombres;}
   void setApellidos(string newApellidos) {apellidos=newApellidos;}
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
   void setCodigoUnid(int newCodUnid) {codUnid=newCodUnid;}
   void setCodigoOp(int newCodOp) {codOp=newCodOp;}
   void setDestino(string newDestino) {destino=newDestino;}
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

int compensacionUTF8(const string &texto){
	int compensacion{};
	for (size_t i=0; i<texto.size(); i++){
		unsigned char c=(unsigned char)texto[i];
		if (c>=0xC0 && c<=0xDF && i+1<texto.size()){ // inicio de secuencia UTF-8 de 2 bytes
			compensacion++;
			i++; // saltar el byte de continuacion, ya contabilizado
		}
	}
	return compensacion;
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
   cout<<"├╴[1] PADRÓN DE UNIDADES\n";
   cout<<"├╴[2] PADRÓN DE OPERADORES\n";
   cout<<"└╴[0] REGRESAR AL MENÚ PRINCIPAL\n";
   cout<<"\n►► Ingresar opción -→ ";
}

void menuOperaciones(){
   limpiarPantalla();
   titulo("MÓDULO DE OPERACIONES", 1);
   cout<<"├╴[1] PROGRAMAR NUEVO SERVICIO\n";
   cout<<"├╴[2] PROCESAR SALIDA DE UNIDAD\n";
   cout<<"├╴[3] PROCESAR ARRIBO DE UNIDAD\n";
   cout<<"├╴[4] MARCAR FIN DE DESCANSO\n";
   cout<<"└╴[0] REGRESAR AL MENÚ PRINCIPAL\n";
   cout<<"\n►► Ingresar opción -→ ";
}

void menuRegistros(){
   limpiarPantalla();
   titulo("MÓDULO DE REGISTROS", 1);
   cout<<"├╴[1] REGISTRAR NUEVA UNIDAD\n";
   cout<<"├╴[2] REGISTRAR NUEVO OPERADOR\n";
   cout<<"├╴[3] MODIFICAR DATOS\n";
   cout<<"├╴[4] ELIMINAR UN REGISTRO\n";
   cout<<"└╴[0] REGRESAR AL MENÚ PRINCIPAL\n";
   cout<<"\n►► Ingresar opción -→ ";
}

void menuModificar(){
   limpiarPantalla();
   titulo("MODIFICAR DATOS", 2);
   cout<<"├╴[1] UNIDAD\n";
   cout<<"├╴[2] OPERADOR\n";
   cout<<"├╴[3] SERVICIO\n";
   cout<<"└╴[0] REGRESAR AL MENÚ DE REGISTROS\n";
   cout<<"\n►► Ingresar opción -→ ";
}

void menuEliminar(){
   limpiarPantalla();
   titulo("ELIMINAR UN REGISTRO", 2);
   cout<<"├╴[1] UNIDAD\n";
   cout<<"├╴[2] OPERADOR\n";
   cout<<"├╴[3] SERVICIO\n";
   cout<<"└╴[0] REGRESAR AL MENÚ DE REGISTROS\n";
   cout<<"\n►► Ingresar opción -→ ";
}

void menuFinDescansos(){
   limpiarPantalla();
   titulo("FIN DE DESCANSO", 2);
   cout<<"├╴[1] UNIDAD\n";
   cout<<"├╴[2] OPERADOR\n";
   cout<<"└╴[0] REGRESAR AL MENÚ DE OPERACIONES\n";
   cout<<"\n►► Ingresar opción -→ ";
}

void menuCamposUnid(Unidad &unidad){
   titulo("CAMPO A MODIFICAR", 3);
   cout<<"├╴[1] CÓDIGO      (actual: "<<unidad.getCodigo()<<")\n";
   cout<<"├╴[2] MATRÍCULA   (actual: "<<unidad.getPlaca()<<")\n";
   cout<<"└╴[0] REGRESAR AL MENÚ DE MODIFICAR DATOS\n";
   cout<<"\n►► Ingresar opción -→ ";
}

void menuCamposOp(Operador &op){
   titulo("CAMPO A MODIFICAR", 3);
   cout<<"├╴[1] DNI / C.E.  (actual: "<<op.getDNI()<<")\n";
   cout<<"├╴[2] NOMBRES     (actual: "<<op.getNombres()<<")\n";
   cout<<"├╴[3] APELLIDOS   (actual: "<<op.getApellidos()<<")\n";
   cout<<"└╴[0] REGRESAR AL MENÚ DE MODIFICAR DATOS\n";
   cout<<"\n►► Ingresar opción -→ ";
}

void menuCamposServ(Servicio &serv){
   titulo("CAMPO A MODIFICAR", 3);
   cout<<"├╴[1] UNIDAD ASIGNADA     (actual: UNIDAD "<<serv.getCodigoUnid()<<")\n";
   cout<<"├╴[2] OPERADOR ASIGNADO   (actual: OPERADOR "<<serv.getCodigoOp()<<")\n";
   cout<<"├╴[3] DESTINO             (actual: "<<serv.getDestino()<<")\n";
   cout<<"└╴[0] REGRESAR AL MENÚ DE MODIFICAR DATOS\n";
   cout<<"\n►► Ingresar opción -→ ";
}

void pausar(){
   cout<<"\n\033[2;37mPresione ENTER para continuar...\033[0m";
   //cin.ignore();
   cin.get();
}

bool esSoloDigitos(const string &texto, size_t desde=0){
   if (desde>=texto.size()) return false;
   return all_of(texto.begin()+desde, texto.end(), [](unsigned char c){
      return isdigit(c);
   });
}

bool esCancelacion(const string &entrada){
   string t=entrada;
   for (size_t i=0; i<t.size(); i++) t[i]=(char)toupper((unsigned char)t[i]);
   return (t=="Q" || t=="CANCELAR");
}

string capitalizarTexto(const string &texto){
   string resultado{};
   for (size_t i=0; i<texto.size(); i++){
      unsigned char c=(unsigned char)texto[i];
      // Caracteres UTF-8 de 2 bytes (tildes y diéresis): 0xC3 0x??
      if (c==0xC3 && i+1<texto.size()){
         unsigned char c2=(unsigned char)texto[i+1];
         switch (c2){
            case 0x81: case 0xA1: resultado+="\xC3\x81"; i++; continue; // Á á -> Á
            case 0x89: case 0xA9: resultado+="\xC3\x89"; i++; continue; // É é -> É
            case 0x8D: case 0xAD: resultado+="\xC3\x8D"; i++; continue; // Í í -> Í
            case 0x93: case 0xB3: resultado+="\xC3\x93"; i++; continue; // Ó ó -> Ó
            case 0x9A: case 0xBA: resultado+="\xC3\x9A"; i++; continue; // Ú ú -> Ú
            case 0x9C: case 0xBC: resultado+="\xC3\x9C"; i++; continue; // Ü ü -> Ü
            case 0x91: case 0xB1: resultado+="\xC3\x91"; i++; continue; // Ñ/ñ -> Ñ (se conserva)
            default: break; // Otro caracter UTF-8 no contemplado: se deja tal cual
         }
      }
      resultado+=(char)toupper(c);
   }
   return resultado;
}

bool confirmarAccion(const string &mensaje){
   string entrada{};
   while (true){
      cout<<mensaje<<" [S/N]: ";
      getline(cin, entrada);
      string t=capitalizarTexto(entrada);
      if (t=="S" || t=="SI" || t=="SÍ") return true;
      if (t=="N" || t=="NO") return false;
      cout<<"\033[31m[ERROR] Responda 'S' para confirmar o 'N' para cancelar.\033[0m\n";
   }
}

//garantizar el ingreso de algo o el intento de cancelación
bool leerTexto(const string &mensaje, string &variableDestino, bool permitirVacio=false){
   string entrada{};
   while (true){
      cout<<mensaje;
      getline(cin, entrada);
      if (esCancelacion(entrada)) return false;
      if (entrada.empty() && !permitirVacio){
         cout<<"\033[31m[ERROR] Campo obligatorio. (Escriba 'Q' o 'CANCELAR' si desea cancelar)\033[0m\n";
         continue;
      }
      variableDestino=capitalizarTexto(entrada);
      return true;
   }
}

//garantiza un número dentro del rango [minimo, maximo].
bool leerEntero(const string &mensaje, int &variableDestino, int minimo=INT_MIN, int maximo=INT_MAX){
   string entrada{};
   while (true){
      cout<<mensaje;
      getline(cin, entrada);
      if (esCancelacion(entrada)) return false;
      size_t desdeDigito=0;
      if (!entrada.empty() && (entrada[0]=='-' || entrada[0]=='+')) desdeDigito=1;
      if (!esSoloDigitos(entrada, desdeDigito)){
         cout<<"\033[31m[ERROR] Debe ingresar un numero valido. (Escriba 'Q' o 'CANCELAR' si desea cancelar)\033[0m\n";
         continue;
      }
      int numero{};
      try{
         numero=stoi(entrada);
      } catch(...){
         cout<<"\033[31m[ERROR] El numero ingresado es demasiado grande. (Escriba 'Q' o 'CANCELAR' si desea cancelar)\033[0m\n";
         continue;
      }
      if (numero<minimo || numero>maximo){
         cout<<"\033[31m[ERROR] El valor debe estar entre "<<minimo<<" y "<<maximo<<". (Escriba 'Q' o 'CANCELAR' si desea cancelar)\033[0m\n";
         continue;
      }
      variableDestino=numero;
      return true;
   }
}

//garantiza leer DNI/C.E.: solo digitos, entre 8 (DNI) y 12 (C.E.) caracteres
bool leerDNI(const string &mensaje, int &variableDestino){
   string entrada{};
   while (true){
      cout<<mensaje;
      getline(cin, entrada);
      if (esCancelacion(entrada)) return false;
      if (!esSoloDigitos(entrada) || entrada.size()<8 || entrada.size()>12){
         cout<<"\033[31m[ERROR] El DNI/C.E. debe tener entre 8 y 12 digitos numericos. (Escriba 'Q' o 'CANCELAR' si desea cancelar)\033[0m\n";
         continue;
      }
      try{
         variableDestino=stoi(entrada);
      } catch(...){
         cout<<"\033[31m[ERROR] El DNI/C.E. ingresado no es valido. (Escriba 'Q' o 'CANCELAR' si desea cancelar)\033[0m\n";
         continue;
      }
      return true;
   }
}

//garantiza el formato de placa específico: 3 letras + guion + 3 numeros (ej. ABC-123)
bool tieneFormatoPlaca(const string &placa){
   if (placa.size()!=7) return false;
   for (int i=0; i<3; i++) if (!isalpha((unsigned char)placa[i])) return false;
   if (placa[3]!='-') return false;
   for (int i=4; i<7; i++) if (!isdigit((unsigned char)placa[i])) return false;
   return true;
}

//garantiza que la placa se guarde con el formato correcto (ej. ABC-123)
bool leerPlaca(const string &mensaje, string &variableDestino){
   string entrada{};
   while (true){
      cout<<mensaje;
      getline(cin, entrada);
      if (esCancelacion(entrada)) return false;
      if (!tieneFormatoPlaca(entrada)){
         cout<<"\033[31m[ERROR] Formato de placa no valido. Use el formato ABC-123. (Escriba 'Q' o 'CANCELAR' si desea cancelar)\033[0m\n";
         continue;
      }
      variableDestino=capitalizarTexto(entrada);
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
void imprimirTablaUnid(vector<Unidad>& padron){
   if (padron.empty()){
      cout<<"\033[33m[ALERTA] No hay unidades registradas en el padron.\033[0m"<<endl;
      return;
   }
   sort(padron.begin(), padron.end(), [](Unidad &a, Unidad &b){
      return a.getCodigo()<b.getCodigo();
   });
   cout<<"\033[1;36m"<<left<<setw(10)<<"CÓDIGO"<<setw(10)<<"PLACA"<<setw(12)<<"CAPACIDAD"<<setw(11)<<"ESTADO"<<"\033[0m"<<endl;
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

// POR MOVER !!!!!
void mostrarPadronUnid(vector<Unidad>& padron){
   limpiarPantalla();
   titulo("PADRÓN DE UNIDADES", 2);
   cout<<endl;
   imprimirTablaUnid(padron);
   pausar();
}

void imprimirTablaOp(vector<Operador>& padron){
   if (padron.empty()){
      cout<<"\033[33m[ALERTA] No hay operadores registrados en el padron.\033[0m"<<endl;
      return;
   }
   sort(padron.begin(), padron.end(), [](Operador &a, Operador &b){
      return a.getCodigo()<b.getCodigo();
   });
   cout<<"\033[1;36m"<<left<<setw(10)<<"CÓDIGO"<<setw(12)<<"DNI"<<setw(38)<<"NOMBRE COMPLETO"<<setw(20)<<"ESTADO"<<"\033[0m"<<endl;
   cout<<"\033[36m"<<llenar(75, "-")<<"\033[0m\n";
   for (size_t i=0; i<padron.size(); i++){
      // Colores basicos ASCII  (Verde: "Disponible", Rojo: "Asignado", Amarillo: "En reposo")
      if(padron[i].getEstado()=="Disponible") cout<<"\033[32m";
      else if(padron[i].getEstado()=="Asignado") cout<<"\033[31m";
      else cout<<"\033[33m";
      //Información coloreada
      string nombreCompleto=padron[i].getNombreCompleto();
      int extras=compensacionUTF8(nombreCompleto);
      cout<<left
      <<setw(9)<<padron[i].getCodigo() 
      <<setw(12)<<padron[i].getDNI() 
      <<setw(38+extras)<<nombreCompleto 
      <<setw(20)<<padron[i].getEstado()<<"\033[0m"<<endl;
   }
}

// POR MOVER !!!!!
void mostrarPadronOp(vector<Operador>& padron){
   limpiarPantalla();
   titulo("PADRÓN DE OPERADORES", 2);
   cout<<endl;
   imprimirTablaOp(padron);
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
         string destino=historial[i].getDestino();
         int extras=compensacionUTF8(destino);
         cout<<left
         <<setw(5)<<historial[i].getID() 
         <<setw(11)<<historial[i].getCodigoUnid() 
         <<setw(9)<<historial[i].getCodigoOp() 
         <<setw(12)<<historial[i].getNumPasajeros() 
         <<setw(20+extras)<<destino 
         <<setw(18)<<historial[i].getEstado()<<"\033[0m"<<endl;
      }
   }
   pausar();
}

int seleccionarUnidDisponible(vector<Unidad>& padron, int capacidadMinima){
   vector<int> indexUnid;
   for (size_t i=0; i<padron.size(); i++){
      if (padron[i].getEstado()=="Disponible" && padron[i].getCapacidad()>=capacidadMinima){
         indexUnid.push_back((int)i);
      }
   }
   if (indexUnid.empty()){
      cout<<"\n\033[33m[ALERTA] No hay unidades disponibles con capacidad para "<<capacidadMinima<<" pasajeros.\033[0m\n";
      cout<<"Considere fraccionar el servicio asignando en multiples unidades mas pequeñas.\n";
      return -1;
   }

   cout<<endl; titulo("UNIDADES DISPONIBLES", 3); cout<<endl;
   cout<<"\033[1;36m"<<left<<setw(10)<<"CÓDIGO"<<setw(15)<<"PLACA"<<setw(11)<<"CAPACIDAD"<<"\033[0m"<<endl;
   cout<<"\033[36m"<<llenar(36, "-")<<"\033[0m\n";
   for (size_t i=0; i<indexUnid.size(); i++){
      cout<<left<<setw(9)<<padron[indexUnid[i]].getCodigo()
                <<setw(15)<<padron[indexUnid[i]].getPlaca()
                <<setw(11)<<padron[indexUnid[i]].getCapacidad()<<endl;
   }

   int codUnidE{}, indexUnidE=-1;
   bool validUnid=false;
   do {
      if (!leerEntero("\nCÓDIGO de la UNIDAD por asignar: ", codUnidE)) return -1;
      for (size_t i=0; i<indexUnid.size(); i++){
         if (padron[indexUnid[i]].getCodigo()==codUnidE){
            indexUnidE=indexUnid[i];
            validUnid=true;
            break;
         }
      }
      if (!validUnid) cout<<"\033[31m[!] Código inválido o unidad no apta. (Escriba 'Q' o 'CANCELAR' si desea cancelar)\033[0m\n";
   } while (!validUnid);

   return indexUnidE;
}

int seleccionarOpDisponible(vector<Operador>& padron){
   vector<int> indexOp;
   for (size_t i=0; i<padron.size(); i++){
      if (padron[i].getEstado()=="Disponible"){
         indexOp.push_back((int)i);
      }
   }
   if (indexOp.empty()){
      cout<<"\n\033[31m[ERROR] No hay operadores DISPONIBLES en este momento. Intente nuevamente mas tarde.\033[0m\n";
      return -1;
   }

   cout<<endl; titulo("OPERADORES DISPONIBLES", 3); cout<<endl;
   cout<<"\033[1;36m"<<left<<setw(10)<<"CÓDIGO"<<setw(12)<<"DNI"<<setw(38)<<"NOMBRE COMPLETO"<<"\033[0m"<<endl;
   cout<<"\033[36m"<<llenar(62, "-")<<"\033[0m\n";
   for (size_t i=0; i<indexOp.size(); i++){
      string nombreCompleto=padron[indexOp[i]].getNombreCompleto();
      int extras=compensacionUTF8(nombreCompleto);
      cout<<left<<setw(9)<<padron[indexOp[i]].getCodigo()
                <<setw(12)<<padron[indexOp[i]].getDNI()
                <<setw(38+extras)<<nombreCompleto<<endl;
   }

   int codOpE{}, indexOpE=-1;
   bool validOp=false;
   do {
      if (!leerEntero("\nCODIGO del OPERADOR por asignar: ", codOpE)) return -1;
      for (size_t i=0; i<indexOp.size(); i++){
         if (padron[indexOp[i]].getCodigo()==codOpE){
            indexOpE=indexOp[i];
            validOp=true;
            break;
         }
      }
      if (!validOp) cout<<"\033[31m[!] Codigo invalido u operador no disponible. (Escriba 'Q' o 'CANCELAR' si desea cancelar)\033[0m\n";
   } while (!validOp);

   return indexOpE;
}

void programarNuevoServ(vector<Unidad>& padronUnid, vector<Operador>& padronOp, vector<Servicio>& historial){
   limpiarPantalla();
   int pasajeros{};
   string destino{};
   titulo("PROGRAMAR NUEVO SERVICIO", 2);
   cout<<"\033[33m(Puede escribir 'Q' en cualquier momento para cancelar la programación)\033[0m\n\n";

   if (!leerTexto("DESTINO: ", destino)){
      cout<<"\n\033[33m[CANCELADO] Programación de servicio cancelada. No se guardaron cambios.\033[0m\n";
      pausar();
      return;
   }
   if (!leerEntero("N° PASAJEROS: ", pasajeros, 1, 270)){
      cout<<"\n\033[33m[CANCELADO] Programación de servicio cancelada. No se guardaron cambios.\033[0m\n";
      pausar();
      return;
   }

   //Mostrar y seleccionar Unidad
   int indexUnidE=seleccionarUnidDisponible(padronUnid, pasajeros);
   if (indexUnidE==-1){
      cout<<"\n\033[33m[CANCELADO] Programación de servicio cancelada. No se guardaron cambios.\033[0m\n";
      pausar();
      return;
   }

   //Mostrar y seleccionar Operador
   int indexOpE=seleccionarOpDisponible(padronOp);
   if (indexOpE==-1){
      cout<<"\n\033[33m[CANCELADO] Programación de servicio cancelada. No se guardaron cambios.\033[0m\n";
      pausar();
      return;
   }

   //Creación del servicio y actualización de estados
   int codUnidE=padronUnid[indexUnidE].getCodigo();
   int codOpE=padronOp[indexOpE].getCodigo();
   int id=(int)(historial.size())+1; 
   historial.push_back(Servicio(id, codUnidE, codOpE, pasajeros, destino, "Pendiente"));
   padronUnid[indexUnidE].setEstado("Asignado");
   padronOp[indexOpE].setEstado("Asignado");
   cout<<"\n\033[32m[EXITO] Servicio "<<id<<" programado correctamente.\033[0m\n";
   cout<<"Unidad asignada: " <<codUnidE<< " | Operador asignado: "<<codOpE<<endl;
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
      pausar();
      return; 
   }

   //Mostrar lista de servicios pendientes
   cout<<endl; titulo("SERVICIOS PENDIENTES DE SALIDA", 3); cout<<endl;
   cout<<"\033[1;36m"<<left<<setw(5)<<"ID"<<setw(11)<<"COD-UNID"<<setw(9)<<"COD-OP"<<setw(13)<<"N° PAS."<<setw(20)<<"DESTINO"<<"\033[0m"<<endl;
   cout<<"\033[36m"<<llenar(58, "-")<<"\033[0m\n";
   for (size_t i=0; i<indexPend.size(); i++){
      string destino=historial[indexPend[i]].getDestino();
      int extras=compensacionUTF8(destino);
      cout<<left<<setw(5)<<historial[indexPend[i]].getID()
                <<setw(11)<<historial[indexPend[i]].getCodigoUnid()
                <<setw(9)<<historial[indexPend[i]].getCodigoOp()
                <<setw(12)<<historial[indexPend[i]].getNumPasajeros()
                <<setw(20+extras)<<destino<<endl;
   }

   //Selección y validación del usuario
   cout<<"\n\033[33m(Puede escribir 'Q' o 'CANCELAR' para cancelar el proceso)\033[0m\n";
   int idServSalida{}, indexServE=-1;
   bool validID=false;
   do {
      if (!leerEntero("\nID del servicio ACTIVO: ", idServSalida)){
         cout<<"\n\033[33m[CANCELADO] Proceso de salida cancelado. No se guardaron cambios.\033[0m\n";
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
      if (!validID) cout<<"\033[31m[!] ID invalido o no esta en estado PENDIENTE. (Escriba 'Q' o 'CANCELAR' si desea cancelar)\033[0m\n";
   } while (!validID);

   historial[indexServE].setEstado("Activo");
   cout<<"\n\033[32m[EXITO] El servicio "<<idServSalida<<" ha iniciado su ruta.\033[0m\n";
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
      pausar();
      return; 
   }

   //Mostrar lista de servicios activos
   cout<<endl; titulo("SERVICIOS ACTIVOS (EN RUTA)", 3); cout<<endl;
   cout<<"\033[1;36m"<<left<<setw(5)<<"ID"<<setw(11)<<"COD-UNID"<<setw(9)<<"COD-OP"<<setw(13)<<"N° PAS."<<setw(20)<<"DESTINO"<<"\033[0m"<<endl;
   cout<<"\033[36m"<<llenar(58, "-")<<"\033[0m\n";
   for (size_t i=0; i<indexActivos.size(); i++){
      string destino=historial[indexActivos[i]].getDestino();
      int extras=compensacionUTF8(destino);
      cout<<left<<setw(5)<<historial[indexActivos[i]].getID()
                <<setw(11)<<historial[indexActivos[i]].getCodigoUnid()
                <<setw(9)<<historial[indexActivos[i]].getCodigoOp()
                <<setw(12)<<historial[indexActivos[i]].getNumPasajeros()
                <<setw(20+extras)<<destino<<endl;
   }

   //Selección y validación del usuario
   cout<<"\n\033[33m(Puede escribir 'Q' o 'CANCELAR' para cancelar el proceso)\033[0m\n";
   int idServArribo{}, indexServE=-1;
   bool validID=false;
   do {
      if (!leerEntero("\nID del servicio COMPLETADO: ", idServArribo)){
         cout<<"\n\033[33m[CANCELADO] Proceso de arribo cancelado. No se guardaron cambios.\033[0m\n";
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
      if (!validID) cout<<"\033[31m[!] ID invalido o no esta en estado ACTIVO. (Escriba 'Q' o 'CANCELAR' si desea cancelar)\033[0m\n";
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
   pausar();
}

void completarDescansoUnid(vector<Unidad>& padron){
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
   cout<<"\n\033[33m(Puede escribir 'Q' o 'CANCELAR' para cancelar el proceso)\033[0m\n";
   int codUnidE{}, indexUnidE=-1;
   bool validCod=false;
   do {
      if (!leerEntero("\nCODIGO de la UNIDAD en reposo: ", codUnidE)){
         cout<<"\n\033[33m[CANCELADO] Proceso cancelado. No se guardaron cambios.\033[0m\n";
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
      if (!validCod) cout<<"\033[31m[!] Codigo invalido o la unidad no esta en reposo. (Escriba 'Q' o 'CANCELAR' si desea cancelar)\033[0m\n";
   } while (!validCod);

   //Cambio de estado directo: el usuario ya eligio explicitamente esta unidad
   //de la lista de "en reposo", por lo que no se le vuelve a preguntar nada mas.
   padron[indexUnidE].setEstado("Disponible");
   cout<<"\n\033[32m[EXITO] La unidad "<<codUnidE<<" ha completado su descanso y vuelve a estar DISPONIBLE.\033[0m\n";
   pausar();
}

void completarDescansoOp(vector<Operador>& padron){
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
      string nombreCompleto=padron[indexReposo[i]].getNombreCompleto();
      int extras=compensacionUTF8(nombreCompleto);
      cout<<left<<setw(10)<<padron[indexReposo[i]].getCodigo()
                <<setw(12)<<padron[indexReposo[i]].getDNI()
                <<setw(40+extras)<<nombreCompleto<<endl;
   }

   //Selección y validación del usuario
   cout<<"\n\033[33m(Puede escribir 'Q' o 'CANCELAR' para cancelar el proceso)\033[0m\n";
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
      if (!validCod) cout<<"\033[31m[!] Codigo invalido o el operador no esta en reposo. (Escriba 'Q' o 'CANCELAR' si desea cancelar)\033[0m\n";
   } while (!validCod);

   //Cambio de estado directo: el usuario ya eligio explicitamente este operador
   //de la lista de "en reposo", por lo que no se le vuelve a preguntar nada mas.
   padron[indexOpE].setEstado("Disponible");
   cout<<"\n\033[32m[EXITO] El operador "<<codOpE<<" ha completado su descanso y vuelve a estar DISPONIBLE.\033[0m\n";
   pausar();
}

// Submenu de la opcion [4] del Modulo de Operaciones: permite elegir si se
// va a completar el descanso de una Unidad o de un Operador.
// POR MOVER !!!!!!
void completarDescanso(vector<Unidad>& padronUnid, vector<Operador>& padronOp){
   string teclado{};
   char opc{};
   do {
      menuFinDescansos();
      getline(cin, teclado);
      opc='X';
      if (teclado.size()==1) opc=teclado[0];

      switch (opc){
         case '1': completarDescansoUnid(padronUnid); break;
         case '2': completarDescansoOp(padronOp); break;
         case '0': break; // Cancelar sin hacer nada
         default:
            cout<<"\n\033[31m[ERROR] Opcion no valida.\033[0m\n";
            pausar();
            break;
      }
   } while(opc!='0');
}
   
int categoriaUnid(int cod){
   if (cod>=100 && cod<200) return 1;
   if (cod>=200 && cod<300) return 2;
   if (cod>=300 && cod<400) return 3;
   return 0;
}

int capacidadPorCategoria(int categoria){
   switch (categoria){
      case 1: return 8;
      case 2: return 45;
      case 3: return 39;
      default: return 0;
   }
}

void registrarUnidad(vector<Unidad>& padron){
   limpiarPantalla();
   string placa{};
   int cod{};
   int capacidad{};

   titulo("REGISTRO DE NUEVA UNIDAD", 2);
   cout<<"\n\033[33m(Puede escribir 'Q' o 'CANCELAR' en cualquier momento para cancelar el registro)\033[0m\n\n";

   if (!leerPlaca("N° DE MATRICULA (ej. ABC-123): ", placa)){
      cout<<"\n\033[33m[CANCELADO] Registro de unidad cancelado. No se guardaron cambios.\033[0m\n";
      pausar();
      return;
   }

   titulo("TIPOS DE UNIDADES", 3);
   cout<<"► (1NN) Unidad pequeña         (CAPACIDAD:  8 asientos)\n"
       <<"► (2NN) Unidad grande          (CAPACIDAD: 45 asientos)\n"
       <<"► (3NN) Unidad grande premium  (CAPACIDAD: 39 asientos)\n";

   bool validCode=false;
   do {
      if (!leerEntero("\nCÓDIGO de la UNIDAD: ", cod)){
         cout<<"\n\033[33m[CANCELADO] Registro de unidad cancelado. No se guardaron cambios.\033[0m\n";
         pausar();
         return;
      }
      capacidad=capacidadPorCategoria(categoriaUnid(cod));
      validCode=(capacidad!=0);
      if (!validCode){
         cout<<"\033[31m[ERROR] Codigo de unidad no valido. Debe estar en el rango 100-399. (Escriba 'Q' o 'CANCELAR' si desea cancelar)\033[0m\n";
         continue;
      }
      // Validar que el codigo no este ya asignado a otra unidad del padron
      for (size_t i=0; i<padron.size(); i++){
         if (padron[i].getCodigo()==cod){
            cout<<"\033[31m[ERROR] El codigo "<<cod<<" ya esta registrado en el padrón. (Escriba 'Q' o 'CANCELAR' si desea cancelar)\033[0m\n";
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
   cout<<"\n\033[33m(Puede escribir 'Q' o 'CANCELAR' en cualquier momento para cancelar el registro)\033[0m\n\n";

   bool validCode=false;
   do {
      if (!leerEntero("CODIGO DE OPERADOR (ej. 9NN): ", cod)){
         cout<<"\n\033[33m[CANCELADO] Registro de operador cancelado. No se guardaron cambios.\033[0m\n";
         pausar();
         return;
      }
      validCode=true;
      for (size_t i=0; i<padron.size(); i++){
         if (padron[i].getCodigo()==cod){
            cout<<"\033[31m[ERROR] El codigo "<<cod<<" ya esta registrado en el padron. (Escriba 'Q' o 'CANCELAR' si desea cancelar)\033[0m\n";
            validCode=false;
            break;
         }
      }
   } while (!validCode);
   bool validDNI=false;
   do {
      if (!leerDNI("DNI / C.E.: ", dni)){
         cout<<"\n\033[33m[CANCELADO] Registro de operador cancelado. No se guardaron cambios.\033[0m\n";
         pausar();
         return;
      }
      validDNI=true;
      for (size_t i=0; i<padron.size(); i++){
         if (padron[i].getDNI()==dni){
            cout<<"\033[31m[ERROR] El DNI "<<dni<<" ya esta registrado en el padron. (Escriba 'Q' o 'CANCELAR' si desea cancelar)\033[0m\n";
            validDNI=false;
            break;
         }
      }
   } while (!validDNI);
   titulo("NOMBRE COMPLETO", 3);
   if (!leerTexto("NOMBRES: ", nombres)){
      cout<<"\n\033[33m[CANCELADO] Registro de operador cancelado. No se guardaron cambios.\033[0m\n";
      pausar();
      return;
   }
   if (!leerTexto("APELLIDOS: ", apellidos)){
      cout<<"\n\033[33m[CANCELADO] Registro de operador cancelado. No se guardaron cambios.\033[0m\n";
      pausar();
      return;
   }

   padron.push_back(Operador(cod, dni, nombres, apellidos, "Disponible"));
   cout<<"\n\033[32m[EXITO] Operador registrado en memoria temporal.\033[0m"<<endl;
   pausar();
}

void modificarCodigoUnid(vector<Unidad>& padron, int index){
   int codActual=padron[index].getCodigo();
   int categoriaActual=categoriaUnid(codActual);

   cout<<"\nCÓDIGO ACTUAL: "<<codActual<<"\n";
   cout<<"\n\033[33m[!] El CÓDIGO solo puede cambiar si la unidad pasa a otra CATEGORÍA (ej. de 3NN a 2NN).\033[0m\n";
   cout<<"\033[33m(Puede escribir 'Q' o 'CANCELAR' para cancelar el cambio)\033[0m\n";
   titulo("TIPOS DE UNIDADES", 3);
   cout<<"► (1NN) Unidad pequeña         (CAPACIDAD:  8 asientos)\n"
       <<"► (2NN) Unidad grande          (CAPACIDAD: 45 asientos)\n"
       <<"► (3NN) Unidad grande premium  (CAPACIDAD: 39 asientos)\n";

   int nuevoCod{};
   bool validCod=false;
   do {
      if (!leerEntero("\nNUEVO CÓDIGO de la UNIDAD: ", nuevoCod)){
         cout<<"\n\033[33m[CANCELADO] No se modificó el código.\033[0m\n";
         pausar();
         return;
      }
      int nuevaCategoria=categoriaUnid(nuevoCod);
      if (nuevaCategoria==0){
         cout<<"\033[31m[ERROR] Código de unidad no válido. Debe estar en el rango 100-399. (Escriba 'Q' o 'CANCELAR' si desea cancelar)\033[0m\n";
         continue;
      }
      if (nuevaCategoria==categoriaActual){
         cout<<"\033[31m[!] Ese código pertenece a la MISMA categoria ("<<categoriaActual<<"NN). Solo se permite el cambio si la unidad pasa a otra categoria. (Escriba 'Q' o 'CANCELAR' si desea cancelar)\033[0m\n";
         continue;
      }
      bool duplicado=false;
      for (size_t i=0; i<padron.size(); i++){
         if ((int)i!=index && padron[i].getCodigo()==nuevoCod){
            duplicado=true;
            break;
         }
      }
      if (duplicado){
         cout<<"\033[31m[ERROR] El código "<<nuevoCod<<" ya esta registrado en el padrón. (Escriba 'Q' o 'CANCELAR' si desea cancelar)\033[0m\n";
         continue;
      }
      validCod=true;
   } while (!validCod);
   int nuevaCapacidad=capacidadPorCategoria(categoriaUnid(nuevoCod));
   padron[index].setCodigo(nuevoCod);
   padron[index].setCapacidad(nuevaCapacidad);
   cout<<"\n\033[32m[EXITO] La unidad cambio de categoria. CÓDIGO: "<<codActual<<" -→ "<<nuevoCod
       <<" | CAPACIDAD actualizada a "<<nuevaCapacidad<<" asientos.\033[0m\n";
   pausar();
}

void modificarPlacaUnid(vector<Unidad>& padron, int index){
   string placaActual=padron[index].getPlaca();
   cout<<"\nPLACA ACTUAL: "<<placaActual<<"\n";
   string nuevaPlaca{};
   bool validPlaca=false;
   do {
      if (!leerPlaca("NUEVA MATRÍCULA (ej. ABC-123): ", nuevaPlaca)){
         cout<<"\n\033[33m[CANCELADO] No se modifico la placa.\033[0m\n";
         pausar();
         return;
      }
      bool duplicado=false;
      for (size_t i=0; i<padron.size(); i++){
         if ((int)i!=index && padron[i].getPlaca()==nuevaPlaca){
            duplicado=true;
            break;
         }
      }
      if (duplicado){
         cout<<"\033[31m[ERROR] La placa "<<nuevaPlaca<<" ya esta registrada en el padrón. (Escriba 'Q' o 'CANCELAR' si desea cancelar)\033[0m\n";
         continue;
      }
      validPlaca=true;
   } while (!validPlaca);
   padron[index].setPlaca(nuevaPlaca);
   cout<<"\n\033[32m[EXITO] Placa actualizada: "<<placaActual<<" -→ "<<nuevaPlaca<<"\033[0m\n";
   pausar();
}

void modificarUnidad(vector<Unidad>& padron){
   limpiarPantalla();
   titulo("MODIFICAR UNIDAD", 2);
   cout<<endl;
   imprimirTablaUnid(padron);
   if (padron.empty()){
      pausar();
      return;
   }

   cout<<"\n\033[33m(Puede escribir 'Q' o 'CANCELAR' para cancelar el proceso)\033[0m\n";
   int codUnidE{}, indexUnidE=-1;
   bool validCod=false;
   do {
      if (!leerEntero("\nCÓDIGO de la UNIDAD a modificar: ", codUnidE)){
         cout<<"\n\033[33m[CANCELADO] Proceso cancelado. No se guardaron cambios.\033[0m\n";
         pausar();
         return;
      }
      for (size_t i=0; i<padron.size(); i++){
         if (padron[i].getCodigo()==codUnidE){
            indexUnidE=(int)i;
            validCod=true;
            break;
         }
      }
      if (!validCod) cout<<"\033[31m[!] Codigo invalido. (Escriba 'Q' o 'CANCELAR' si desea cancelar)\033[0m\n";
   } while (!validCod);

   string teclado{};
   char opc{};
   do {
      limpiarPantalla();
      titulo("MODIFICAR UNIDAD", 2);
      cout<<endl;
      menuCamposUnid(padron[indexUnidE]);
      getline(cin, teclado);
      opc='X';
      if (teclado.size()==1) opc=teclado[0];

      switch(opc){
         case '1': modificarCodigoUnid(padron, indexUnidE); break;
         case '2': modificarPlacaUnid(padron, indexUnidE); break;
         case '0': break; // Regresa al menu de Modificar Datos
         default:
            cout<<"\n\033[31m[ERROR] Opcion no valida.\033[0m\n";
            pausar();
            break;
      }
   } while (opc!='0');
}

void modificarNombresOp(Operador &op){
   string actual=op.getNombres();
   cout<<"\nNOMBRES ACTUALES: "<<actual<<"\n";
   string nuevo{};
   if (!leerTexto("NUEVOS NOMBRES: ", nuevo)){
      cout<<"\n\033[33m[CANCELADO] No se modificaron los nombres.\033[0m\n";
      pausar();
      return;
   }
   op.setNombres(nuevo);
   cout<<"\n\033[32m[EXITO] Nombres actualizados: "<<actual<<" -→ "<<nuevo<<"\033[0m\n";
   pausar();
}

void modificarApellidosOp(Operador &op){
   string actual=op.getApellidos();
   cout<<"\nAPELLIDOS ACTUALES: "<<actual<<"\n";
   string nuevo{};
   if (!leerTexto("NUEVOS APELLIDOS: ", nuevo)){
      cout<<"\n\033[33m[CANCELADO] No se modificaron los apellidos.\033[0m\n";
      pausar();
      return;
   }
   op.setApellidos(nuevo);
   cout<<"\n\033[32m[EXITO] Apellidos actualizados: "<<actual<<" -→ "<<nuevo<<"\033[0m\n";
   pausar();
}

void modificarDNIOp(vector<Operador>& padron, int index){
   int actual=padron[index].getDNI();
   cout<<"\nDNI/C.E. ACTUAL: "<<actual<<"\n";
   int nuevoDNI{};
   bool validDNI=false;
   do {
      if (!leerDNI("NUEVO DNI/C.E.: ", nuevoDNI)){
         cout<<"\n\033[33m[CANCELADO] No se modifico el DNI/C.E.\033[0m\n";
         pausar();
         return;
      }
      bool duplicado=false;
      for (size_t i=0; i<padron.size(); i++){
         if ((int)i!=index && padron[i].getDNI()==nuevoDNI){
            duplicado=true;
            break;
         }
      }
      if (duplicado){
         cout<<"\033[31m[ERROR] El DNI/C.E. "<<nuevoDNI<<" ya esta registrado en el padrón. (Escriba 'Q' o 'CANCELAR' si desea cancelar)\033[0m\n";
         continue;
      }
      validDNI=true;
   } while (!validDNI);
   padron[index].setDNI(nuevoDNI);
   cout<<"\n\033[32m[EXITO] DNI/C.E. actualizado: "<<actual<<" -→ "<<nuevoDNI<<"\033[0m\n";
   pausar();
}

void modificarOperador(vector<Operador>& padron){
   limpiarPantalla();
   titulo("MODIFICAR OPERADOR", 2);
   cout<<endl;
   imprimirTablaOp(padron);
   if (padron.empty()){
      pausar();
      return;
   }

   cout<<"\n\033[33m(Puede escribir 'Q' o 'CANCELAR' para cancelar el proceso)\033[0m\n";
   int codOpE{}, indexOpE=-1;
   bool validCod=false;
   do {
      if (!leerEntero("\nCODIGO del OPERADOR a modificar: ", codOpE)){
         cout<<"\n\033[33m[CANCELADO] Proceso cancelado. No se guardaron cambios.\033[0m\n";
         pausar();
         return;
      }
      for (size_t i=0; i<padron.size(); i++){
         if (padron[i].getCodigo()==codOpE){
            indexOpE=(int)i;
            validCod=true;
            break;
         }
      }
      if (!validCod) cout<<"\033[31m[!] Codigo invalido. (Escriba 'Q' o 'CANCELAR' si desea cancelar)\033[0m\n";
   } while (!validCod);

   string teclado{};
   char opc{};
   do {
      limpiarPantalla();
      titulo("MODIFICAR OPERADOR", 2);
      cout<<endl;
      menuCamposOp(padron[indexOpE]);
      getline(cin, teclado);
      opc='X';
      if (teclado.size()==1) opc=teclado[0];

      switch(opc){
         case '1': modificarDNIOp(padron, indexOpE); break;
         case '2': modificarNombresOp(padron[indexOpE]); break;
         case '3': modificarApellidosOp(padron[indexOpE]); break;
         case '0': break; // Regresa al menu de Modificar Datos
         default:
            cout<<"\n\033[31m[ERROR] Opcion no valida.\033[0m\n";
            pausar();
            break;
      }
   } while (opc!='0');
}

void modificarDestinoServ(Servicio &serv){
   string actual=serv.getDestino();
   cout<<"\nDESTINO ACTUAL: "<<actual<<"\n";
   string nuevo{};
   if (!leerTexto("NUEVO DESTINO: ", nuevo)){
      cout<<"\n\033[33m[CANCELADO] No se modifico el destino.\033[0m\n";
      pausar();
      return;
   }
   serv.setDestino(nuevo);
   cout<<"\n\033[32m[EXITO] Destino actualizado: "<<actual<<" -→ "<<nuevo<<"\033[0m\n";
   pausar();
}

// Reasigna la UNIDAD y el OPERADOR de un servicio pendiente. Vuelve a
// mostrar las listas de unidades/operadores DISPONIBLES (reutilizando los
// mismos selectores de programarNuevoServ()) para elegir los nuevos, y solo
// libera la asignacion anterior si el usuario confirma ambas elecciones; si
// cancela en cualquier punto, la asignacion original queda intacta.
// Permite modificar SOLO la unidad asignada al servicio
void modificarUnidadServ(vector<Unidad>& padronUnid, Servicio &serv){
   limpiarPantalla();
   titulo("CAMBIAR UNIDAD ASIGNADA", 3);
   cout<<"\nActualmente asignada -> UNIDAD: "<<serv.getCodigoUnid()<<"\n";
   cout<<"\033[33m(Puede escribir 'Q' o 'CANCELAR' en cualquier momento para cancelar el reemplazo)\033[0m\n";

   // 1. Elegir nueva unidad (respetando la capacidad de pasajeros del servicio)
   int indexNuevaUnid = seleccionarUnidDisponible(padronUnid, serv.getNumPasajeros());
   if (indexNuevaUnid == -1){
      cout<<"\n\033[33m[CANCELADO] Se conserva la unidad actual.\033[0m\n";
      pausar();
      return;
   }

   // 2. Liberar la unidad anterior
   int codUnidAnterior = serv.getCodigoUnid();
   for (size_t i = 0; i < padronUnid.size(); i++){
      if (padronUnid[i].getCodigo() == codUnidAnterior) {
         padronUnid[i].setEstado("Disponible");
         break; // Optimización: ya lo encontramos, salimos del bucle
      }
   }

   // 3. Ocupar la nueva unidad y actualizar el servicio
   padronUnid[indexNuevaUnid].setEstado("Asignado");
   serv.setCodigoUnid(padronUnid[indexNuevaUnid].getCodigo());

   cout<<"\n\033[32m[EXITO] Unidad actualizada -→ "<<codUnidAnterior<<" -→ "<<serv.getCodigoUnid()<<"\033[0m\n";
   pausar();
}

// Permite modificar SOLO el operador asignado al servicio
void modificarOperadorServ(vector<Operador>& padronOp, Servicio &serv){
   limpiarPantalla();
   titulo("CAMBIAR OPERADOR ASIGNADO", 3);
   cout<<"\nActualmente asignado -> OPERADOR: "<<serv.getCodigoOp()<<"\n";
   cout<<"\033[33m(Puede escribir 'Q' o 'CANCELAR' en cualquier momento para cancelar el reemplazo)\033[0m\n";

   // 1. Elegir nuevo operador
   int indexNuevoOp = seleccionarOpDisponible(padronOp);
   if (indexNuevoOp == -1){
      cout<<"\n\033[33m[CANCELADO] Se conserva el operador actual.\033[0m\n";
      pausar();
      return;
   }

   // 2. Liberar el operador anterior
   int codOpAnterior = serv.getCodigoOp();
   for (size_t i = 0; i < padronOp.size(); i++){
      if (padronOp[i].getCodigo() == codOpAnterior) {
         padronOp[i].setEstado("Disponible");
         break; // Optimización
      }
   }

   // 3. Ocupar el nuevo operador y actualizar el servicio
   padronOp[indexNuevoOp].setEstado("Asignado");
   serv.setCodigoOp(padronOp[indexNuevoOp].getCodigo());

   cout<<"\n\033[32m[EXITO] Operador actualizado -→ "<<codOpAnterior<<" -→ "<<serv.getCodigoOp()<<"\033[0m\n";
   pausar();
}

// Elige un servicio en estado "Pendiente" y permite editar su destino y/o su
// unidad/operador asignado. Solo se listan los servicios Pendientes porque
// un servicio Activo o Completado ya no deberia reprogramarse por aqui.
void modificarServicio(vector<Unidad>& padronUnid, vector<Operador>& padronOp, vector<Servicio>& historial){
   limpiarPantalla();
   titulo("MODIFICAR SERVICIO", 2);
   cout<<endl;

   vector<int> indexPend;
   for (size_t i=0; i<historial.size(); i++){
      if (historial[i].getEstado()=="Pendiente"){
         indexPend.push_back((int)i);
      }
   }
   if (indexPend.empty()){
      cout<<"\033[33m[ALERTA] No hay servicios en estado PENDIENTE para modificar.\033[0m\n";
      pausar();
      return;
   }

   titulo("SERVICIOS PENDIENTES", 4); cout<<endl;
   cout<<"\033[1;36m"<<left<<setw(5)<<"ID"<<setw(11)<<"COD-UNID"<<setw(9)<<"COD-OP"<<setw(13)<<"N° PAS."<<setw(20)<<"DESTINO"<<"\033[0m"<<endl;
   cout<<"\033[36m"<<llenar(58, "-")<<"\033[0m\n";
   for (size_t i=0; i<indexPend.size(); i++){
      string destino=historial[indexPend[i]].getDestino();
      int extras=compensacionUTF8(destino);
      cout<<left<<setw(5)<<historial[indexPend[i]].getID()
                <<setw(11)<<historial[indexPend[i]].getCodigoUnid()
                <<setw(9)<<historial[indexPend[i]].getCodigoOp()
                <<setw(12)<<historial[indexPend[i]].getNumPasajeros()
                <<setw(20+extras)<<destino<<endl;
   }

   cout<<"\n\033[33m(Puede escribir 'Q' o 'CANCELAR' para cancelar el proceso)\033[0m\n";
   int idServE{}, indexServE=-1;
   bool validID=false;
   do {
      if (!leerEntero("\nID del servicio PENDIENTE a modificar: ", idServE)){
         cout<<"\n\033[33m[CANCELADO] Proceso cancelado. No se guardaron cambios.\033[0m\n";
         pausar();
         return;
      }
      for (size_t i=0; i<indexPend.size(); i++){
         if (historial[indexPend[i]].getID()==idServE){
            indexServE=indexPend[i];
            validID=true;
            break;
         }
      }
      if (!validID) cout<<"\033[31m[!] ID invalido o el servicio no esta PENDIENTE. (Escriba 'Q' o 'CANCELAR' si desea cancelar)\033[0m\n";
   } while (!validID);

   string teclado{};
   char opc{};
   do {
      limpiarPantalla();
      titulo("MODIFICAR SERVICIO", 2);
      cout<<endl;
      menuCamposServ(historial[indexServE]);
      getline(cin, teclado);
      opc='X';
      if (teclado.size()==1) opc=teclado[0];

      switch(opc){
         case '1': modificarUnidadServ(padronUnid, historial[indexServE]); break;
         case '2': modificarOperadorServ(padronOp, historial[indexServE]); break;
         case '3': modificarDestinoServ(historial[indexServE]); break;
         case '0': break; // Regresa al menu principal
         default:
            cout<<"\n\033[31m[ERROR] Opcion no valida.\033[0m\n";
            pausar();
            break;
      }
   } while (opc!='0');
}

// Submenu de la opcion [3] de REGISTROS: permite elegir si se va a modificar
// una Unidad, un Operador o un Servicio.
// POR MOVER !!!!!!
void modificarDatos(vector<Unidad>& padronUnid, vector<Operador>& padronOp, vector<Servicio>& historial){
   string teclado{};
   char opc{};
   do {
      menuModificar();
      getline(cin, teclado);
      opc='X';
      if (teclado.size()==1) opc=teclado[0];

      switch (opc){
         case '1': modificarUnidad(padronUnid); break;
         case '2': modificarOperador(padronOp); break;
         case '3': modificarServicio(padronUnid, padronOp, historial); break;
         case '0': break; // Cancelar sin hacer nada
         default:
            cout<<"\n\033[31m[ERROR] Opción no valida.\033[0m\n";
            pausar();
            break;
      }
   } while(opc!='0');
}

// === ELIMINAR UN REGISTRO ===
void eliminarUnidad(vector<Unidad>& padron){
   limpiarPantalla();
   titulo("ELIMINAR UNIDAD", 2);
   cout<<endl;

   vector<int> indexUnid;
   for (size_t i=0; i<padron.size(); i++){
      if (padron[i].getEstado()!="Asignado"){
         indexUnid.push_back((int)i);
      }
   }
   if (indexUnid.empty()){
      cout<<"\033[33m[ALERTA] Ninguna UNIDAD se puede eliminar (todas están ASIGNADAS).\033[0m\n";
      pausar();
      return;
   }

   titulo("UNIDADES ELEGIBLES PARA ELIMINAR", 4); cout<<endl;
   cout<<"\033[1;36m"<<left<<setw(10)<<"CÓDIGO"<<setw(10)<<"PLACA"<<setw(12)<<"CAPACIDAD"<<setw(11)<<"ESTADO"<<"\033[0m"<<endl;
   cout<<"\033[36m"<<llenar(44, "-")<<"\033[0m\n";
   for (size_t i=0; i<indexUnid.size(); i++){
      cout<<left<<setw(9)<<padron[indexUnid[i]].getCodigo()
                <<setw(10)<<padron[indexUnid[i]].getPlaca()
                <<setw(12)<<padron[indexUnid[i]].getCapacidad()
                <<setw(11)<<padron[indexUnid[i]].getEstado()<<endl;
   }
   cout<<"\n\033[33m(Puede escribir 'Q' o 'CANCELAR' para cancelar el proceso)\033[0m\n";
   int codUnidE{}, indexUnidE=-1;
   bool validCod=false;
   do {
      if (!leerEntero("\nCÓDIGO de la UNIDAD a eliminar: ", codUnidE)){
         cout<<"\n\033[33m[CANCELADO] Proceso cancelado. No se elimino nada.\033[0m\n";
         pausar();
         return;
      }
      for (size_t i=0; i<indexUnid.size(); i++){
         if (padron[indexUnid[i]].getCodigo()==codUnidE){
            indexUnidE=indexUnid[i];
            validCod=true;
            break;
         }
      }
      if (!validCod) cout<<"\033[31m[!] Codigo invalido o la unidad esta ASIGNADA. (Escriba 'Q' o 'CANCELAR' si desea cancelar)\033[0m\n";
   } while (!validCod);

   cout<<"\n\033[31m[!] Esta a punto de ELIMINAR la unidad "<<codUnidE<<" (placa "<<padron[indexUnidE].getPlaca()<<"). Esta accion no se puede deshacer.\033[0m\n";
   if (!confirmarAccion("¿Confirma la eliminación?")){
      cout<<"\n\033[33m[CANCELADO] No se eliminó la unidad.\033[0m\n";
      pausar();
      return;
   }
   padron.erase(padron.begin()+indexUnidE);
   cout<<"\n\033[32m[EXITO] La unidad "<<codUnidE<<" fue eliminada del padron.\033[0m\n";
   pausar();
}

void eliminarOperador(vector<Operador>& padron){
   limpiarPantalla();
   titulo("ELIMINAR OPERADOR", 2);
   cout<<endl;

   vector<int> indexOp;
   for (size_t i=0; i<padron.size(); i++){
      if (padron[i].getEstado()!="Asignado"){
         indexOp.push_back((int)i);
      }
   }
   if (indexOp.empty()){
      cout<<"\033[33m[ALERTA] Ningún OPERADOR se puede eliminar (todos estan ASIGNADOS).\033[0m\n";
      pausar();
      return;
   }

   titulo("OPERADORES ELEGIBLES PARA ELIMINAR", 4); cout<<endl;
   cout<<"\033[1;36m"<<left<<setw(10)<<"CÓDIGO"<<setw(12)<<"DNI"<<setw(38)<<"NOMBRE COMPLETO"<<setw(20)<<"ESTADO"<<"\033[0m"<<endl;
   cout<<"\033[36m"<<llenar(75, "-")<<"\033[0m\n";
   for (size_t i=0; i<indexOp.size(); i++){
      string nombreCompleto=padron[indexOp[i]].getNombreCompleto();
      int extras=compensacionUTF8(nombreCompleto);
      cout<<left<<setw(9)<<padron[indexOp[i]].getCodigo()
                <<setw(12)<<padron[indexOp[i]].getDNI()
                <<setw(38+extras)<<nombreCompleto
                <<setw(20)<<padron[indexOp[i]].getEstado()<<endl;
   }

   cout<<"\n\033[33m(Puede escribir 'Q' o 'CANCELAR' para cancelar el proceso)\033[0m\n";
   int codOpE{}, indexOpE=-1;
   bool validCod=false;
   do {
      if (!leerEntero("\nCÓDIGO del OPERADOR a eliminar: ", codOpE)){
         cout<<"\n\033[33m[CANCELADO] Proceso cancelado. No se elimino nada.\033[0m\n";
         pausar();
         return;
      }
      for (size_t i=0; i<indexOp.size(); i++){
         if (padron[indexOp[i]].getCodigo()==codOpE){
            indexOpE=indexOp[i];
            validCod=true;
            break;
         }
      }
      if (!validCod) cout<<"\033[31m[!] Codigo invalido o el operador esta ASIGNADO. (Escriba 'Q' o 'CANCELAR' si desea cancelar)\033[0m\n";
   } while (!validCod);

   cout<<"\n\033[31m[!] Esta a punto de ELIMINAR al operador "<<codOpE<<" ("<<padron[indexOpE].getNombreCompleto()<<"). Esta accion no se puede deshacer.\033[0m\n";
   if (!confirmarAccion("¿Confirma la eliminación?")){
      cout<<"\n\033[33m[CANCELADO] No se eliminó el operador.\033[0m\n";
      pausar();
      return;
   }

   padron.erase(padron.begin()+indexOpE);
   cout<<"\n\033[32m[EXITO] El operador "<<codOpE<<" fue eliminado del padron.\033[0m\n";
   pausar();
}

// Elimina un servicio del historial. Solo se pueden eliminar servicios
// "Pendiente": uno "Activo" o "Completado" ya forma parte de la trazabilidad
// real de operaciones y no deberia poder borrarse por aqui.
void eliminarServicio(vector<Servicio>& historial, vector<Unidad>& padronUnid, vector<Operador>& padronOp){
   limpiarPantalla();
   titulo("ELIMINAR SERVICIO", 2);
   cout<<endl;

   vector<int> indexPend;
   for (size_t i=0; i<historial.size(); i++){
      if (historial[i].getEstado()=="Pendiente"){
         indexPend.push_back((int)i);
      }
   }
   if (indexPend.empty()){
      cout<<"\033[33m[ALERTA] No hay servicios en estado PENDIENTE para eliminar.\033[0m\n";
      pausar();
      return;
   }

   titulo("SERVICIOS PENDIENTES", 4); cout<<endl;
   cout<<"\033[1;36m"<<left<<setw(5)<<"ID"<<setw(11)<<"COD-UNID"<<setw(9)<<"COD-OP"<<setw(13)<<"N° PAS."<<setw(20)<<"DESTINO"<<"\033[0m"<<endl;
   cout<<"\033[36m"<<llenar(58, "-")<<"\033[0m\n";
   for (size_t i=0; i<indexPend.size(); i++){
      string destino=historial[indexPend[i]].getDestino();
      int extras=compensacionUTF8(destino);
      cout<<left<<setw(5)<<historial[indexPend[i]].getID()
                <<setw(11)<<historial[indexPend[i]].getCodigoUnid()
                <<setw(9)<<historial[indexPend[i]].getCodigoOp()
                <<setw(12)<<historial[indexPend[i]].getNumPasajeros()
                <<setw(20+extras)<<destino<<endl;
   }

   cout<<"\n\033[33m(Puede escribir 'Q' o 'CANCELAR' para cancelar el proceso)\033[0m\n";
   int idServE{}, indexServE=-1;
   bool validID=false;
   do {
      if (!leerEntero("\nID del servicio PENDIENTE a eliminar: ", idServE)){
         cout<<"\n\033[33m[CANCELADO] Proceso cancelado. No se elimino nada.\033[0m\n";
         pausar();
         return;
      }
      for (size_t i=0; i<indexPend.size(); i++){
         if (historial[indexPend[i]].getID()==idServE){
            indexServE=indexPend[i];
            validID=true;
            break;
         }
      }
      if (!validID) cout<<"\033[31m[!] ID invalido o el servicio no esta PENDIENTE. (Escriba 'Q' o 'CANCELAR' si desea cancelar)\033[0m\n";
   } while (!validID);
   cout<<"\n\033[31m[!] Esta a punto de ELIMINAR el servicio "<<idServE<<" (destino: "<<historial[indexServE].getDestino()<<"). Esta accion no se puede deshacer.\033[0m\n";
   if (!confirmarAccion("¿Confirma la eliminacion?")){
      cout<<"\n\033[33m[CANCELADO] No se elimino el servicio.\033[0m\n";
      pausar();
      return;
   }
   int indexUnid=-1, indexOp=-1;
   for (size_t i=0; i<padronUnid.size(); i++){
      if (padronUnid[i].getCodigo()==historial[indexServE].getCodigoUnid()){
         indexUnid=(int)i;
         break;
      }
   }
   for (size_t i=0; i<padronOp.size(); i++){
      if (padronOp[i].getCodigo()==historial[indexServE].getCodigoOp()){
         indexOp=(int)i;
         break;
      }
   }
   padronUnid[indexUnid].setEstado("Disponible");
   padronOp[indexOp].setEstado("Disponible");
   historial.erase(historial.begin()+indexServE);
   cout<<"\n\033[32m[EXITO] El servicio "<<idServE<<" fue eliminado del historial.\033[0m\n";
   cout<<"\n\033[33m[!] NOTA: La UNIDAD "<<padronUnid[indexUnid].getCodigo()<<" y el OPERADOR "<<padronOp[indexOp].getCodigo()<<" fueron marcados como DISPONIBLE.\033[0m\n";
   pausar();
}

// Submenu de la opcion [4] de REGISTROS: permite elegir si se va a eliminar
// una Unidad, un Operador o un Servicio.
// POR MOVER !!!!!!
void eliminarRegistro(vector<Unidad>& padronUnid, vector<Operador>& padronOp, vector<Servicio>& historial){
   string teclado{};
   char opc{};
   do {
      menuEliminar();
      getline(cin, teclado);
      opc='X';
      if (teclado.size()==1) opc=teclado[0];

      switch (opc){
         case '1': eliminarUnidad(padronUnid); break;
         case '2': eliminarOperador(padronOp); break;
         case '3': eliminarServicio(historial, padronUnid, padronOp); break;
         case '0': break; // Cancelar sin hacer nada
         default:
            cout<<"\n\033[31m[ERROR] Opcion no valida.\033[0m\n";
            pausar();
            break;
      }
   } while(opc!='0');
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
                  case '3': modificarDatos(padronUnid, padronOp, historialServ); break;
                  case '4': eliminarRegistro(padronUnid, padronOp, historialServ); break;
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
   pausar();
   return 0;
}