Integrantes de GG WP: 
- Alex Aravena
- Álvaro Catalán
- Leandro Chamorro
- Patricio Henríquez

Se compila primero pidiendo la opción del menú que se quiere ejecutar, recomendamos en primera instancia ejecutar la primera opción o la octava, puesto que si se hace cualquier otra opción antes solo dirá que no hay jugadores.
//Opción 1
Entonces, primero, al registrar un jugador, solo se nos pedirá su nombre y se creará su respectiva lista,
donde tanto la cantidad de items como sus pH(puntos de habilidad), se inicializarán en 0, además, se creará su lista de items y pila de acciones.
//Opción 2
Esta opción solicita el nombre del jugador y lo muestra junto a sus puntos de habilidad y su respectivo "inventario".
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
La opción 6 se encarga de mostrar todos los jugadores que tiene determinado ítem, el cuál será ingresado por el usuario.
//Opción 7
Esta opción se encargará de deshacer la última acción que haya realizado el usuario respecto a cualquier jugador, esto mediante el ingreso de este último por el usuario, donde, mediante al acceso a la pila de acciones que se hicieron respecto al jugador,
se procederá a eliminar la determinada acción que se haya realizado.
//Opción 8
Al momento de importar la información, se le pide al usuario que ingrese el nombre del archivo tal cual está subido al programa, incluyendo la extención del archivo, por ejemplo, si el archivo es "players10000.csv", ingresarlo tal y como es, incluyendo la terminación del archivo ".csv".
//Opción 9
La opción 9 exporta todos los pacientes a un archivo de la terminación que deseemos conveniente, en este caso, si lo pide con terminación ".csv"
simplemente deberá escribirlo al final. Por ejemplo, si mi archivo 
lo quiero nombrar como "players", para que sea terminación ".csv" 
simplemente debo agregarlo al final, el resultado será "players.csv".

Al testear, todas la opciones funcionan correctamente. :)

Herramientas utilizadas: Replit para trabajar de forma conjunta.

Nombre Equipo: GG WP
Participación activa y equitativa: 20 pts
Resolución de conflictos: 20 pts
Colaboración: 20 pts
Responsabilidad: 20 pts
Comunicación: 20 pts
Pje Total: 100 pts

Tabla aporte Individual

Nombre: Alex Aravena; Álvaro Catalán; Leandro Chamorro; Patricio Henríquez
Participación: 20 pts; 20 pts; 20 pts; 20 pts
Responsabilidad: 20 pts; 15 pts; 20 pts; 15 pts
Comunicación: 20 pts; 20 pts; 20 pts; 15 pts
Calidad del Trabajo: 20 pts; 20 pts; 20 pts; 20 pts
Trabajo en Equipo: 20 pts; 20 pts; 20 pts; 20 pts
Pje Total: 100 pts; 95 pts; 100 pts; 90 pts

Aspectos positivos y a mejorar:
Alex: Autocritico a la hora de trabajar, realiza aportes de mucha importancia y está en constante comunicación con el profesor en caso de duda.
Álvaro: Trabajo por su cuenta en todo lo que él podía hacer.
Leandro: Full comprometido con la tarea, ningún punto a mejorar.
Patricio: Si bien no pudo conectarse todo el tiempo, tuvo buena disposición a los demás.
⢕⢕⢕⢕⢕⢕⢕⢕⢕⢕⢕⢕⢕⢕⢕⢕⢕⢕⢕⢕⢕⢕⠕⠕⠕⠕⢕⢕
⢕⢕⢕⢕⢕⠕⠕⢕⢕⢕⢕⢕⢕⢕⢕⢕⢕⠕⠁⣁⣠⣤⣤⣤⣶⣦⡄⢑
⢕⢕⢕⠅⢁⣴⣤⠀⣀⠁⠑⠑⠁⢁⣀⣀⣀⣀⣘⢻⣿⣿⣿⣿⣿⡟⢁⢔
⢕⢕⠕⠀⣿⡁⠄⠀⣹⣿⣿⣿⡿⢋⣥⠤⠙⣿⣿⣿⣿⣿⡿⠿⡟⠀⢔⢕
⢕⠕⠁⣴⣦⣤⣴⣾⣿⣿⣿⣿⣇⠻⣇⠐⠀⣼⣿⣿⣿⣿⣿⣄⠀⠐⢕⢕
⠅⢀⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣶⣶⣿⣿⣿⣿⣿⣿⣿⣿⣷⡄⠐⢕
⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡄⠐
⢄⠈⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡆
⢕⢔⠀⠈⠛⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⢕⢕⢄⠈⠳⣶⣶⣶⣤⣤⣤⣤⣭⡍⢭⡍⢨⣯⡛⢿⣿⣿⣿⣿⣿⣿⣿⣿
⢕⢕⢕⢕⠀⠈⠛⠿⢿⣿⣿⣿⣿⣿⣦⣤⣿⣿⣿⣦⣈⠛⢿⢿⣿⣿⣿⣿
⢕⢕⢕⠁⢠⣾⣶⣾⣭⣖⣛⣿⠿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡆⢸⣿⣿⣿⡟
⢕⢕⠅⢀⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠟⠈⢿⣿⣿⡇
⢕⠕⠀⠼⠟⢉⣉⡙⠻⠿⢿⣿⣿⣿⣿⣿⡿⢿⣛⣭⡴⠶⠶⠂⠀⠿⠿⠇