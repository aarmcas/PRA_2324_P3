#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

using namespace std;

template <typename T> 
class BSTree {
    private:
     	int nelem; // Número de elementos almacenados en el ABB. 
		BSNode<T>* root; // Nodo raíz del ABB.
    
		BSNode<T>* search(BSNode<T>* n, T e) const{

		// Método recursivo para la búsqueda elementos en el ABB. Busca y devuelve el elemento e de tipo T si se encuentra en el (sub-)árbol cuya raíz es n, de lo contrario lanza una std::runtime_error. Ver pseudocódigo abajo.
	
			if(n == nullptr){
				throw runtime_error("Elemento no encontrado");
			}
			else if(n -> elem < e){
				return search(n -> right, e);
			}
			else if(n -> elem > e){
				return search(n -> left, e);
			}
			else{
				return n;
			}
		}

		BSNode<T>* insert(BSNode<T>* n, T e){
		//Método recursivo para la inserción ordenada de elementos. Inserta el elemento e de tipo T de manera ordenada en el (sub-)árbol cuya raíz es n. Devuelve el nodo que encabeza dicho (sub-)árbol modificado. Si el elemento e ya existe, lanza un std::runtime_error.
	
			if(n == nullptr){
				nelem ++;
				return new BSNode<T>(e);
			}
			else if(n -> elem == e){
				throw runtime_error("Elemento duplicado");
			}
			else if(n -> elem < e){
				n -> right = insert(n -> right, e);
			}
			else{
				n -> left = insert(n -> left, e);
			}
			return n;
		}

		void print_inorder(std::ostream &out, BSNode<T>* n) const{
		// Recorrido inorden o simétrico del (sub-)árbol cuya raíz es n para mostrar a través de out los elementos ordenados de menor a mayor.
	
			if(n != nullptr){
				print_inorder(out, n -> left);
				out << n -> elem << " ";
				print_inorder(out, n -> right);
			}
		}

		BSNode<T>* remove(BSNode<T>* n, T e){
		// Método recursivo para la eliminación de elementos. Elimina el elemento e del (sub-)árbol cuya raíz es n. Devuelve el nodo que encabeza dicho (sub-)árbol modificado. En caso de eliminar un nodo con dos sucesores (izquierdo y derecho), aplicará la politica de reemplazo por el elemento máximo del subárbol izquierdo. Para ello, se apoyará en los métodos privados auxiliares max() y remove_max(). Si el elemento e no existe, lanza un std::runtime_error.
	
			if(n == nullptr){
				throw runtime_error("Elemento no encontrado");
			}
			else if(n -> elem < e){
				n -> right = remove(n -> right, e);
			}
			else if(n -> elem > e){
				n -> left = remove(n -> left, e);
			}
			else{
				if(n -> left != nullptr && n -> right != nullptr){ // 2 desc.
					n -> elem = max(n -> left);
					n -> left = remove_max(n -> left);
				}
				else{ // 1 ó 0 descendientes
					n = (n -> left != nullptr)? n -> left: n -> right;
				}
			}
			return n;
		}

		T max(BSNode<T>* n) const{
		// Método recursivo que devuelve el elemento de máximo valor contenido en el (sub-)árbol cuya raíz es n.
	
			if(n == nullptr){
				throw runtime_error("Elemento no encontrado");
    		}
			else if (n -> right != nullptr){
        		return max(n -> right);
    		}
			else{
        		return n -> elem;
			}
		}

		BSNode<T>* remove_max(BSNode<T>* n){
		// Método recursivo que elimina el elemento de máximo valor contenido en el (sub-)árbol cuya raíz es n.
	
			if(n -> right == nullptr){
				return n -> left;
			}else{
				n -> right = remove_max(n -> right);
				return n;
			}
		}

		void delete_cascade(BSNode<T>* n){
		// Método recursivo para liberación de la memoria dinámica ocupada por los objetos de tipo BSNode<T> que conforman el (sub-)árbol cuya raíz es n.
	
			if(n != nullptr){
				delete_cascade(n->right);
				delete_cascade(n->left);
				delete n;
			}
		}

    public:

        BSTree(){
		// Método constructor. Crea un ABB vacío.
			this->nelem = 0;
			this->root = nullptr;
		}

		int size() const{
		// Devuelve el número de elementos nelem del ABB.
			return nelem;
		}

		T search(T e) const{

		//Busca y devuelve el elemento  e de tipo T en el ABB.  Actúa como método lanzadera del método privado recursivo search(BSNode<T>* n, T e).  Notar que deberá devolver el elemento contenido por el nodo devuelto por el método privado.
		
			return search(root, e) -> elem; // r -> nodo raíz
		}

		T operator[](T e) const{
		//Sobrecarga del operador[]. Actúa como interfaz al método search(T e).
	
			return search(root, e) -> elem; // r -> nodo raíz
		}

		void insert(T e){
		//Inserta el elemento e de tipo T de manera ordenada en el  ABB. Actúa como método lanzadera del método privado recursivo insert(BSNode<T>* n, T e).
	
			root = insert(root, e); // r -> nodo raíz

		}

		friend ostream& operator<<(ostream &out, const BSTree<T> &bst){
		// Sobrecarga del operador << para mostrar a través de out los contenidos del ABB bst, realizando un recorrido inorden o simétrico del árbol para mostrar los elementos ordenados de menor a mayor. Delega en el método privado recursivo print_inorder().
	
			bst.print_inorder(out, bst.root);   // función lanzadera

			return out;
		}

    	void remove(T e){
		// Elimina el elemento e de tipo T del ABB. Actúa como método lanzadera del método privado recursivo remove(BSNode<T>* n, T e).

			root = remove(root, e);
		}

		~BSTree(){
		// Método destructor. Delega en el método privado recursivo delete_cascade().
	
			delete_cascade(root);
			root = nullptr;
		}
};

#endif
