#include <iostream>
#include <string>

using namespace std;

int main(){
    cout <<"Bienvenidos al Laboratorio MIA_B_2S2026" <<endl;
    
    string texto;
    // pedir datos al usuario
    cout << "Ingrese un texto: ";
    getline(cin, texto);
    cout << "El texto ingresado es: " << texto << endl;

    char caracter;
    cout << "Ingrese un caracter: ";
    cin >> caracter;
    cout << "El caracter ingresado es: " << caracter << endl;
    return 0;
}

