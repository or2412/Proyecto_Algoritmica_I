#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <windows.h>
#include <cstdlib>
#include <fstream>
#include <sstream> // Para procesar lineas de texto separadas por comas

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
void clearScreen(){
   #ifdef _WIN32
      system("cls");
   #else
      system("clear");
   #endif
}

string fill(int lenght, const string &symbol){
	string relleno{};
	for (int i=1; i<=lenght; i++) relleno+=symbol;
	return relleno;
}

void printTitle(const string &title, int cat){
	int tamReal{};
	for (size_t i=0; i<title.size(); i++){
		unsigned char c=(unsigned char)(title[i]);
		if (c<128 || c>191) tamReal++;
	}
	//cout<<"El texto tiene "<<title.size()<<" caracteres."<<endl;
	//cout<<"El texto tiene "<<tamReal<<" caracteres."<<endl;
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
			cout<<"  ╔"<<fill(anchoBorde-6, "═")   <<"╗  \n";
			cout<<"╔═╝ "<<fill(anchoBorde-8, "─") <<" ╚═╗\n";
			cout<<"║ │"<<centros<<newTitle<<centros<<"│ ║\n";
			cout<<"╚═╗ "<<fill(anchoBorde-8, "─") <<" ╔═╝\n";
			cout<<"  ╚"<<fill(anchoBorde-6, "═")   <<"╝  \n";
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
			cout<<"  ╔"<<fill(anchoBorde-2, "═")<<"╗\n";
			cout<<"► ║"<<centros<<title<<centros<<"║\n";
			cout<<"  ╚"<<fill(anchoBorde-2, "═")<<"╝\n";
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
			cout<<"   ┌"<<fill(anchoBorde-2, "─")<<"┐\n";
			cout<<"►► │"<<centros<<title<<centros<<"│\n";
			cout<<"   └"<<fill(anchoBorde-2, "─")<<"┘\n";
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
			cout<<"►►► "<<centros<<" "<<title<<" "<<centros<<endl;
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
			cout<<"►►►► "<<centros<<" "<<title<<" "<<centros<<endl;
			break;
		}
	}
}

void loadingDots(int repeat, unsigned int delay){
   for(int i=1; i<=repeat; i++){
      for (int j=1; j<=3; j++){
         cout<<".";
         Sleep(delay);
      }
      cout<<fill(3,"\b")<<fill(3," ")<<fill(3,"\b");
      Sleep(delay);
   }
}

void menuPrincipal(){
   clearScreen();
   printTitle("SISTEMA DE GESTION DE TRANSPORTE", 0);
   cout<<"  ├╴[1] Mostrar Padron General\n";
   cout<<"  ├╴[2] Mostrar Historial de Servicios\n";
   cout<<"  ├╴[3] Modulo de Operaciones (Programar/Despachar)\n";
   cout<<"  ├╴[4] Modulo de Registros (Unidades/Operadores)\n";
   cout<<"  └╴[0] Salir y Guardar\n";
   cout<<"\n►► Ingresar opcion -→ ";
}

void menuOperaciones(){
   clearScreen();
   printTitle("MODULO DE OPERACIONES", 1);
   cout<<"  ├╴[1] Programar nuevo servicio\n";
   cout<<"  ├╴[2] Procesar salida de bus (En Ruta)\n";
   cout<<"  ├╴[3] Procesar arribo de bus (Completado)\n";
   cout<<"  └╴[0] Regresar al menu principal\n";
   cout<<"\n►► Ingresar opcion -→ ";
}

void menuRegistros(){
   clearScreen();
   printTitle("MODULO DE REGISTROS", 1);
   cout<<"  ├╴[1] Registrar nueva Unidad\n";
   cout<<"  ├╴[2] Registrar nuevo Operador\n";
   cout<<"  └╴[0] Regresar al menu principal\n";
   cout<<"\n►► Ingresar opcion -→ ";
}

