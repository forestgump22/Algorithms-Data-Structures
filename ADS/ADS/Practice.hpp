#include<iostream>
#include<string>
#include<fstream>
#include<functional>

typedef long long ll;
using namespace std;
using namespace System;

template<class T>
class DLCL;

template<class T>
class Node{
private:
	T element;
	Node<T>* next;
	Node<T>* back;
	DLCL<T>* child;
public:
	Node(T element, Node<T>* next=nullptr,Node<T>* back=nullptr):
	element(element),next(next),back(back){
		child = new DLCL<T>();
	}
	~Node() {}
	void insertChild(T value) {
		child->push_back(value);
	}
};

template<class T>
class DLCL {
	Node<T>* begin;
	Node<T>* end;
	Node<T>* aux;
	ll size;
public:
	DLCL() {
		aux = begin = end = nullptr;
		size = 0;
	}
	~DLCL() {
		while (size > 0) {
			pop_back();
		}
	}
	ll Size() {
		return size;
	}
	void push_front(T value) {
		Node<T>* newNode = new Node<T>(value);
		if (size==0){
			begin = end = newNode;
			begin->back = end;
			end->next = begin;
		}else{
			end->next = begin->back = nullptr;
			newNode->next = begin;
			begin->back = newNode;
			begin = newNode;
			end->next = begin;
			begin->back = end;
		}
		++size;
	}
	void push_back(T value) {
		Node<T>* newNode = new Node<T>(value);
		if (size==0){
			begin = end = newNode;
			begin->back = end;
			end->next = begin;
			++size;
		}else{
			end->next=begin->back = nullptr;
			end->next = newNode;
			newNode->back = end;
			end = newNode;
			end->next = begin;
			begin->back = end;
			++size;
		}
	}
	void insertAt(T value, ll pos) {
		if(pos<=0){
			push_front(value);
		}else if(pos >= size) {
			push_back(value);
		}else{
			aux = begin;
			for (ll i = 0; i < pos-1; i++){
				aux = aux->next;
			}
			Node<T>* newNode = new Node<T>(value);
			//enlazamos el nuevo nodo
			newNode->next = aux->next;
			newNode->back = aux;
			//enlazamos los nodos existentes
			aux->next = newNode;
			aux->next->next->back = newNode;
			++size;
		}
	}
	DLCL<T>*& insertChild(T value, ll pos) {
		aux = begin;
		if (pos==0){
			aux->insertChild(value);
			return aux->child;
		}
		for (ll i = 0; i < pos; i++){
			aux = aux->next;
		}
		aux->insertChild(value);
		return aux->child;
	}
	void pop_back() {
		if (size==1){
			delete begin;
			begin = end = nullptr;
		}
		else if (size > 1) {
			end->next = begin->back = nullptr;
			aux = end;
			end = end->back;
			end->next = nullptr;
			aux->back = nullptr;
			delete aux;
			end->next = begin;
			begin->back = end;
		}
		--size;
	}
	class Iterator {
		Node<T>* aux;
		int pos;
	public:
		Iterator(Node<T>* aux,ll pos):aux(aux),pos(pos){}
		void operator++() {
			aux = aux->next;
			++pos;
		}
		void operator--() {
			aux = aux->back;
			--pos;
		}
		T operator*() {
			return aux->element;
		}
		Node<T>*&getNodo() {
			return aux;
		}
		bool operator!=(Iterator a) {
			return (this->pos != a.pos);
		}
	};
	Iterator IteBegin() {
		return Iterator(begin, 0);
	}
	Iterator IteEnd() {
		return Iterator(nullptr, size);
	}
	void ToDLL() {
		end->next = begin->back = nullptr;
	}
	void ToDLCL() {
		end->next = begin;
		begin->back = end;
	}
	void AllToDLL(DLCL<T>*& dll) {
		ToDLL();
		DLCL<T>::Iterator it = IteBegin();
		MoveInDLL(it.getNodo(), dll);
		ToDLCL();
	}
	void saveInFile(ofstream& arch) {
		DLCL<T>::Iterator it = IteBegin();
		for (ll i = 0; i < size; i++){
			arch << *(it) << " ";
			++it;
		}
		arch << "\n5n + 5";
	}
private:
	void _print(Node<T>* n) {
		if (n==nullptr){
			return;
		}
		cout << n->element << " ";
		if (n->child->size>0){
			DLCL<T>::Iterator it = n->child->IteBegin();
			n->child->ToDLL();
			_print(it.getNodo());
			n->child->ToDLCL();
		}
		_print(n->next);
	}
	void MoveInDLL(Node<T>* n, DLCL)
	void print() {
		ToDLL();
		DLCL<T>::Iterator it = IteBegin();
		_print(it.getNodo());
	}
};
