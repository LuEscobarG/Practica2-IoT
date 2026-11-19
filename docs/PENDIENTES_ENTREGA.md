# Pendientes para completar el informe

Actualización del 19 de noviembre de 2026. Las observaciones de otra práctica se aplican a calidad de evidencia, trazabilidad y redacción. AWS, Alexa, MQTT, Shadow y órdenes pendientes no forman parte de esta implementación TCP.

## Prioridad 1 Montaje y evidencia funcional

- [ ] Verificar ECHO: el informe describe conexión directa y el esquema propone divisor. Comprobar nivel, adaptar según el módulo y documentar el circuito real con fotografía antes de nuevas pruebas.
- [ ] Fotografiar ambos ESP y sus conexiones; confirmar resistencias de LEDs y pines 5/18 y 25/26/27.
- [ ] Grabar rojo intermitente cerca, amarillo en rango medio y azul lejos, con una referencia de distancia visible y secuencias correlacionadas.
- [ ] Registrar ensayo controlado de medición inválida y apagado físico. Las lecturas invalid existentes no prueban cómo se provocó la ausencia de eco.

## Prioridad 2 Medir los requisitos

| Requisito | Trabajo mínimo pendiente | Evidencia para cerrar |
| --- | --- | --- |
| RNF01 | 15 min de operación normal; acreditar mínimo de 10 sin reinicios/bloqueos | Bitácora, logs completos y observación del montaje |
| RNF02 | Referencias 10, 20, 30, 40, 50 y 60 cm, al menos 10 lecturas válidas por punto; conservar inválidas | CSV con referencia, máximo absoluto ≤ 3 cm y foto de montaje/medición |
| RNF03 | Al menos 10 repeticiones por transición entre rangos con reloj común | Video o analizador, instantes identificables, resolución y máximo ≤ 1 s |
| RNF04 | 60 s útiles de adquisiciones del sensor | CSV sin reinicios/pérdidas no explicadas; mínimo 120 lecturas |

Los 4,004 Hz actuales son recepción en el servidor durante 24,473 s. No bastan para aprobar RNF04. Los 27,248 s totales no bastan para RNF01. No hay datos para error absoluto ni latencia física.

- [ ] Ejecutar tres cortes WiFi, tres reinicios del actuador y tres reinicios del servidor, midiendo apagado y recuperación. Esperar datos nuevos después de reconectar.
- [ ] Medir parpadeo rojo a 4 Hz, no deducirlo únicamente del código.
- [ ] Si se mantiene el objetivo de Internet entre redes distintas, ejecutar PF12; la red compartida del iPhone es LAN.

## Prioridad 3 Trazabilidad de entrega

- [ ] Completar responsable, fecha, red, versión y hash de binarios para cada prueba nueva. No atribuir al binario probado físicamente el hash de una recompilación posterior.
- [ ] Incorporar datos y archivos al repositorio y actualizar tablas de resultados y conclusiones con los valores obtenidos, incluidos fallos.
- [ ] Revisar git config user.name y user.email en el equipo de cada integrante. En este equipo LuEscobarG ya está configurado; no se verificó el equipo del compañero.
- [ ] Confirmar aportes reales por integrante en commits/ramas; el historial local inspeccionado contiene dos commits de LuEscobarG. No inventar aportes ni cambiar autorías para aparentarlos.
- [ ] Crear el commit final y verificar subida, enlaces y acceso del docente. El historial remoto no se auditó en esta revisión.
- [ ] Distinguir fecha límite original del 13 de octubre y evidencias posteriores de noviembre. No afirmar que estas últimas se entregaron antes del plazo.

## Correcciones ya realizadas

- Informe con ocho secciones, resultados cuantificados y evidencia enlazada.
- Matriz requisito–código–prueba–resultado.
- 32 pruebas Python y 34 casos compartidos C++ con salida guardada.
- Análisis del JSONL: 99 muestras, 89 válidas, 10 inválidas, 90 entregadas y 90 confirmadas.
- Clasificación explícita de comprobado, parcial y no verificado.
- Colores reales rojo, amarillo y azul; greenLed documentado como nombre histórico del canal azul.
- Incidencias con causa comprobada y límites de inferencia. No se atribuye el éxito al timeout sin una comparación controlada.
