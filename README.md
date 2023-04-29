Integrantes de GG WP: 
- Alex Aravena
- Álvaro Catalán
- Leandro Chamorro
- Patricio Henríquez

Se compila primero pidiendo la opción del menú que se quiere ejecutar, recomendamos en primera instancia ejecutar la primera opción o la octava, puesto que si se hace cualquier otra opción antes solo dirá que no hay pacientes.
//Opción 1
Entonces, primero, al registrar un jugador, solo se nos pedirá su nombre y se creará su respectiva lista,
donde tanto los items como sus pH(puntos de habilidad), se inicializarán en 0, además, se creará su lista de items y pila de acciones.
//Opción 2
Esta opción netamente muestra al jugador y sus respectivo "inventario".
//Opción 3
Esta opción se encarga de agregar un item al inventario de un jugador (El cuál es solicitado al usuario), cuándo este es ingresado se le pide el nombre del item y este se encargará de dos cosas,
la primera es insertar el item en el inventario del jugador y actualizar su pila de acciones, la segunda es que ingresa al jugador en un mapa de items que servirá en una opción más adelante.
//Opción 4
La opción 4 solicita al usuario algún item del jugador que se desea eliminar, dónde, a su vez, actualiza todas aquellas variables que tengan que ver con el mismo item. Como por ejemplo, eliminar al jugador del 
mapa de items, actualizar la pila de acción y sus respectivas flags.
//Opción 5
Esta opción solicita al usuario el nombre del jugador al que se le desean modificar sus puntos de habilidad (veáse como agregar a los puntos de habilidad, si es que habían agregados previamente). Si el jugador no existe,
muestra un jugador por pantalla.
//Opción 6
