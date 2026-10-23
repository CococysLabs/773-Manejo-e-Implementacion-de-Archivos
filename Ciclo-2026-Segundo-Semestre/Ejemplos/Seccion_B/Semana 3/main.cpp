#include <iostream>
#include <vector>
#include "datos.h"

using namespace std;

int main()
{
    bool bandera = true;

    // Aquí se almacenarán todas las personas
    vector<Persona> personas;

    while (bandera)
    {
        int opcion;

        cout << "--------------------------------------" << endl;
        cout << "|                                    |" << endl;
        cout << "|          [1] Ingresar datos        |" << endl;
        cout << "|          [2] Salir                |" << endl;
        cout << "|          [3] leer binario         |" << endl;
        cout << "--------------------------------------" << endl;

        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            ingresarDatos(personas);
            crearArchivoBinario(personas, "personas.dat");
         

            break;

        case 2:
            bandera = false;
            cout << "Saliendo del programa... :)" << endl;
            break;
        case 3:
            leerArchivoBinario("personas.dat");
            break;
        default:
            cout << "Opcion no valida." << endl;
        }

        cout << endl;
    }

    cout << "\nTotal de personas registradas: "
         << personas.size() << endl;

    for (const auto& p : personas)
    {
        cout << "Datos ingresados: " << p.nombre << " " << p.apellido << " " << p.correo << endl;
    }

    return 0;
}