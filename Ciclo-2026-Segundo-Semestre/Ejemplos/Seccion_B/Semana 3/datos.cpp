#include <iostream>
#include <limits>
#include <fstream>
#include <vector>
#include "datos.h"

using namespace std;


// Funcion para ingresar datos de personas
void ingresarDatos(vector<Persona>& personas)
{
    Persona p;

    cout << "------------------------------------" << endl;
    cout << "|         INGRESAR DATOS           |" << endl;
    cout << "------------------------------------" << endl;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Ingrese su nombres: ";
    cin.getline(p.nombre, 50);

    cout << "Ingrese su apellidos: ";
    cin.getline(p.apellido, 50);
       
    cout << "Ingrese su correo: ";
    cin.getline(p.correo, 150);

    personas.push_back(p);

    cout << "\nPersona registrada correctamente.\n";
}


// Funcion para crear el archivo binario
void crearArchivoBinario(const vector<Persona>& personas, const string& nombreArchivo)
{
    ofstream archivo(nombreArchivo, ios::binary);

    if (!archivo)
    {
        cout << "Error al crear el archivo binario: "
             << nombreArchivo << endl;
        return;
    }

    for (const auto& p : personas)
    {
        archivo.write(reinterpret_cast<const char*>(&p), sizeof(Persona));
    }

    archivo.close();

    cout << "Archivo binario \"" << nombreArchivo
         << "\" creado correctamente." << endl;
}

void leerArchivoBinario(const string& nombreArchivo)
{
    ifstream archivo(nombreArchivo, ios::binary);

    if (!archivo)
    {
        cout << "Error al abrir el archivo binario: "
             << nombreArchivo << endl;
        return;
    }

    Persona p;

    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Persona)))
    {
        cout << "Nombres: " << p.nombre << endl;
        cout << "Apellidos: " << p.apellido << endl;
        cout << "Correo: " << p.correo << endl;
        cout << "------------------------------------" << endl;
    }

    archivo.close();
}