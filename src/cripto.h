/*
 * cripto.h
 *
 *  Autor:Víctor Valdés Cobos vvaldesc@alumnos.unex.es
 *  Fecha: 29 Abril 2022
 */

#ifndef __CRIPTO_H
#define __CRIPTO_H

#include <iostream>
#include <fstream>
#include <string>

#include "bstree.h"
#include "mensaje.h"
#include "lpi.h"


using namespace std;


class Cripto {

	int passwd;
	BSTree <KeyValue<string,Mensaje*>> *abb;
	BSTree <KeyValue<char,char>> *abbC;
	LPI<Mensaje*> *lpi;


private:

	// PRE  = { }
	// POST = { }
	// DESC:  Interpreta los datos del archivo "mensajes.csv" para su posterior
	//	inserción en el sistema.
	// COMPL: O(n)
	void cargarMensaje();

	// PRE  = { }
	// POST = { }
	// DESC:  Recorre el abb en preorden y devuelve el mensaje con el id indicado.
	// COMPL: O(log n)
	bool buscar(BSTree<KeyValue<string,Mensaje*>> *abb,string id,Mensaje *&m);

	// PRE  = { }
	// POST = { }
	// DESC:  Recorre el abb en preorden hasta encontrar la letra original y devuelve la letra codificada.
	// COMPL: O(log n)
	bool buscarCodificada(BSTree<KeyValue<char,char>> *abb,char sO,char &sC);

	// PRE  = { }
	// POST = { }
	// DESC:  Recorre el abb en preorden y devuelve la letra decodificada.
	// COMPL: O(n)
	bool buscarDecodificada(BSTree<KeyValue<char,char>> *abb,char sC,char &sO);

	// PRE  = { }
	// POST = { }
	// DESC:  Mediante un recorrido inorden, Si {autor == ""} muestra
	//	todos los mensajes por pantalla, mientras que si no, muestra los mensajes del
	//	indicado y los inserta en una lista LPI.
	// COMPL: O(n)
	void mostrarMensajes(BSTree<KeyValue<string,Mensaje*>> *abb,string autor);

	// PRE  = { }
	// POST = { }
	// DESC:  Mediante un recorrido inorden, escribe en un fichero pasado por parámetro
	//	todos los datos actuales del programa.
	// COMPL: O(n)
	void escribirFichero(BSTree<KeyValue<string,Mensaje*>> *abb,ofstream &fichero);

	// PRE  = { }
	// POST = { }
	// DESC:  Inserta un mensaje en la lista LPI.
	// COMPL: O(1)
	void insertarEnLista(Mensaje *m);

	// PRE  = { }
	// POST = { }
	// DESC:  Muestra por pantalla los datos de la lista LPI.
	// COMPL: O(n)
	void mostrarLista();

	// PRE  = { }
	// POST = { }
	// DESC:  Borra un mensaje del sistema.
	// COMPL: O(n)
	void borrarMensaje(BSTree<KeyValue<string,Mensaje*>> *abb,string id);


public:

	// PRE  = { }
	// POST = { }
	// DESC:  Inserta un mensaje en la estructura del arbol.
	// COMPL: O(log n)
	void insertarMensaje(string id,string mensaje,string autor);

	// PRE  = { }
	// POST = { }
	// DESC:  Crea un fichero y escribe los datos.
	// COMPL: O(n)
	void escribirFichero();

	// PRE  = {  }
	// POST = {  }
	// DESC:  Busca un mensaje mediante su id y devuelve sus datos.
	// COMPL: O(log n)
	bool buscar(string id,Mensaje *&m);

	// PRE  = { }
	// POST = { }
	// DESC:  Muestra todos los mensajes del autor, los inserta en la lista
	//			y los mustra por pantalla.
	// COMPL: O(log n)
	void mostrarMensajes(string autor);

	// PRE  = { }
	// POST = { }
	// DESC:  Muestra todos los mensajes por pantalla.
	// COMPL: O(n)
	void mostrarMensajes();

	// PRE  = { }
	// POST = { }
	// DESC:  Codifica un mensaje por su id.
	// COMPL: O(log n)
	void codificar(string id);

	// PRE  = { }
	// POST = { }
	// DESC:  Codifica un mensaje por su id.
	// COMPL: O(n)
	void decodificar(string id);

	// PRE  = { }
	// POST = { }
	// DESC:  Borra un mensaje.
	// COMPL: O(log n)
	void borrarMensaje(string id);

	// PRE  = { }
	// POST = { this->passwd = passwd % 26, if (passwd==0) then 1 }
	// DESC:  Establece una contraseña y la guarda codificada. En realidad, es un
	//        desplazamiento de cada una de las 26 letras entre 1 y 25.
	// COMPL:
	void cambiarContra(int passwd);


	// PRE  = { }
	// POST = { passwd = 0 }
	// DESC:  Carga datos de mensajes en el sistema.
	// COMPL:
	Cripto      ();

	// PRE  = { }
	// POST = { passwd = 0 }
	// DESC:  Destructor de Cripto, borra todas las estructuras del sistema.
	// COMPL:
	~ Cripto      ();

};


#endif /* __CRIPTO_H */
