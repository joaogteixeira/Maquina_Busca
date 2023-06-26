#include "buscador.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <filesystem>
#include <algorithm>


using std::filesystem::directory_entry;
using namespace std;
using std::string;
using std::map;

//usar em shell - g++ -std=c++20 main.cpp buscador.cpp- e - ./a.out -

int main() {
	string bus;
	cout << "Digite a busca: ";
	cin >> bus;
  Indice proc;
 	proc.imprimir(bus);
}
