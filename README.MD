# ESP Flash dumper

![C](https://img.shields.io/badge/language-C-blue.svg)
![ESP32](https://img.shields.io/badge/plataform-ESP32-red.svg)
![ESP-IDF](https://img.shields.io/badge/framework-ESP--IDF-black.svg)
![License](https://img.shields.io/badge/license-MIT-purple.svg)

ESP32-based SPI flash dumping and analysis tool using bit-banged SPI and a serial CLI for flash reading, JEDEC identification, and firmware extraction.

## 📚 Overview

Instead of relying on the ESP32 hardware SPI peripheral, the project implements a software-driven SPI interface (**bit-banging**), giving full control over GPIO timing and communication behavior. This approach makes the tool flexible for interacting with a wide range of external SPI flash chips and low-level hardware targets.

The tool provides a serial command-line interface through `idf.py monitor`, allowing direct interaction with flash devices using simple commands for reading memory, dumping firmware contents, and retrieving JEDEC manufacturer information.

### ✨ Features

- Software-implemented SPI (bit-banging)
- Interactive serial CLI
- SPI flash memory reading
- Full firmware dumping (Via CLI)
- JEDEC manufacturer identification
- Configurable GPIO pin mapping
- Designed for firmware analysis and reverse engineering workflows

### 📖 Command structure

```bash
COMMAND ADDRESS CHUNK_SIZE FAST_READ
```

### 📍Purpose

This project was created as a low-level learning and research tool focused on:

- Understanding SPI communication
- Extraction with Bit-banging technique
- Embedded systems development
- Manual protocol implementation

## 💻 Usage

 1. Clone this repository with `git clone https://github.com/santtos0x1/spi-flash-dumper.git`
 2. Enter folder and flash your ESP32 using `idf.py flash -p /dev/X`
 3. Open the ESP-IDF monitor: `idf.py monitor -p /dev/X`

---

### ⚠️ Warning

- It is recommended to ***disable the Task Watchdog Timer (TWDT)*** to prevent it from triggering during bit-banging operations.

Step-by-Step TWDT deactivation:

1. Open ESP-IDF menuconfig: `idf.py menuconfig`
2. Disables TWDT in `Component config -> ESP System Settings -> Initialize Task Watchdog Timer on startup`

### 📋 Commands

```bash
read 0x000100 256
```

- Reads data from a specific flash memory address.

```bash
jedec
```

- Retrieves JEDEC manufacturer information.

```bash
dump 0x100000 16 1
```

- Dumps the full flash memory contents.

### ⛔ Stopping the Dump Process

To stop the dump process, press the **BOOT** button on the microcontroller board. The firmware continuously checks the BOOT button state during execution. When the button is pressed, the dump operation is safely interrupted and returns to command line.

---
