# Inicio de pruebas con dos ESP físicos

Preparación del 19 de noviembre de 2026. La IPv4 WiFi observada del PC es
192.168.0.6, con perfil privado y regla TCP 5000 habilitada. Config.local.h
se actualizó con esa dirección conservando las credenciales. No se detectaron
puertos seriales ni servidor activo durante la preparación. Esto no es una
validación física aprobada.

## Preparar red y montaje

1. Conectar PC y ambos ESP a la misma red con acceso entre dispositivos.
2. Confirmar SSID y contraseña en firmware/include/Config.local.h. Si aún
   corresponden al celular, reemplazarlos por los del WiFi usado ahora.
3. Verificar ipconfig antes de cargar: IOT_SERVER_HOST es la IPv4 WiFi del PC,
   no la dirección WSL ni la puerta de enlace. El puerto debe ser 5000.
4. Sensor: TRIG 5 y ECHO 18 con adaptación de nivel. Actuador: rojo 25,
   amarillo 26 y azul 27, cada uno con resistencia. Ver GUIA_MONTAJE.md.
5. Cerrar simuladores y monitores seriales antes de cargar. Un solo cliente
   por rol: un simulador abierto puede causar ROLE_IN_USE.

## Identificar y cargar

Desde PowerShell en la raíz del proyecto:

```powershell
$pioPython = "$env:USERPROFILE\.platformio\penv\Scripts\python.exe"
& $pioPython -m platformio device list
```

Conectar una placa por vez para identificar su puerto. Etiquetar cada placa.
Sustituir COM_SENSOR y COM_ACTUADOR por los puertos observados; no asumir COM5.

```powershell
& $pioPython -m platformio run -d firmware -e sensor -t upload --upload-port COM_SENSOR
& $pioPython -m platformio run -d firmware -e actuator -t upload --upload-port COM_ACTUADOR
```

Esperar SUCCESS en cada carga. Ambos ESP deben quedar alimentados simultáneamente;
USB se usa para cargar, alimentar y observar, pero los datos pasan por WiFi.

## Arranque

Terminal 1, servidor (mantener abierta):

```powershell
.\tools\python.cmd -m server --host 0.0.0.0 --port 5000 --log-file logs/prueba-dos-esp.jsonl
```

Debe mostrar server_started. Si el puerto está ocupado, identificar la instancia
anterior antes de iniciar otra. No ejecutar simulate_sensor ni simulate_actuator.

Terminal 2, monitor del sensor:

```powershell
& "$env:USERPROFILE\.platformio\penv\Scripts\python.exe" -m platformio device monitor --port COM_SENSOR --baud 115200
```

Terminal 3, monitor del actuador:

```powershell
& "$env:USERPROFILE\.platformio\penv\Scripts\python.exe" -m platformio device monitor --port COM_ACTUADOR --baud 115200
```

Esperar WiFi IP y TCP registered en ambas placas. Los registros del servidor
deben identificar sensor y actuator. Correlacionar sample seq=N, measurement
con delivered=true y applied seq=N. sent=1 por sí solo no confirma actuación.

## Secuencia de pruebas

| Paso | Acción | Resultado esperado |
| --- | --- | --- |
| 1 | Objeto aproximadamente a 10 cm | Rojo blink_4; amarillo y azul apagados |
| 2 | Objeto aproximadamente a 30 cm | Amarillo fijo; otros apagados |
| 3 | Objeto aproximadamente a 50 cm | Azul fijo; otros apagados |
| 4 | Provocar ausencia de eco | Medición invalid y todos apagados |
| 5 | Desconectar alimentación del sensor | Apagado por vencimiento de datos, plazo configurado 2 s |
| 6 | Reconectar sensor | Nuevo registro y reanudación; sesión anterior puede tardar hasta su timeout de 15 s en liberarse |
| 7 | Reiniciar actuador | Inicia apagado y aplica una lectura nueva |
| 8 | Detener servidor y reiniciarlo | Apagado, reconexión y registro de ambas placas |

Comparar estados con la distancia transmitida, no solo con la cinta métrica.
Para estabilidad, ejecutar otra sesión sin cortes inducidos durante 15 minutos.
Registrar reinicios, interrupciones y evidencia. No declarar latencia física
usando relojes millis() de placas distintas sin sincronización.

Completar PRUEBAS_FISICAS.md y seguir PLAN_PRUEBAS.md para exactitud ≤ 3 cm,
respuesta ≤ 1 s, al menos 2 lecturas/s y mínimo 10 minutos sin reinicios/bloqueos.
Los resultados todavía son pendientes hasta realizar las pruebas.

Esta primera integración es en LAN. El funcionamiento por Internet entre redes
distintas requiere servidor alcanzable y una prueba adicional documentada.

## Diagnóstico de conexión del actuador

Ante conexiones aceptadas por el servidor pero sin REGISTER y fallos en la placa,
se amplió el límite de conexión a 3000 ms (IOT_CONNECT_TIMEOUT_MS). El envío
no bloqueante conserva su límite independiente de 1000 ms. El entorno actuator
habilita logs WiFiClient con CORE_DEBUG_LEVEL=3; el firmware imprime duración,
límite y RSSI del intento, y el rol cuando consigue conectar. La hipótesis de
expiración requiere confirmación en placa; compilar no demuestra su resolución.
El intento puede detener el bucle hasta 3 s mientras está desconectado, por lo que
la cadencia física debe medirse conectado y reportarse aparte durante reconexión.
