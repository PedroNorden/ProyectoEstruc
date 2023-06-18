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
    printf("Ingrese el nombre del producto: ");
    scanf("%s", nombre);
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

void buscarProducto(Map *tiendas, char *nombreProducto)
{
    char *nombreTienda = (char *)malloc(sizeof(char)*50);
    printf("Ingrese el nombre de la tienda. Si no sabe la tienda, ingrese un 0: ");
    scanf("%s", nombreTienda);
    if(strcmp(nombreTienda, "0") == 0)
    {
        Map *mapaProductos = firstMap(tiendas);
        while(mapaProductos != NULL)
        {
            Productos *producto = firstMap(mapaProductos);
            while(producto != NULL)
            {
                if(strcmp(producto->nombre, nombreProducto) == 0)
                {
                    printf("Producto encontrado\n");
                    printf("Nombre: %s\n", producto->nombre);
                    printf("Precio: %d\n", producto->precio);
                    printf("Categoria: %s\n", producto->categoria);
                    printf("Popularidad: %f\n", producto->popularidad);
                    return;
                }
                producto = nextMap(mapaProductos);
            }
            mapaProductos = nextMap(tiendas);
        }
    }
    else
    {
        Map *mapaProductos = searchMap(tiendas, nombreTienda);
        if(mapaProductos == NULL)
        {
            printf("La tienda no existe\n");
            return;
        }
        Productos *producto = firstMap(mapaProductos);
        while(producto != NULL)
        {
            if(strcmp(producto->nombre, nombreProducto) == 0)
            {
                printf("Producto encontrado\n");
                printf("Nombre: %s\n", producto->nombre);
                printf("Precio: %d\n", producto->precio);
                printf("Categoria: %s\n", producto->categoria);
                printf("Popularidad: %f\n", producto->popularidad);
                return;
            }
            producto = nextMap(mapaProductos);
        }
    }
}

void eliminarProducto(Map *tiendas, char *nombreProducto)
{
    char *nombreTienda = (char *)malloc(sizeof(char)*50);
    printf("Ingrese el nombre de la tienda. Si no sabe la tienda, ingrese un 0: ");
    scanf("%s", nombreTienda);
    if(strcmp(nombreTienda, "0") == 0)
    {
        Map *mapaProductos = firstMap(tiendas);
        while(mapaProductos != NULL)
        {
            Productos *producto = firstMap(mapaProductos);
            while(producto != NULL)
            {
                if(strcmp(producto->nombre, nombreProducto) == 0)
                {
                    eraseMap(mapaProductos, producto->nombre);
                    printf("Producto eliminado\n");
                    return;
                }
                producto = nextMap(mapaProductos);
            }
            mapaProductos = nextMap(tiendas);
        }
    }
    else
    {
        Map *mapaProductos = searchMap(tiendas, nombreTienda);
        if(mapaProductos == NULL)
        {
            printf("La tienda no existe\n");
            return;
        }
        Productos *producto = firstMap(mapaProductos);
        while(producto != NULL)
        {
            if(strcmp(producto->nombre, nombreProducto) == 0)
            {
                eraseMap(mapaProductos, producto->nombre);
                printf("Producto eliminado\n");
                return;
            }
            producto = nextMap(mapaProductos);
        }
    }
                    
}

int main()
{
    Map *mapaTiendas = createMap(is_equal_string);
    char *nombreTienda = (char *)malloc(sizeof(char)*50);
    Productos *nuevoProducto = (Productos *)malloc(sizeof(Productos));
    char nombreProducto[50];
    int opcion = 0;
    while(1)
    {
        printf("1. Agregar tienda\n");
        printf("2. Agregar producto\n");
        printf("3. Buscar producto\n");
        printf("4. Eliminar producto\n");
        printf("5. Ordenar productos\n");
        printf("6. Guardar productos en lista de deseados\n");
        printf("7. Mostrar lista de deseados\n");
        printf("8. Leer datos de pagina\n");
        printf("0. Salir\n");
        scanf("%d", &opcion);
        switch(opcion)
        {
            case 1: ;
                printf("Ingrese el nombre de la tienda: ");
                scanf("%s", nombreTienda);
                if(searchMap(mapaTiendas, nombreTienda) != NULL)
                {
                    printf("La tienda ya existe\n");
                    break;
                }
                Map *mapaProductos = createMap(is_equal_string);
                insertMap(mapaTiendas, nombreTienda, mapaProductos);
                printf("Tienda agregada con exito\n");
                break;
            case 2:
                nuevoProducto = agregarProducto(mapaTiendas);
                printf("A que tienda pertenece el producto?: ");
                scanf("%s", nombreTienda);
                if(searchMap(mapaTiendas, nombreTienda) == NULL)
                {
                    printf("La tienda no existe\n");
                    break;
                }
                
                insertMap(mapaProductos, nuevoProducto->nombre, nuevoProducto);
                insertMap(mapaTiendas, nombreTienda, mapaProductos);
                break;
            case 3: ;
                printf("Ingrese el nombre del producto: ");
                scanf("%s", nombreProducto);
                buscarProducto(mapaTiendas, nombreProducto);
                break;
            case 4: ;
                printf("Ingrese el nombre del producto: ");
                scanf("%s", nombreProducto);
                eliminarProducto(mapaTiendas, nombreProducto);
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
