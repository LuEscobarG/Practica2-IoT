# Guía de demo y defensa

## Recorrido de la demo

1. Mostrar los dos montajes e identificar sensor y actuador.
2. Arrancar el servidor y mostrar el registro de ambos roles.
3. Variar la distancia en los tres rangos; seguir una secuencia POST–SET–APPLIED.
4. Demostrar apagado por ausencia de mediciones y recuperación de conexión.
5. Presentar las mediciones reales y distinguirlas de simulaciones de software.

## Explicaciones que cada integrante debe dominar

- Por qué ambos ESP son clientes y el servidor decide la actuación.
- Qué aporta TCP y por qué aun así se necesitan líneas, buffers y reconexión.
- Cómo se interpretan 20 y 40 cm y cómo influye el error del sensor.
- Diferencia entre timeout de comandos, heartbeat y plazo de sesión.
- Por qué DNS está en una tarea separada y los LEDs usan temporización sin delay.
- Diferencia entre IP local, dominio y acceso desde otra red.
- Qué prueban sent, delivered y APPLIED; qué no prueban sobre latencia física.
- Dónde están el control, el protocolo y las pruebas en el código.

## Evidencias para presentar

Mostrar [resultados de software](evidencias/software-2026-11-12.md), [registros físicos](PRUEBAS_FISICAS.md), diagramas y aportes individuales en el historial de Git. No afirmar cumplimiento físico mientras falten medidas. Revisar las ocho secciones exigidas en el [enunciado](../Práctica_2.md) antes de entregar el informe.
