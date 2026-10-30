#ifndef DATOS_H
#define DATOS_H

#include <vector>
#include <string>

using namespace std;

struct Persona
{
    char nombre[50];
    char apellido[50];
    char correo[150];
};
                    
void ingresarDatos(vector<Persona>& personas);

void crearArchivoBinario(
    const vector<Persona>& personas,
    const string& nombreArchivo);
//leer archivo binario
void leerArchivoBinario(const string& nombreArchivo);
#endif