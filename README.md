# REGISTRO DE TÉRMINOS UTILIZADOS EN EL PROYECTO
Esta estandarización busca uniformizar todo el contenido

## 1. UNIDADES (AUTOS, BUSES)
Las unidades tienen características que se encuentran en su clase `Unidad`:
+ `placa`. Placa: `ABC-123`.
+ `cod`. Código. Se determinaron 3 dígitos, donde el primer caracter indica su tipo:
   + `1XX`: Para unidades pequeñas. Tomar de referencia una van.\
   **Capacidad:** 8 asientos.
   + `2XX`: Para unidades grandes. Tomar de referencia un autobús clásico. \
   **Capacidad:** 45 asientos.
   + `3XX`: Para unidades grandes y largas distancias. Tomar de referencia un bus interprovincial. Aunque no puedes llevar tantas personas, garantiza una mejor experiencia a los pasajeros. \
   **Capacidad:** 39 asientos.
+ `capacidad`. Capacidad (dependiendo de cada tipo).
+ `estado`. Estado: `Disponible`, `Asignado`, `En reposo`.

## 2. OPERADOR (CHOFERES)
Los operadores tienen características que se encuentran en su clase `Operador`:
+ `cod`. Código: `9XX`.
+ `dni`. DNI: `NNNNNNNN`.
+ `nombres`. Nombres.
+ `apellidos`. Apellidos.
+ `estado`. Estado: `Disponible`, `Asignado`, `En reposo`.

## 3. SERVICIO (VIAJES)
Los viajes guardan información vital para el servicio. Se usa la clase `Servicio`:
+ `id`. ID del servicio: `0001` ... `9999`.
+ `codUnid`. Unidad asignada (se identificará con el código de la unidad).
+ `codOp`. Operador asignado (se identificará con el código del operador).
+ `pasajeros`. Cantidad de pasajeros.
+ `destino`. Destino. Por el momento solo como un `string` estático. *Por implementar: que defina el tiempo de viaje estimado.*
+ `estado`. Estado: `Pendiente`,`Activo`, `Completado`.

## 4. VECTORES (NOMBRES COLECTIVOS)
Se trabajarán con tres grupos de vectores temporales: `padronUnid`, `padronOp`, `historialServ`. Con ellos se realizarán todas las funciones dentro del sistema.

## 5. FUNCIONES
+ `mostrarPadron()`: Mostrará el padrón de unidades, el de operadores o ambos.
+ `programarServ()`: Pide los datos para la creación de un objeto `Servicio`. Solo permiten tomar operadores y unidades con **estado disponible**. Activará el estado como `Pendiente`.
+ `procesarSalida()` y `procesarArribo()`: Procesa la salida (`Servicio.estado=Activo`) y llegada (`Servicio.estado=Completado`) del bus y manda a la unidad y su operador a un periodo de descanso.
+ `registrarUnidad()` y `registrarOperador()`: Estas funciones agreguen a nuevo personal y autobuses.
+ *`simularPasoTiempo()`: Función aún sin decisión de usar. Será usada para simular el paso del tiempo de no poderse leer los segundos en tiempo real.*
+ `cargarUNIDADES()`, `cargarOPERADORES()`, `cargarSERVICIOS`: Esta función cargará los datos guardados en `unidades.txt`, `operadores.txt` y `historial_serv.txt` dentro de los vectores temporales `padronUnid`, `padronOp` y `historialServ`, respectivamente.

## 6. OTRAS VARIABLES
+ `UNIDADES`: Reemplaza a `unidades.txt`.
+ `OPERADORES`: Reemplaza a `operadores.txt`.
+ `SERVICIOS`: Reemplaza a `historial_serv.txt`.
+ `datoLinea` y `linea`: Variables para facilitar la lectura de los archivos y su guardado en los vectores respectivos.
+ Todos los `index`: Buscan ubicar posiciones estratégicas necesarias para el correcto funcionamiento del sistema.