void pausar(){
   cout<<"\nPresione ENTER para continuar...";
   cin.ignore();
   cin.get();
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
   cout<<"\nCargando datos de UNIDADES"; loadingDots(3, 150);

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
   cout<<"\nCargando datos de OPERADORES"; loadingDots(3, 150);

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
   cout<<"\nCargando datos de SERVICIOS"; loadingDots(3, 150);

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
   cout<<"\nGuardando datos de UNIDADES"; loadingDots(3, 150);
   
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
   cout<<"\nGuardando datos de OPERADORES"; loadingDots(3, 150);
   
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
   cout<<"\nGuardando datos de SERVICIOS"; loadingDots(3, 150);
   
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
   clearScreen();
   cout<<"=== PADRON DE UNIDADES ===\n\n";
   if (padron.empty()){
      cout<<"¡¡¡No hay unidades registradas!!!"<<endl;
   }
   else{
      cout<<left<<setw(10)<<"PLACA"<<setw(10)<<"CODIGO"<<setw(15)<<"CAPACIDAD"<<setw(20)<<"ESTADO"<<endl;
      cout<<fill(55, "-")<<"\n";
      for (size_t i=0; i<padron.size(); i++){
         // Colores basicos ASCII  (Verde: "Disponible", Rojo: "Asignado", Amarillo: "en reposo")
         if(padron[i].getEstado()=="Disponible") cout<<"\033[32m";
         else if(padron[i].getEstado()=="Asignado") cout<<"\033[31m";
         else cout<<"\033[33m";
         //Información coloreada
         cout<<left
         <<setw(10)<<padron[i].getPlaca() 
         <<setw(10)<<padron[i].getCodigo() 
         <<setw(15)<<padron[i].getCapacidad() 
         <<setw(20)<<padron[i].getEstado()<<"\033[0m"<<endl;
        }
    }
    pausar();
}

void mostrarPadronOp(vector<Operador>& padron){
   clearScreen();
   cout<<"=== PADRON DE OPERADORES ===\n\n";
   if (padron.empty()){
      cout<<"¡¡¡No hay operadores registrados!!!"<<endl;
   }
   else{
      cout<<left<<setw(5)<<"CODIGO"<<setw(10)<<"DNI"<<setw(40)<<"NOMBRE COMPLETO"<<setw(20)<<"ESTADO"<<endl;
      cout<<fill(75, "-")<<"\n";
      for (size_t i=0; i<padron.size(); i++){
         // Colores basicos ASCII  (Verde: "Disponible", Rojo: "Asignado", Amarillo: "En reposo")
         if(padron[i].getEstado()=="Disponible") cout<<"\033[32m";
         else if(padron[i].getEstado()=="Asignado") cout<<"\033[31m";
         else cout<<"\033[33m";
         //Información coloreada
         cout<<left
         <<setw(5)<<padron[i].getCodigo() 
         <<setw(10)<<padron[i].getDNI() 
         <<setw(40)<<padron[i].getNombreCompleto() 
         <<setw(20)<<padron[i].getEstado()<<"\033[0m"<<endl;
        }
    }
    pausar();
}

void mostrarHistorialServ(vector<Servicio>& historial){
   clearScreen();
   cout<<"=== HISTORIAL DE SERVICIOS ===\n\n";
   if (historial.empty()){
      cout<<"¡¡¡No hay servicios registrados!!!"<<endl;
   }
   else{
      cout<<left<<setw(5)<<"ID"<<setw(14)<<"COD. UNID."<<setw(12)<<"COD. OP."<<setw(12)<<"N° PAS."<<setw(20)<<"DESTINO"<<setw(20)<<"ESTADO"<<endl;
      cout<<fill(75, "-")<<"\n";
      for (size_t i=0; i<historial.size(); i++){
         // Colores basicos ASCII  (Verde: "Completado", Rojo: "Activo", Amarillo: "Pendiente")
         if(historial[i].getEstado()=="Completado") cout<<"\033[32m";
         else if(historial[i].getEstado()=="Activo") cout<<"\033[31m";
         else cout<<"\033[33m";
         //Información coloreada
         cout<<left
         <<setw(5)<<historial[i].getID() 
         <<setw(14)<<historial[i].getCodigoUnid() 
         <<setw(12)<<historial[i].getCodigoOp() 
         <<setw(12)<<historial[i].getNumPasajeros() 
         <<setw(20)<<historial[i].getDestino() 
         <<setw(20)<<historial[i].getEstado()<<"\033[0m"<<endl;
        }
    }
    pausar();
}

