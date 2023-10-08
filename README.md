# dhb: Decimal/Hexadecimal/Binary

The `dhb` utility is used to convert numbers between different base systems.
The name stands for "Decimal, Hexadecimal, Binary."

## Usage

By default, the decimal, hexadecimal, and binary representations of an input
number are printed to standard output.

```sh
$ dhb 224
    224 0xE0    0b11100000
```

If a number is entered with a known prefix, it is assumed to be in the base
system represented with that prefix. These are: `0x` for hexadecimal and `0b`
for binary.

```sh
$ dhb 0xe0
    224 0xE0    0b11100000
```

## License

This project is licensed under the MIT license.
