# Conway's Game of Life

![Game of Life Demo](./game_of_life.gif)

## Build

```
make build
```

## Run

```
./life
```

By default this will run the program with no cells filled in.

If you want to fill in a cell, you have three different shapes you can use:
* Acorn
* Glider
* Square

You use a flag bearing the same name as the target shape and then you specify the `x` and `y` coordinates as the next two arguments after the shape name.
Here's an example:

```
./life --glider 20 25
```

```
./life --acorn 10 35
```

They can also be combined to spawn multiple shapes on the same board.
```
./life --acorn 10 35 --square 0 0
```
