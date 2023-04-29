#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "Map.h"
#include "Stack.h"

typedef struct{
  int cantItems;
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

//Comparar Cadenas
int is_equal_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2)==0) return 1;
    return 0;
}

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

//Con esa función se obtienen las palabras entre comas o punto comas
const char *get_csv_field(char *tmp, int k, char separator1, char separator2) {
    static char *line = NULL;
    static int line_size = 0;
    int open_mark = 0;
    char *ret = (char *) malloc(100 * sizeof(char));
    int ini_i = 0, i = 0;
    int j = 0;
    char separator = separator1;
    if (line == NULL) {
        line_size = strlen(tmp);
        line = (char *) malloc((line_size + 1) * sizeof(char));
        strcpy(line, tmp);
    } else if (strcmp(line, tmp) != 0) {
        line_size = strlen(tmp);
        line = (char *) realloc(line, (line_size + 1) * sizeof(char));
        strcpy(line, tmp);
    }
    while (line[i + 1] != '\0') {
        if (line[i] == '\"') {
            open_mark = 1 - open_mark;
            if (open_mark) ini_i = i + 1;
            i++;
            continue;
        }
        if (open_mark || (line[i] != separator1 && line[i] != separator2)) {
            if (k == j) ret[i - ini_i] = line[i];
            i++;
            continue;
        }
        if (line[i] == separator1 || line[i] == separator2) {
            if (k == j) {
                ret[i - ini_i] = 0;
                return ret;
            }
            j++;
            ini_i = i + 1;
            if (line[i] == separator1) {
                separator = separator1;
            } else {
                separator = separator2;
            }
        }
        i++;
    }
    if (k == j) {
        ret[i - ini_i] = 0;
        return ret;
    }
    return NULL;
}

//FUNCIONES PRINCIPALES

