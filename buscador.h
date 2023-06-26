#ifndef __BUSCADOR_H__
#define __BUSCADOR_H__

#include <algorithm>
#include <fstream>
#include <list>
#include <map>
#include <string>
#include <unordered_map>

using std::list;
using std::map;
using std::string;
using std::unordered_map;

class Arquivo {
public:
  Arquivo();

  map<string, map<string, int>> abrir_arquivo();

  void normalizar(list<string> sujas, string n_do_arq);

  void contagem(const list<string> &limpas, const string &arquivo);

private:
  map<string, map<string, int>> arquivos_;
};
class Indice {
public:
  Indice();

  void imprimir(string busca);

  void tratar_busca(string busca);

  void pesquisa(const list<string> &busca_l);

private:
  Arquivo palavra;
  map<string, map<string, int>> indice_;
};

#endif //__BUSCADOR_H__
