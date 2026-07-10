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
			cout<<"  ╔"<<fill(anchoBorde-6, "═")   <<"╗  "<<endl;
			cout<<"╔═╝ "<<fill(anchoBorde-8, "─") <<" ╚═╗"<<endl;
			cout<<"║ │"<<centros<<newTitle<<centros<<"│ ║"<<endl;
			cout<<"╚═╗ "<<fill(anchoBorde-8, "─") <<" ╔═╝"<<endl;
			cout<<"  ╚"<<fill(anchoBorde-6, "═")   <<"╝  "<<endl;
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
			cout<<"  ╔"<<fill(anchoBorde-2, "═")<<"╗"<<endl;
			cout<<"► ║"<<centros<<title<<centros<<"║"<<endl;
			cout<<"  ╚"<<fill(anchoBorde-2, "═")<<"╝"<<endl;
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
			cout<<"   ┌"<<fill(anchoBorde-2, "─")<<"┐"<<endl;
			cout<<"►► │"<<centros<<title<<centros<<"│"<<endl;
			cout<<"   └"<<fill(anchoBorde-2, "─")<<"┘"<<endl;
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
void guardarDatos(vector<Unidad>& padron) {
   ofstream archivo(UNIDADES);
    
   if (archivo.is_open()){
      for (size_t i = 0; i < padron.size(); i++) {
         archivo << padron[i].getPlaca() << ","
                 << padron[i].getCodigo() << ","
                 << padron[i].getCapacidad() << ","
                 << padron[i].getEstado() << "\n";
      }
      archivo.close();
      cout << "\n[OK] Datos guardados exitosamente. Cierre seguro.\n";
   }
   else{
      cout << "\n[ERROR CRITICO] No se pudo guardar en el disco.\n";
   }
}

// === LOGICA DE NEGOCIO Y FUNCIONALIDADES ===
void mostrarPadronUnid(vector<Unidad>& padron){
   clearScreen();
   cout<<"=== PADRON DE UNIDADES ==="<<endl<<endl;
   if (padron.empty()){
      cout<<"¡¡¡No hay unidades registradas!!!"<<endl;
   }
   else{
      cout<<left<<setw(15)<<"PLACA"<<setw(10)<<"CODIGO"<<setw(15)<<"CAPACIDAD"<<setw(20)<<"ESTADO"<<endl;
      cout<<"--------------------------------------------------"<<endl;
      for (size_t i=0; i<padron.size(); i++){
         // Colores basicos ASCII  (Verde: "Disponible", Rojo: "En ruta", Amarillo: "en reposo")
         if(padron[i].getEstado()=="Disponible") cout<<"\033[32m";
         else if(padron[i].getEstado()=="En Ruta") cout<<"\033[31m";
         else cout<<"\033[33m";
         //Información coloreada
         cout<<left
         <<setw(15)<<padron[i].getPlaca() 
         <<setw(10)<<padron[i].getCodigo() 
         <<setw(15)<<padron[i].getCapacidad() 
         <<setw(20)<<padron[i].getEstado()<<"\033[0m"<<endl;
        }
    }
    pausar();
}

void mostrarPadronOp(vector<Operador>& padron){
   clearScreen();
   cout<<"=== PADRON DE OPERADORES ==="<<endl<<endl;
   if (padron.empty()){
      cout<<"¡¡¡No hay operadores registrados!!!"<<endl;
   }
   else{
      cout<<left<<setw(10)<<"CODIGO"<<setw(10)<<"DNI"<<setw(40)<<"NOMBRE COMPLETO"<<setw(20)<<"ESTADO"<<endl;
      cout<<"--------------------------------------------------"<<endl;
      for (size_t i=0; i<padron.size(); i++){
         // Colores basicos ASCII  (Verde: "Disponible", Rojo: "En ruta", Amarillo: "en reposo")
         if(padron[i].getEstado()=="Disponible") cout<<"\033[32m";
         else if(padron[i].getEstado()=="En Ruta") cout<<"\033[31m";
         else cout<<"\033[33m";
         //Información coloreada
         cout<<left
         <<setw(10)<<padron[i].getCodigo() 
         <<setw(10)<<padron[i].getDNI() 
         <<setw(40)<<padron[i].getNombreCompleto() 
         <<setw(20)<<padron[i].getEstado()<<"\033[0m"<<endl;
        }
    }
    pausar();
}

