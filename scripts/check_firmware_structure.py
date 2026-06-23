#!/usr/bin/env python3
from pathlib import Path
import sys
ROOT=Path(__file__).resolve().parents[1]
def fail(m): print(f"ERROR: {m}"); sys.exit(1)
for p in ['firmware/EdgeGuard_ESP32/EdgeGuard_ESP32.ino','firmware/EdgeGuard_ESP32/edgeguard_control.h','firmware/EdgeGuard_ESP32/edgeguard_control.cpp','firmware/EdgeGuard_ESP32/edgeguard_types.h','firmware/EdgeGuard_ESP32/edgeguard_event_log.h','firmware/EdgeGuard_ESP32/edgeguard_event_log.cpp']:
    if not (ROOT/p).exists(): fail(f'missing {p}')
forbidden=['OLED display required','camera required','Firebase required','Blynk required','MQTT required','ESP-IDF required','PlatformIO required']
for path in list((ROOT/'README.md').glob('*')) + list((ROOT/'docs').glob('*.md')) + list((ROOT/'hardware').glob('*.md')):
    text=path.read_text(errors='ignore')
    for term in forbidden:
        if term.lower() in text.lower(): fail(f'forbidden requirement phrase "{term}" in {path.relative_to(ROOT)}')
print('Firmware structure validation passed.')
