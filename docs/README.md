# Documentación de la comunicación sensor actuador por TCP

Este proyecto conecta dos ESP32 mediante un servidor TCP Python: uno mide distancia con HC-SR04 y otro controla LEDs. Esta carpeta reúne diseño, operación, pruebas y evidencias. Hay pruebas de software aprobadas e integración TCP real documentada. Faltan mediciones completas de RNF, evidencia visual y prueba entre redes distintas.

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

El [informe actualizado](../informe.md) incorpora 99 mediciones reales y 90 envíos confirmados. Las [salidas Python](evidencias/tests-python-2026-11-19.txt) y [nativas](evidencias/tests-nativos-2026-11-19.txt) documentan la ejecución del 19 de noviembre.

### Historial de software

Consultar el [registro del 12 de noviembre](evidencias/software-2026-11-12.md): 32 pruebas Python, 34 casos compartidos, compilación de ambos firmwares y 40 mediciones simuladas en 10 s. El registro anterior de octubre se conserva como histórico. No mezclar esos resultados con mediciones físicas.

Para la integración final, seguir [Inicio con dos ESP físicos](INICIO_DOS_ESP.md).

## Colores del montaje

Cerca: rojo intermitente; distancia media: amarillo fijo; lejos: azul fijo. GPIO 27 corresponde al azul. La clave TCP `greenLed` sigue designando ese canal por compatibilidad; consultar [el contrato](../contracts/protocol.md).

Para cerrar la entrega, consultar [pendientes priorizados](PENDIENTES_ENTREGA.md) y [métricas reales](evidencias/metricas-tcp-2026-11-19.json).
