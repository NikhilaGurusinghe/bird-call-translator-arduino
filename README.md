# Uses platformIO
https://docs.platformio.org/en/latest/core/quickstart.html

# Useful commands
`pio run`. Process (build) all environments specified in “platformio.ini” (Project Configuration File)

`pio run --target upload`. Build project and upload firmware to the all devices specified in “platformio.ini” (Project Configuration File)

`pio run --target clean`. Clean project (delete compiled objects)

`pio run -e uno`. Process only uno environment

`pio run -e uno -t upload`. Build project only for uno and upload firmware.