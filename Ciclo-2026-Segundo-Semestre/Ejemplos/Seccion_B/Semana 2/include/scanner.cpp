#include "../lib/scanner.h"
#include "../lib/disco.h"

#include <iostream>
#include <stdlib.h>
#include <locale>
#include <cstring>
#include <locale>
#include <fstream>
#include <vector>
#include <cstdlib>

using namespace std;
// Crear una instancia de la clase Disk
Disk disco;

bool logued = false;
scanner::scanner()
{
}
void Clear()
{
    cout << "\x1B[2J\x1B[H";
}

void scanner::start()
{
    system("clear");
    cout << "\033[1;92m";

    cout << R"(

            .--.
           |o_o |
           |:_/ |
          //   \ \
         (|     | )
        /'\_   _/`\
        \___)=(___/

        Linux Practica - WILLIAMS BRAMLLEY CONSTANZA OSCAL - 199919737

)";

        cout << "\033[47m"; 
    cout << "\033[32m"; 

    cout << "====================================" << endl;
    cout << "                                    " << endl;
    cout << "          [1] Ingrese Comando       " << endl;
    cout << "          [2] exit                  " << endl;
    cout << "                                    " << endl;
    cout << "====================================" << endl;

    cout << "\033[0m";
    cout << "\033[32m[(execute)]>: \033[0m ";
    
    while (true)
    {
        string texto;
        getline(cin, texto);
        Clear();
        if (compare(texto, "exit"))
        {
            break;
        }
        string tk = token(texto);
        texto.erase(0, tk.length() + 1); 
        vector<string> tks = split_tokens(texto);
        functions(tk, tks);
        cout << "\033[30;43mPRESIONAR ENTER <--|\033[0m" << endl;
        getline(cin, texto);
        Clear();
                cout << "\033[47m"; 
    cout << "\033[32m"; 

    cout << "====================================" << endl;
    cout << "                                    " << endl;
    cout << "          [1] Ingrese Comando       " << endl;
    cout << "          [2] exit                  " << endl;
    cout << "                                    " << endl;
    cout << "====================================" << endl;

    cout << "\033[0m";
    cout << "\033[32m[(execute)]>: \033[0m ";
    
    }
}

void scanner::functions(string token, vector<string> tks)
{
    if (compare(token, "MKDISK"))
    {
       std::cout << "SE CREO MKDISK" << std::endl;
        disco.mkdisk(tks);
      
    }
    else if (compare(token, "RMDISK"))
    {
        cout << "SE CREO RMDISK" << endl;
    }
    else if (compare(token, "FDISK"))
    {
        cout << "SE CREO FDISK" << endl;
    }
    else if (compare(token, "MOUNT"))
    {
        cout << "SE CREO MOUNT" << endl;
    }
    else
    {
        errores("SYSTEM", "COMANDO INVALIDO \"" + token + "\"");
    }
}

string scanner::token(string text)
{
    string tkn = "";
    bool terminar = false;
    for (char &c : text)
    {
        if (terminar)
        {
            if (c == ' ' || c == '-')
            {
                break;
            }
            tkn += c;
        }
        else if ((c != ' ' && !terminar))
        {
            if (c == '#')
            {
                tkn = text;
                break;
            }
            else
            {
                tkn += c;
                terminar = true;
            }
        }
    }
    return tkn;
}

vector<string> scanner::split(string text, string text_split)
{
    vector<string> cadena;
    if (text.empty())
    {
        return cadena;
    }

    int n = text.length();
    char char_array[n + 1];
    strcpy(char_array, text.c_str());
    char *point = strtok(char_array, text_split.c_str());
    while (point != NULL)
    {
        cadena.push_back(string(point));
        point = strtok(NULL, text_split.c_str());
    }
    return cadena;
}

vector<string> scanner::split_tokens(string text)
{
    vector<string> tokens;
    if (text.empty())
    {
        return tokens;
    }
    text.push_back(' ');
    string token = "";
    int estado = 0;
    for (char &c : text)
    {
        if (estado == 0 && c == '-')
        {
            estado = 1;
        }
        else if (estado == 0 && c == '#')
        {
            continue;
        }
        else if (estado != 0)
        {
            if (estado == 1)
            {
                if (c == '=')
                {
                    estado = 2;
                }
                else if (c == ' ')
                {
                    continue;
                }
            }
            else if (estado == 2)
            {
                if (c == '\"')
                {
                    estado = 3;
                }
                else
                {
                    estado = 4;
                }
            }
            else if (estado == 3)
            {
                if (c == '\"')
                {
                    estado = 4;
                }
            }
            else if (estado == 4 && c == '\"')
            {
                tokens.clear();
                continue;
            }
            else if (estado == 4 && c == ' ')
            {
                estado = 0;
                tokens.push_back(token);
                token = "";
                continue;
            }
            token += c;
        }
    }
    return tokens;
}

string scanner::upper(string a)
{
    string up = "";
    for (char &a : a)
    {
        up += toupper(a);
    }
    return up;
}

bool scanner::compare(string a, string b)
{
    if (upper(a) == upper(b))
    {
        return true;
    }
    return false;
}

void scanner::errores(string operacion, string mensaje)
{

    cout << "\033[1;41m Error\033" << "\033[0;31m(" + operacion + ")~~> \033[0m" << mensaje << endl;
}

void scanner::respuesta(string operacion, string mensaje)
{

    cout << "\033[0;42m(" + operacion + ")~~> \033[0m" << mensaje << endl;
}

bool scanner::confirmar(string mensaje)
{
    cout << mensaje << "[S/N]" << endl;
    string respuesta;
    getline(cin, respuesta);
    if (compare(respuesta, "s"))
    {
        return true;
    }
    return false;
}

void scanner::funcion_excec(vector<string> tokens)
{
    string path = "";
    for (string token : tokens)
    {
        string tk = token.substr(0, token.find("="));
        token.erase(0, tk.length() + 1);
        if (compare(tk, "path"))
        {
            path = token;
        }
    }
    if (path.empty())
    {
        errores("EXEC", " path no ingresado ");
        return;
    }
    excec(path);
}

void scanner::excec(string path)
{
    string filename(path);
    vector<string> lines;
    string line;
    ifstream input_file(filename);
    if (!input_file.is_open())
    {
        cerr << "ERROR al abrir archivo" << filename << endl;
        return;
    }
    while (getline(input_file, line))
    {
        lines.push_back(line);
    }
    for (const auto &i : lines)
    {
        string texto = i;
        string tk = token(texto);
        if (texto != "")
        {
            if (compare(texto, "PAUSE"))
            {
                string pause;
                respuesta("PAUSE", "Presionar enter....");
                getline(cin, pause);
                continue;
            }
            texto.erase(0, tk.length() + 1);
            vector<string> tks = split_tokens(texto);
            functions(tk, tks);
        }
    }
    input_file.close();
    return;
}
