#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"list.h"
#include"Map.h"
#include"heap.h"

typedef struct{
    char nombre[50];
    int precio;
    char categoria[50];
    float popularidad;
}Productos;

int is_equal_string(void *key1, void *key2)
{
    if (strcmp((char *)key1, (char *)key2) == 0)
    {
        return 1;
    }
    return 0;
}

Productos *agregarProducto(Map *tiendas)
{
    char nombre[20];
    int precio;
    char categoria[20];
    float popularidad;
    Productos *producto = (Productos *)malloc(sizeof(Productos));
    printf("Ingrese el nombre de la tienda: ");
    char *tienda;
    scanf("%s", tienda);
    if(searchMap(tiendas, tienda) == NULL)
    {
        printf("La tienda no existe\n");
        return NULL;
    }
    printf("Ingrese el nombre del producto: ");
    scanf("%s", nombre);
    if(searchMap(tiendas, nombre) != NULL)
    {
        printf("El producto ya existe\n");
        return NULL;
    }
    strcpy(producto->nombre, nombre);

    printf("Ingrese el precio del producto: ");
    scanf("%d", &precio);
    producto->precio = precio;

    printf("Ingrese la categoria del producto: ");
    scanf("%s", categoria);
    strcpy(producto->categoria, categoria);
    
    printf("Ingrese la popularidad del producto: ");
    scanf("%f", &popularidad);
    producto->popularidad = popularidad;
    return producto;
}


int main()
{
    Map *tiendas = createMap(is_equal_string);
    Productos *nuevoProducto = (Productos *)malloc(sizeof(Productos));
    int opcion = 0;
    while(1)
    {
        printf("1. Agregar tienda\n");
        printf("2. Agregar producto\n");
        printf("3. Buscar producto\n");
        printf("4. Ordenar productos\n");
        printf("5. Guardar productos en lista de deseados\n");
        printf("6. Mostrar lista de deseados\n");
        printf("7. Leer datos de pagina\n");
        printf("0. Salir\n");
        scanf("%d", &opcion);
        switch(opcion)
        {
            case 1: ;
                char *nombreTienda;
                printf("Ingrese el nombre de la tienda: ");
                scanf("%s", nombreTienda);
                if(searchMap(tiendas, nombreTienda) == NULL)
                {
                    insertMap(tiendas, nombreTienda, NULL);
                    printf("Tienda agregada con exito\n");
                }
                else
                    printf("La tienda ya existe\n");
                break;
            case 2:
                nuevoProducto = agregarProducto(tiendas);
                if(nuevoProducto != NULL)
                {
                    char *tienda;
                    printf("Ingrese el nombre de la tienda: ");
                    scanf("%s", tienda);
                    insertMap(tiendas, tienda, nuevoProducto);
                    printf("Producto agregado con exito\n");
                }
                else
                    printf("No se pudo agregar el producto\n");
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:

                break;
            case 7:
                break;
            case 0:
                printf("Saliendo...");
                return 0;
        }
    }
}
