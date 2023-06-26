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
	normalizar(palavras, arquivo.path().filename());
		palavras.clear();
		}
	}
	return arquivos_;
}

void trim(string& str) {
    // Remover espaços em branco à esquerda
    str.erase(str.begin(), find_if(str.begin(), str.end(), [](int ch) {
        return !isspace(ch);
    }));
    
    // Remover espaços em branco à direita
    str.erase(find_if(str.rbegin(), str.rend(), [](int ch) {
        return !isspace(ch);
    }).base(), str.end());
}

void Arquivo::normalizar(list<string> sujas, string n_do_arquivo) {
    list<string> limpas;
    for (const string& str : sujas) {
        string limpa;
        for (char c : str) {
            if (isalpha(c)) {
                limpa.push_back(tolower(c));
            }
        }
        // Remover espaços em branco antes e depois da palavra
        trim(limpa);
        if (!limpa.empty()) {
            limpas.push_back(move(limpa));
        }
		}
    if (!limpas.empty()) {
        contagem(limpas, n_do_arquivo);
    }
}
void Arquivo::contagem(const list<string>& limpas, const string& arquivo) {
    unordered_map<string, int> ocorrenciasMap;

    // Contar as ocorrências de cada palavra em limpas
    for (const string& str : limpas) {
        ocorrenciasMap[str]++;
    }

    // Atualizar o mapa arquivos_ com as ocorrências
    for (const auto& pair : ocorrenciasMap) {
        const string& palavra = pair.first;
        int ocorrencias = pair.second;

        auto it = arquivos_.find(palavra);
        if (it != arquivos_.end()) {
            // Verificar se o arquivo já existe para a chave 'palavra'
            auto it2 = it->second.find(arquivo);
            if (it2 == it->second.end()) {
                it->second[arquivo] = ocorrencias;
            }
        } else {
            // A chave 'palavra' não existe no mapa, adicionar um novo par chave-valor
            arquivos_[palavra][arquivo] = ocorrencias;
        }
    }
}

