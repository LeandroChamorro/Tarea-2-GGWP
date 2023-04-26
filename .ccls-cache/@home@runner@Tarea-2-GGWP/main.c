#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "Map.h"
#include "Stack.h"

typedef struct{
  int cantitems;
  int ph;
  List *items;
  Stack *pilaAcc;
  char nombreJugador[100];
}TipoJugador;

typedef struct{
  bool accion; //True == Item ; False == ph
  bool itemMas; //True == se Añadió ; False == Se eliminó
  char item[100];
  int ph;
}TipoAccion;

typedef struct{
  char jugador[100];
  int cont;
}tipoItemCont;

//FUNCIONES SECUNDARIAS

//Confirmar longitud menor a 30
void confirmarCaracteres(char *cadena){
  if(strlen(cadena)>=30) 
  //En caso de ser mayor a 30,  le pide al usuario que ingrese una de menor tamaño hasta que la ingresa
  while(strlen(cadena)>=30){
    printf("Ingrese una cantidad de caracteres menor a 30");
    scanf("%s", cadena);
  } 
}

//Ingresar una cadena
void solicitarString(char *cadena, const char *mensaje){
  printf("%s\n", mensaje);
  fflush(stdin);
  scanf("%[^\n]s", cadena);
  getchar();
  confirmarCaracteres(cadena);
}

//Buscar un jugador
TipoJugador* buscarJugador(List *lista, char *nombre){
  for (TipoJugador* p = firstList(lista) ; p != NULL ; p = nextList(lista)){
      //Se busca si el nombre coincide
      if (strcmp(p->nombreJugador, nombre) == 0){
        return p;
      }
    }
  return NULL;
}

//FUNCIONES PRINCIPALES

//Opción 1
void insertarJugador(List *jugadores){
  TipoJugador *jugador;
  jugador=malloc(sizeof(TipoJugador));
  
  //nombre 
  solicitarString(jugador->nombreJugador, "Ingrese el nombre del jugador:");
  
  //Inicializar puntos de habilidad en 0
  jugador->ph = 0;

  //Crear lista de items vacía items
  jugador->items=createList();
  
  //Se agrega el jugador a la lista de jugadores
  pushBack(jugadores, jugador);

  // Se crea su pila de acciones
  jugador->pilaAcc= stack_create();
}


//Opción 2
void mostrarJugador(List *lista){
  //Se lee el nombre del jugador
  char nombre[100];
  solicitarString(nombre, "Ingrese el nombre del Jugador:");
  
  //Se crea un puntero para almacenar los datos del jugador
  TipoJugador *jugador=(TipoJugador*) buscarJugador(lista,nombre);

  //Si el jugador existe, osea no es "NULL"
  printf("╔═════════════════════════════════════════════════════════════╗\n");
  if (jugador != NULL)
  {
    //Se mostrará por pantalla el nombre y puntos de habilidad del jugador 
    printf("  Nombre: %52s\n", jugador->nombreJugador);
    printf("  Puntos de Habilidad: %39i\n", jugador->ph);


    char *actual = firstList(jugador->items);
    if(actual != NULL){
      
      //Se muestra por pantalla el primer item
      printf("  Items/s:");
      char item[100];
      strcpy(item,actual);
      printf("%52s\n",item);

      while(actual!=NULL){
        actual = nextList(jugador->items);
        if(actual!=NULL) {//Se comprueba que no se ha acabado la lista
          strcpy(item , actual);
          printf(" %61s\n",item);
        }
      }
      
      printf("╚═════════════════════════════════════════════════════════════╝\n");
      return;
    }
    else{//Si actual es NULL, no tiene items
      printf("║ El jugador no tiene items registrados                       ║\n");
      printf("╚═════════════════════════════════════════════════════════════╝\n\n");
    }
  }
  else{
    //Se avisa si el jugador no se encuentra registrado en el sistema
    printf("║ El Jugador no se encuentra registrado.                     ║\n");
    printf("╚═════════════════════════════════════════════════════════════╝\n\n");
  }
}

//Opción 3
void insertaItem(TipoJugador *jugador, Map *mapaItems){
  char item[100];
  printf("Ingrese el nombre del %i item:", jugador->cantitems+1);
  solicitarString(item,"");
  
  //Se inserta el item en la lista de items del jugador
  pushBack(jugador->items, strdup(item));
  //se agregó y se suma la cantidad total de items
  jugador->cantitems++;
}

void procesoInsertarItem(List* jugadores, Map* mapaItems){
  char nombre[100];
  solicitarString(nombre,"Inserte nombre de jugador\n");

  TipoJugador *jugador=(TipoJugador*)buscarJugador(jugadores,nombre);
  if (jugador != NULL){
    insertaItem(jugador, mapaItems);
    return;
  }
  printf("El jugador no existe\n\n");
}


