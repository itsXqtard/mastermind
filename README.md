# my_mastermind

Mastermind is a game composed of 8 pieces of different colors. A secret code is then composed of 4 distinct pieces. A player has a certain amount of attemps to guess the secret code.


## Game Rules

The default configurations allows users 10 attempts to guess the code. The default code will result in a randomized 4 digit number ranging between `0000-7777`

Each guess must have exactly 4 digits. Every subsequent guess will introduce a new round until the number of allows attempts.
Rounds will start at 0 and increase as user attempts a guess. Meaning player is only pieces `0 - 7` or range between `0000-7777` 


## Supervisor Mode

From the command line you are allowed to set the number of attempts if you prefer and also the code to that you want player to guess.
```
`-c [value]` -  Allows you to set the code. 
                Range: [0000-7777]. 
                If code contains non digit value code will revert 
                to default of randomized 4 digit number

`-t [value]` -  Allows you to set the number of allowed attempts
                Range: [0-Positive Value]
                If code contains any non positive value attempts 
                will revert to 10 for the number of allowed attempts
```

if during the game you wanted to give up and see the answer you can type `-s` and it will print the code.


## Setup
To compile the files in the terminal just type `make` and it will build a binary for you to run the game.
To have a clean build of the game type `make clean` and then `make`.


## Authors

[@Quang Doan](https://git.us.qwasar.io/doan_q)

## Version History

* 0.1
    * Initial Release