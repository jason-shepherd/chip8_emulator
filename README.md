# A Chip 8 emulator
My takes on the "Hello World" of emulators. A simple chip8 emulator written in C, follows super chip8 quirks. Graphics and sound done with SDL2.

# Build
Install SDL2 dependency, on Unix you can use a package manager to install the dev libraries. On Windows download the dev libraries from SDL2 releases and put the path to them in your PATH enviroment variable. Then:
```cd chip8_emulator
mkdir build
cd build
cmake ..
cmake --build .
```

# Usage
Pass the desired rom path as an arguement
`./chip8 rom.ch8`
or
`chip8.exe rom.ch8`
or drag the rom onto the executable.
