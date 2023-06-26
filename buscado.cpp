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
