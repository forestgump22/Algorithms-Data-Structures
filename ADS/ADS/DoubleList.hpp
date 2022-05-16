#pragma once
#include<iostream>
#include<fstream>
#include<functional>
#include<string>
#include<string.h>

using namespace std;
using namespace System;
template<typename T>
class Nodo
{
public:
	Nodo<T>* next;
	Nodo<T>* back;
	T dato;
public:
	Nodo(T dato, Nodo<T>* next = nullptr, Nodo<T>* back = nullptr) :dato(dato), next(next), back(back)
	{}
	~Nodo() {
		this->next = nullptr;
		this->beck = nullptr;
	}
};
template<typename T>
class ListaDoble
{
private:
	Nodo<T>* begin;
	Nodo<T>* end;
	Nodo<T>* aux;
	size_t size;
public:
	ListaDoble() {
		size = 0;
		aux = begin = end = nullptr;
	}
	~ListaDoble() {
		begin = nullptr;
		end = nullptr;
	}
	void pushFront(T dato) {
		Nodo<T>* nuevo = new  Nodo<T>(dato);
		if (size == 0)
		{
			begin = end = nuevo;
		}
		else {
			nuevo->next = begin;
			begin->back = nuevo;
			begin = nuevo;
		}
		if (size == 1) { end = begin = nuevo; }
		size++;
	}
	void pushback(T dato) {
		if (size == 0) { pushFront(dato); return; }
		else
		{
			Nodo<T>* nuevo = new Nodo<T>(dato);
			end->next = nuevo;
			nuevo->back = end;
			end = nuevo;
			size++;
		}
	}
	void insertAt(T dato, int pos) {
		if (pos <= 0) { pushFront(dato); return; }
		else if (pos >= size) { pushback(dato); return; }
		else {
			Nodo<T>* nuevo = new Nodo<T>(dato);
			aux = begin;
			int cont = 0;
			while (cont++ < pos)
			{
				aux = aux->next;
			}
		}
	}

	void buscar(T dato, function<bool(T, T)>comp) {
		aux = end;
		if (end = begin) {
			if (comp(dato, begin->dato)) {
				cout << "encontrado";
			}
		}
		while (aux->back == nullptr)
		{
			if (comp(aux->dato, dato))
			{
				cout << "encontrado";
			}
			aux = aux->back;
		}
	}
	void _rotar() {
		Nodo<T>* cambia = end;
		end = end->back;
		end->next = nullptr;
		cambia->next = begin;
		begin->back = cambia;
		begin = cambia;
	}
	void rotar(int n) {
		int cont = 0;
		while (cont++ != n) {
			_rotar();
		}
	}
	void print() {
		aux = begin;
		while (aux != nullptr) {
			cout << aux->dato << "-->";
			aux = aux->next;
		}
		cout << "nullptr";
	}
};

int main() {

	ListaDoble<int> lista;
	lista.pushback(1);
	lista.pushback(2);
	lista.pushback(3);
	lista.pushback(4);
	lista.print();
	lista.rotar(3);
	cout << "\nrotado" << endl;
	lista.print();

	string line;
	getline(cin, line);
	return 0;
}