void programarNuevoServ(vector<Unidad>& padronUnid, vector<Operador>& padronOp, vector<Servicio>& historial){
   clearScreen();
   int pasajeros{};
   string destino{};
   printTitle("PROGRAMAR NUEVO SERVICIO", 1);
   cin.ignore();
   cout<<"DESTINO: "; getline(cin, destino);
   cout<<"N° PASAJEROS: "; cin>>pasajeros;

   //Validar si hay operadores disponibles primero
   vector<int> indexOp;
   for (size_t i=0; i<padronOp.size(); i++){
      if (padronOp[i].getEstado()=="Disponible"){
         indexOp.push_back((int)i);
      }
   }
   if (indexOp.empty()){
      cout<<"\n\033[31m[ERROR] No hay operadores DISPONIBLES en este momento. Intente nuevamente mas tarde.\033[0m\n";
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
      pausar();
      return; 
   }

   //Mostrar y seleccionar Unidad
   cout<<"\n=== UNIDADES DISPONIBLES ===\n";
   cout<<left<<setw(10)<<"CODIGO"<<setw(15)<<"PLACA"<<setw(15)<<"CAPACIDAD"<<endl;
   cout<<fill(40, "-")<<"\n";
   for (size_t i=0; i<indexUnid.size(); i++){
      cout<<left<<setw(10)<<padronUnid[indexUnid[i]].getCodigo()
                <<setw(15)<<padronUnid[indexUnid[i]].getPlaca()
                <<setw(15)<<padronUnid[indexUnid[i]].getCapacidad()<<endl;
   }
   int codUnidE{}, indexUnidE=-1;
   bool validUnid=false;
   do {
      cout<<"\nCODIGO de la UNIDAD por asignar: "; cin>>codUnidE;
      for (size_t i=0; i<indexUnid.size(); i++){
         if (padronUnid[indexUnid[i]].getCodigo()==codUnidE){
            indexUnidE=indexUnid[i];
            validUnid=true;
            break;
         }
      }
      if (!validUnid) cout<<"\033[31m[!] Codigo invalido o unidad no apta. Intente de nuevo.\033[0m\n";
   } while (!validUnid);

   //Mostrar y seleccionar Operador
   cout<<"\n=== OPERADORES DISPONIBLES ===\n";
   cout<<left<<setw(10)<<"CODIGO"<<setw(12)<<"DNI"<<setw(40)<<"NOMBRE COMPLETO"<<endl;
   cout<<fill(62, "-")<<"\n";
   for (size_t i=0; i<indexOp.size(); i++){
      cout<<left<<setw(10)<<padronOp[indexOp[i]].getCodigo()
                <<setw(12)<<padronOp[indexOp[i]].getDNI()
                <<setw(40)<<padronOp[indexOp[i]].getNombreCompleto()<<endl;
   }
   int codOpE{}, indexOpE=-1;
   bool validOp=false;
   do {
      cout<<"\nCODIGO del OPERADOR por asignar: "; cin>>codOpE;
      for (size_t i=0; i<indexOp.size(); i++) {
         if (padronOp[indexOp[i]].getCodigo()==codOpE) {
            indexOpE=indexOp[i];
            validOp=true;
            break;
         }
      }
      if (!validOp) cout<<"\033[31m[!] Codigo invalido u operador no disponible. Intente de nuevo.\033[0m\n";
   } while (!validOp);

   //Creación del servicio y actualización de estados
   int id=(int)(historial.size())+1; 
   historial.push_back(Servicio(id, codUnidE, codOpE, pasajeros, destino, "Pendiente"));
   padronUnid[indexUnidE].setEstado("Asignado");
   padronOp[indexOpE].setEstado("Asignado");
   cout<<"\n\033[32m[EXITO] Servicio "<<id<<" programado correctamente.\033[0m\n";
   cout<<"Unidad asignada: " <<codUnidE<< " | Operador asignado: "<<codOpE<<endl;
   pausar();
}

void procesarSalida(vector<Servicio>& historial){
   clearScreen();
   printTitle("PROCESAR SALIDA DE SERVICIO", 1);

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
   cout<<"\n=== SERVICIOS PENDIENTES DE SALIDA ===\n";
   cout<<left<<setw(5)<<"ID"<<setw(14)<<"COD. UNID."<<setw(12)<<"COD. OP."<<setw(12)<<"N° PAS."<<setw(20)<<"DESTINO"<<endl;
   cout<<fill(55, "-")<<"\n";
   for (size_t i=0; i<indexPend.size(); i++){
      cout<<left<<setw(5)<<historial[indexPend[i]].getID()
                <<setw(12)<<historial[indexPend[i]].getCodigoUnid()
                <<setw(12)<<historial[indexPend[i]].getCodigoOp()
                <<setw(12)<<historial[indexPend[i]].getNumPasajeros()
                <<setw(20)<<historial[indexPend[i]].getDestino()<<endl;
   }

   //Selección y validación del usuario
   int idServSalida{}, indexServE=-1;
   bool validID=false;
   do {
      cout<<"\nID del servicio ACTIVO: "; cin>>idServSalida;
      for (size_t i=0; i<indexPend.size(); i++){
         if (historial[indexPend[i]].getID()==idServSalida){
            indexServE=indexPend[i];
            validID=true;
            break;
         }
      }
      if (!validID) cout<<"\033[31m[!] ID invalido o no esta en estado PENDIENTE. Intente de nuevo.\033[0m\n";
   } while (!validID);

   historial[indexServE].setEstado("Activo");
   cout<<"\n\033[32m[EXITO] El servicio "<<idServSalida<<" ha iniciado su ruta.\033[0m\n";
   pausar();
}

