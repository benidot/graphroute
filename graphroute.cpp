#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

struct graph {
    vector<string> headers;
    vector<vector<string>> rows;
};

void sel_saida() {
    cout << "Selecione o formato de saida do GraphViz:\n";
    cout << "1. Tela\n2. PNG\n3. PDF\nOpcao: ";
    int c; cin >> c;
    switch (c) {
        case 1:
            cout << "tela selecionado\n";
            break;
        case 2:
            cout << "png selecionado\n";
            break;
        case 3:
            cout << "pdf selecionado\n";
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

int main(int argc, char *argv[]) {
    ifstream inp; graph A;
    inp.open(argv[1]);
    if(!inp) {cout << "Erro: Arquivo Invalido\n"; return -1;};
    cout << "Arquivo valido. Continuando.\n";
    csv(inp, A.headers, A.rows);

    for (const auto& row : A.rows) {
        for (const auto& cell : row) {
            cout << cell << "\t";
        }
        cout << endl;
    } // so pra printar por agora

    inp.close();
}