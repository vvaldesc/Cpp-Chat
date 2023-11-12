/*
 * cripto.cpp
 *
 *  Autor:Víctor Valdés Cobos vvaldesc@alumnos.unex.es
 *  Fecha: 29 Abril 2022
 */

#include <iostream>
#include <fstream>
#include <string>


#include "cripto.h"




using namespace std;

void Cripto::cargarMensaje() {
	ifstream ifs;
	string id,mensaje,autor;
	ifs.open("mensajes.csv");
	if(ifs.is_open()){
		while(!ifs.eof()){
			getline(ifs,id,'#');
			if(!ifs.eof()){
				getline(ifs,mensaje,'#');
				getline(ifs,autor);
				insertarMensaje(id,mensaje,autor);
			}

		}
		ifs.close();
	}
	else{
		cout << "el fichero no se ha abierto." << endl;
	}
}


void Cripto::borrarMensaje(BSTree<KeyValue<string, Mensaje*> > *abb,string id) {
	BSTree<KeyValue<string,Mensaje*>> *aux;

	if(abb->root().key()==id){
		delete abb->root().value();
		abb->remove(id);
	}

	if (! abb->empty()) {

		aux = abb->left();
		if (aux != nullptr) {
			borrarMensaje(aux,id);
		}

		aux = abb->right();
		if (aux != nullptr) {
			borrarMensaje(aux,id);
		}

	}
}

void Cripto::insertarEnLista(Mensaje *m) {
	lpi->moverInicio();
	lpi->insertar(m);
}

void Cripto::mostrarLista() {
	Mensaje *m=new Mensaje();
	lpi->moverInicio();
	while(!lpi->enFin()){
		lpi->consultar(m);
		m->mostrar();
		lpi->avanzar();
	}
}

void Cripto::escribirFichero(BSTree<KeyValue<string, Mensaje*>> *abb, ofstream &fichero) {
    if (fichero.is_open()) {
        BSTree<KeyValue<string, Mensaje*>> *aux;

        if (!abb->empty()) {
            aux = abb->left();
            if (aux != nullptr) {
                escribirFichero(aux, fichero);
            }

            fichero << abb->root().value()->getId() << "#" << abb->root().value()->getMensaje() << "#" << abb->root().value()->getAutor() << endl;

            aux = abb->right();
            if (aux != nullptr) {
                escribirFichero(aux, fichero);
            }
        }
    }
}


bool Cripto::buscarDecodificada(BSTree<KeyValue<char, char> > *abb, char sC,char &sO) {

	bool bandera=false;
	BSTree<KeyValue<char,char>> *aux;
	if(abb->root().value()==sC){
		bandera=true;
		sO=abb->root().key();
	}
	else{

		aux = abb->left();
		if (aux != nullptr) {
			bandera=buscarDecodificada(aux,sC,sO);
		}
		if(!bandera){
			aux = abb->right();
			if (aux != nullptr) {
				bandera=buscarDecodificada(aux,sC,sO);
			}

		}
	}

	return bandera;
}

bool Cripto::buscarCodificada(BSTree<KeyValue<char,char>> *abb,char sO,char &sC) {

	bool bandera=false;
	BSTree<KeyValue<char,char>> *aux;
	if(abb->root().key()==sO){
		bandera=true;
		sC=abb->root().value();
	}
	else{
		if(abb->root().key()>sO){
			aux = abb->left();
			if (aux != nullptr) {
				bandera=buscarCodificada(aux,sO,sC);
			}
		}
		else{
			if(!bandera){

				aux = abb->right();
				if (aux != nullptr) {
					bandera=buscarCodificada(aux,sO,sC);
				}
			}
		}
	}

	return bandera;
}

void Cripto::mostrarMensajes(BSTree<KeyValue<string, Mensaje*> > *abb,string autor) {


	BSTree<KeyValue<string,Mensaje*>> *aux;

	if (! abb->empty()) {


		aux = abb->left();
		if (aux != nullptr) {
			mostrarMensajes(aux,autor);
		}


		if(autor!=""){
			if(abb->root().value()->getAutor()==autor){
				insertarEnLista(abb->root().value());
			}
		}
		else{
			abb->root().value()->mostrar();
		}


		aux = abb->right();
		if (aux != nullptr) {
			mostrarMensajes(aux,autor);
		}

	}


}

