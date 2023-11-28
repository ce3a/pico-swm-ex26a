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
sudo apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi build-essential
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
sudo apt install gdb-multiarch
```

Build and install OpenOCD as described in [installing-openocd](https://www.raspberrypi.com/documentation/microcontrollers/debug-probe.html#installing-openocd).

Execute the following steps to allow running `openocd` without `sudo`.

- Make sure you are in the `plugdev` group.

    ```
    sudo useradd -G plugdev $(whoami)
    ```

-  From the `openocd` directoy:

    ```
    sudo cp contrib/60-openocd.rules /etc/udev/rules.d/
    sudo udevadm control --reload
    sudo udevadm trigger
    ```

OpenOCD server.

```sh
openocd -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c "adapter speed 5000"
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

1. [RP2040 Datasheet](https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf)
2. [Getting started with Raspberry Pi Pico](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf)
3. [Raspberry Pi Pico C/C++ sdk](https://datasheets.raspberrypi.com/pico/raspberry-pi-pico-c-sdk.pdf)
4. [Pico C SDK Doxygen](https://www.raspberrypi.com/documentation/pico-sdk/index_doxygen.html)