//Menú principal
void menu(List *jugadores,Map*mapaItems){
  //Se crea una variable "opcion" la cual será una condicionante para el ciclo "while" base de nuestro programa
  int opcion = 1;
  while(opcion != 0){
    printf("╔════════════════════════════•°🜧°•════════════════════════════╗\n");
    printf("║ Si desea crear el perfil de un jugador presione 1           ║\n");
    printf("║ Si desea mostrar datos de un jugador presione 2             ║\n");
    printf("║ Si desea agregar un item de un jugador presione 3           ║\n");
    printf("║ Si desea eliminar un item de un jugador presione 4          ║\n");
    printf("║ Si desea agregar puntos de habilidad a un jugador presione 5║\n");
    printf("║ Si desea mostrar todos los jugadores con un item en especifico presione 6║\n");
    printf("║ Si desea deshacer la última acción de un jugador presione 7 ║\n");
    printf("║ Si desea exportar datos de jugadores presione 8             ║\n");
    printf("║ Si desea importar datos de jugadores presione 9             ║\n");
    printf("║ Si no desea hacer nada más presione 0                       ║\n");
    printf("╚════════════════════════════•°🜥°•════════════════════════════╝\n\n");
    //Se cambia el valor de la variable "opcion" con un valor que desee el usuario realizar
    scanf("%d", &opcion);
    getchar();
    //Se utiliza un switch para acceder a las opciones de cada función
    switch(opcion){
      case 1: insertarJugador(jugadores);
      break; 
            
      case 2: mostrarJugador(jugadores);
      break;
          
      case 3: procesoInsertarItem(jugadores,mapaItems);
      break;

      case 4: //EliminarItem(jugadores, mapaItems);
      break;
      
      case 5: //agregarPh(jugadores);
      break;
        
      case 6: //ItemEspecifico(jugadores,mapaItems);
      break;

      case 7: //deshacerAcción(jugadores,mapaItems);
      break;
    
      case 8: //importarDatos(jugadores,mapaItems);
      break;

      case 9: //exportarDatos(jugadores,mapaItems);
      break;
      //en caso de ser cero se imprime lo sgte. Para finalizar el programa
      case 0:
        printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣤⣤⣤⣤⣤⣶⣦⣤⣄⡀\n");
        printf("⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⡿⠛⠉⠙⠛⠛⠛⠛⠻⢿⣿⣷⣤⡀\n");
        printf("⠀⠀⠀⠀⠀⠀⠀⠀⣼⣿⠋⠀⠀⠀⠀⠀⠀⠀⢀⣀⣀⠈⢻⣿⣿⡄\n");
        printf("⠀⠀⠀⠀⠀⠀⠀⣸⣿⡏⠀⠀⠀⣠⣶⣾⣿⣿⣿⠿⠿⠿⢿⣿⣿⣿⣄\n");
        printf("⠀⠀⠀⠀⠀⠀⠀⣿⣿⠁⠀⠀⢰⣿⣿⣯⠁⠀⠀⠀⠀⠀⠀⠀⠈⠙⢿⣷⡄\n");
        printf("⠀⠀⣀⣤⣴⣶⣶⣿⡟⠀⠀⠀⢸⣿⣿⣿⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣷\n");
        printf("⠀⢰⣿⡟⠋⠉⣹⣿⡇⠀⠀⠀⠘⣿⣿⣿⣿⣷⣦⣤⣤⣤⣶⣶⣶⣶⣿⣿⣿\n");
        printf("⠀⢸⣿⡇⠀⠀⣿⣿⡇⠀⠀⠀⠀⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠃\n");
        printf("⠀⣸⣿⡇⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠉⠻⠿⣿⣿⣿⣿⡿⠿⠿⠛⢻⣿⡇\n");
        printf("⠀⣿⣿⠁⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣧\n");
        printf("⠀⣿⣿⠀⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿\n");
        printf("⠀⣿⣿⠀⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿\n");
        printf("⠀⢿⣿⡆⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⡇\n");
        printf("⠀⠸⣿⣧⡀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⠃\n");
        printf("⠀⠀⠛⢿⣿⣿⣿⣿⣇⠀⠀⠀⠀⠀⣰⣿⣿⣷⣶⣶⣶⣶⠶ ⢠⣿⣿\n");
        printf("⠀⠀⠀⠀⠀⠀⠀⣿⣿⠀⠀⠀⠀⠀⣿⣿⡇⠀⣽⣿⡏⠁⠀⠀⢸⣿⡇\n");
        printf("⠀⠀⠀⠀⠀⠀⠀⣿⣿⠀⠀⠀⠀⠀⣿⣿⡇⠀⢹⣿⡆⠀⠀⠀⣸⣿⠇\n");
        printf("⠀⠀⠀⠀⠀⠀⠀⢿⣿⣦⣄⣀⣠⣴⣿⣿⠁⠀⠈⠻⣿⣿⣿⣿⡿⠏\n");
        printf("⠀⠀⠀⠀⠀⠀⠀⠈⠛⠻⠿⠿⠿⠿⠋⠁\n");
        printf("          Adiós by GG WP//");
        break;
    }
  }
}

int main(void) {
  List *jugadores = createList();
  Map * mapaItems = createMap(is_equal_string);
  menu(jugadores,mapaItems);
  return 0;
}