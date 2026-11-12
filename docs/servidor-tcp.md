# Servidor TCP Python

El servidor de [server/tcp_server.py](../server/tcp_server.py) enlaza ambos objetos. Los ESP son clientes; no necesitan aceptar conexiones entrantes. El servidor acepta un sensor y un actuador activos.

## Ejecución

Desde la raíz del repositorio:

```powershell
.\tools\python.cmd -m server --host 0.0.0.0 --port 5000 --log-file logs/server.jsonl
```

El servidor usa la biblioteca estándar de Python. Los clientes apuntan a una IPv4 o dominio alcanzable, nunca a 0.0.0.0. Ver [configuración de red](configuracion-red.md).

## Flujo

1. REGISTER identifica el rol y OK confirma registro.
2. El sensor envía POST con distancia o status=invalid.
3. El servidor clasifica y envía SET: rojo intermitente si d < 20, amarillo si 20 ≤ d ≤ 40, verde si d > 40; datos inválidos apagan todos.
4. El actuador responde APPLIED con la misma secuencia cuando existe.
5. PING recibe PONG para comprobar conexión.

## Recuperación

El registro tiene un límite de 5 s. El servidor libera sesiones sin actividad válida durante 15 s, configurable con --idle-timeout. El apagado por ausencia de mediciones ocurre después de 2 s, configurable con --stale-after. Heartbeat no renueva la vigencia de las mediciones. Un actuador nuevo recibe apagado y espera una lectura nueva.

ROLE_IN_USE rechaza duplicados; después de un corte silencioso puede persistir hasta vencer la sesión anterior. Los registros connected, registered, measurement, applied, idle_timeout y disconnected permiten seguir cada sesión.

## Límites

El protocolo no incluye autenticación ni cifrado. La validación actual corresponde a software local; desplegarlo públicamente requiere protección de acceso y transporte. El repositorio no crea hosting ni configura el router.
