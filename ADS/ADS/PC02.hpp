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
class Node {
private:
	T element;
	Node<T>* next;
	Node<T>* back;
	DLCL<T>* child;
	friend class DLCL<T>;
public:
	Node(T element, Node<T>* next = nullptr, Node<T>* back = nullptr)
		:element(element), next(next), back(back) {
		child = new DLCL<T>();
	}
	~Node() {
		child->eraseAll();
	}
	void insertChild(T value) {
		child->push_back(value);
	}
};

template<class T>
class DLCL {
private:
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
		eraseAll();
	}
	void eraseAll() {
		while (size > 0) {
			pop_back();
		}
	}
	ll Size() {
		return size;
	}
	void push_Front(T value) {
		Node<T>* newNode = new Node<T>(value);
		if (size==0){
			begin = end = newNode;
			++size;
		}
		else {
			end->next = begin->back = nullptr;
			newNode->next = begin;
			begin->back = newNode;
			begin = newNode;
			end->next = begin;
			begin->back = end;
			++size;
		}
	}
	void push_back(T value) {
		Node<T>* newNode = new Node<T>(value);
		if (size==0){
			begin = end = newNode;
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
		if (pos<=0){
			push_Front(value);
		}else if(pos >= size) {
			push_back(value);
		}else{
			aux = begin;
			for (ll i = 0; i < pos-1; i++){
				aux = aux->next;
			}
			Node<T>* newNode = new Node<T>(value);
			newNode->next = aux->next;
			newNode->back = aux;
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
		if (size <= 0) {
			return;
		}
		if (size==1){
			delete begin;
			begin = end = nullptr;
		}
		else {
			end->next = begin->back = nullptr;
			aux = end;
			end= end->back;
			aux->back = nullptr;
			end->next = nullptr;
			aux->child->eraseAll();
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
		Iterator(Node<T>* aux, ll pos) :aux(aux), pos(pos){}
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
		Node<T>* getNodo() {
			return aux;
		}
		bool operator!=(Iterator a) {
			return (this->pos != a.pos);
		}
	};
	Iterator Itebegin() {
		return Iterator(begin, 0);
	}
	Iterator Iteend() {
		return Iterator(nullptr, size);
	}
	void print() {
		ToDLL();
		DLCL<T>::Iterator it = Itebegin();
		_print(it.getNodo());
		ToDLCL();
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
		DLCL<T>::Iterator it = Itebegin();
		MoveInDLL(it.getNodo(), dll);
		ToDLCL();
	}
	void saveInFile(ofstream& arch) {
		DLCL<T>::Iterator it = Itebegin();
		for (ll i = 0; i < size; i++){
			arch << *(it) << " ";
			++it;
		}
		arch << "\n5n+ 5";
	}
private:
	void _print(Node<T>* n) {
		if (n==nullptr){
			return;
		}
		cout << n->element << " ";
		if (n->child->size>0){
			DLCL<T>::Iterator it = n->child->Itebegin();
			n->child->ToDLL();
			_print(it.getNodo());
			n->child->ToDLCL();
		}
		_print(n->next);
	}
	void MoveInDLL(Node<T>* n, DLCL<T>*& dll) {
		if (n==nullptr){
			return;
		}
		dll->push_back(n->element);
		if (n->child->size>0){
			DLCL<T>::Iterator it = n->child->begin();
			n->child->ToDLL();
			MoveInDLL(it.getNodo(), dll);
			n->child->ToDLCL();
		}
		MoveInDLL(n->next, dll);
	}
};

class Sample {
	DLCL<string>* lista;
	DLCL<string>* current;
	DLCL<string>* res;
public:
	Sample() {
		lista = new DLCL<string>();
		res = new DLCL<string>();
	}
	~Sample() {
		lista->eraseAll();
		current->eraseAll();
		res->eraseAll();
	}
	void readInput() {
		ifstream arch("input.txt");
		string line;
		int nullCount = -1;
		current = lista;
		while (getline(arch,line,',')){
			if (line=="nullptr"){
				++nullCount;
				continue;
			}
			if (nullCount==-1){
				current->push_back(line);
			}else{
				current = current->insertChild(line, nullCount);
				nullCount = -1;
			}
		}
		lista->AllToDLL(res);
		cout << "\nEl resultado es: ";
		res->print();
		ofstream out("output.txt");
		res->saveInFile(out);
	}
};

int main() {
	Sample* s = new Sample;
	s->readInput();
	delete s;
	return 0;
}