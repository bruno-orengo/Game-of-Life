# Game of Life

A Game of Life program made using C, with some aditional 'quality of life' features.

## Table of contents
* [Introduction](#introduction)
* [Features](#features)
* [Status](#status)
* [How to Use It](#how-to-use-it)
* [Example](#example)

## Introduction

Conway's Game of Life problem is known by many and this is a code implementing it. Using the C language, this serves as a simple yet fun personal project. This version has some menu options to make the program a little bit more interactive.

## Features

- Define the maximum number of generations
* Choose the starting size of the cells matrix
+ Limit how many times new generations will be created after the population remains stagnated
- A cool 'Title Screen'

## Status

This code is already completed, I do not intend to further modify it and no more features will be added since it was made as a simple exercize.

## How to Use It

Just compile the main.c file and run the program, then all you need to do is follow the menu options.

**Menu Options:**

`Row Size:` Number of rows.\
`Columns size:` Number of columns.\
`Rate of new generations:` Rate in which new generations will be created; measured in seconds.\
`Number of generations to be stable:` Sets the amount of generations in which the program will stop if the population remains the same.\
`Limit generations:` Sets wheter or not to set a max number of generations.\
`Max number of generations:` Sets the max number of generations if the answer to the previous option was 'y'.

## Example

**Title Screen:**

![Title Screen made using ASCII](./examples/TitleScreen.png)

___________________________________

**Exmple of Inputs:**

![Input example](./examples/InputExample.png)

___________________________________


**First Execution Screen:**

![First Execution Screen](./examples/FirstScreen.png)

___________________________________

**Execution Example:**

![Execution Example](./examples/example.gif)

___________________________________
