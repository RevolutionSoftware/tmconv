# TMConv

A tool for converting formated-text tilemaps into assembly source files, written in ANSI C.

## Build

```
cc tmconv.c -std=c89 -Os -DNDEBUG -g0 -s -Wall -o tmconv
```

or with gnu make

```
make
```

## Usage

```
./tmconv formated.txt [optional: base for outputnames]
```

The optional parameter decides what to use for basename for the generated .asm and .inc files.

## TODO

- Parser
- Translator
- Design how the formated-text inputfile should be written
