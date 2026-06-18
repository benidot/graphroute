#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>
#include "digraph.cpp"

using namespace std;

struct graph {
  vector<string> headers;
  vector<vector<string>> rows;
};

string sel_saida() {
  cout << "Selecione o formato de saida do GraphViz:\n";
  cout << "1. Tela\n2. PNG\n3. PDF\nOpcao: ";
  int c;
  cin >> c;
  switch (c) {
    case 1:
      return "-Tx11";
      break;
    case 2:
      return "-Tpng";
      break;
    case 3:
      return "-Tpdf";
      break;
    default:
      return "erro";
      break;
  }
}

void csv(ifstream& inp, vector<string>& headers, vector<vector<string>>& rows) {
  string line;
  if (getline(inp, line)) {
    stringstream ss(line);
    string header;
    while (getline(ss, header, ',')) {
      headers.push_back(header);
    }
  }  // primeira linha

  while (getline(inp, line)) {
    stringstream ss(line);
    string cell;
    vector<string> row;
    while (getline(ss, cell, ',')) {
      row.push_back(cell);
    }
    rows.push_back(row);
  }  // resto
}

void make_graph(ifstream& inp, vector<string>& headers,
                vector<vector<string>>& rows, dg::digraph<string>& root) {
  for (const auto& row : rows) {
    for (const auto& cell : row) {
      if (cell == "*" || cell == "") {
        continue;
      }
    }

    root.insert_node(row[4]);
    root.insert_node(row[5]);
    root.insert_link(row[4], row[5]);
  }
}

void fullprint(const graph& A) {
  for (const auto& header : A.headers) {
    cout << header << "\t";
  }
  cout << endl;

  for (const auto& row : A.rows) {
    for (const auto& cell : row) {
      cout << cell << "\t";
    }
    cout << endl;
  }  // so pra printar por agora
}

void print_dados(graph& A) {
  int vertices_unicos = 0;
  int arestas = 0;
  cout << "Vertices unicos (IPs): " << vertices_unicos
       << " | Arestas: " << arestas << endl;
}

void sel_comando(dg::digraph<string>& root, string filename) {
  cout << "======================================================\n";
  cout << "1. Exibir grafo completo\n"
       << "2. Encontrar menor caminho\n"
       << "3. Calcular o diametro do grafo\n"
       << "4. Identificar roteadores criticos\n"
       << "0. Sair\n";
  cout << "======================================================\n";
  cout << "Escolha uma opcao: ";
  int op = 0;
  cin >> op;
  if (op != 0 && op >= 5) {
    return;
  }
  string ch_s;
  switch (op) {
    case 1:
      ch_s = sel_saida();
      root.show(ch_s);
    case 2:
      shortest_path(root, filename);
    case 3:
      return;  // calcular diametro
    case 4:
      
      return;  // identificar roteadores
  }
}

void shortest_path(dg::digraph<string> &root, const string &filename)
{
    string origem;
    string destino;

    cout << "Digite o IP de Origem: ";
    getline(cin, origem);

    cout << "Digite o IP de Destino: ";
    getline(cin, destino);

    auto path = root.shortest_path(origem, destino);

    if (path.empty()) {

        cout << "Nenhum caminho encontrado.\n";

        return;
    }

    // Terminar!!

}

int main(int argc, char* argv[]) {
  ifstream inp;
  graph A;
  dg::digraph<string> root;
  string filename = argv[1];
  inp.open(argv[1]);

  if (!inp) {
    cout << "Erro: Arquivo Invalido\n";
    return -1;
  };
  cout << "Arquivo valido. Continuando.\n";
  csv(inp, A.headers, A.rows);
  make_graph(inp, A.headers, A.rows, root);
  print_dados(A);
  sel_comando(root, filename);

  // fullprint();

  inp.close();
}