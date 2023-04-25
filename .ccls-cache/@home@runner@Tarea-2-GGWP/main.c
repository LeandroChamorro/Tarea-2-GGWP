#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "Map.h"
#include "Stack.h"


int main(void) {
  List *jugadores = createList();
  Map * mapaItems = createMap(is_equal_string);
  return 0;
}