//Opción 1
void insertarJugador(List *jugadores){
  TipoJugador *jugador;
  jugador=malloc(sizeof(TipoJugador));
  
  //Ingresar nombre 
  solicitarString(jugador->nombreJugador, "Ingrese el nombre del jugador:");
  
  //Inicializar puntos de habilidad en 0
  jugador->ph = 0;

  //Inicializar cantidad de items del jugador en 0
  jugador->cantItems=0;
  
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

void insertaItem(TipoJugador *jugador, Map *mapaItems, bool archivo){
  char *item=malloc(100*sizeof(char));
  
  if(archivo==false){
    printf("Ingrese el nombre del %i° item:", jugador->cantItems+1);
    solicitarString(item,"");
    //Se inserta el item en la lista de items del jugador
    pushBack(jugador->items, strdup(item));
    //se agregó y se suma la cantidad total de items
    jugador->cantItems++;
  }else{
    strcpy(item,lastList(jugador->items));
  }

  //PARA PROXIMA FUNCIÓN 6
  //Hay que insertar el jugador en la lista vinculada a cada item del mapa
  
  tipoItemCont *jugadorxCont=malloc(sizeof(tipoItemCont));
  strcpy(jugadorxCont->jugador,jugador->nombreJugador);
  
  //Se busca la lista de jugadores, se manipulará como el valor de la llave
  
  List* itemActual = (List*) searchMap(mapaItems,item);
  
  if(itemActual!=NULL){
    // El item está en el mapa y por lo tanto tambien su lista con los jugadores correspondientes 
    //al item, habría que verificar que el jugador que se añadirá a la lista ya está en esta.
    for (tipoItemCont *aux = firstList(itemActual) ; aux  != NULL ; aux = nextList(itemActual)){
      if(strcmp(aux->jugador, jugadorxCont->jugador)==0){
        aux->cont ++;
        return;
      }
    }
    jugadorxCont->cont=1;
    pushBack(itemActual, jugadorxCont);
  }
  else{
    // Como el item no está en el mapa, se crea la lista de jugadores del item, se añade el
    //jugador a la lista y se inserta todo en el mapa
    itemActual = createList();
    tipoItemCont *aux=malloc(sizeof(tipoItemCont));
    strcpy(aux->jugador,jugador->nombreJugador);
    aux->cont = 1;
    
    pushBack(itemActual,aux);
    insertMap(mapaItems, item, itemActual);
  
    TipoAccion *accionJugador=(TipoAccion *) malloc(sizeof(TipoAccion));
    
    accionJugador->accion=true;// true significa que corresponde a un item
    accionJugador->itemMas=true;//true significa que se añadio
    strcpy(accionJugador->item,item);
    stack_push(jugador->pilaAcc, accionJugador);
  }
}

void procesoInsertarItem(List* jugadores, Map* mapaItems){
  char nombre[100];
  solicitarString(nombre,"Inserte nombre de jugador");

  TipoJugador *jugador=(TipoJugador*)buscarJugador(jugadores,nombre);
  if (jugador != NULL){
    insertaItem(jugador, mapaItems, false);
    return;
  }
  printf("El jugador no existe\n\n");
}

//Opción 4
void erasedproces(TipoJugador *idPlayer, Map *Mapitems){
  char basura[100];
  solicitarString(basura,"Inserte nombre del item que desea eliminar");
  bool esta = false;

  //Se busca el item en la lista de items del jugador, si se encuentra se elimina
  for (char *item = firstList(idPlayer->items) ; item != NULL ; item = nextList(idPlayer->items)){
    if(strcmp(item,basura)==0){
      popCurrent(idPlayer->items);
      //Se confirma que el item existe, para eliminar al jugador de la lista correspondiente
      // a la clave del item del mapa de items
      esta=true;
    }
  }
  
//se elimina el jugador de la lista de jugadores que tienen ese item en el mapa de items
  if(esta==true){
    //Se busca la lista correspondiente al item del mapa de items
    List *listaItems = searchMap(Mapitems, basura);
    //Como la lista está constituida por un tipo de variable tipoItemCont, esta variable guarda el nombre
    //del jugador y la cantidad de veces que tiene ese item, se va revisando la lista hasta encontrar
    //al jugador.
    for (tipoItemCont *jugadorItem = firstList(listaItems) ; jugadorItem != NULL ; jugadorItem = nextList(listaItems)){
      
      if(strcmp(jugadorItem->jugador, idPlayer->nombreJugador)==0){
        //Si lo encuentra y el jugador tiene 2 o mas veces ese item, solo se le quita uno al contador, en el 
        //caso de que solo lo tenga una vez, se le hace popCurrent.
        if(jugadorItem->cont>1){
          jugadorItem->cont--;
        }
        else{
          popCurrent(listaItems);
          printf("El item fué eliminado");
        }
      }
    }
    TipoAccion *accionJugador=(TipoAccion *) malloc(sizeof(TipoAccion));
  
    accionJugador->accion=true;// true significa que corresponde a un item
    accionJugador->itemMas=false;//false se elimino un item
    strcpy(accionJugador->item,basura);
    stack_push(idPlayer->pilaAcc, accionJugador);
    return;
  }
  // en caso de no entrar en ningun caso anterior se le avisa al usuario que ese item no se encuentra
  printf("El item que desea eliminar no existe o no lo posee este jugador\n\n");
}
    
void EliminarItem (List *jugadores, Map *mapaItems){
  //Se pide el nombre de jugador
  char idPlayer[100];
  solicitarString(idPlayer,"Inserte nombre de jugador");

  //Se busca al jugador en la lista de jugadores, si no existe se avisa, si se encuentra llama a la funcion
  //erasedproces
  TipoJugador *jugador=(TipoJugador*)buscarJugador(jugadores,idPlayer);
  if (jugador != NULL){
    erasedproces(jugador, mapaItems);
    return;
  }
  printf("El jugador no existe\n\n");
}

//opcion 5
void agregarPh(List *jugadores){
  char nombre[100];
  solicitarString(nombre,"Inserte nombre de jugador\n");

  TipoJugador *jugador=(TipoJugador*)buscarJugador(jugadores,nombre);
  if (jugador != NULL){
    int newPh;
    printf("Inserte puntos de habilidad a ingresar");
    scanf("%i", &newPh);
    jugador->ph = jugador->ph + newPh;

    TipoAccion *accionJugador=(TipoAccion *) malloc(sizeof(TipoAccion));
    accionJugador->accion=false; // False significa que corresponde a ph
    accionJugador->ph = newPh; //puntos de habilidad agregados
    stack_push(jugador->pilaAcc, accionJugador);
    
    return;
  }
  printf("El jugador no existe\n\n");
}


//Opción 6

void ItemEspecifico(List *jugadores,Map *mapaItems){
  char item[100];
  printf("Ingrese el nombre del item:");
  solicitarString(item,"");

  
  List* JugadoresxItem = searchMap(mapaItems,item);
  
  if(JugadoresxItem!=NULL && firstList(JugadoresxItem)!=NULL){
    printf("Jugadores con el item: \n");
    for (tipoItemCont *aux = firstList(JugadoresxItem) ; aux  != NULL ; aux = nextList(JugadoresxItem)){
      printf("%s\n",aux->jugador);
    }
  }
  else{
    printf("No hay jugadores que posean este ítem\n");
  }
}

//Opción 7

void deshacerAccion(List *jugadores,Map *mapaItems){
  char nombre[100];
  solicitarString(nombre, "Ingrese el nombre del Jugador:");

  //Se crea un puntero para almacenar los datos del jugador
  TipoJugador *jugador=(TipoJugador*) buscarJugador(jugadores,nombre);
  if(jugador==NULL) printf("El jugador no se encuentra registrado\n");
  
  TipoAccion *accion = (TipoAccion *) stack_top(jugador->pilaAcc);

  if(accion==NULL){
    printf("El usuario no tiene acciones\n");
    return;
  }
  if(accion->accion==true){
    if(accion->itemMas == true){
      popBack(jugador->items);
      popFront(jugador->pilaAcc);
      printf("El item ha sido eliminado correctamente del jugador\n");
      List* itemActual = (void*)searchMap(mapaItems,accion->item);
      for (tipoItemCont *aux = firstList(itemActual) ; aux  != NULL ; aux = nextList(itemActual)){
        if(strcmp(aux->jugador, jugador->nombreJugador)==0){
          aux->cont --;
          if(aux->cont==0){
            popCurrent(itemActual);
            return;
          }
        }
      }
    }
    else{
      pushBack(jugador->items, accion->item);      
      List* itemActual = (List*)searchMap(mapaItems,accion->item);
      for (tipoItemCont *aux = firstList(itemActual) ; aux  != NULL ; aux = nextList(itemActual)){
        if(strcmp(aux->jugador, jugador->nombreJugador)==0){
          aux->cont ++;
          return;
        }
      }
      tipoItemCont *jugadorLista = (tipoItemCont *) malloc(sizeof(tipoItemCont));;
      strcpy(jugadorLista->jugador, jugador->nombreJugador);
      jugadorLista->cont++;
      pushBack(itemActual, jugadorLista);
    }
  }
  else{
    int phRestar = accion->ph;
    jugador->ph = jugador->ph - phRestar;
    popFront(jugador->pilaAcc);
    printf("Se actualizaron los puntos de habilidad con éxito\n");
  }
  return;
}

//Opción 8 

void importarArchivo(Map *mapaItems, List *jugadores){
  char archivo[100];
  //Se le pide al usuario que ingrese el nombre del archivo de donde desea importar a los jugadores
  printf("Ingrese el nombre del archivo que quiere ingresar:\n");
  fflush(stdin);
  scanf("%[^\n]s",archivo);
  getchar();

  //Se abre el archivo
  FILE *fp=fopen(archivo, "r");
  if(fp==NULL){
    printf("===============================================================\n");
    printf("                   Error al importar archivo...\n");
    printf("     Asegúrese de importar al programa con el mismo nombre\n");
    printf("===============================================================\n");
    return;
  }
  char linea[801];

  //Se obtiene la primera línea (Que no nos sirve porque son las descripciones de las columnas)
  fgets(linea,800,fp);

  //A partir de aqui las lineas son importante porque tienen la información que necesitamos
  while(fgets(linea,800,fp)!=NULL){
    //Es un jugador por linea, por lo que aquí se crea
    TipoJugador *jugador;
    jugador=malloc(sizeof(TipoJugador));
    int j=0;

    //Con esa función se obtienen las palabras entre comas o punto comas
    while(get_csv_field(linea, j, ',', ';')!=NULL){

      //Se le asigna a un auxiliar la palabra, que va cambiando por columna, en la primera es el nombre del jugador, en la segunda son los puntos de habilidad, dependiendo de lo que sea se lleva un contador para asignarle toda la información al jugador.
      char *aux =(char *) get_csv_field(linea, j, ',', ';');
      if(aux==NULL) break;
      
      if(j==0){
        strcpy(jugador->nombreJugador,aux);
        //Se agrega el jugador a la lista de jugadores
        pushBack(jugadores, jugador);
        // Se crea su pila de acciones
        jugador->pilaAcc= stack_create();
      }
      if(j==1){
        //Se guardan los puntos de habilidad
        jugador->ph=atoi(aux);
        TipoAccion *accion=malloc(sizeof(TipoAccion));
        accion->accion=false;
        accion->ph=jugador->ph;
        //Se guarda la acción en la pila de acciones
        stack_push(jugador->pilaAcc,accion);
      }
      if(j==2){
        //Se le asigna la cantidad de items al jugador
        jugador->cantItems=atoi(aux);
      }
      if(j==3){
        //Se inserta el primer ítem
        jugador->items=createList();
        pushBack(jugador->items, aux);
        insertaItem(jugador, mapaItems, jugadores, true);
      }
      if(j>=4){
        //Se insertan el resto de item
        pushBack(jugador->items, aux);
        insertaItem(jugador, mapaItems, jugadores, true);
      }
      j++;
    }
    pushBack(jugadores, jugador);
  }
  printf("===============================================================\n");
  printf("        La importación de jugadores fue hecha con éxito\n");
  printf("===============================================================\n");
  fclose(fp);
}


// opcion 9

void exportarDatos(List *jugadores){
  //Se crea una string estática para dar un nombre al archivo que exportará a los jugadores
  
  char archivo[100];
  printf("Nombre al archivo que se creará:\n");
  scanf("%[^\n]s",archivo);
  getchar();
  FILE *fp = fopen(archivo, "w");
  
  fprintf(fp, "Nombre,Puntos,#items,Item 1,Item 2,Item 3,Item 4,Item 5,Item 6,Item 7,Item 8\n");
  //Se comienza a recorrer la lista jugaadores para imprimir los datos al archivo que se exportará todo
  for (TipoJugador *player = firstList(jugadores) ; player != NULL ; player = nextList(jugadores)){
    fprintf(fp, "%s,%d,%d,", player->nombreJugador, player->ph, player->cantItems);
    
    //Dentro de la iteración "for", se entra a otra, ya que puede existir el caso de que hayan más de un item
    for(char* items=firstList(player->items) ; items!=NULL; items=nextList(player->items)){
      
      fprintf(fp, "%s,", items);
    }
    fprintf(fp, "\n");
  }
  
  //De no haber errores, se muestra el siguiente mensaje por pantalla 
  printf("===============================================================\n");
  printf("        La exportación de jugadores fue hecha con éxito\n");
  printf("▒▒▒▒▒▒▒▒▒▄▄▄▄▒▄▄▄▒▒▒\n");
  printf("▒▒▒▒▒▒▄▀▀▓▓▓▀█░░░█▒▒\n");
  printf("▒▒▒▒▄▀▓▓▄██████▄░█▒▒\n");
  printf("▒▒▒▄█▄█▀░░▄░▄░█▀▀▄▒▒\n");
  printf("▒▒▄▀░██▄░░▀░▀░▀▄▓█▒▒\n");
  printf("▒▒▀▄░░▀░▄█▄▄░░▄█▄▀▒▒\n");
  printf("▒▒▒▒▀█▄▄░░▀▀▀█▀▓█▒▒▒\n");
  printf("▒▒▒▄▀▓▓▓▀██▀▀█▄▀▒▒▒▒\n");
  printf("▒▒█▓▓▄▀▀▀▄█▄▓▓▀█▒▒▒▒\n");
  printf("▒▒▀▄█░░░░░█▀▀▄▄▀█▒▒▒\n");
  printf("▒▒▒▄▀▀▄▄▄██▄▄█▀▓▓█▒▒\n");
  printf("▒▒█▀▓█████████▓▓▓█▒▒\n");
  printf("▒▒█▓▓██▀▀▀▒▒▒▀▄▄█▀▒▒\n");
  printf("▒▒▒▀▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒\n");
  printf("===============================================================\n");
  fclose(fp);
  
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
    printf("║ Si desea mostrar todos los jugadores con un item            ║\n");
    printf("║ en especifico presione 6                                    ║\n");
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

      case 4: EliminarItem(jugadores, mapaItems);
      break;
      
      case 5: agregarPh(jugadores);
      break;
        
      case 6: ItemEspecifico(jugadores,mapaItems);
      break;

      case 7: deshacerAccion(jugadores,mapaItems);
      break;
    
      case 8: exportarDatos(jugadores);
      break;

      case 9: importarDatos(jugadores,mapaItems);
      break;
      //en caso de ser cero se imprime lo sgte. Para finalizar el programa
      case 0:
        printf("⠀⠀⠀⠀⠀⠀⠀⢀⣤⠖⠛⠉⠉⠛⠶⣄⡤⠞⠛⠛⠙⠳⢤⡀\n");
        printf("⠀⠀⠀⠀⠀⠀⢠⠟⠁⠀⠀⠀⠀⠀⠀ ⠀⢰⡆⠀⠀⠐⡄⠻⡄\n");
        printf("⠀⠀⠀⠀⠀⠀⡾⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠛⠦⠤⣤⣇ ⢷\n");
        printf("⠀⠀⠀⠀⠀⠀⢳⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀   ⡼\n");
        printf("⠀⠀⠀⠀⠀⠀⠘⣆⢰⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ ⣼⠃\n");
        printf("⠀⠀⠀⠀⠀⠀⠀⠙⣎⢳⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡾⠃\n");
        printf("⠀⠀⠀⠀⠀⠀⠀⠀⠈⢳⣝⠳⣄⡀⠀⠀⠀⠀⠀⢀⡴⠟⠁\n");
        printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠳⢮⣉⣒⣖⣠⠴⠚⠉\n");
        printf("⠀⠀⠀⣀⣴⠶⠶⢦⣀⠀⠀⠀⠀⠀⠉⠁⠀⠀⠀⠀ ⣠⣤⣤⣀⠀\n");
        printf("⠀⢀⡾⠋⠀⠀⠀⠀⠉⠧⠶⠒⠛⠛⠛⠛⠓⠲⢤⣴⡟⠅⠀⠀⠈⠙⣦⠀\n");
        printf("⠀⣾⠁⠀⠀⠀⠀⠀⠀⠀⣠⡄⠀⠀⠀⣀⠀⠀⠀ ⠀⠀⠀⠀⠀⠀⠸⣇\n");
        printf("⠀⣿⡀⠀⠀⠀⠀⠀⢀⡟⢁⣿⠀⢠⠎⢙⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣽\n");
        printf("⠀⠈⢻⡇⠀⠀⠀⠀⣾⣧⣾⡃⠀⣾⣦⣾⠇⠀⠀⠀⠀⠀⠀⠀ ⠀⣼⠇\n");
        printf("⠀⢰⡟⠀⡤⠴⠦⣬⣿⣿⡏⠀⢰⣿⣿⡿⢀⡄⠤⣀⡀⠀⠀⠀⠰⢿⡁\n");
        printf("⠀⡞⠀⢸⣇⣄⣤⡏⠙⠛⢁⣴⡈⠻⠿⠃⢚⡀⠀⣨⣿⠀⠀⠀⠀⢸⡇\n");
        printf("⢰⡇⠀⠀⠈⠉⠁⠀⠀⠀⠀⠙⠁⠀⠀⠀⠈⠓⠲⠟⠋⠀⠀⠀⠀⢀⡇\n");
        printf("⠈⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠇\n");
        printf("⠀⢹⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⡄\n");
        printf("⠀⠀⠻⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣽⠋⣷\n");
        printf("⠀⠀⢰⣿⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⡾⠃⠀⣿⡇\n");
        printf("⠀⠀⢸⡯⠈⠛⢶⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⠾⠋ ⠀⠀⣿⡇\n");
        printf("⠀⠀⠈⣷    ⠉⠛⠶⢶⣶⠶⠶⢶⡶⠾⠛⠉⠀⠀⠀   ⣿⡇\n");
        printf("⠀⠀⠀⠈⠳⣤  ⠀⣀⡶⠟⠁⠀⠀⠘⢷⡄⠀     ⢀⣾⡿\n");
        printf("⠀⠀⠀⠀⠀⠈⠙⠛⠛⠋⠀⠀⠀⠀  ⠀⠙⠶⣤⣀⣀⣤⡶⠟⠁\n");
        printf("         by GG WP//");
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