/*void asignarViaje(vector<Unidad>& flota) {
   clearScreen();
   cout<<"=== MODULO DE OPERACIONES: ASIGNACION ==="<<endl<<endl;
   
   if (flota.empty()) {
      cout << "[!] No hay buses disponibles para asignar.\n";
      pausar();
      return;
   }

   int demanda;
   cout << "Ingrese la demanda de pasajeros para este contrato B2B: ";
   cin >> demanda;
   
   cout << "\nBuscando unidades idoneas (Capacidad >=" << demanda << " y Estado = Disponible)...\n";
   cout << "--------------------------------------------------\n";
   
   bool hayOpciones = false;
   vector<int> indicesValidos; // Para guardar la posicion de los buses aptos

   // Regla de Negocio: Validar Capacidad y Disponibilidad
   for (size_t i = 0; i < flota.size(); i++) {
      if (flota[i].getCapacidad() >= demanda && flota[i].getEstado() == "Disponible") {
         cout << "[" << i << "] Placa: " << flota[i].getPlaca() << " | Asientos: " << flota[i].getCapacidad() << endl;
         indicesValidos.push_back(i);
         hayOpciones = true;
      }
   }
   
   if (!hayOpciones) {
      cout << "\n[!] No se encontro ningun bus que cumpla las reglas de negocio.\n";
   } else {
      int seleccion;
      cout << "\nSeleccione el indice del bus a despachar: ";
      cin >> seleccion;
      
      // Validar que el indice seleccionado exista en nuestras opciones validas
      bool seleccionCorrecta = false;
      for(size_t i=0; i < indicesValidos.size(); i++){
         if(seleccion == indicesValidos[i]) seleccionCorrecta = true;
      }
      
      if (seleccionCorrecta) {
         flota[seleccion].setEstado("En Ruta");
         cout << "\n[OK] Viaje asignado. El bus " << flota[seleccion].getPlaca() << " esta ahora en ruta.\n";
      } else {
         cout << "\n[ERROR] Indice invalido o bus no apto.\n";
      }
   }
   pausar();
}*/
   
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
   cout<<"CODIGO DE OPERADOR (ej. 098): "; cin>>cod;
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
   
   // Carga Inicial
   cargarUNIDADES(padronUnid);
   cargarOPERADORES(padronOp);
   cargarSERVICIOS(historialServ);

   int opcion;
   do{
      clearScreen();
      printTitle("SISTEMA DE GESTION DE TRANSPORTE", 0);
      cout<<"1. Mostrar Padron General\n";
      cout<<"2. Mostrar Historial de Servicios\n";
      cout<<"3. Asignar Viaje (Operaciones)\n";
      cout<<"4. Registrar nueva unidad y operador\n";
      cout<<"0. Salir y Guardar\n";
      cout<<"---------------------------------------\n";
      cout<<"Seleccione una opcion: ";
      
      // Manejo robusto de errores si el usuario ingresa letras
      if (!(cin >> opcion)) {
         cin.clear(); 
         cin.ignore(10000, '\n'); 
         opcion = 0; 
      }

      switch (opcion) {
         case 1:{
            mostrarPadronUnid(padronUnid);
            cout<<endl;
            mostrarPadronOp(padronOp);
            break;
         } 
         case 2:{
            //mostrarHistorialServicios(historialServ);
            break;
         }
         case 3:{
            //asignarViaje(padronUnid, padronOp, historialServ);
            break;
         }
         case 4:{
            registrarUnidad(padronUnid);
            cout<<endl;
            registrarOperador(padronOp);
            break;
         }
         case 0:{
            cout << "\nIniciando rutina de apagado...\n";
            guardarDatos(padronUnid); // Guardado final
            break;
         }
         default:{
            cout << "\n[ERROR] Opcion no valida.\n";
            pausar();
            break;
         }
      }
   } while(opcion!=0);

   return 0;
}