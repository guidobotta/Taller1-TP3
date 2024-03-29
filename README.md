# <center> TP3 </center>
# <center> Adivina el Número </center>

### <center> BOTTA, Guido Tomas </center>

### <center> Padron: 102103 </center>

### <center> Enlace a Github: https://github.com/guidobotta/tp2-taller </center>

# Introducción

&nbsp;&nbsp;&nbsp;&nbsp; El presente trabajo práctico fue realizado con la finalidad de incorporar conceptos de manejo de servidores multi-clientes. Se debió unir conceptos de hilos y sockets.

&nbsp;&nbsp;&nbsp;&nbsp; Se desarrolló un juego en dos partes: una aplicación servidor y una aplicación cliente. La aplicación servidor soporta multiples clientes conectados en simultáneo.

# Desarrollo

## Consigna: Adivina el Número

&nbsp;&nbsp;&nbsp;&nbsp; El juego consiste en que un cliente debe adivinar un número de 3 cifras no repetidas generado por el servidor. El cliente tiene 10 intentos para adivinar. Para cada dígito, el servidor sumará se la siguiente forma:

- Si alguna cifra del número del cliente se encuentra en el número real, pero en otra posición, se contará como `1 regular`.
- Si alguna cifra del números del cliente se encuentra en el número real y en la posición correcta, se contará como `1 bien`.
- Si ninguna de las tres cifra del número del cliente se en encuentra en el número real, se contará como `3 mal`.

&nbsp;&nbsp;&nbsp;&nbsp; Una vez que el cliente ingrese un número, se envíara, con un cierto formato que se verá más adelante, al servidor. Este analizará si el número es válido (de 3 cifras sin repetir), la cantidad de dígitos bien, regular o mal, y le devolverá una respuesta al cliente.

&nbsp;&nbsp;&nbsp;&nbsp; Por ejemplo, suponiendo que el número real generado por el servidor es `135`, se puede dar el siguiente caso:

~~~
Cliente:~$ 489

//Cliente -> Servidor (envía intento)
//Servidor -> Cliente (envía respuesta)

Cliente:~$ 3 mal
Cliente:~$ 153

//Cliente -> Servidor (envía intento)
//Servidor -> Cliente (envía respuesta)

Cliente:~$ 1 bien, 2 regular
Cliente:~$ 135

//Cliente -> Servidor (envía intento)
//Servidor -> Cliente (envía respuesta)

Cliente:~$ Ganaste
~~~

&nbsp;&nbsp;&nbsp;&nbsp; El juego termina cuando el cliente adivine el número o cuando haya agotado sus 10 intentos.

## Ejecución, Entrada y Salida

### Servidor

&nbsp;&nbsp;&nbsp;&nbsp; El servidor debe ejecutarse de la siguiente manera:

~~~
./server <puerto> <numeros>
~~~

&nbsp;&nbsp;&nbsp;&nbsp; Donde numeros es un archivo de texto que contiene números. Por ejemplo:

~~~
153
456
129
~~~

&nbsp;&nbsp;&nbsp;&nbsp; Estos números deben ser procesador por la aplicación del servidor en forma de lista circular. Es decir, al primer cliente se le asignará el 153, al segundo el 456, al tercero el 129 y cuando ingrese un cuarto se volverá a asignar el 153.

&nbsp;&nbsp;&nbsp;&nbsp; Por entrada estándar, el servidor espera recibir una `q` cuando se desee cerrarlo. Al cerrar el servidor se esperará que se terminen todas las ejecuciones de los hilos.

&nbsp;&nbsp;&nbsp;&nbsp; Por salida estándar, el servidor imprimirá una lista de ganadores y perdedores al ser cerrado. El formato es el siguiente:

~~~
Estadísticas:
    Ganadores:  <cantidad de ganadores>
    Perdedores: <cantidad de perdedores>
~~~

&nbsp;&nbsp;&nbsp;&nbsp; Por la salida de error, el servidor imprimira los siguientes errores si es que ocurren:

- Si la cantidad de parámetros es inválida:

~~~
Error: argumentos inválidos
~~~

- Si alguno de los números de la lista que recibe por parámetro no se encuentra entre los valores 100 y 999:

~~~
Error: archivo con números fuera de rango
~~~

- Si alguno de los números de la lista posee cifras repetidas:

~~~
Error: formato de los números inválidos
~~~

### Cliente

&nbsp;&nbsp;&nbsp;&nbsp; El cliente debe ejecutarse de la siguiente manera:

~~~
./client <puerto> <ip>
~~~

&nbsp;&nbsp;&nbsp;&nbsp; Por entrada estándar, el cliente recibiŕa los números que el usuario quiera ingresar.

&nbsp;&nbsp;&nbsp;&nbsp; Por salida estándar, el cliente imprimirá la cantidad el mensaje que reciba del servidor, o un mensaje de ayuda si el comando ingresado por el usuario es inválido:

~~~
Error: comando inválido. Escriba AYUDA para obtener ayuda
~~~

## Diseño e Implementación

### En común

&nbsp;&nbsp;&nbsp;&nbsp; Hay dos clases que fueron desarrolladas para uso común entre el servidor y el cliente:

- **AppError**: excepción desarrollada para lanzar a lo largo de ambas aplicaciones para tener más control sobre ellas.

- **SocketTCP**: clase socket de tipo TCP para realizar las conexiones y comunicaciones entre servidor y cliente.

### Cliente

&nbsp;&nbsp;&nbsp;&nbsp; La aplicación cliente es sencilla, simplemente cuenta con el archivo principal donde se encuentra el main y dos clases:

- **ClientConnector**: Se encarga de conectar el cliente al servidor y de realizar la comunicación entre ellos.

- **ClientController**: Almacena la lógica de ejecución del juego del lado del cliente.

&nbsp;&nbsp;&nbsp;&nbsp; En el siguiente diagrama se puede observar lo simple que es.

![client class](img/clientclass.jpg)

### Servidor

&nbsp;&nbsp;&nbsp;&nbsp; En esta aplicación se encuentra la lógica más pesada y el problema del manejo de multiples hilos y sockets en simultáneo. 

&nbsp;&nbsp;&nbsp;&nbsp; Por una parte, se encuentra el main, que se encarga de instanciar los objetos que leen el archivo de números, levantar el servidor y el hilo que se encarga de manejar todos los hilos de clientes.

&nbsp;&nbsp;&nbsp;&nbsp; En principio, se lee el archivo y se chequea que sea correcto. Luego, se crea una lista circular. Para esto, se tienen las siguientes clases:

- **FileReader**: clase que encapsula la apertura, lectura y clausura de archivos.

- **RoundList**: clase lista circular que recibe un `FileReader` y lee el archivo, chequeando que sean correctos los números. Cuenta con una función getNext() que se encarga de devolverte un número y avanzar hacia el siguiente de forma circular.

&nbsp;&nbsp;&nbsp;&nbsp; Luego, se levanta el servidor, para esto se encuentra la siguiente clase:

- **ServerManager**: se encarga de levantar el servidor y de escuchar y aceptar clientes entrantes. Cuenta con un `SocketTCP bindAndListen`.

&nbsp;&nbsp;&nbsp;&nbsp; A continuación, se crea el hilo que se encarga de la creación de los hilos que contienen la lógica y la comunicación con el cliente. Las clases que participan son:

- **ThreadsManager**: se encarga de pedirle a `ServerManager` que le devuelva un `socket peer` cuando acepte un cliente, y se lo asigna a un hilo del tipo `ServerClient`, el cual contiene toda la lógica de ejecución.

- **ServerClient** y **_ServerClient**: de utilizan dos clases para usar memoria dinámica de forma encapsulada. En `ServerClient` se crea una instancia en el heap de la clase `_ServerClient`, que contiene la lógica del juego y de la comunicación con el cliente.

- **SurrenderCommand**, **HelpCommand** y **NumberCommand**: son tres clases, hijas de la clase `Command`, utilizadas para quitarle responsabilidad en la lógica al `ServerClient`. Se utilizan cada vez que el usuario envía un mensaje. `SurrenderCommand` si se rinde, `HelpCommand` si pide ayuda y `NumberCommand` si envía un número no signado de 2 bytes.

&nbsp;&nbsp;&nbsp;&nbsp; Finalmente, se encuentra la clase **Score**, que lleva el conteo de los perdedores y ganadores.

&nbsp;&nbsp;&nbsp;&nbsp; Sin entrar en detalles de implementación, el diagrama general del servidor quedaría de la siguiente manera.

![server class](img/serverclass.jpg)

