# Registro de pruebas físicas

**Estado:** pendiente de validación integrada. La usuaria reportó pruebas individuales del sensor ultrasónico y de los LEDs; no se adjuntaron datos crudos ni resultados cuantificados. No se consideran evidencia de comunicación TCP.

Los procedimientos detallados están en [PLAN_PRUEBAS.md](PLAN_PRUEBAS.md).

| ID | Prueba y aceptación | Estado |
| --- | --- | --- |
| PF01 | Ambos ESP obtienen IP y registran roles distintos | Pendiente |
| PF02 | Distancias 10, 30 y 50 cm producen rojo intermitente, amarillo y verde; APPLIED correlacionado | Pendiente |
| PF03 | Fronteras 20 y 40 cm pertenecen al rango amarillo según la lectura transmitida | Pendiente |
| PF04 | Sin eco se transmite invalid y se apagan LEDs | Pendiente |
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