void procesarArribo(vector<Unidad>& padronUnid, vector<Operador>& padronOp, vector<Servicio>& historial){
   clearScreen();
   printTitle("PROCESAR ARRIBO DE SERVICIO", 1);

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
   cout<<"\n=== SERVICIOS ACTIVOS (EN RUTA) ===\n";
   cout<<left<<setw(5)<<"ID"<<setw(14)<<"COD. UNID."<<setw(12)<<"COD. OP."<<setw(12)<<"N° PAS."<<setw(20)<<"DESTINO"<<endl;
   cout<<fill(55, "-")<<"\n";
   for (size_t i=0; i<indexActivos.size(); i++){
      cout<<left<<setw(5)<<historial[indexActivos[i]].getID()
                <<setw(14)<<historial[indexActivos[i]].getCodigoUnid()
                <<setw(12)<<historial[indexActivos[i]].getCodigoOp()
                <<setw(12)<<historial[indexActivos[i]].getNumPasajeros()
                <<setw(20)<<historial[indexActivos[i]].getDestino()<<endl;
   }

   //Selección y validación del usuario
   int idServArribo{}, indexServE=-1;
   bool validID=false;
   do {
      cout<<"\nID del servicio COMPLETADO: "; cin>>idServArribo;
      for (size_t i=0; i<indexActivos.size(); i++){
         if (historial[indexActivos[i]].getID()==idServArribo){
            indexServE=indexActivos[i];
            validID=true;
            break;
         }
      }
      if (!validID) cout<<"\033[31m[!] ID invalido o no esta en estado ACTIVO. Intente de nuevo.\033[0m\n";
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
   
void registrarUnidad(vector<Unidad>& padron){
   clearScreen();
   string placa{};
   int cod{};
   int capacidad{};

   cout<<"=== REGISTRO DE NUEVA UNIDAD ==="<<endl<<endl;
   cout<<"N° DE MATRICULA (ej. ABC-123): "; cin>>placa;
   cout<<"-- CODIGO DE UNIDAD --\n"
      <<"\t(1NN) Unidad pequeña. CAPACIDAD: 8 asientos.\n"
      <<"\t(2NN) Unidad grande. CAPACIDAD: 45 asientos.\n"
      <<"\t(3NN) Unidad grande premium. CAPACIDAD: 39 asientos.\n"
      <<"Indique el codigo de la unidad: "; cin>>cod;
   bool validCode=false;
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
      cout<<"\n[ERROR] Codigo de unidad no valido. No se registro la unidad"<<endl;
   }
   if (validCode){
      padron.push_back(Unidad(placa, cod, capacidad, "Disponible"));
      cout<<"\nUnidad registrada en memoria temporal."<<endl;
   }
   pausar();
}

void registrarOperador(vector<Operador>& padron){
   clearScreen();
   int cod{};
   int dni{};
   string nombres{};
   string apellidos{};

   cout<<"=== REGISTRO DE NUEVO OPERADOR ==="<<endl<<endl;
   cout<<"CODIGO DE OPERADOR (ej. 9NN): "; cin>>cod;
   cout<<"DNI / C.E.: "; cin>>dni;
   cin.ignore();
   cout<<"-- NOMBRE COMPLETO --"<<endl;
   cout<<"NOMBRES: "; getline(cin, nombres);
   cout<<"APELLIDOS: "; getline(cin, apellidos);
      
   padron.push_back(Operador(cod, dni, nombres, apellidos, "Disponible"));
   cout<<"\nOperador registrado en memoria temporal."<<endl;
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
   
   printTitle("CARGA INICIAL", 0);
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
            mostrarPadronUnid(padronUnid);
            cout<<endl;
            mostrarPadronOp(padronOp);
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