# Naming convention

Glossary of names to use when talking about the technicals of the game or decompiling the project.

## Player

The playable character that can be controlled.

Avoid using names like Alucard or Richter if variables or functions are shared between the two. Use `player` when in doubt.

## Entity

An object that has its own logic and life-span. An example of entity is the Player, breakable objects like the candle, the item dropped by the foes or the foes themselves.

Name discarded:

- Actor: it did not feel right to call Actor a game object that is completely passive like an invisible trigger.
- Object: ambiguous when used in the context of object oriented programming.

## State machine

Each entity has its own state machine with a switch/case that performs different tasks based on its `step` value. The function of the entity `Foo` that handles its state machine follows the name schema `EntityFoo`.

The name `step` is found in the debugging strings of the game.

Avoid using names such as `AI` or `logic`.

The name convention `UpdateFoo` is being evaluated as strong candidate to replace the existing one.

## Stage

The game is split into stages (eg. `ST0`, `NO3`, `NZ0`). The name was decided due to the structure of the game disc `ST/{stageName}`. It is assumed ST stands for Stage.

Avoid using names such as `zone`, `level`, `area` or `map`.

## Room

Each stage contains a series of rooms. A room is where the player can roam around and it is confined within the camera borders. When the player reaches the border of the screen, the room is changed with a different layout and set of entities.

Avoid using names such as `area` or `map`.
