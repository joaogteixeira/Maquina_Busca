#include "buscador.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <filesystem>
#include <algorithm>
#include <unordered_map>

using namespace std;
using std::list;
using std::string;
using std::map;
using std::filesystem::directory_entry;
using std::unordered_map;


Indice::Indice() : indice_(palavra.abrir_arquivo()){

}

Arquivo::Arquivo() {

}
map<string, map<string, int>> Arquivo::abrir_arquivo() {
	for(const filesystem::directory_entry& arquivo : filesystem::directory_iterator("documentos")) {
		list<string> palavras;
		ifstream obj_arquivo(arquivo.path());
		if (!obj_arquivo.is_open()) {
    cout << "Erro ao abrir o arquivo: " << arquivo.path() << endl;
    continue; // Pular para o próximo arquivo
		}
		else{
		string linha;
  	while (getline(obj_arquivo, linha)) {
    	istringstream iss(linha);
    	string palavra;
    		while (iss >> palavra) {
					palavras.push_back(palavra);
				}
		}
