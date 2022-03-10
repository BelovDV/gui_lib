GUI library
===
System of gui objects based on SFML

- [Predantant](#predantant)
	- [Description](#description)
	- [Building](#building)
		- [Dependencies](#dependencies)
		- [Commands](#commands)
	- [Purpose](#purpose)


### Description

This library provides set of classes for creating gui

Directory `example` contains example - library used only in menu.cpp (mostly in constructor), other files used for environment

Screenshots from app (which logic is written in __ lines in menu.cpp - from 10?? to ___) are located in `screenshots`

### Building

Run `make build` to compile, `make run` to start

Options may be seen after `make help` command

#### Dependencies

[SFML](https://www.sfml-dev.org/): `apt-get install libsfml` (example for ubuntu)

### Purpose

It's personal educational project
I was working on [game](https://github.com/BelovDV/game-logic.git), after several rewriting of gui for it I decided to make it as a separate project
