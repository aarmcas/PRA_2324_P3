#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <iostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

using namespace std;

template <typename V>
class BSTreeDict: public Dict<V> {

    private:

        BSTree<TableEntry<V>>* tree; // ABB con elementos de tipo TableEntry<V> para gestionar los elementos de un diccionario.

    public:

        BSTreeDict(){
		// Constructor. Crea un ABB vacío con memoria dinámica.
	
			tree = new BSTree<TableEntry<V>>;
		}

		~BSTreeDict(){
		// Método destructor. Se encargará de liberar la memoria dinámica ocupada por el ABB tree.
	
			delete tree;
		}

		friend ostream& operator<<(ostream &out, const BSTreeDict<V> &bs){
		// Sobrecarga global del operador << para imprimir el contenido del Diccionario por pantalla.
	
			out << *(bs.tree);  // Llamamos a la sobrecarga global del operador << para imprimir una instancia de ListLinked<T> por pantalla.

            return out;
		}

		V operator[](string key){
		//Sobrecarga del operador[]. Actúa como interfaz al método de interfaz heredado search(std::string key).
	
			TableEntry<V> valor(key);   // Creamos una variable de tipo TableEntry<V>, donde almacenamos la clave sin valor.

            TableEntry<V> result = tree->search(valor);   // Buscamos el valor que se guarda en la posición de la clave (Key).

            return result.value;    // Retornamos el resultado
		}
	
		void insert(string key, V value) override {
		// Inserta el par key->value en el diccionario. Lanza una excepción std::runtime_error si key ya existe en el diccionario.
			TableEntry<V> valor(key, value);  // Creamos una variable de tipo TableEntry<V>, donde almacenamos los pares clave→valor

            tree->insert(valor);
		}

		V search(string key) override {
		// Busca el valor correspondiente a key. Devuelve el valor value asociado si key está en el diccionario. Si no se encuentra, lanza una excepción std::runtime_error.
	
			TableEntry<V> valor(key);   // Creamos una variable de tipo TableEntry<V>, donde almacenamos la clave sin valor.

            TableEntry<V> result = tree->search(valor);   // Buscamos el valor que se guarda en la posición de la clave (Key).

            return result.value;
		}

		V remove(string key) override {
		// Elimina el par key->value si se encuentra en el diccionario. Si no se encuentra, lanza una excepción std::runtime_error.
	
			 TableEntry<V> valor(key);   // Creamos una variable de tipo TableEntry<V>, donde almacenamos la clave sin valor.

            TableEntry<V> result = tree->search(valor);   // Buscamos el valor que se guarda en la posición de la clave (Key).

            tree->remove(valor);   // Eliminamos el valor que se guarda en la posición de la clave (Key).

            return result.value;
		}

		int entries() override{
		// Devuelve el número de elementos que tiene el Diccionario.
	
			return tree -> size();
		}

};

#endif
