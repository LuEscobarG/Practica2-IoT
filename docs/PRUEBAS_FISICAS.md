# Registro de pruebas físicas

**Estado al 19 de noviembre de 2026:** integración TCP real documentada en la misma red del iPhone. El [registro](evidencias/tcp-dos-esp-2026-11-19.jsonl) acredita ambos roles y 90 envíos confirmados. La respuesta visual fue comunicada durante la prueba, pero no se adjuntó video por rango. Los RNF físicos permanecen sin verificación completa.

Los procedimientos detallados están en [PLAN_PRUEBAS.md](PLAN_PRUEBAS.md).

| ID | Prueba y aceptación | Estado |
| --- | --- | --- |
| PF01 | Ambos ESP obtienen IP y registran roles distintos | Verificado en registro TCP: sensor 172.20.10.2 y actuador 172.20.10.4 |
| PF02 | Distancias 10, 30 y 50 cm producen rojo intermitente, amarillo y azul; APPLIED correlacionado | Tres estados en JSONL y 90 APPLIED; falta video con referencia de distancia |
| PF03 | Fronteras 20 y 40 cm pertenecen al rango amarillo según la lectura transmitida | Verificado en software; contraste físico pendiente |
| PF04 | Sin eco se transmite invalid y se apagan LEDs | Hay 10 invalid en el registro; falta provocar y documentar el fallo y el apagado físico |
| PF05 | Corte WiFi del sensor: apagado por vencimiento y reconexión al recuperar red | Pendiente |
| PF06 | Reinicio del actuador: inicia apagado, registra y espera lectura nueva | Pendiente |
| PF07 | Reinicio del servidor: ambos clientes reconectan y registran | Pendiente |
| PF08 | Exactitud: 10 lecturas por punto a 10, 20, 30, 40, 50 y 60 cm; error máximo ≤ 3 cm | Pendiente |
| PF09 | Muestreo: ≥ 2 lecturas/s durante 60 s útiles | Pendiente |
| PF10 | Respuesta física: máximo ≤ 1 s con referencia temporal común | Pendiente |
| PF11 | Estabilidad: 15 min registrados; mínimo 10 min sin reinicios ni bloqueos | Pendiente |
| PF12 | Redes distintas: ambos alcanzan servidor, completan POST–SET–APPLIED y recuperan cortes | Pendiente |

## Ficha por ejecución

Copiar y completar para cada prueba, conservando también las fallidas:

- ID y fecha:
- Responsable y versión del código:
- Placas, puertos y montaje:
- Red utilizada y ubicación del servidor:
- Procedimiento y duración:
- Resultado esperado:
- Resultado observado y medidas:
- Estado final: aprobado / fallido / no ejecutado.
- Evidencia enlazada en evidencias/:
- Incidencias, análisis y acción correctiva:

No incluir contraseñas WiFi. No restar millis() entre ESP sin sincronización; usar una referencia común para la respuesta física. Las desconexiones inducidas se prueban separadas de la estabilidad normal.

## Evidencias y alcance

- [Métricas del recorte](evidencias/metricas-tcp-2026-11-19.json): 99 lecturas en 24,473 s, 89 válidas y 10 inválidas.
- [Pruebas Python](evidencias/tests-python-2026-11-19.txt): 32 aprobadas.
- [Pruebas C++](evidencias/tests-nativos-2026-11-19.txt): 34 casos compartidos y componentes simulados aprobados.

Las nueve lecturas sin entrega preceden al registro del actuador; no equivalen a nueve pérdidas de red. No se ejecutó una campaña física controlada de recuperación: el arranque exitoso tras iniciar el servidor no aprueba PF05–PF07.

Antes de nuevas mediciones, conciliar el montaje descrito con ECHO directo en el informe y el divisor mostrado en el esquema. Fotografiar y medir la adaptación real; no registrar una corrección como realizada sin comprobarla.
