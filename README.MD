# ESP Flash dumper

ESP32-based SPI flash dumping and analysis tool using bit-banged SPI and a serial CLI for flash reading, JEDEC identification, and firmware extraction.

## Overview

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

### 📖 Example Commands

```bash
read 0x03 0x000100
```

Reads data from a specific flash memory address.

```bash
getman 0x9F
```

Retrieves JEDEC manufacturer information.

```bash
dumpf 0x03 0x200000
```

Dumps the full flash memory contents.

### Purpose

This project was created as a low-level learning and research tool focused on:

- Understanding SPI communication internals
- Firmware extraction techniques
- Embedded systems development
- Hardware reverse engineering
- Manual protocol implementation

---
