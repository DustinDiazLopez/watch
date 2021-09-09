# Watch

A file watcher for windows.

## What it does

If the file which is being watched changes the specified command will be run.

### Usage

```batch
# watch [sleep] '[cmd]' [...files]
watch 500 'echo this is a test' test.cpp
```

`sleep` is the time in milliseconds that the watcher will wait for to check if _any_ of the specified files have changed.
`cmd` is the command that will execute if any changes are detected.
`...files` are all the files that will be watched for changes.

#### Limitations

There are some limitations to this:

- files with spaces are not supported.
- only `256` files can be watched at a given time.
- the command cannot exceed `1024` characters.

> **NOTE**: These numbers can be changed values can be changes.
>
> - Change the definitions in the header file (`src/watch.h`)
> - Build the app (run `build` -- this will execute the script inside the watch directory)

## Getting started

### Build from source

Clone the repository

```bash
git clone https://github.com/DustinDiazLopez/watch.git
```

You'll need to have a `c` or `c++` compiler:

If you have `g++` available -- simply run the build script. In the command prompt:

```bash
cd watch/
build
````

or run it like this with you own compiler:

```bash
cd watch/
g++ -O2 -o build/watch.exe src/watch.c
```

### Download the release

Download the latest release [here](https://github.com/DustinDiazLopez/watch/releases)

## License

This project uses the following license: [GNU General Public License v3.0](./LICENSE).