# dict-word-finder
A cli tool to find words in a dictionary

## Intro

This repo contains tools to scrape words from a text dictionary as well as search for words with a prefix in a dictionary.

## Installation

To build `dict-word-finder`, run the following commands after cloning the repo

```
mkdir -p bin
cd bin
cmake ..
make
```

## Usage

This section explains how to use the cli tools

### `word_scrape`

To use `word_scrape`, run a command like:

```
$ ./word_scrape dictionary.txt words.txt
```

This scrapes the dictionary file into a pure words file. They will appear in the new file like this

```
append
apple
apply
```

### `word_finder`

To use `word_finder`, run a command such as

```
$ ./word_finder yo words.txt
```

This will print out a list of alphabetically ordered words that start with that prefix:

```
$ ./word_finder yo words.txt
yockel
yode
yodle
yoga
yogi
yoicks
yoit
yojan
yoke
yold
yolk
yoll
yom
yon
yore
york
yot
you
yow
yox
```

## License

This work is MIT licensed. 

Also licenses of the Webster dictionary apply appropiately
