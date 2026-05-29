# Tic-Tac-Toe with Minimax AI

![Demostración del juego](https://github.com/miguets/tic-tac-toe-with-minimax/assets/73564090/8621252f-c84a-4ffa-87a3-b94a99df5c0a)

## Descripción

Implementación en lenguaje C del clásico juego de "Gato" (Tic-Tac-Toe) interactivo a través de la terminal, impulsado por el algoritmo de inteligencia artificial **Minimax**. El algoritmo evalúa el árbol completo de juego para cada estado del tablero, asegurando que la IA tome decisiones matemáticamente óptimas. Como resultado, la máquina es invencible: el jugador humano solo puede aspirar a un empate.

## Características Principales

* **Inteligencia Artificial Invencible:** El núcleo del proyecto es una función recursiva Minimax que calcula la utilidad de cada movimiento posible.
* **Compatibilidad Multiplataforma:** El código detecta automáticamente el sistema operativo en tiempo de compilación mediante macros predefinidas (`__linux__` y `_WIN32`). Esto garantiza que la limpieza de consola (`clear` vs `cls`) funcione correctamente sin importar el entorno.
* **Interfaz de Usuario Resaltada:** Implementación de secuencias de escape ANSI para dar formato y color al texto en sistemas basados en Unix (verde para el jugador, rojo para la IA), mejorando la experiencia de usuario en la terminal.
* **Validación de Entradas:** El sistema asegura que los movimientos del usuario estén dentro del rango permitido (1-9) y que no se sobrescriban casillas previamente ocupadas, manejando los errores de manera recursiva hasta obtener un movimiento válido.

## Estructura del Proyecto

El flujo del programa está dividido en módulos lógicos dentro del mismo archivo `tictactoe.c`:

* `minimax()`: Función recursiva principal que evalúa las ramas del árbol de decisiones.
* `estimateBoard()`: Función de utilidad que determina el estado de victoria, derrota o empate en un tablero dado.
* `getMove()`: Manejador de la entrada del usuario con validación de datos.
* `hardmode()`: Bucle principal del juego que coordina los turnos entre el jugador humano y la IA.

## Requisitos del Sistema

* Un compilador de C (GCC, Clang o MSVC).
* Una terminal o línea de comandos.

## Compilación y Ejecución

Para compilar y ejecutar el juego localmente, abre tu terminal, navega al directorio del proyecto y utiliza los siguientes comandos:

**En Linux / macOS:**
```bash
gcc tictactoe.c -o tictactoe
./tictactoe
```
**En Windows:**
```cmd
gcc tictactoe.c -o tictactoe.exe
tictactoe.exe
```
## Cómo Jugar

1. Al iniciar el programa, se mostrará un tablero vacío con posiciones numeradas del 1 al 9.
2. Ingresa el número correspondiente a la casilla donde deseas colocar tu marca.
3. El jugador humano siempre utiliza el identificador `o` y juega el primer turno por defecto.
4. La inteligencia artificial jugará automáticamente su turno utilizando el identificador `x`.
5. El juego termina cuando uno de los dos logra alinear tres marcas de forma horizontal, vertical o diagonal, o cuando no quedan casillas disponibles (empate).
