#include <colapersonas.h>
#include <listamaletas.h>


using namespace std;


ColaPersonas::ColaPersonas()
{
    this->Primero = nullptr;
    this->Ultimo = nullptr;
}

NodoPersona* ColaPersonas::GenerarPersona()
{
    int NoMaletas = GenerarNumero(1,4);
    int NoDocumentos = GenerarNumero(1,10);
    int NTR = GenerarNumero(1,3);

    NodoPersona* tmp = new NodoPersona(IDPersona,NoMaletas,NoDocumentos,NTR);
    IDPersona++;
    return tmp;
}

void ColaPersonas::IngresarPersona(ListaMaletas* l)
{
    NodoPersona* nuevo = GenerarPersona();
    l->CargarMaletas(nuevo->NoMaletas);
    if(this->Primero == nullptr)
    {
        this->Primero = nuevo;
        this->Ultimo = nuevo;
    }
    else
    {
        nuevo->siguiente = this->Primero;
        this->Primero = nuevo;
    }
}

void ColaPersonas::IngresarPersona2(NodoPersona *nueva)
{
    if(this->Primero == nullptr)
    {
        this->Primero = nueva;
        this->Ultimo = nueva;
    }
    else
    {
        nueva->siguiente = this->Primero;
        this->Primero = nueva;
    }
}

void ColaPersonas::CargarPasajeros(int Cantidad, ListaMaletas *l)
{
    if(Cantidad > 0)
    {
        IngresarPersona(l);
        CargarPasajeros(Cantidad - 1, l);
    }
}

NodoPersona* ColaPersonas::SacarPersona()
{
    if(this->Primero != nullptr)
    {
        NodoPersona* tmp = this->Primero;
        if(this->Primero == this->Ultimo)
        {
            this->Primero = nullptr;
            this->Ultimo = nullptr;
            return tmp;
        }
        else
        {
            while(tmp->siguiente != this->Ultimo)
                tmp = tmp->siguiente;

            NodoPersona* tmp2 = this->Ultimo;
            this->Ultimo = tmp;
            this->Ultimo->siguiente = nullptr;
            return tmp2;
        }
    }
    return nullptr;
}

bool ColaPersonas::EstaVacia()
{
    if(this->Primero == nullptr)
        return true;
    return false;

}

string ColaPersonas::GenerarSubGrafo(int NumeroCola)
{
    string subgrafo = "subgraph cluster_ColaPersonas" + to_string(NumeroCola) + "{\n";

    subgrafo += "node [shape=box, style=filled];\n";
    subgrafo += "label = \"Cola de Personas\";\n";
    subgrafo += "color = blue;\n";

    if(this->Primero != nullptr)
    {
        NodoPersona* aux = this->Primero;

        do {
            if(aux->siguiente != nullptr)
            {


                subgrafo += "\"Persona " + to_string(aux->siguiente->IDPersona) + "\n";
                subgrafo += "No. Maletas: " + to_string(aux->siguiente->NoMaletas) + "\n";
                subgrafo += "No. Documentos: " + to_string(aux->siguiente->NoDocumentos) + "\n";
                subgrafo += "Turdos para Registro: " + to_string(aux->siguiente->NoTurnosR) + "\"";

                subgrafo += " -> ";

            }

            subgrafo += "\"Persona " + to_string(aux->IDPersona) + "\n";
            subgrafo += "No. Maletas: " + to_string(aux->NoMaletas) + "\n";
            subgrafo += "No. Documentos: " + to_string(aux->NoDocumentos) + "\n";
            subgrafo += "Turdos para Registro: " + to_string(aux->NoTurnosR) + "\"";



            aux = aux->siguiente;
        } while (aux != nullptr);

        free(aux);
    }

    subgrafo = subgrafo + "\n" + "}" + "\n\n";
    return subgrafo;
}
