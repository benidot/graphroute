#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void sel_saida() {
    cout << "Selecione o formato de saída do GraphViz:\n";
    cout << "1. Tela\n2.PNG\n3. PDF\nOpção: ";
    int c; cin >> c;
    switch (c) {
        case 1:
            cout << "wtf";
        case 2:
            cout << "png";
        case 3:
            cout << "pdf";
    }
}

int main(int argc, char *argv[]) {
    ifstream inp;
    inp.open(argv[1]);
    if(!inp) return -1;
    string line;
    while(getline(inp, line)) {
        cout << line << endl;
    }
    cout << "hi\n";
}