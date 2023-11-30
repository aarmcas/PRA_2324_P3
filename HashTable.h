#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <iostream>
#include <stdexcept>
#include <string>
#include "Dict.h"
#include "TableEntry.h"

#include "ListLinked.h"

using namespace std;

template <typename V>
class HashTable: public Dict<V> {

    private:
        int n;
	int max;
	ListLinked<TableEntry<V>>* table;

	int h(string key){
		int sum = 0;
		int c;
		cin >> key;
		int longitud = key.length();
    		for (int i = 0; i < longitud; i++) {
			c = key[i];
			c = getchar();
			sum += c;	
		}
		return sum % max;
	}


    public:
	void insert(std::string key, V value) override {
		int index = h(key);  
		// Verificar si la clave ya existe en la cubeta
   	 	Node<TableEntry<V>>* aux = table[index].getHead();
    		while (aux) {
        		if (aux-> data.key == key) {
            			throw std::runtime_error("Clave ya existe en el diccionario");
        		}
			aux = aux -> next;
    		}

    		// La clave no existe, insertar el par key->value en la cubeta
    		aux.TableEntry(key, value);
    		n++;  // Incrementar el contador de elementos
	}

	V search(std::string key) override {
		int index = h(key);  
                Node<TableEntry<V>>* aux = table[index].getHead();
                while (aux) {
                        if (aux-> data.key == key) {
				return aux -> data.value;
                        }
                        aux = aux -> next;
                }
                throw std::runtime_error("Clave no encontrada en el diccionario");
	}

	V remove(std::string key) override {
		int index = h(key);
                Node<TableEntry<V>>* aux = table[index].getHead();
                while (aux) {
                        if (aux-> data.key == key) {
                                while(aux != nullptr){
					Node<TableEntry<V>>* t = aux -> next;
					delete aux;
					aux = t;
				}
                        }
                        aux = aux -> next;
                }
	}

	int entries() override{
		return n;
	}

        HashTable(int size){
		n = 0;
		max = size;
		table = new ListLinked<TableEntry<V>>[size];
	}
	
	~HashTable(){
		delete[] table;
	}

	int capacity(){
		return max;
	}

	friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th){
		for (int i = 0; i < th.max; ++i) {
        		out << "Cubeta " << i << ": ";
        		Node<TableEntry<V>>* aux = th.table[i].getHead();
        		while (aux) {
            			out << aux -> data << " ";
            			aux = aux -> next;
        		}
			out << std::endl;
    		}
		return out;
	}

	V operator[](std::string key){
		int index = h(key);  // Obtener la posición (cubeta) en la tabla hash
		// Buscar la clave en la lista de la cubeta correspondiente
		Node<TableEntry<V>>* aux = table[index].getHead();
		while (aux) {
        		if (aux -> data == key) {
            			// La clave fue encontrada, devolver el valor asociado
            			return aux -> data.value;
        		}
        		aux = aux -> next;
    		}
		// Si la clave no fue encontrada, lanzar una excepción
    		throw std::runtime_error("Clave no encontrada en el diccionario");
	}
        
};

#endif
