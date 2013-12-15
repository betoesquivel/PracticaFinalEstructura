/*
 * =====================================================================================
 *
 *       Filename:  examen.cpp
 *
 *    Description:  Contiene el examen final de estructura de datos.
 * *        Version:  1.0
 *        Created:  09/12/13 19:17:08
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jose Alberto Esquivel Patino (), 
 *   Organization:  ITESM Campus Monterrey
 *
 * =====================================================================================
 */

#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
using namespace std;

template <class T>
class Nodo
{
	public:
		Nodo<T> *sig;
		T info;
		Nodo() {sig = NULL;}
		Nodo(T dato) {sig = NULL; info = dato;}
};
template <class T>
class FILA
{
	private:
		Nodo<T> *fin;//fin->sig tiene el siguiente dato en salir
		int tam;
	public: 
		FILA() {fin = NULL; tam = 0;}
		FILA(T dato) {fin = new Nodo<T>(dato); fin->sig = fin; tam = 1;}

		int TAM();
		bool empty();
		bool pop();
		void push(T dato);
		void despliega();
		T front() { return fin->sig->info; } 

		~FILA() {
			while(fin!=NULL){
				pop();
			}
		}
};

template <class T>
int FILA<T>::TAM()
{
	return tam;
}
template <class T>
bool FILA<T>::empty()
{
	return fin==NULL;
}
template <class T>
bool FILA<T>::pop()
{
	if (fin!=NULL) {
		Nodo<T> *aux = fin->sig;
		if(fin->sig == fin){
			fin = NULL;
		}else{
			fin->sig = aux->sig; 
		}
		delete aux; 
		tam-=1;
		return true;
	}else{
		return false; 
	}
}
template <class T>
void FILA<T>::push(T dato)
{
	Nodo<T> *nuevo = new Nodo<T>(dato);
	if (nuevo != NULL) {
		if( fin!=NULL ){
			Nodo<T> *aux = fin;

			fin = nuevo; 
			fin->sig = aux->sig;
			aux->sig = fin;
		} else {
			fin = nuevo;
			fin->sig = fin;
		}
	} 
	tam+=1;
}
template <class T>
void FILA<T>::despliega()
{
	if (!empty()) {
		Nodo<T> *aux = fin->sig;
		while(aux!=fin){
			cout<<aux->info<<' ';			
			aux = aux->sig;
		}
		if(aux==fin){
			cout<<aux->info<<' ';
		}
		cout<<endl;
	}
}

//Implementación del nivel físico de un ABB
template <class T>
class NodoArbol
{ public:
	T info;
	NodoArbol<T> *izq, *der;
	NodoArbol() { izq = der = NULL; }
	NodoArbol(T dato) { info = dato; izq = der = NULL; }
};

template <class T>
class ABB
{
public:
		NodoArbol<T> *raiz;
public:
		ABB() { raiz = NULL; }
		NodoArbol<T>* getRaiz(){ return raiz; } 
		void inserta (T dato);
		bool balanceado(NodoArbol<T>* inicial);
		int calcularAltura(NodoArbol<T>* inicial);
		void desplegarNivelPorNivelConversoEInverso(NodoArbol<T>* inicial);
		void desplegarInorden(NodoArbol<T>* inicial);
		void desplegarPreorden(NodoArbol<T>* inicial);
		~ABB() { libera(raiz); }
};

template <class T>
bool ABB<T>::balanceado(NodoArbol<T>* inicial)
{
	if(inicial!=NULL){
		int FB = calcularAltura(inicial->der)-calcularAltura(inicial->izq);		
		if(FB>1 || FB<-1) 
			return false;
		else
			return (balanceado(inicial->izq) && balanceado(inicial->der));
	}else{
		return true;;
	}
}

template <class T>
int ABB<T>::calcularAltura(NodoArbol<T>* inicial)
{
	if(inicial!=NULL){
		int izquierdo = calcularAltura(inicial->izq);	
		int derecho = calcularAltura(inicial->der);	
		return (izquierdo>derecho) ? izquierdo+1:derecho+1;
	}else{
		return 0;
	}
}

