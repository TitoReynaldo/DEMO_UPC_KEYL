# Keylogger (source.c)

## Descripción general

Keylogger para Windows que registra las teclas presionadas y las envía en tiempo real a Telegram mediante HTTP.

## Estructura del código

### `send_telegram(const char *text)`
Envía el texto proporcionado al bot de Telegram (`api.telegram.org`) usando `WinHttp` con método POST. Cierra todos los handles al finalizar.

### `keylogger_loop(void)`
Bucle principal de registro de teclas:
- Recorre los 256 códigos virtuales con `GetAsyncKeyState`.
- Letras mayúsculas (0x41–0x5A) → se convierten a minúsculas (+32).
- Dígitos (0x30–0x39) → se mapean directamente.
- Teclas especiales (backspace, espacio, enter, tab): si hay buffer acumulado se envía primero y luego la etiqueta correspondiente; el contador `len` se reinicia a 0.

### `WinMain`
Punto de entrada. Llama a `keylogger_loop()` y retorna 0.

## Certificado de firma

El archivo `source.pfx` contiene el certificado digital con el que está firmado el binario. Es lo que hace que Windows Defender y Control Inteligente de Aplicaciones no lo detecten ni bloqueen.