&nbsp;&nbsp;&nbsp;&nbsp; El hilo `server`, que no es un objeto, se encarga de instanciar a `FileReader` y a `RoundList`, con lo que se chequea que el archivo sea correcto y se arma la lista. Luego instancia al `Score`, al `ServerManager`, quien levanta el servidor, y al `ThreadsManager`.

&nbsp;&nbsp;&nbsp;&nbsp; El hilo de `ThreadsManager` se encarga de instanciar cada `ServerClient`, quienes se encargan de la comunicación con el cliente, la lógica del juego, para la cual necesitan de un número brindado por `RoundList`, y de actualizar el `Score`. Para esta lógica, usan el apoyo de las clases de tipo `Command`.

## Dificultades en el Desarrollo

- Se encontró una gran dificultad a la hora de crear un `socket peer` en el hilo `ThreadsManager` al querer utilizar asignación por movimiento, ya que al querer actualizar el valor de este al principio de cada ciclo, se invalidaba el valor del socket, rompiendo al socket del `ServerClient`. A continuación se muestra dónde estaba el problema:

~~~c++
void ThreadsManager::run() {
    SocketTCP peer;
        /*Ejecuto mientras el main no avise que mandaron una
        'q' para cerrar el servidor.*/
        while (!this->ended) { 
            //Asignación por movimiento
            peer = std::move(this->serverManager.connect());
            this->serverClients.push_back(ServerClient(peer, ...));
            (...)
        }
}
~~~

&nbsp;&nbsp;&nbsp;&nbsp; Como se puede observar, se actualizaba por asignación por movimiento al valor del peer en cada ciclo, lo cual invalidaba el valor que había adoptado en el ciclo anterior. Para solucionar, se decidió llamar al constructor por movimiento del SocketTCP como parámetro del constructor del ServerClient.

~~~c++
void ThreadsManager::run() {
    while (!this->ended) {
        this->serverClients.push_back(ServerClient(SocketTCP(this->serverManager.accept()), ...));
        (...)
    }
}
~~~

# Conclusiones

&nbsp;&nbsp;&nbsp;&nbsp; Como se pudo ver en la parte de `Dificultades en el Desarrollo`, hay que tener cuidado a la hora de trabajar con multiples clientes, ya que se puede facilmente cerrar la comunicación por error, o perder el valor de un socket y no poder recuperarlo.

&nbsp;&nbsp;&nbsp;&nbsp; En este trabajo se utilizó el hilo "*extra*" para el manejo de los hilos de los clientes para poder facilitar el cierre del servidor cuando se desease y poder liberar los recursos de manera más ordenada.

# Apéndice

## Correcciones

- **SocketTCP**: Hago shutdown y close en el destructor para que los objetos no deban preocuparse de cerrarlo. También se añadió una clase pública close para el caso que se necesite cerrarlo con anterioridad, se tuvo cuidado de no poder cerrarlo más de una vez. Esto se usó para el manejo de la excepción cuando se desea cerrar el servidor.

- **ServerScore**: Agrego `mutex` para no tener `race condition` al agregar `Winners` o `Loosers`.

- **ServerThreadsManager**: Cambio `bool ended` por `std::atomic<bool> ended` para no tener problemas al querer finalizar la ejecución del servidor, donde tengo que cambiar el estado de este mismo en el hilo del cliente.

- **ServerThreadsManager**, **ServerClient** y **ServerProtocol**: Se agregó un `ServerProtocol` para manejar `send` y `recieve` por lado del `ServerClient`. Esto cambio la creación del `ServerClient` dentro del `ServerThreadsManager`.

- **Command**, **HelpCommand**, **SurrenderCommand**, **NumberCommand** y **CommandMaker**: Se creó un `CommandMaker` encargado de analizar qué comando se debe crear según el char de operacióne enviado por el cliente. Se uso el patrón Factory para esto. Se instancia un `CommandMaker`, pasandole el char de operación. Este hace un new del comando a utilizar. Luego, se hace un `Command *cm = cmMaker.getCommand();` y se ejecuta `cm->run();`. Así, se logra un polimorfismo sin que el `ServerClient` sepa la existencia de distintos comandos.

- **NumberCommand**: Se modularizó la función para chequear el número.

- **ClientController**: Se cambió un poco la funcionalidad utilizando desde antes strings.