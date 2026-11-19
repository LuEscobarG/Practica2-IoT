# Evidencias del proyecto

- [Software del 12 de noviembre](software-2026-11-12.md): ejecución anterior.
- [Software de octubre](software-validation.md): registro histórico.
- [Pruebas físicas](../PRUEBAS_FISICAS.md): estado de la integración y de los ensayos físicos.
- measurements-template.csv y response-template.csv: plantillas sin resultados.

Guardar los datos de cada ensayo con fecha, ID de prueba y versión del código. La entrega utiliza registros JSONL, métricas JSON, resultados de pruebas y un video de demostración, sin fotografías ni capturas de pantalla.

## Evidencia del 19 de noviembre

- [Registro de dos ESP](tcp-dos-esp-2026-11-19.jsonl) y [métricas calculadas](metricas-tcp-2026-11-19.json).
- [Salida Python](tests-python-2026-11-19.txt) y [salida nativa](tests-nativos-2026-11-19.txt).
- [Versión de fuentes validada](version-validada-2026-11-19.json).

El registro contiene 99 mediciones, 89 válidas y 10 inválidas. El actuador confirmó las 90 órdenes entregadas. El [informe](../../informe.md#5-resultados) indica qué requisitos acredita la ejecución.

## Video de demostración (PF02)

- [Video adjunto en el repositorio (MP4)](demo-dos-esp.mp4)
- [Copia de respaldo en Google Drive](https://drive.google.com/file/d/1ulbUEx8PoZetxdWD0rBImKyQozog3XL8/view?usp=sharing)

El criterio de PF02 es observar rojo intermitente cerca de 10 cm, amarillo fijo cerca de 30 cm y azul fijo cerca de 50 cm. Consultar el [registro de pruebas físicas](../PRUEBAS_FISICAS.md) para el alcance de la evidencia.
