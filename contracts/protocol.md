# Protocolo de aplicación

TCP IPv4, puerto configurable (5000 predeterminado). Cada ESP abre una conexión
persistente al servidor. ASCII imprimible, una línea por mensaje terminada en LF;
se acepta CRLF. Máximo 256 bytes antes del terminador, excluyendo el CR opcional.
Los receptores conservan fragmentos y procesan líneas agrupadas; los emisores
completan escrituras parciales. No se supone que un recv equivalga a un mensaje.

## Mensajes

| Mensaje | Dirección | Obligatorios | Opcionales |
| --- | --- | --- | --- |
| REGISTER | Cliente → servidor | type=sensor o type=actuator | version=1 |
| OK | Servidor → cliente | type del cliente | version=1 si se solicitó |
| POST | Sensor → servidor | distance=<cm> o status=invalid | seq |
| SET | Servidor → actuador | redLed, yellowLed, greenLed | seq |
| APPLIED | Actuador → servidor | Ninguno | seq |
| PING | Cliente → servidor | Ninguno | Ninguno |
| PONG | Servidor → cliente | Ninguno | Ninguno |
| ERROR | Servidor → cliente | code | Ninguno |

Claves sensibles a mayúsculas, sin duplicados ni claves desconocidas. Se aceptan
espacios y comas como separadores, en cualquier orden. No se admiten tabulaciones
ni otros controles. Distancia positiva y finita con punto decimal, sin signo,
exponente, coma decimal, nan o inf. seq es un entero entre 0 y 4294967295;
puede reiniciarse entre sesiones y desbordarse. No ordena sesiones distintas.
Los LEDs aceptan on, off, blink_2 y blink_4; alternancia cada 250 y 125 ms.
Repetir un estado conserva la fase del parpadeo.

```text
REGISTER type=actuator version=1
OK type=actuator version=1
SET redLed=off, yellowLed=off, greenLed=off
APPLIED
REGISTER type=sensor version=1
OK type=sensor version=1
POST seq=42 distance=19.80
SET seq=42 redLed=blink_4, yellowLed=off, greenLed=off
APPLIED seq=42
PING
PONG
POST seq=43 status=invalid
SET seq=43 redLed=off, yellowLed=off, greenLed=off
APPLIED seq=43
```

## Estados y recuperación

- Registro dentro de 5 s. Un cliente por rol; duplicados reciben ROLE_IN_USE
  y se cierran. Un cliente registrado no puede cambiar de rol.
- El actuador nuevo empieza apagado y espera una medición nueva.
- Solo el sensor envía POST y solo el actuador envía APPLIED.
- El servidor copia seq de POST a SET. Si falta, no lo agrega. Apagados por
  conexión o timeout no llevan secuencia. APPLIED confirma instalación del
  estado, no un ciclo completo de parpadeo ni la latencia desde el sensor.
- Una medición inválida, desconexión del sensor o 2 s sin mediciones aceptadas
  apagan las salidas. El actuador apaga tras 2 s sin SET o al detectar desconexión.
- El sensor adquiere cada 250 ms incluso desconectado; no acumula muestras antiguas.
- PING cada 5 s. El servidor responde PONG. El ESP reconecta tras 15 s sin
  recibir mensajes válidos. El servidor cierra sesiones tras 15 s sin POST,
  APPLIED o PING aceptados y libera el rol. --idle-timeout configura ese plazo.
  Heartbeats no renuevan la vigencia de mediciones ni comandos.
- Reintentos TCP cada 2 s y WiFi cada 5 s. Conexión y envío TCP limitados a
  1000 ms; un único mensaje pendiente. DNS en tarea separada para mantener
  el bucle de control disponible; el plazo DNS depende de la pila WiFi.

## Errores

| Código | Situación |
| --- | --- |
| BAD_MESSAGE | Sintaxis, clave, valor o comando inválido |
| LINE_TOO_LONG | Límite de línea excedido; cierra conexión |
| REGISTER_REQUIRED | Mensaje antes del registro |
| REGISTER_TIMEOUT | Registro ausente dentro del plazo; cierra conexión |
| ROLE_IN_USE | Rol ocupado; rechaza y cierra al nuevo cliente |
| ALREADY_REGISTERED | Segundo registro; conserva el rol original |
| WRONG_ROLE | Comando incompatible con el rol |
| UNSUPPORTED_VERSION | Versión distinta de 1 |

Errores de delimitación o codificación cierran la conexión. Errores de mensaje
permiten intentar el siguiente mensaje correcto, sin renovar la vigencia de la
medición. El firmware desconecta y reintenta ante ERROR o respuesta inválida.

| Distancia | Rojo | Amarillo | Verde |
| --- | --- | --- | --- |
| 0 < d < 20 | blink_4 | off | off |
| 20 <= d <= 40 | off | on | off |
| d > 40 | off | off | on |
| Inválida o vencida | off | off | off |

Los [34 casos compartidos](protocol-cases.json) se ejecutan contra Python y C++.
Las [pruebas TCP](../server/tests/test_tcp_server.py) verifican fragmentos,
agrupación, fronteras, roles, orden de conexión, timeouts, heartbeat y reconexión.
