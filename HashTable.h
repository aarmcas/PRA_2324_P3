#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <iostream>
#include <stdexcept>
#include <string>
#include "Dict.h"
#include "TableEntry.h"

#include "../../Pr1/PRA_2324_P1/ListLinked.h"

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
	void insert(string key, V value) override {
		int Key_value = h(key);

		TableEntry<V> valor(key, value);

		if (table[Key_value].search(valor) == -1){
                throw runtime_error("Clave no encontrada en el diccionario");
		}

		table[Key_value].prepend(valor);

		n++;
	}

	V search(string key) override {
		int Key_value = h(key);

		TableEntry<V> valor(key);

		if (table[Key_value].search(valor) == -1){
                throw runtime_error("Clave no encontrada en el diccionario");
		}

		int Pos_Key = table[Key_value].search(valor);

		TableEntry<V> result = table[Key_value].get(Pos_Key);

		return result.value;
	}

	V remove(string key) override {
		int Key_value = h(key);

		TableEntry<V> valor(key);

		if (table[Key_value].search(valor) == -1){
                throw runtime_error("Clave no encontrada en el diccionario");
		}
		n--;

		int Pos_Key = table[Key_value].search(valor);

		TableEntry<V> result = table[Key_value].remove(Pos_Key);

		return result.value;
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

	friend ostream& operator<<(ostream &out, const HashTable<V> &th){

		out << "===================================" << endl;
		out << "HashTable [entries: " << th.n << ", capacity: " << th.max << "]" << endl;
		out << "===================================" << endl << endl;

		for (int i = 0; i < th.max; ++i) {
			out << "== Cubeta " << i << "==" << endl;
			out << th.table[i] << endl << endl;
    		}
		return out;
	}

	V operator[](string key){

		int Key_value = h(key);

		TableEntry<V> value(key);

		if (table[Key_value].search(value) == -1){
                throw runtime_error("Clave no encontrada en el diccionario");
		}

		int Pos_Key = table[Key_value].search(value);

		TableEntry<V> result = table[Key_value].get(Pos_Key);
		return result.value;
	}
};

#endif
