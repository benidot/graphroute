#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "digraph.cpp"

using namespace std;

struct graph {
    vector<string> headers;
    vector<vector<string>> rows;
};

string sel_saida() {
    cout << "Selecione o formato de saida do GraphViz:\n";
    cout << "1. Tela\n2. PNG\n3. PDF\nOpcao: ";
    int c; cin >> c;
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

void csv(ifstream &inp, vector<string> &headers, vector<vector<string>> &rows) {
    string line;
    if(getline(inp, line)) {
        stringstream ss(line);
        string header;
        while(getline(ss, header, ',')) {
            headers.push_back(header);
        }
    } // primeira linha

    while(getline(inp, line)) {
        stringstream ss(line);
        string cell;
        vector<string> row;
        while(getline(ss, cell, ',')) {
            row.push_back(cell);
        }
        rows.push_back(row);
    } // resto
}

void make_graph (ifstream &inp, vector<string> &headers, vector<vector<string>> &rows, dg::digraph<string> &root) {

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

void fullprint(const graph &A) {
    for (const auto& header : A.headers) {
        cout << header << "\t";
    } cout << endl;

    for (const auto& row : A.rows) {
        for (const auto& cell : row) {
            cout << cell << "\t";
        }
        cout << endl;
    } // so pra printar por agora
}

int main(int argc, char *argv[]) {
    ifstream inp; graph A; dg::digraph<string> root;
    inp.open(argv[1]);
    if(!inp) {cout << "Erro: Arquivo Invalido\n"; return -1;};
    cout << "Arquivo valido. Continuando.\n";
    csv(inp, A.headers, A.rows);
    make_graph(inp, A.headers, A.rows, root);
    string choice = sel_saida();
    root.show(choice);
    //fullprint();

    inp.close();
}