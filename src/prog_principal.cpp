/*
 * prog_principal.cpp
 *
//  Autor: Víctor Valdés Cobos vvaldesc@alumnos.unex.es
//  Fecha: 29 Abril 2022
 */

#include <iostream>
#include <fstream>
#include <string>

#include "cripto.h"

using namespace std;

int opcion;




// Muestra el menu por pantalla y devuelve una opcion elegida.
int menu() {





	do {
		cout << endl;
		cout << "______________ MENU PRINCIPAL ______________"<< endl << endl;

	  cout << "     1. Insertar mensaje                   " << endl;
      cout << "     2. Borrar mensaje                     " << endl;
      cout << "     3. Buscar mensaje y mostrar           " << endl;
      cout << "     4. Mostrar todos                      " << endl;
      cout << "     5. Mensajes por autor                 " << endl;
      cout << "                                           " << endl;
      cout << "     6. Cambiar PIN                        " << endl;
      cout << "     7. Codificar un mensaje               " << endl;
      cout << "     8. Decodificar un mensaje             " << endl;
		cout <<                                                  endl;
		cout << "     0. Finalizar.                         " << endl;
		cout << "                        Opcion:  ";
		cin >> opcion;
		cin.ignore();

	} while ((opcion < 0) || (opcion > 8));

	return opcion;
}


// Programa principal: 
int main() {
	int pin=0;
	string id;string mensaje;string autor;
	bool fin=false;
	Cripto *cripto = new Cripto();

   
	do {
		opcion = menu();

		switch (opcion) {
			case 1:
				cout << "inserta id"<<endl;
				cin >> id;
				cout << "inserta mensaje"<<endl;
				cin.ignore();
				getline(cin,mensaje);
				cout << "inserta autor"<<endl;
				cin >> autor;
				cripto->insertarMensaje(id, mensaje, autor);
				break;
			case 2:
				cout << "inserta id"<<endl;
				cin >> id;
				cripto->borrarMensaje(id);
				break;
			case 3:
			{
				Mensaje *maux = new Mensaje();
				cout << "inserta id"<<endl;
				cin >> id;
				cripto->buscar(id, maux);
				cout << maux->getMensaje() << endl;
			}
				break;
			case 4:
				cripto->mostrarMensajes();
				break;
			case 5:
				cout << "inserta autor"<<endl;
				cin >> autor;
				cripto->mostrarMensajes(autor);
				break;
			case 6:
				cout<<"introduce PIN"<<endl;
				cin>>pin;
				cripto->cambiarContra(pin);
				break;
			case 7:
				cout<<"introduce id"<<endl;
				cin>>id;
				cripto->codificar(id);
				break;
			case 8:
				cout<<"introduce id"<<endl;
				cin>>id;
				cripto->decodificar(id);
				break;
			case 0:
				fin = true;
				cripto->escribirFichero();
            delete cripto;
				break;

			default:
				break;

		}
		
	} while (!fin);

	return 0;
}


