//#define _CRT_SECURE_NO_WARNINGS
#ifdef _WIN32
#include <windows.h>
//#include <clocale>
#endif

#include <iostream>
#include <ctime>
#include <string>
#include <iomanip>
using namespace std;

//declaración de funciones
void menu();
string fill(int, const string &);
void title(const string &, int);
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

//void setDato(tipo &);

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	//setlocale(LC_ALL, "spanish");
	srand((unsigned int)time(NULL));
	string teclado{}; //variable{}, la inicializa con el valor por defecto
	char opc{};

	//bucle menú principal
	do {
		menu(); 
		getline(cin, teclado);
		opc='X';
		if (teclado.size()==1) opc=teclado[0]; //toma solo el primer caracter para evitar ejecuciones innecesarias
		switch (opc){
			case '1':{
				//operacion 1
            cout<<"\nCargando datos de SERVICIOS";
            loadingDots(3,150);
            cout<<"\r[OK] Datos de SERVICIOS cargados exitosamente."<<endl;
				break;
			}
			case '2':{
				//operacion 2
            title("HOLA", 0);
            title("MI PRIMER TÍTULO", 1);
            title("ALGORITMOS Y ESTRUCTURAS DE DATOS", 2);
            title("PROGRAMACIÓN EN C++ DESDE CERO", 3);
            title("ESTE ES UN TÍTULO UN POCO MÁS LARGO PARA PROBAR", 4);
				break;
			}
			case '3':{
				//operacion 3
            string texto{};
            title("TEXTO NORMAL", 3);
            cout<<"\033[0;30m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[0;31m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[0;32m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[0;33m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[0;34m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[0;35m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[0;36m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[0;37m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            title("TEXTO BRILLANTE", 3);
            cout<<"\033[90m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[91m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[92m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[93m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[94m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[95m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[96m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[97m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            title("TEXTO OPACO", 3);
            cout<<"\033[2;30m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[2;31m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[2;32m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[2;33m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[2;34m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[2;35m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[2;36m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[2;37m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            title("TEXTO BRILLANTE OPACO", 3); //si es posible jejeje
            cout<<"\033[2;90m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[2;91m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[2;92m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[2;93m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[2;94m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[2;95m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[2;96m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[2;97m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            title("TEXTO CURSIVA", 3);
            cout<<"\033[3;30m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[3;31m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[3;32m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[3;33m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[3;34m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[3;35m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[3;36m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[3;37m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            title("TEXTO SUBRAYADO", 3);
            cout<<"\033[4;30m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[4;31m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[4;32m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[4;33m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[4;34m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[4;35m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[4;36m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[4;37m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            title("TEXTO CON FONDO DE COLOR", 3);
            cout<<"\033[37;40m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[37;41m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[37;42m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[37;43m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[37;44m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[37;45m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[37;46m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[30;47m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            title("TEXTO CON FONDO DE COLOR BRILLANTE", 3);
            cout<<"\033[2;30;100m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[2;30;101m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[2;30;102m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[2;30;103m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[2;30;104m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[2;30;105m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[2;30;106m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            cout<<"\033[2;30;107m"<<"TEXTO de PrUeBa"<<"\033[0m\n";
            title("MENSAJES DE TEXTO CLÁSICO", 3);
            cout<<"\033[31m"<<"ALERTA"<<"\033[0m\n";
            cout<<"\033[30;41m"<<"ALERTA CRÍTICA"<<"\033[0m\n";
            cout<<"\033[32m"<<"CONFIRMACIÓN"<<"\033[0m\n";
            cout<<"\033[30;42m"<<"CONFIRMACIÓN ALTERNATIVA"<<"\033[0m\n";
            cout<<"\033[33m"<<"ADVERTENCIA"<<"\033[0m\n";
            cout<<"\033[30;43m"<<"ADVERTENCIA ALTERNATIVA"<<"\033[0m\n";
            cout<<"\033[4;34m"<<"INFORMACIÓN / LINK"<<"\033[0m\n";
            cout<<"\033[7m"<<"INVERSION CLÁSICA"<<"\033[0m\n";
            cout<<"\033[97;44m"<<"SELECCIÓN"<<"\033[0m\n";
            cout<<"ESCRIBE ALGO: \033[7m"; getline(cin, texto);
            cout<<"\033[0m";
				break;
			}
         case '4':{
            // --- CAT 0: Título Principal del Programa (Hero Header) ---
            // Fondo azul fuerte, letras blancas brillantes, con un bloque de acento.
            cout << "\n\033[44;1;97m  ██  SISTEMA DE GESTIÓN DE BUSES V2.0  ██  \033[0m\n\n";

            // --- CAT 1: Título de Módulo / Sección ---
            // El estilo "Badge" (escarapela) que te gustó antes.
            cout << "\n\033[1;36m ▌ \033[30;46m PROGRAMAR NUEVO SERVICIO \033[0m\n\n";

            // --- CAT 2: Título de Formulario / Sub-sección ---
            // Un bloque lateral elegante, texto en blanco brillante y una sutil línea gris de base.
            cout << "\n\033[1;34m ▍ \033[1;97mDatos del Operador\033[0m\n";
            cout << "\033[90m └──────────────────────────────────────\033[0m\n";

            // --- CAT 3: Separador de bloque ---
            // Se acabaron los "====". Usamos una línea continua muy tenue y el texto coloreado.
            cout << "\n\033[90m ────── \033[1;35mResumen de Ruta\033[90m ────── \033[0m\n\n";

            // --- CAT 4: Título de Lista / Tabla ---
            // Super minimalista, gris tenue, usa una viñeta moderna de flecha.
            cout << "\n\033[1;90m › Servicios Pendientes \033[0m\n\n";

            // --- CAT 0: Título Principal del Programa (Hero Header) ---
            // Dos líneas gruesas enmarcando el texto, sin cerrar los lados para que respire.
            cout << "\n\033[38;5;63m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m\n";
            cout << "\033[1;97m               MENU PRINCIPAL               \033[0m\n";
            cout << "\033[38;5;63m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m\n\n";

            // --- CAT 1: Título de Módulo / Sección ---
            // Un borde superior flotante con esquinas redondeadas.
            cout << "\n\033[36m╭───────── \033[1;97mMODULO DE RUTAS\033[36m ─────────╮\033[0m\n\n";

            // --- CAT 2: Título de Formulario / Sub-sección ---
            // Una flecha de continuidad que nace del borde izquierdo.
            cout << "\n\033[34m ╰─► \033[1;97mDetalles del Pasajero\033[0m\n";

            // --- CAT 3: Separador de bloque ---
            // Un rombo como viñeta central.
            cout << "\n\033[35m ◈ \033[1;97mInformación Adicional\033[0m\n\n";

            // --- CAT 4: Título de Lista / Tabla ---
            // Línea punteada sutil.
            cout << "\n\033[90m ┄┄ \033[37mHistorial de Viajes\033[90m ┄┄\033[0m\n";
            break;
         }
			case '0':{
				//salida del programa
				cout<<"\nSaliendo del programa...";
				Sleep(250); //pausa dramatica
				break;
			}
			default:{
				cout<<"\nOpcion no valida. Intente de nuevo...";
				break;
			}
		}
		cout<<endl;
		system("pause");
	} while (opc!='0');

	//aplicar consistencia getDato(valor);
	
	cout<<"\nFIN DEL PROGRAMA\n";
	system("pause");
	return 0;
}

//Función menú
void menu(){
	system("cls");
	title("MENU DE OPCIONES", 0);
	cout<<"├╴[1] Ejercicio 1"<<endl;
	cout<<"├╴[2] Ejercicio 2"<<endl;
	cout<<"├╴[3] Ejercicio 3"<<endl;
   cout<<"├╴[4] Ejercicio 4"<<endl;
	cout<<"└╴[0] Salir"<<endl;
	cout<<"\n►►Ingresar opcion -→ ";	
}

//Función de rellenado
string fill(int lenght, const string &symbol){
	string relleno{};
	for (int i=1; i<=lenght; i++) relleno+=symbol;
	return relleno;
}

//Función de titulos
void title(const string &title, int cat){
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
				anchoBorde=tamReal+10;
				string relleno(2, ' ');
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

//Funcion de consistencia
/*void setDato(tipo &dato){
	tipo d;
	bool ver_dato=false;
	do{
		cout<<"Ingresar el dato:\t"; cin>>d;
		if (cin.fail()){
			cin.clear();
			cin.ignore(10000,'\n');
			cout<<"Dato no válido. Verifique el dato e ingréselo de nuevo."<<endl;
			system("pause");
		}
		else if (condición_de_validez){
			d=dato;
			ver_dato=true;
		}
		else{
			cout<<"No se puede ingresar 'valores no válidos'. Compruebe el dato e ingréselo de nuevo."<<endl;
		}
	} while (ver_dato==false);
}*/