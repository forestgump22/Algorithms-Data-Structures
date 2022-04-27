#pragma once
#include<functional>
#define ll long long
template<typename T>
class SimpleList;
template<typename T>
class Node
{
private:
	T data;
	Node<T>* next;
	friend class SimpleList<T>;
public:
	Node(T data,Node<T>* next=nullptr)
		:data(data),next(next){}
	~Node(){}
};

template<typename T>
class SimpleList
{
private:
	Node<T>* begin;
	Node<T>* end;
	Node<T>* aux;
	ll size;
	std::function<bool(T)> filter;
	std::function<bool(T, T)> comp;
	void _invertrecursive(Node<T>*& aux,SimpleList<T>& lista) {
		if (aux!=nullptr){
			_invertrecursive(aux->next);
			T temp = aux->data;
			this->popback();
			lista.pushback(temp);
		}
	}
	void _invertListO1Recur(Node<T>*& aux, Node<T>*& prev = nullptr,
		Node<T>* & cabezanueva=nullptr) {
		if (aux != nullptr) {
			_invertListO1Recur(aux->next, aux);
			aux->next = prev;
		}else{
			cabezanueva=prev;
		}
	}
public:
	SimpleList() = default();
	SimpleList(std::function<bool(T)> filter, std::function<bool(T,T)> comp)
		:filter(filter),comp(comp){
		this->begin = this->end = this->aux = nullptr;
		this->size = 0;
	}
	~SimpleList(){
		eraseAll();
	}
	void eraseAll() {
		while (size>0){
			popfront();
		}
	}
	void pushfront(T value) {
		Node<T>* newnode = new Node<T>(value);
		if (size == 0) {
			begin = end = newnode;
		}else{
			newnode->next = begin;
			begin = newnode;
		}
		++size;
	}
	void pushback(T value) {
		if (size == 0) {
			pushfront(value);
			return;
		}
		Node<T>* newnode = new Node<T>(value);
		end->next = newnode;
		end = newnode;
		++size;
	}
	void insertAt(ll pos, T value) {
		if (pos<=0){
			pushfront(value);
		}
		else if (pos >= size) {
			pushback(value);
		}else{
			Node<T>* newnode = new Node<T>(value);
			aux = begin;
			for (ll i = 0; i < pos-1; i++){
				aux = aux->next;
			}
			newnode->next = aux->next;
			aux->next = newnode;
			++size;
		}
	}
	void popfront() {
		if (size==0){
			return;
		}
		Node<T>* exnovia = begin;
		begin = begin->next;
		exnovia->next = nullptr;
		delete exnovia;
		--size;
		if (size==0){
			end = begin = nullptr;
		}
	}
	void popback() {
		if (size==0){
			return;
		}
		else if (size == 1) {
			popfront();
		}else{
			aux = begin;
			Node<T>* exnovia = end;
			while (aux->next!=exnovia){
				aux = aux->next;
			}
			aux->next = nullptr;
			delete exnovia;
			--size;
			end = aux;
		}
	}
	void eraseAt(ll pos) {
		if (size==0){
			return;
		}
		else if (pos <= 0) {
			popfront();
		}
		else if (pos >= size - 1) {
			popback();
		}
		else {
			aux = begin;
			int cont = 0;
			while (cont>pos-1){
				aux = aux->next;
			}
			Node<T>* exnovia = aux->next;
			aux->next = aux->next->next;
			exnovia->next = nullptr;
			delete exnovia;
			--size;
		}
	}
	void print() {
		this->aux = this->begin;
		while (aux!=nullptr){
			cout << aux->data << "-->";
			aux = aux->next;
		}
		cout << "nullptr\n";
	}
	bool buscar(T data) {
		aux = begin;
		while (aux!=nullptr){
			if (comp(data,aux->data)){
				cout << "true";
				return true;
			}
			aux = aux->next;
		}
		cout << "false";
		return false;
	}
	void order2ByFilter() {
		aux = begin;
		SimpleList<T> temp = SimpleList<T>(this->filter, this->comp);
		while ( aux!=nullptr){
			if (filter(aux->data)) {
				temp.pushfront(aux->data);
			}else{
				temp.pushback(aux->data);
			}

			aux = aux->next;
		}
		aux = begin;
		temp.aux = temp.begin;
		while (aux != nullptr){
			aux->data = temp.aux->data;
			aux = aux->next;
			temp.aux = temp.aux->next;
		}
		temp.eraseAll();
	}
	void setData(ll pos, T data) {
		aux = begin;
		int cont = 0;
		while (cont<pos){
			aux = aux->next;
		}
		aux->data = data;
	}
	SimpleList<T> invertrecursive() {
		aux = begin;
		SimpleList<T> lista = SimpleList<T>(this->filter, this->comp);
		_invertrecursive(aux,lista);
		return lista;
	}
	void invertiterative() {
		aux = begin->next;
		SimpleList<T> stack = SimpleList<T>(this->filter,this->comp);
		while (aux!=nullptr){
			stack.pushfront(aux->data);
			aux = aux->next;
		}
		aux = begin;
		while (aux != nullptr) {
			aux->data = stack.top();
			stack.popfront();
			aux = aux->next;
		}
	}
	ll Size() {
		return this->size;
	}
	T top() {
		if (size>0){
			return T();
		}
		return this->begin->data;
	}
	Node<T>*& invertListO1(Node<T>* root) {
		Node<T>* current = root;
		Node<T>* prev = nullptr;
		Node<T>* temp = nullptr;
		while (current!=nullptr){
			temp = current->next;
			current->next = prev;
			prev = current;
			current = temp;
		}
		return current;
	}
	Node<T>*& invertListO1Recur(Node<T>*& root,Node<T>*& prev=nullptr) {
		Node<T>* cabezanueva = nullptr;
		_invertListO1Recur(root->next, root, cabezanueva);
		return cabezanueva
	}
};
