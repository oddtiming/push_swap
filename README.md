# push_swap
1. [Description](#description)
    1. [Goal](#goal)
    2. [Allowed moves](#allowed)
    3. [Problem definition](#definition)
    4. [Initial ideas](#ideas)
    5. [Structs](#structs)
        - [Iterators](#iterators)

# Description

42 Push_swap’s project; a little game to introduce sorting algorithms. 

The algo wiki is pending until I figure it out for myself :)
Feel free to take a look at the project journal for now

## Goal

The goal is to sort a given stack of n values (`stack_a`) in ascending order from the top of the stack by using a selected set of moves.

- The values are taken in as executable parameters, and can be any signed integer values, without duplicates.
- The first value entered in argv will be at the top of the stack (`index == 0`), the last will be at the bottom (`index == size - 1`)
- Although the final sorted values needs to be in the first stack, you dispose of an adjust stack, (`stack_b`), to which you can temporarily push values.
- For the values to be parsed outside the scope of the program, the sequence of moves used to sort need to be written to STDOUT.

<a name="allowed"></a>
## Allowed moves

- rotate (`rx`)
    - Notation: `ra, rb, rr (both)`
    - Rotate the stack towards the top; the first value of `stack_x` becomes the last, and every other value decrements its index by one.
- reverse rotate (`rrx`)
    - Notation: `rra, rrb, rrr (both)`
    - Reverse rotate the stack towards the top; the last value of `stack_x` becomes the first, and every other value increments its index by one.
- push (`sx`)
    - Notation: `sa, sb, or ss (both)`
    - Swap the first and second values of `stack_x`.
- push (`px`)
    - Notation: `pa (b→a), pb (a→b)`
    - Take the value at the top of one stack to the top of `stack_x`.

<a name="definition"></a>
## Problem definition

The way I defined its problem, this project was not about building a sorting algorithm per se, but rather about modding and applying different sorting algorithms to a custom set of constraints. From the get-go, I had in mind that I should be comparing solutions to find the best for a given starting stack, because each algo has different edge cases, so it seemed like a good way to learn about the pros and cons of each of them, and come up with a custom solution for each set of values.

<a name="ideas"></a>
### Ideas

- Start by finding a center at which the number of sorted values is maximal
- I would like to do a virtual state or a duplicate of each stacks through which I could simulate a couple moves in advance, and add the best list of moves to a move buffer
    - The constraints could be:
        - Does it increase the number of sorted from center?
        
<a name="structs"></a>
## Structs

<a name="iterators"></a>
### t_iterator 🎡

```c	
int     head;
int     index;
int     prev_index;
int     max_size;
int     nb_loops;
bool    is_reverse;
```