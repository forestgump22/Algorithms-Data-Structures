#include<iostream>
#include<fstream>
#include<vector>
#include<list>
#include<algorithm>
#include<string>
#include<string.h>
#include<functional>

using namespace std;
using namespace System;

int contEspacios(string line, function<bool(char a)> comparar) {
	int cont = 0;
	for (int i = 0; i < line.size(); i++){
		if (comparar(line.at(i))){
			++cont;
		}
	}
	return cont;
}
void readMatrix(vector<vector<int>>& m) {
	ifstream arch("datos_matriz.txt");
	ifstream arch1("datos_matrix.txt");
	string line;
	std::getline(arch, line);
	vector<int>arraux;
	int size = std::count_if(line.begin(), line.end(), [](char a)->bool {return a == ' '; });
	int i = 0;
	while (arch1 >> line) {
		i++;
		arraux.push_back(std::stoi(line));
		if (i>size){
			i = 0;
			m.push_back(arraux);
			arraux.clear();
		}
	}
}
void convertMatrix(vector<vector<int>>& m, int filas, int columnas) {
	if (filas*columnas!=m.size()*m.at(0).size()){
		cout << "No se puede convertir la matriz sorry\n";
	}else{
		vector<int> arraux;
		for (int i = 0; i < m.size(); i++){
			for (int j = 0; j < m.at(0).size(); j++){
				arraux.push_back(m[i][j]);
			}
		}
		m.clear();
		vector<int> arraux2;
		int cont = 0;
		for (int i = 0; i < filas; i++){
			for (int j = 0; j < columnas; j++){
				arraux2.push_back(arraux.at(cont++));
			}
			m.push_back(arraux2);
			arraux2.clear();
		}
	}
}
void print(vector<vector<int>> m) {
	for (int i = 0; i < m.size(); i++){
		for (int j = 0; j < m.at(0).size(); j++){
			cout << m[i][j] << " ";
		}
		cout << "\n";
	}
}
void writeMatrix(string nameArch, vector<vector<int>> m) {
	ofstream archE(nameArch);
	for (int i = 0; i < m.size(); i++){
		for (int j = 0; j < m.at(0).size(); j++){
			archE << m[i][j] << " ";
		}
		cout << " ";
	}
}
void readingList(list<int>& lista1, list<int>& lista2) {
	ifstream archL("Leerenlistas.txt");
	ifstream archL1("LeerenListas.txt");
	string line1;
	getline(archL, line1);
	int size = contEspacios(line1, [](char a)->bool {return a == ' '; });
	int auxLine = 0;
	int i = 0;
	list<int> listaAcum;
	while (archL1>>line1){
		i++;
		listaAcum.push_back(std::stoi(line1));
		if (i>size){
			i = 0;
			if (auxLine==0){
				lista1 = listaAcum;
				auxLine++;
				listaAcum.clear();
			}
			else {
				lista2 = listaAcum;
				auxLine++;
				listaAcum.clear();
			}
		}
	}
}
void print(list<int> lista) {
	if (lista.empty()){
		return;
	}
	cout << lista.front() << " ";
	lista.pop_front();
	print(lista);
}
void convertirListas(list<int>& lista1, list<int>& lista2,
	list<int>& lista3,function<bool(int,int)> comparar) {

	while (!lista1.empty() && !lista2.empty()) {
		if (comparar(lista1.front(), lista2.front())) {
			lista3.push_back(lista2.front());
			lista2.pop_front();
		}
		else {
			lista3.push_back(lista1.front());
			lista1.pop_front();
		}
	}

	while (!lista1.empty()) {
		lista3.push_back(lista1.front());
		lista1.pop_front();
	}

	while (!lista2.empty()) {
		lista3.push_back(lista2.front());
		lista2.pop_front();
	}
}
void mergeSorting(vector<int>& arr,function<bool(int num1,int num2)> cmp) {
	if (arr.size()>1){
		int m = arr.size() / 2;
		vector<int> left;
		vector<int> right;
		for (int i = 0; i < m; i++){
			left.push_back(arr[i]);
		}
		for (int i = m; i < arr.size(); i++){
			right.push_back(arr[i]);
		}
		mergeSorting(left,cmp);
		mergeSorting(right,cmp);

		int i = 0; int j = 0;int k = 0;
		int nl = left.size();
		int nr = right.size();
		while (i < nl && j < nr) {
			if (cmp(left[i],right[j])){
				arr[k++] = left[i++];
			}else{
				arr[k++] = right[j++];
			}
		}

		while (i < nl) {
			arr[k++] = left[i++];
		}
		while (j < nr) {
			arr[k++] = right[j++];
		}
	}
}
void guardarLista(list<int> lista) {
	ofstream archE("resultadoListas.txt");
	while (!lista.empty()){
		archE << lista.front() << " ";
		lista.pop_front();
	}
}

