#!/usr/bin/env python3
"""
ram_tope.py - falla si la RAM principal de un mapa pasa de un tope.

Rama apm32, 13/11/2026. El APM32F407 tiene 128 kB de SRAM y el firmware
pedia 194.720 bytes: el enlazador ya avisa al pasarse de la region, pero
el presupuesto del puerto deja margen (126 kB = 129.024 bytes) y eso solo
lo puede vigilar alguien que cuente.

Cuenta EXACTAMENTE lo que cuenta tools/ram_mapa.py (.bss + .data +
.noinit), usando su misma funcion, para que los dos numeros no puedan
separarse.

    python3 tools/ram_tope.py <fichero.map> <tope_en_bytes>

Sale con 0 si cabe y con 1 si no.
"""
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from ram_mapa import secciones  # noqa: E402


def main():
    if len(sys.argv) != 3:
        sys.exit('uso: ram_tope.py <fichero.map> <tope_en_bytes>')
    mapa, tope = sys.argv[1], int(sys.argv[2], 0)
    if not os.path.exists(mapa):
        sys.exit('ram_tope: no hay mapa en %s (compila primero)' % mapa)
    filas = (secciones(mapa, '.bss') + secciones(mapa, '.data')
             + secciones(mapa, '.noinit'))
    if not filas:
        sys.exit('ram_tope: el mapa no tiene secciones .bss/.data reconocibles')
    total = sum(f[0] for f in filas)
    if total <= tope:
        print('RAM %d <= %d' % (total, tope))
        return 0
    print('RAM %d > %d (sobran %d)' % (total, tope, total - tope))
    return 1


if __name__ == '__main__':
    sys.exit(main())