template <class T>
void ABB<T>::desplegarInorden(NodoArbol<T>* inicial)
{
	if (inicial!=NULL) {
		desplegarInorden(inicial->izq);
		cout<<inicial->info<<' ';
		desplegarInorden(inicial->der);
	}
}
template <class T>
void ABB<T>::desplegarPreorden(NodoArbol<T>* inicial)
{
	if (inicial!=NULL) {
		cout<<inicial->info<<' ';
		desplegarInorden(inicial->izq);
		desplegarInorden(inicial->der);
	}
}
template <class T>
void ABB<T>::desplegarNivelPorNivelConversoEInverso(NodoArbol<T>* inicial)
{
	// queue<NodoArbol<T>*> fila;
	FILA<NodoArbol<T>*> fila;
	stack<NodoArbol<T>*> salida;
	fila.push(inicial);
	while(!fila.empty()){
		salida.push(fila.front());
		if(fila.front()->izq!=NULL)
			fila.push(fila.front()->izq);
		if(fila.front()->der!=NULL)
			fila.push(fila.front()->der);

		fila.pop();
	}
	while(!salida.empty()){
		cout<<salida.top()->info<<' ';
		salida.pop();
	}
	cout<<endl;
}

template <class T>
void libera (NodoArbol<T>* raiz)
{
	if (raiz != NULL)
	{ 
		libera(raiz->izq);
		libera(raiz->der);
		delete(raiz);
	}
}

template <class T>
void ABB<T>::inserta (T valor)
{
	NodoArbol<T> *NuevoNodo = new NodoArbol<T>(valor);
	NodoArbol<T> *actual = raiz, *anterior = NULL;
	while (actual != NULL)
	{
		anterior=actual;
		actual=(actual->info>valor? actual->izq: actual->der);
	}
	if (anterior==NULL)
	{
		raiz = NuevoNodo;
	}
	else
	{
		if (anterior->info > valor)
		{
			anterior->izq = NuevoNodo;
		}
		else
		{
			if(anterior->info!=valor)
			{
				anterior->der = NuevoNodo;
			}else{
				cout<<"Estoy metiendo el mismo dato.\nPorque el archivo tiene una linea en blanco.\nPor eso no lo guardo otra vez en el arbol."<<endl;
			}
		}
	}
}

// Implemetación del programa de aplicación
int main()
{
	ifstream arch;
	string nomarch;
	int dato;
	ABB<int> arbol;
	// FILA<int> fila;
	
	// cin>>dato;
	// while(dato!=0){
	// 	arbol.inserta(dato);
	// 	cin>>dato;
	// }
	// cout<<endl;
	cout << "Ingrese el nombre del archivo a cargar: ";
	cin >> nomarch;

	arch.open(nomarch.c_str());
	while (!arch.eof())
	{
		arch >> dato;
		cout << dato << " ";
		arbol.inserta(dato);
		// fila.push(dato);
	}
	arch.close();
	cout << endl;
	if(arbol.balanceado(arbol.getRaiz())){
		cout<<"Está balanceado."<<endl;
	}else{
		cout<<"No está balanceado."<<endl;
	}
	arbol.desplegarNivelPorNivelConversoEInverso(arbol.getRaiz());
	// Lo use para probar mi metodo de balanceado.
	// arbol.inserta(2050);
	// if(arbol.balanceado(arbol.getRaiz())){
	// 	cout<<"Está balanceado."<<endl;
	// }else{
	// 	cout<<"No está balanceado."<<endl;
	// }
	// arbol.inserta(1723);
	// if(arbol.balanceado(arbol.getRaiz())){
	// 	cout<<"Está balanceado."<<endl;
	// }else{
	// 	cout<<"No está balanceado."<<endl;
	// }
	// Lo use para probar mi fila stl.
	// cout<<"Voy a desplegar: "<<endl;
	// cout<<fila.TAM()<<endl;
	// fila.despliega();
	// fila.pop();
	// cout<<fila.TAM()<<endl;
	// fila.despliega();
	// fila.push(9999);
	// cout<<fila.TAM()<<endl;
	// fila.despliega();

	return 0;
}

