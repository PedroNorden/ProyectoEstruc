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
    int popularidad;
}Productos;

int is_equal_string(void *key1, void *key2)
{
    if (strcmp((char *)key1, (char *)key2) == 0)
    {
        return 1;
    }
    return 0;
}

Productos *agregarProducto(Map *tiendas, char *nombreTienda)
{
    char nombre[20];
    int precio;
    char categoria[20];
    int popularidad;
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
    scanf("%d", &popularidad);
    producto->popularidad = popularidad;
    return producto;
}

Productos *buscarProducto(Map *tiendas, char *nombreProducto)
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
                    return producto;
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
            return NULL;
        }
        Productos *producto = firstMap(mapaProductos);
        while(producto != NULL)
        {
            if(strcmp(producto->nombre, nombreProducto) == 0)
            {
                return producto;
            }
            producto = nextMap(mapaProductos);
        }
    }
    return NULL;
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

void ordenarProductos(Map *mapaTiendas, char *nombreTienda)
{
    int opcion = 0;
    Map *mapaProductos = searchMap(mapaTiendas, nombreTienda);
    Heap *productosOrdenados = createHeap();
    Productos *producto = firstMap(mapaProductos);
    List *listaProductos = createList(); // Sirve para ordenar por precio de menor a mayor
    int cantidadProductos = 0;
    printf("Desea ordenar por precio o por popularidad? (1 = popularidad, 2 = precio): ");
    scanf("%d", &opcion);
    if(opcion == 1)
    {
        while(producto != NULL)
        {
            heap_push(productosOrdenados, producto, producto->popularidad);
            cantidadProductos++;
            producto = nextMap(mapaProductos);
        }
    
        for(int i = 0; i < cantidadProductos; i++)
        {
            producto = (Productos *)heap_top(productosOrdenados);
            printf("Nombre: %s |", producto->nombre);
            printf(" Precio: %d |", producto->precio);
            printf(" Categoria: %s |", producto->categoria);
            printf(" Popularidad: %d\n", producto->popularidad);
            heap_pop(productosOrdenados);
        }
    }
    else
    {
        while(producto != NULL)
        {
            heap_push(productosOrdenados, producto, producto->precio);
            cantidadProductos++;
            producto = nextMap(mapaProductos);
        }
        for(int i = 0; i < cantidadProductos; i++)
        {
            producto = (Productos *)heap_top(productosOrdenados);
            pushFront(listaProductos, producto); // Con el pushFront se ordena de menor a mayor
            heap_pop(productosOrdenados);
        }
        producto = firstList(listaProductos);
        for(int i = 0; i < cantidadProductos; i++)
        {
            printf("Nombre: %s |", producto->nombre);
            printf("Precio: %d |", producto->precio);
            printf("Categoria: %s |", producto->categoria);
            printf("Popularidad: %d\n", producto->popularidad);
            producto = nextList(listaProductos);
        }
    }
    free(productosOrdenados);
    cleanList(listaProductos);
}


int main()
{
    Map *mapaTiendas = createMap(is_equal_string);
    Map *nombresTiendas = createMap(is_equal_string);
    Productos *nuevoProducto = (Productos *)malloc(sizeof(Productos));
    List *listaDeseados = createList();
    char nombreProducto[50];
    int opcion = 0;
    while(1)
    {   printf("===========================================================\n");
        printf("||    1. Agregar tienda                                   ||\n");
        printf("||    2. Agregar producto                                 ||\n");
        printf("||    3. Buscar producto                                  ||\n");
        printf("||    4. Eliminar producto                                ||\n");
        printf("||    5. Ordenar productos                                ||\n");
        printf("||    6. Guardar productos en lista de deseados           ||\n");
        printf("||    7. Mostrar lista de deseados                        ||\n");
        printf("||    8. Leer datos de pagina                             ||\n");
        printf("||    0. Salir                                            ||\n");
        printf("===========================================================\n");
        scanf("%d", &opcion);
        switch(opcion)
        {
            case 1: ;
                char *nombreTienda = (char *)malloc(sizeof(char)*50);
                printf("Ingrese el nombre de la tienda: ");
                scanf("%s", nombreTienda);
                if(searchMap(nombresTiendas, nombreTienda) != NULL)
                {
                    printf("La tienda ya existe\n");
                    break;
                }
                Map *mapaProductos = createMap(is_equal_string);
                insertMap(mapaTiendas, nombreTienda, mapaProductos);
                insertMap(nombresTiendas, nombreTienda, nombreTienda);
                printf("Tienda agregada con exito\n");
                break;
            case 2: 
                nombreTienda = (char *)malloc(sizeof(char)*50);
                printf("A que tienda pertenece el producto?: ");
                scanf("%s", nombreTienda);
                
                if(searchMap(nombresTiendas, nombreTienda) == NULL)
                {
                    printf("La tienda no existe\n");
                    break;
                }
                nuevoProducto = agregarProducto(mapaTiendas, nombreTienda);
                insertMap(mapaProductos, nuevoProducto->nombre, nuevoProducto);
                insertMap(mapaTiendas, nombreTienda, mapaProductos);
                printf("Producto agregado con exito\n");
                break;
            case 3: ;
                printf("Ingrese el nombre del producto: ");
                scanf("%s", nombreProducto);
                Productos *producto = buscarProducto(mapaTiendas, nombreProducto);
                if(producto == NULL)
                {
                    printf("Producto no encontrado\n");
                    break;
                }
                printf("Producto encontrado\n");
                printf("Nombre: %s |", producto->nombre);
                printf("Precio: %d |", producto->precio);
                printf("Categoria: %s |", producto->categoria);
                printf("Popularidad: %d\n", producto->popularidad);
                break;
            case 4: ;
                printf("Ingrese el nombre del producto: ");
                scanf("%s", nombreProducto);
                eliminarProducto(mapaTiendas, nombreProducto);
                break;
            case 5:
                nombreTienda = (char *)malloc(sizeof(char)*50);
                printf("Ingrese el nombre de la tienda: ");
                scanf("%s", nombreTienda);
                if(searchMap(nombresTiendas, nombreTienda) == NULL)
                {
                    printf("La tienda no existe\n");
                    break;
                }
                ordenarProductos(mapaTiendas, nombreTienda);
                break;
            case 6:
                printf("Ingrese el nombre del producto: ");
                scanf("%s", nombreProducto);
                producto = buscarProducto(mapaTiendas, nombreProducto);
                if(producto == NULL)
                {
                    printf("Producto no encontrado\n");
                    break;
                }
                pushBack(listaDeseados, producto);
                printf("Producto agregado a la lista de deseados\n");
                break;
            case 7:
                producto = firstList(listaDeseados);
                while(producto != NULL)
                {
                    printf("Nombre: %s |", producto->nombre);
                    printf("Precio: %d |", producto->precio);
                    printf("Categoria: %s |", producto->categoria);
                    printf("Popularidad: %d\n", producto->popularidad);
                    producto = nextList(listaDeseados);
                }
                break;
            case 8:
                printf("Trabajo en progreso...\n");
                break;
            case 0:
                printf("Saliendo...");
                return 0;
        }
    }
}
