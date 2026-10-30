#include "../lib/scanner.h"
#include "../lib/disco.h"
#include "../lib/mount.h"
#include "../lib/filesystem.h"

#include <iostream>
#include <stdlib.h>
#include <locale>
#include <cstring>
#include <locale>
#include <fstream>
#include <vector>
#include <cstdlib>


using namespace std;

Mount mount;
Disk disco;
FileSystem fileSystem = FileSystem(mount);
Shared shared;

bool logued = false;
scanner::scanner()
{
}

void scanner::start()
{
       
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
        std::cout << "FUNCION MKDISK" << std::endl;
        disco.mkdisk(tks); 
    }else if(compare(token, "RMDISK")){
        std::cout << "FUNCION RMDISK" << std::endl;
        disco.rmdisk(tks);
    }else if(compare(token, "FDISK")){
        std::cout << "FUNCION FDISK" << std::endl;
        disco.fdisk(tks);
    }else if(compare(token, "MOUNT")){
        std::cout << "FUNCION MOUNT" << std::endl;
        mount.mount(tks);
    }else if(compare(token, "MKFS")){
        std::cout << "FUNCION MKFS" << std::endl;
        FileSystem fileSystem = FileSystem(mount);
        fileSystem.mkfs(tks);
    

    }else if(compare(token, "MKUSR")){
        if(!logued){
            shared.handler("MKUSR", " debe de iniciar sesion primero");
            return;
        }
        std::cout << "FUNCION MKUSR" << std::endl;
        user.usr(tks,"MK");

  
    }else if(compare(token, "MKDIR")){
        if(!logued){
            shared.handler("MKDIR", " debe de iniciar sesion primero");
            return;
        }
        string p;
        std::cout << "FUNCION MKDIR" << std::endl;
        Structs::Partition partition = mount.getmount(user.logged.id, &p);
        filemanager.mkdir(tks, partition, p);
  
    }else{
        errores("SYSTEM","El comando ingresado no se reconoce en el sistema \""+token+"\"");
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
    cout << "\033[30;42m "+operacion+" \033[97;48;5;208mDISCO NUEVO \033[0m" << endl;
    cout << "\033[0;42m" + mensaje  + "\033[0m" << endl;

}


