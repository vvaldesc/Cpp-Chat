//
//  mensaje.cpp
//
//  Autor: Víctor Valdés Cobos vvaldesc@alumnos.unex.es
//  Fecha: 29 Abril 2022



#include <iostream>
#include <string>

#include "mensaje.h"

using namespace std;

string Mensaje::getId() {
	return this->id;
}

string Mensaje::getMensaje() {
	return this->mensaje;

}

string Mensaje::getAutor() {
	return this->autor;

}

void Mensaje::setId(string id) {
	this->id=id;
}

void Mensaje::setMensaje(string mensaje) {
	this->mensaje=mensaje;
}

void Mensaje::setAutor(string autor) {
	this->autor=autor;
}

Mensaje::Mensaje() {
	this->id="";
	this->mensaje="";
	this->autor="";
}

Mensaje::Mensaje(string id, string mensaje, string autor) {
	this->id=id;
	this->mensaje=mensaje;
	this->autor=autor;
}

void Mensaje::mostrar() {
	cout << getId() << "#" << getMensaje() << "#" << getAutor() << endl;
}
