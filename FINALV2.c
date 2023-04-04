#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define DIM 55
#define DIM2 1000

typedef struct{
    int id;
    char marca[DIM];
    char modelo[DIM];
    float precio;
    float descuento;
} registro;


void getData(char* nomArchivo, registro* data);
int TamVector(registro* data);
float CalculaDto(float precio, float descuento);
int getMejorModelo(registro* data);
void mostrarOrdenado(registro* data);


int main() {

    char *nombre="productos.txt";

    registro* Productos;
    //Productos=(registro*)malloc(sizeof(registro)); // SI COMPILA CLION EN MAC ESTO HACE FALLAR
    Productos=(registro*)calloc(DIM2,sizeof(registro));;

    int idprod;

    getData(nombre, Productos);

    idprod=getMejorModelo(Productos);
    printf("El ID del producto mas barato es: %d\n", idprod);

    mostrarOrdenado(Productos);

    return 0;

}



void getData(char* nomArchivo, registro* data){

    FILE* ArchivoProductos;
    ArchivoProductos=fopen(nomArchivo,"r");

    int i=0;
    int linea=1;
    char texto[2000];
    char* separador=",\n";
    char* token;


    if (ArchivoProductos !=NULL){

        fgets(texto,2000,ArchivoProductos);
        printf("%s", texto);

        while (!feof(ArchivoProductos)) {
            if (linea > 1) {

                token = strtok(texto, separador);
                data[i].id = atoi(token);

                token = strtok(NULL, separador);
                strcpy(data[i].marca, token);

                token = strtok(NULL, separador);
                strcpy(data[i].modelo, token);

                token = strtok(NULL, separador);
                data[i].precio = (float)atof(token);

                token = strtok(NULL, separador);
                data[i].descuento = (float)atof(token);

                i = i + 1;

            } else {
            }
            linea = linea + 1;
            fgets(texto, 2000, ArchivoProductos);
        }
        fclose(ArchivoProductos);
    } else {
        printf("Error de lectura del archivo");
    }


    data[i].id = -999999;
    strcpy(data[i].marca, "-999999");
    strcpy(data[i].modelo, "-999999");
    data[i].precio = -999999;
    data[i].descuento = -999999;

    data=(registro * )realloc(data, i* sizeof(registro));

}


int TamVector(registro* data){

    int i=0;

    while (data[i].id != -999999){
        i=i+1;
    }

    return i;
}

float CalculaDto(float precio, float descuento){

    float preciocondto;

    preciocondto=precio-(precio*descuento);

    return preciocondto;
}


int getMejorModelo(registro* data){

    int dim;
    dim=TamVector(data);

    int idmasbarato=data[0].id;
    float preciomasbarato=CalculaDto(data[0].precio, data[0].descuento);

    for (int i = 0; i <dim ; ++i) {

        printf("ID:%d, Marca: %s, Modelo: %s, Precio: %f, Descuento: %f\n", data[i].id, data[i].marca, data[i].modelo, data[i].precio, data[i].descuento);

        if (preciomasbarato>CalculaDto(data[i].precio, data[i].descuento)){
            preciomasbarato=CalculaDto(data[i].precio, data[i].descuento);
            idmasbarato=data[i].id;
        }
    }

    return idmasbarato;

}


void intercambio(registro *a, registro *b) {
    registro c;

    c = *a;
    *a = *b;
    *b = c;
}


void OrdenamientoBurbuja(registro *vec) {

    int i, j, dim;

    dim=TamVector(vec);
    dim=dim-1;

    for (i = 0; i < dim-1; i++) {
        for (j = 0; j < dim - i; j++){
            if (vec[j].precio > vec[j+1].precio){
                intercambio(&vec[j], & vec[j+1]);
            }
        }
    }
}


void mostrarOrdenado(registro* data){

    int dim;
    dim=TamVector(data);

    OrdenamientoBurbuja(data);

    for (int i = 0; i <dim ; ++i) {
        printf("Precio: %f, Marca: %s, Modelo: %s\n", data[i].precio, data[i].marca, data[i].modelo);
    }

}




