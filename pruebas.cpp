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
void printTitle(const string &, int);
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
            printTitle("HOLA", 0);
            printTitle("MI PRIMER TÍTULO", 1);
            printTitle("ALGORITMOS Y ESTRUCTURAS DE DATOS", 2);
            printTitle("PROGRAMACIÓN EN C++ DESDE CERO", 3);
            printTitle("ESTE ES UN TÍTULO UN POCO MÁS LARGO PARA PROBAR", 4);
				break;
			}
			case '3':{
				//operacion 3
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
	printTitle("MENU DE OPCIONES", 0);
	cout<<"├╴[1] Ejercicio 1"<<endl;
	cout<<"├╴[2] Ejercicio 2"<<endl;
	cout<<"├╴[3] Ejercicio 3"<<endl;
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