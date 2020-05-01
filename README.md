# sdl2-hearts-game

A [SDL 2.0](https://www.libsdl.org/) based game of Hearts I created during college.

Note: This project was originally created using Eclipse CDT for Linux, and started by following a [simple SDL tutorial by Will Usher](https://www.willusher.io/pages/sdl2/)

Special credit to [kenney.nl](https://www.kenney.nl/) for the card images: [https://www.kenney.nl/assets/boardgame-pack](https://www.kenney.nl/assets/boardgame-pack)

## Requirements:

### Linux

#### Building

Most Linux systems should support command-line installation. Simply follow the instructions listed here: [https://wiki.libsdl.org/Installation#Linux.2FUnix](https://wiki.libsdl.org/Installation#Linux.2FUnix)

#### Running

- Navigate to the source directory
- Run the following:
    ```bash
    > make
    > ./sdl2-hearts-game.out
    ```

### Windows with [Cygwin](https://www.cygwin.com/)

#### Building

- gcc-g++
- libSDL2-devel
- libSDL2_image-devel
- libSDL2_ttf-devel

#### Running

- debus-x11
- openssh
- xinit
- xorg-server

1. Open a Cygwin terminal and run `startxwin`
1. Open a second Cygwin terminal
    - Navigate to the source directory
    - Run the following:
        ```bash
        > export DISPLAY=:0
        > make
        > ./sdl2-hearts-game.exe
        ```

## Game Info:

### Rules

- The full deck (52 cards) is dealt randomly between four players (13 each)
- Just to spice it up, at the very beginning everyone picks three cards to swap with others
- The person with the two of clubs starts off the first round
- You must match the starting suit (per round)
- If you don't have one of that suit, you can play anything
- __Hearts__
    * These cards are a "last resort"
    * If no one has played a heart yet, you can't play one
    * You can only play a heart if it's the last suit you have
    * If someone has already played a heart (anytime during the game, per deal) hearts are "broken"
    * If hearts are "broken" they become a normal suit that can be played just like any others
- At the end of a round (each person has layed down a card) the winner is the one with the highest value in the starting suit

### Scoring

- For each heart you win you gain a point
- The queen of spades counts as 13 points
- The scoring is like golf, lowest score wins at the end

## Demo:

![Demo](Demo.gif?raw=true "Demo")
