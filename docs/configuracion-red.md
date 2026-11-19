# Configuración y diagnóstico TCP

ESP sensor → servidor Python → ESP actuador. Ambos ESP inician conexiones
salientes; el servidor debe permanecer activo y ser alcanzable desde ambas redes.

## Preparación

1. Copiar firmware/include/Config.example.h a firmware/include/Config.local.h.
2. Completar WiFi, host y puerto. Host acepta IPv4 o dominio con registro IPv4,
   sin tcp:// ni rutas. Las credenciales locales quedan ignoradas por Git.
3. Si las placas usan WiFi diferentes, configurar las credenciales de cada una
   antes de compilar y cargar su entorno sensor o actuator por separado.
4. Iniciar: `python -m server --host 0.0.0.0 --port 5000 --log-file logs/server.jsonl`.
5. En LAN usar la IPv4 del PC obtenida con ipconfig y permitir TCP entrante
   al puerto elegido. Una red de invitados puede aislar los dispositivos.
6. Abrir monitores seriales a 115200: deben aparecer WiFi IP, TCP connecting,
   TCP registered, sample seq=N ... sent=1 y applied seq=N.

Config.h contiene pines y tiempos compartidos. Sin Config.local.h se compila con
valores de ejemplo y una advertencia; completar datos reales antes de cargar.

## Internet

Para redes diferentes se necesita un servidor remoto alcanzable o una ruta
privada entre redes que permita TCP. Una IP local 192.168.x.x no crea esa ruta.
0.0.0.0 es una dirección de escucha, no el destino de los ESP.
El código no crea hosting, VPN, reglas de router ni reglas de firewall.
El protocolo es TCP sin autenticación ni cifrado: usar una red privada controlada;
exposición pública directa requiere protección de acceso y transporte adicional.

## Recuperación y tiempos

PING cada 5 s, respuesta PONG. El ESP reconecta tras 15 s sin mensajes válidos;
el servidor libera sesiones inactivas tras 15 s (--idle-timeout). Una sesión
anterior puede causar ROLE_IN_USE temporalmente hasta vencer. PONG no mantiene
encendidos los LEDs: se conserva apagado tras 2 s sin SET/mediciones válidas.

Conexión: 3000 ms; envío: 1000 ms; registro: 5 s. DNS se ejecuta en una tarea separada
para no detener el control de LEDs; su duración depende de la pila WiFi.
Solo se permite una consulta DNS pendiente por objeto.
Si la latencia medida exige cambiar el apagado de seguridad, ajustar juntos
--stale-after del servidor e IOT_COMMAND_TIMEOUT_MS de Config.local.h.

## Diagnóstico

| Evidencia | Revisar |
| --- | --- |
| WiFi reconnect sin IP | Credenciales, cobertura y red compatible |
| DNS failed | Dominio y DNS; probar IPv4 |
| TCP connect failed | Servidor activo, dirección, puerto, firewall y ruta |
| TCP registration timeout | Servidor correcto en ese puerto y respuesta OK |
| ROLE_IN_USE | Otra placa/simulador con ese rol o sesión anterior aún vigente |
| sent=0 | Conexión no registrada o salida pendiente |
| delivered=false | Actuador ausente o envío fallido desde servidor |
| APPLIED y LEDs apagados | Lectura inválida, timeout, pines o cableado |

sent=1 solo indica aceptación local del mensaje. delivered=true indica envío
por el servidor. APPLIED confirma aplicación del comando por el firmware.
Correlacionar seq entre sensor, log del servidor y actuador.

## Validación realizada

32 pruebas Python aprobadas, 34 casos compartidos con C++ aprobados y pruebas
nativas de sensor/LEDs aprobadas. Ambos firmwares compilaron para ESP32.
Simulación TCP en loopback: 40 mediciones en 10 s, 4 por segundo.
La comunicación física y la conexión a Internet elegida requieren prueba real.
