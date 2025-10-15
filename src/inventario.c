#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura base del producto
struct Node {
    int id;
    char name[40];
    int stock;
    struct Node* next;
};

// Prototipos de las funciones
void insertarInicio(struct Node** head);
void insertarFinal(struct Node** head);
void buscarPorId(struct Node* head);
void actualizarStock(struct Node* head);
void eliminarPorId(struct Node** head);
void listarInventario(struct Node* head);
void liberarLista(struct Node** head);

int main() {
    struct Node* head = NULL;
    int opcion;

    do {
        printf("\n===== MENU INVENTARIO =====\n");
        printf("1. Insertar producto al inicio\n");
        printf("2. Insertar producto al final\n");
        printf("3. Buscar producto por ID\n");
        printf("4. Actualizar stock por ID\n");
        printf("5. Eliminar producto por ID\n");
        printf("6. Listar inventario\n");
        printf("0. Salir\n");
        printf("===========================\n");
        printf("Elige una opcion: ");
        scanf("%d", &opcion);
        getchar(); // limpiar el buffer

        switch(opcion) {
            case 1:
                insertarInicio(&head);
                break;
            case 2:
                insertarFinal(&head);
                break;
            case 3:
                buscarPorId(head);
                break;
            case 4:
                actualizarStock(head);
                break;
            case 5:
                eliminarPorId(&head);
                break;
            case 6:
                listarInventario(head);
                break;
            case 0:
                liberarLista(&head);
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion invalida, intenta de nuevo.\n");
        }
    } while(opcion != 0);

    return 0;
}

void insertarInicio(struct Node** head) {
    struct Node* nuevo = (struct Node*) malloc(sizeof(struct Node));

    if (nuevo == NULL) {
        printf("Error: no hay memoria disponible.\n");
        return;
    }

    printf("Ingrese ID: ");
    scanf("%d", &nuevo->id);
    getchar();

    printf("Ingrese nombre: ");
    fgets(nuevo->name, 40, stdin);
    nuevo->name[strcspn(nuevo->name, "\n")] = '\0'; // quitar salto de linea

    printf("Ingrese stock: ");
    scanf("%d", &nuevo->stock);
    getchar();

    nuevo->next = *head;
    *head = nuevo;

    printf("Producto insertado al inicio correctamente.\n");
}

void insertarFinal(struct Node** head) {
    struct Node* nuevo = (struct Node*) malloc(sizeof(struct Node));

    if (nuevo == NULL) {
        printf("Error: no hay memoria disponible.\n");
        return;
    }

    printf("Ingrese ID: ");
    scanf("%d", &nuevo->id);
    getchar();

    printf("Ingrese nombre: ");
    fgets(nuevo->name, 40, stdin);
    nuevo->name[strcspn(nuevo->name, "\n")] = '\0';

    printf("Ingrese stock: ");
    scanf("%d", &nuevo->stock);
    getchar();

    nuevo->next = NULL;

    if (*head == NULL) {
        *head = nuevo;
    } else {
        struct Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = nuevo;
    }

    printf("Producto insertado al final correctamente.\n");
}

void buscarPorId(struct Node* head) {
    int id;
    printf("Ingrese ID a buscar: ");
    scanf("%d", &id);

    struct Node* temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            printf("\n--- Producto encontrado ---\n");
            printf("ID: %d\nNombre: %s\nStock: %d\n", temp->id, temp->name, temp->stock);
            return;
        }
        temp = temp->next;
    }

    printf("No se encontró un producto con ese ID.\n");
}

void actualizarStock(struct Node* head) {
    int id, nuevoStock;
    printf("Ingrese ID del producto a actualizar: ");
    scanf("%d", &id);

    struct Node* temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            printf("Stock actual: %d\n", temp->stock);
            printf("Ingrese nuevo stock: ");
            scanf("%d", &nuevoStock);
            temp->stock = nuevoStock;
            printf("Stock actualizado correctamente.\n");
            return;
        }
        temp = temp->next;
    }

    printf("No se encontró un producto con ese ID.\n");
}

void eliminarPorId(struct Node** head) {
    int id;
    printf("Ingrese ID del producto a eliminar: ");
    scanf("%d", &id);

    struct Node* temp = *head;
    struct Node* prev = NULL;

    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("No se encontró un producto con ese ID.\n");
        return;
    }

    if (prev == NULL) {
        *head = temp->next; // era el primero
    } else {
        prev->next = temp->next;
    }

    free(temp);
    printf("Producto eliminado correctamente.\n");
}

void listarInventario(struct Node* head) {
    if (head == NULL) {
        printf("El inventario está vacío.\n");
        return;
    }

    printf("\n--- LISTA DE PRODUCTOS ---\n");
    struct Node* temp = head;
    while (temp != NULL) {
        printf("ID: %d | Nombre: %s | Stock: %d\n", temp->id, temp->name, temp->stock);
        temp = temp->next;
    }
}

void liberarLista(struct Node** head) {
    struct Node* temp;
    while (*head != NULL) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}
