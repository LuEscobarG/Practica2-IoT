# Contrato de comunicación

La especificación canónica está en [contracts/protocol.md](../contracts/protocol.md); los casos ejecutables están en [protocol-cases.json](../contracts/protocol-cases.json). Se enlaza esa fuente para evitar versiones incompatibles del mismo contrato.

Los mensajes usan ASCII con terminador LF, aceptan CRLF y tienen un máximo de 256 bytes antes del terminador. TCP puede fragmentar o agrupar mensajes: ambos extremos reconstruyen las líneas.

REGISTER y OK registran; POST transmite; SET ordena; APPLIED confirma; PING y PONG comprueban conexión; ERROR diagnostica. seq correlaciona mensajes de una sesión y no representa tiempo sincronizado entre ESP.

sent=1 indica aceptación local del envío, delivered=true indica envío desde el servidor y APPLIED confirma aplicación por el firmware. La latencia física requiere medición independiente.
