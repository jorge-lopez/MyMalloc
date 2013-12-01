#include <stdio.h>
#include <string.h>

char memory[8192];

typedef struct nodo_memoria
{
    void *direccion;
    size_t size;
    struct nodo_memoria *siguiente;        
} Nodo;


Nodo *espacioLibre = (Nodo*)memory;

void InitMem()
{       
    espacioLibre->siguiente = NULL;
    espacioLibre->size = 8192 - sizeof(*espacioLibre);
    espacioLibre->direccion = memory + sizeof(*espacioLibre);
}

void *MyMalloc(size_t size_objeto)
{
    if(espacioLibre->size < size_objeto)
    {
        void *direccion = espacioLibre->direccion;
        Nodo *nuevo = (Nodo*)(char*)direccion + size_objeto;
        nuevo = espacioLibre;
        nuevo->size = espacioLibre->size - size_objeto;
        printf("Memoria asignada\n");
    }
    else
        printf("Error al alojar memoria\n");
}


void MyFree(void *p)
{
    char *temp = p - sizeof(espacioLibre);
    Nodo *datos = (Nodo*)temp;
    printf("Memoria Liberada\n");
}

int main()
{
    InitMem();
    int i = 8192;
    int *var = MyMalloc(i * sizeof *var);
    MyFree((void*)var);
}   