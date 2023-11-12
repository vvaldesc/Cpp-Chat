//
//  mensaje.h
//
//  Autor: Víctor Valdés Cobos vvaldesc@alumnos.unex.es
//  Fecha: 29 Abril 2022


#ifndef MENSAJE_H
#define MENSAJE_H


#include <string>
using namespace std;


class Mensaje {
	string id;
	string mensaje;
	string autor;


public:


// PRE  = { }
// POST = { id="";mensaje="";mensaje="" }
// DESC:  Inicializa la estructura mensaje.
// COMPL: O(1)
Mensaje();

// PRE  = { }
// POST = { }
// DESC:  Inicializa la estructura mensaje con los datos pasados por parámetro.
// COMPL: O(1)
Mensaje(string id,string mensaje,string autor);

// PRE  = { }
// POST = { }
// DESC:  Devuelve el id.
// COMPL: O(1)
string getId();

// PRE  = { }
// POST = { }
// DESC:  Devuelve el mensaje.
// COMPL: O(1)
string getMensaje();

// PRE  = { }
// POST = { }
// DESC:  Devuelve el autor.
// COMPL: O(1)
string getAutor();


// PRE  = { }
// POST = { }
// DESC:  Pone valor a id.
// COMPL: O(1)
void setId(string id);

// PRE  = { }
// POST = { }
// DESC:  Pone valor a mensaje.
// COMPL: O(1)
void setMensaje(string mensaje);

// PRE  = { }
// POST = { }
// DESC:  Pone valor a autor.
// COMPL: O(1)
void setAutor(string autor);


// PRE  = { }
// POST = { }
// DESC:  Muestra la estructura mensaje.
// COMPL: O(1)
void mostrar();



};


#endif /* MENSAJE_H */
