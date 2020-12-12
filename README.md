# aoc_2020
This repo contains my solutions in C++ for Advent of Code's 2020 edition.
As I've always worked with Linux, I wanted to take this oportunity to setup
my personal Windows computer and see how does working in this OS looks like.

While doing the exercises, I struggled a bit with some of the C++ "utilities"
to handle strings and files, when compared to other solutions I found online
written in golang, python or js.

## Feedback
This repo is very open to some feedback! I've done some things very "quick and dirty",
but if, for some reason you land here, and would like to share an improvement,
please, do! :)

## Compiling the code
You are going to need C++17. I am a big fan of some string and file utilities of
boost, but this time I wanted to just use the standard library. So, to compile it,
you just need to navigate to one of the folders in which a main.cpp file is present and run:

```bash
g++ main.cpp -std=c++17 -o <output>
```

## Linux issues
I've noticed that maybe you'd need to change `::isspace`, if running on Linux, to
`std::isspace`.
