# `modules/`
Our project is divided into modules. All items within the module are independent of each other, but modules themselves are interdependent. Modules are composed of **module-items**: individual APIs within defined and implemented within the module.

For example, the `apps` module contains all application-level interfaces. All module-items in the `apps` module are independent, however the `apps` module is dependent on the `devices` module.

**Modules and module items**:
- `internal`: Contains internal data structures and definitions as well as some utilities that help better abstract some parts of the mcu development tools (like mmio and interrupts).
    - `internal/mmio`: contains MMIO system, w/ functions for getting and setting fields.
    - `internal/interrupt.c`: Contains interrupt system: all the interrupts that can be overwritten.

- `kernel`: Threads, mutexes, semaphores... Contains kernel stuff and also startup code.
    - `kernel/mutex`: Mutexes
    - `kernel/thread`: Threads
    - `kernel/semaphore`: Semaphores

- `periphs`: Contains all periheral API. By this I mean a peripheral within the MCU, like the I2C or SPI subsystems.
    - `periphs/SPI`: Serial Peripheral Interface
    - `periphs/I2C`: Inter-Integrated Circuit
    - `periphs/DMA`: Direct Memory Access
    - `periphs/UART`: Universal Asyncronous Receiver/Transceiver
    - `periphs/EXTI`: Extendible Interrupt and Event controller

- `devices`: Contains all device drivers. This would be where code for our temperature sensors, IMUs, etc. would use the `periphs` interfaces to simplify device use.
    - `devices/temp-sensor`: Temperature sensor
    - `devices/imu`: Internal Measurment Unit
    - `devices/baromenter`: Barometer
    - `devices/magnetometer`: Magnetometer
    - `devices/radio`: Radio
    - `devices/gnss`: GNSS
    - `devices/curr-sensor`: Current Sensor
    - `devices/rs485`: RS-485 Transciever

- `apps`: Contains all application-level itnerfaces. Examples: telemetry system, data logging system, data aquisition system for a specific sensor...
    - `apps/data-telem`: Data telemetry system
    - `apps/launch-sequence`: Launch sequence system

- `util`: This includes all utilities such as math libraries, but it crucially contains the error-handling utilities that define the error-handling system.
    - `util/errc`: Error handling and error codes
    - `util/math`: Math utilities

Each module contains an `include/<module-name>` directory with all of the header files for the interfaces, and a `src` directory with the implementation of said interfaces.