bool Cripto::buscar(BSTree<KeyValue<string, Mensaje*>> *abb, string id,
		Mensaje *&m) {
	bool enc=false;
	BSTree<KeyValue<string,Mensaje*>> *aux;

	if(abb->root().key()==id){
		enc=true;
		m=abb->root().value();
	}
	else  {
		if(abb->root().key()>id){
			aux = abb->left();
			if (aux != nullptr) {
				enc=buscar(aux,id,m);
			}
		}
		else{
			aux = abb->right();
			if (aux != nullptr) {
				enc=buscar(aux,id,m);
			}

		}
	}
	return enc;
}



void Cripto::insertarMensaje(string id,string mensaje,string autor) {
	Mensaje *m=new Mensaje(id,mensaje,autor);
	KeyValue<string,Mensaje*>kv(id,m);
	abb->insert(kv);
}

void Cripto::borrarMensaje(string id) {
	if(!abb->empty()){
		borrarMensaje(abb,id);
	}
}

void Cripto::mostrarMensajes(string autor) {
	//Mensaje *m=new Mensaje();
	//string id=m->getId();
	//KeyValue<string,Mensaje*&>kv(id,m);
	if(!abb->empty()){
		lpi = new LPI <Mensaje*>;
		mostrarMensajes(abb,autor);
	}
	mostrarLista();
}

void Cripto::mostrarMensajes() {
	if(!abb->empty()){
		mostrarMensajes(abb,"");
	}
}

void Cripto::escribirFichero() {
	ofstream fichero;
	string filename("mensajes.csv");
	fichero.open("mensajes.csv");
	if(!abb->empty() and fichero.is_open()){
		escribirFichero(abb,fichero);
	}
	fichero.close();
}

void Cripto::cambiarContra (int passwd) {

	// 1. Si cambiamos la contraseña, tenemos que rehacer el árbol de coddificación.
	delete abbC;
	abbC = new 	BSTree <KeyValue<char,char>>;
	// TODO: eliminar y crear un nuevo árbol

	// 2. Cambiar la contraseña
	this->passwd = passwd % 26;
	if (this->passwd == 0) { // No permitimos que sea 0.
		this->passwd++;
	}

	// Letras al árbol.
	// El orden de las letras en el vector hace que el árbol resultante
	// este equilibrado:
	char c_origen  [26] = {'m', 'g', 's', 'd', 'j', 'p', 'w', 'b', 'e',
			'h', 'k', 'n', 'r', 'u', 'y', 'a', 'c', 'f',
			'i', 'l', 'o', 'q', 't', 'v', 'x', 'z' };

	for (int i = 0; i < 26; i++) {

		char letraO, letraS;

		letraO = c_origen[i];
		letraS = (((int(letraO) - 97) + this->passwd) % 26) + 97;

		// TODO: crear KeyValue e insertar en el árbol.
		KeyValue<char,char> kv(letraO,letraS);
		abbC->insert(kv);
		//mostrar profundidad del arbol

	}

}

void Cripto::decodificar(string id) {
	if(0<this->passwd and this->passwd<10000){
	Mensaje *m=new Mensaje();
	string texto;char sO;
	if(buscar(id,m)){
		texto=m->getMensaje();
		for(int i=0;i<texto.length();i++){
			if(buscarDecodificada(this->abbC,texto[i],sO)){
				texto[i]=sO;
			}
		}
		m->setMensaje(texto);
	}
}
}

void Cripto::codificar(string id) {
	if(0<this->passwd and this->passwd<10000){
	Mensaje *m=new Mensaje();
	string texto;char sC;
	if(buscar(id,m)){
		texto=m->getMensaje();
		for(int i=0;i<texto.length();i++){
			if(buscarCodificada(this->abbC,texto[i],sC)){
				texto[i]=sC;
			}
		}
		m->setMensaje(texto);
	}
}
}

bool Cripto::buscar(string id,Mensaje *&m){
	bool bandera=false;
	if(!abb->empty()){
		bandera=buscar(abb,id,m);
	}
	return bandera;
}

Cripto::Cripto () {

	passwd=0;
	abb = new BSTree <KeyValue<string,Mensaje*>>;
	abbC = nullptr;
	lpi = nullptr;
	cargarMensaje();
	// TODO

}

Cripto::~Cripto() {
	if(this->abb!=nullptr){
		KeyValue<string, Mensaje*>kv;
		while(!this->abb->empty()){
			kv=this->abb->root();
			this->abb->remove(this->abb->root());
			delete kv.value();
		}
		delete this->abb;
	}
	if(this->abbC!=nullptr){
		while(!this->abbC->empty()){
			this->abbC->remove(this->abbC->root());
		}
		delete this->abbC;
	}
	if(this->lpi!=nullptr){
		this->lpi->moverInicio();
		while(lpi->vacia()){
			lpi->borrar();
		}
		delete this->lpi;
	}
}
