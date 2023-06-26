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
void Indice::imprimir(string busca) {
	auto it = indice_.find(busca);
	if (it != indice_.end()) {
		for (const auto& pair : it->second) {
			cout << pair.first << " - " << pair.second << endl;
		}
	}
}

void Indice::tratar_busca(string busca) {
    list<string> busca_l;

    // Quebrar a busca em palavras
    istringstream iss(busca);
    string palavra;
    while (iss >> palavra) {
        // Limpar a palavra removendo caracteres indesejados
        string limpa;
        for (char c : palavra) {
            if (isalpha(c)) {
                limpa.push_back(tolower(c));
            }
        }
        // Remover espaços em branco antes e depois da palavra
        trim(limpa);
        
        if (!limpa.empty()) {
            busca_l.push_back(limpa);
        }
    }
    
    // Verificar se os arquivos contêm a frase completa
    pesquisa(busca_l);
}
void Indice::pesquisa(const list<string>& busca_l) {
    vector<string> arquivosComFraseCompleta;
    vector<string> arquivosComPartesDaFrase;

    // Verificar os arquivos que contêm a frase completa
    for (const auto& it : indice_) {
        const string& palavra = it.first;
        const map<string, int>& ocorrenciasArquivo = it.second;

        bool encontrouFraseCompleta = true;
        for (const string& busca : busca_l) {
            if (ocorrenciasArquivo.find(busca) == ocorrenciasArquivo.end()) {
                encontrouFraseCompleta = false;
                break;
            }
        }

        if (encontrouFraseCompleta) {
            for (const auto& pair : ocorrenciasArquivo) {
                const string& arquivo = pair.first;
                arquivosComFraseCompleta.push_back(arquivo);
            }
        } else {
            bool encontrouPartesDaFrase = false;
            for (const string& busca : busca_l) {
                if (ocorrenciasArquivo.find(busca) != ocorrenciasArquivo.end()) {
                    encontrouPartesDaFrase = true;
                    break;
                }
            }
            if (encontrouPartesDaFrase) {
                for (const auto& pair : ocorrenciasArquivo) {
                    const string& arquivo = pair.first;
                    arquivosComPartesDaFrase.push_back(arquivo);
                }
            }
        }
    }

    // Remover duplicatas dos arquivos com partes da frase
    sort(arquivosComPartesDaFrase.begin(), arquivosComPartesDaFrase.end());
    arquivosComPartesDaFrase.erase(unique(arquivosComPartesDaFrase.begin(), arquivosComPartesDaFrase.end()), arquivosComPartesDaFrase.end());

    // Imprimir os arquivos com a frase completa
    cout << "Arquivos com a frase completa:" << endl;
    for (const string& arquivo : arquivosComFraseCompleta) {
        cout << arquivo << endl;
    }

    // Imprimir os arquivos com partes da frase
    cout << "Arquivos com partes da frase:" << endl;
    for (const string& arquivo : arquivosComPartesDaFrase) {
        cout << arquivo << endl;
    }
}
