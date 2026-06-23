#!/usr/bin/env python3
from pathlib import Path
import re, subprocess, sys
ROOT=Path(__file__).resolve().parents[1]
def fail(m): print(f"ERROR: {m}"); sys.exit(1)
def need(p):
    if not (ROOT/p).exists(): fail(f"missing {p}")
for p in [Path('firmware/EdgeGuard_ESP32/secrets.h.example'),Path('README.md'),Path('AGENTS.md'),Path('docs/architecture.md'),Path('docs/state_machine.md'),Path('docs/testing_plan.md'),Path('docs/interview_notes.md'),Path('docs/ci.md')]: need(p)
tracked=subprocess.run(['git','ls-files','firmware/EdgeGuard_ESP32/secrets.h'],cwd=ROOT,text=True,capture_output=True,check=True).stdout.strip()
if tracked: fail('firmware/EdgeGuard_ESP32/secrets.h is tracked')
if (ROOT/'firmware/EdgeGuard_ESP32/secrets.h').exists() and (ROOT/'.github').exists() and 'CI' in __import__('os').environ:
    fail('secrets.h should not be present in CI')
text=(ROOT/'firmware/EdgeGuard_ESP32/config.h').read_text()
expected={'PIN_DHT':4,'PIN_HCSR04_TRIG':5,'PIN_HCSR04_ECHO':18,'PIN_LDR_DO':34,'PIN_RELAY1':26,'PIN_RELAY2':27,'PIN_LED_GREEN':23,'PIN_LED_RED':22}
for name,val in expected.items():
    if not re.search(rf'constexpr\s+uint8_t\s+{name}\s*=\s*{val}\s*;', text): fail(f'{name} must remain GPIO {val}')
print('Repository validation passed.')
