# Comunicación de ambos ESP del 19 de noviembre de 2026

Se inició el servidor porque no había un listener TCP en el puerto 5000.
El sensor 172.20.10.2 y el actuador 172.20.10.4 se registraron al servidor del PC
172.20.10.3 en la red del iPhone. El actuador tenía cargado el diagnóstico con
límite de conexión de 3 s. Esta observación no demuestra que el ajuste de timeout
fuera necesario: el servidor detenido fue un bloqueo comprobado.

En la captura se observaron 90 envíos con delivered=true y
90 de esas secuencias con confirmación APPLIED. El recorte puede terminar
antes de recibir la confirmación de la última muestra.

Datos crudos: [tcp-dos-esp-2026-11-19.jsonl](tcp-dos-esp-2026-11-19.jsonl). Se observaron lecturas válidas e inválidas.
La confirmación acredita aplicación por firmware; no sustituye inspección visual
de LEDs, exactitud, latencia física ni estabilidad. Esas verificaciones siguen
pendientes. El servidor se dejó funcionando para continuar la prueba.
