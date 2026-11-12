# Documentación de la comunicación sensor actuador por TCP

Este proyecto conecta dos ESP32 mediante un servidor TCP Python: uno mide distancia con HC-SR04 y otro controla LEDs. Esta carpeta reúne diseño, operación, pruebas y evidencias. La validación de software está completada; la integración física y la comunicación entre redes siguen pendientes.

## Contenido

| Documento o carpeta | Contenido |
| --- | --- |
| [consigna](consigna/README.md) | Enunciado y requisitos de documentación de la práctica 2. |
| [arquitectura](arquitectura.md) | Componentes, responsabilidades y recorrido de una medición. |
| [diagramas](diagramas/design.md) | Arquitectura, clases, secuencia y circuitos. |
| [planificacion](planificacion/README.md) | Etapas, tareas y condiciones de cierre. |
| [guía de montaje](GUIA_MONTAJE.md) | Componentes, pines y conexiones. |
| [configuración de red](configuracion-red.md) | WiFi, host, puerto, DNS, LAN e Internet. |
| [servidor TCP](servidor-tcp.md) | Ejecución, roles, control y recuperación. |
| [contratos](contratos.md) | Mensajes y enlace al contrato canónico. |
| [implementación](implementacion.md) | Organización del código y trazabilidad. |
| [plan de pruebas](PLAN_PRUEBAS.md) | Procedimientos y criterios de aceptación. |
| [pruebas físicas](PRUEBAS_FISICAS.md) | Registro de ejecución y resultados pendientes. |
| [evidencias](evidencias/README.md) | Resultados de software y datos crudos de pruebas. |
| [guía de defensa](GUIA_DEFENSA.md) | Preparación de demo y explicación técnica. |

El [informe técnico](../informe.md) permanece como documento de entrega. Debe incluir requerimientos, análisis y diseño, implementación, pruebas, resultados, conclusiones, recomendaciones y anexos.

## Qué corresponde a este proyecto

Se incluyen servidor Python, sockets TCP, protocolo propio, dos ESP32, diagnóstico de red, reconexión y pruebas sensor–actuador. No corresponden backend-lambda.md ni configuracion-aws-iot.md: el código actual no utiliza Lambda, AWS IoT, MQTT, reglas de nube ni certificados de esos servicios. Tener acceso a Internet no implica usar AWS.

## Estado de resultados

Consultar el [registro del 12 de noviembre](evidencias/software-2026-11-12.md): 32 pruebas Python, 34 casos compartidos, compilación de ambos firmwares y 40 mediciones simuladas en 10 s. El registro anterior de octubre se conserva como histórico. No mezclar esos resultados con mediciones físicas.
