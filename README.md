# PICO-SWM-EX26A

Smart water meter based on Raspberry Pi Pico and a Panasonic EX26-A
photoelectric sensor.

## Setting up the build environment

Get the  pico sdk.

```sh
git submodule update --init --recursive
```

Install the build toolchain.

```sh
sudo apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi build-essential gdb-multiarch
```

## Building the image

Build the image using CMake.

```sh
cmake --preset debug
cmake --build build/debug/ --target install
```

If the build was successful, you will find the image in the `Debug` directory.
To build the release configuration, replace `debug` by `release` in the commands
above.

## Debugging with GDB

Install the debug toolchain.

```sh
sudo apt install openocd gdb-multiarch
```

OpenOCD server.

```sh
sudo openocd -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c "adapter speed 5000"
```

From a another terminal window, switch to the `Debug` directory and start GDB.

```sh
gdb-multiarch pico-swm-ex26a.elf
```

From the `(gdb)` prompt, connect to the OpenOCD server and run the application.

```
target remote :3333
continue
```

## References

- [Getting started with Raspberry Pi Pico](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf)
- [Raspberry Pi Pico C/C++ sdk](https://datasheets.raspberrypi.com/pico/raspberry-pi-pico-c-sdk.pdf)
