# Continuous Integration

The workflow in `.github/workflows/ci.yml` runs on pushes to `main`, pull requests to `main`, and manual dispatch. Permissions are limited to `contents: read`, and concurrency cancels older runs for the same ref.

## Firmware build
The firmware build checks out the repository, sets up Python, installs dependencies from `requirements.txt`, caches PlatformIO directories, runs `python tools/verify_repo.py`, runs `pio run`, and uploads firmware artifacts when produced:

- `firmware.bin`
- `firmware.elf`
- `firmware.map`

## Repository verification
`tools/verify_repo.py` checks required files, confirms the duplicate Wi-Fi example and local `secrets.h` are absent, rejects likely real Wi-Fi credentials, verifies README local links, and scans tracked text files for disallowed repository-positioning terms.

## Static analysis note
`pio check` is not enabled by default because embedded framework checks can add noisy third-party library findings. It can be run locally when investigating a focused firmware change.
