GUI library
===
System of gui objects based on SFML for fast interface building

- [Predantant](#predantant)
	- [Description](#description)
	- [Building](#building)
		- [Dependencies](#dependencies)
		- [Commands](#commands)
	- [Purpose](#purpose)
	- [Plans](#plans)


### Description

This library provides set of classes for creating gui

Directory `example` contains example - library used only in Menu class, other files used for environment

Screenshots from app (which logic is around 100-200 lines - how to count) are located in `screenshots`

### Building

Run `make build` to compile, `make run` to start

Options may be seen after `make help` command

#### Dependencies

[SFML](https://www.sfml-dev.org/): `apt-get install libsfml` (example for ubuntu)

### Purpose

It's personal educational project
I was working on [game](https://github.com/BelovDV/game-logic.git), after several rewriting of gui for it I decided to make it as a separate project

### Plans

It is third version of basic c++ interface for this library - Block. Now, it is ready to be shown. It isn't good enough, however. So, it is still in development.
