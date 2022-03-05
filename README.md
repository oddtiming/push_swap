# push_swap
- [Description](#10)
    - [Goal](#11)
    - [Allowed moves](#13)
    - [Problem definition](#15)
    - [Initial ideas](#17)
    - [Structs](#19)
        - [Iterators](#51)
- [Project journal](#19)
    - [Start solve5](#70)
    - [Refactor](#71)
    - [Haven’t actually finished sort_5. Hihi](#72)
    - [Start sort_big](#73)
    - [Vectors working, moves list working, onto t_iterator, and bigger things](#74)
    - [moves_list, t_insert_info, and more...](#75)
    - [Debug Galore](#76)

# Description {#10}

42 Push_swap’s project; a little game to introduce sorting algorithms. 

## Goal {#11}

The goal is to sort a given stack of n values (`stack_a`) in ascending order from the top of the stack by using a selected set of moves.

- The values are taken in as executable parameters, and can be any signed integer values, without duplicates.
- The first value entered in argv will be at the top of the stack (`index == 0`), the last will be at the bottom (`index == size - 1`)
- Although the final sorted values needs to be in the first stack, you dispose of an adjust stack, (`stack_b`), to which you can temporarily push values.
- For the values to be parsed outside the scope of the program, the sequence of moves used to sort need to be written to STDOUT.

## Allowed moves {#13}

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

## Problem definition {#15}

The way I defined its problem, this project was not about building a sorting algorithm per se, but rather about modding and applying different sorting algorithms to a custom set of constraints. From the get-go, I had in mind that I should be comparing solutions to find the best for a given starting stack, because each algo has different edge cases, so it seemed like a good way to learn about the pros and cons of each of them, and come up with a custom solution for each set of values.

### Ideas {#17}

- Start by finding a center at which the number of sorted values is maximal
- I would like to do a virtual state or a duplicate of each stacks through which I could simulate a couple moves in advance, and add the best list of moves to a move buffer
    - The constraints could be:
        - Does it increase the number of sorted from center?
        

## Structs {#19}

<aside>
### 🎡 **t_iterator** {#51}

- int head
- int index
- int prev_index
- int max_size
- int nb_loops
- bool is_reverse
</aside>

## Start solve5 February 17, 2022 {#70}

I’ve been watching videos on sorting algorithms, and trying to understand [VBrazhnik’s algorithm](https://github.com/VBrazhnik/Push_swap/wiki/Algorithm), which maxes out at **522 for 100** values, and at **5468 for 500** values. It seems to rely on a hybrid between two comparison parameters, both going full completion, only the best of which he chooses to output... It seems quite smart, and I do believe that if I end up writing out a couple of different algorithms, I should carry out all of them, at least until they reach a number of moves bigger than the smallest number of moves already performed
(e.g. if quick sort gives out 675 operations, and divide and conquer is already at 676, stop there)

I’m not quite there yet, but I do want to expose myself to these algorithms so that they can be digested in the background. Here are the most important tasks that I would like to do until then :

- [x]  Write the sort5 algo
    - [x]  1st rule : is_sorted_at_pos; takes care of 5/120 combinations
    - [x]  2nd rule: off-by-one ; if a set of number could be sorted by swapping only two values, rotate or push and do that.
    - [x]  For everything else, and FOR NOW I think I should simply push two values to stack B and sort the other 3 in two moves max, as seen by the sort3 algo
    - The rest of the complexity should be built on top of that, for now the goal should be mainly to familiarize myself with the algo
- 
- [x]  Refactor my code to change the
    - [x]  t_stacks to t_container{
       t_stack A;
       t_stack B;
       int tot_sz;
    }
    - [x]  typedef struct s_stack{
      int *stack;
      int sz;
    }
    - [ ]  
    
    <aside>
    ⚠️ February 22, 2022 : changed my mind, ended up opting for a t_main_container, not sure if will switch as of yet, not important
    
    </aside>
    
- [x]  Update the move() fct to better separate the arguments 
e.g. : move(t_stacks *stacks, t_move move, char stackID)
    - [x]  Create a typedef for move_type
    `typedef int t_move`
    `enum e_moves {
        R,
        RR,
        P,
        S,
    }`
    - [x]  Make a recursive combination for the ‘r’
    
    ```c
    void move(t_stacks *stacks, t_move move, char stackID){
    	int *stack;
    	int size;
    
    	if (stackID == 'r')
    	{
    		stackID == 'b';
    		move(stacks, move, 'a');
    	}
    	stack = (stackID == 'a') * stacks->A + (stackID == 'b') * stacks->B;
    	size = (stackID == 'a') * stacks->sizeA + (stackID == 'b') * stacks->sizeB;
    	if (move == R)
    		rotate(stack, size)
    	else if(move 
    }
    ```
    
    ---
    
    ### Finished 5x5, moving on to refactoring February 20, 2022
    
    ---
    
    So I spent quite a lot of time (much more than anticipated, but then again that was also anticipated) working out the sort5 algo, and I settled for something quite simple that I shall try and describe concisely here:
    
    1. Is the list sorted at some pos? —Yes—> rotate_to_pos0(pos_smallest) —> exit
    
    2. Can a single swap make the list sorted at some pos ? —Yes —> rotate_to_pos0(swap_index), swap, rotate_to_pos0(pos_smallest) —> exit
        1. —No—> pb
        2. Is the list sorted at some pos? —>Yes—> insert_b

### Refactor {#71}

- Allocate 3x the memory needed for both stacks, this way rotates and pushes will only necessitate a change of index, no reindexation. It is not memory efficiant (requires 300% of the memory), but it will max out at 8000 bytes too many for a stack of 500 (500 entries x 2 stacks x 2 times too big x 4 bytes per int = 8000), and it will save a trmendous amount of reindexation.
- Then move on to circular doubly linked list, which will require quite a large amount of refactorization, plus writing some core functions in the libft (dblst_addback(), dblst_addfront(), dblst_new(), dblst_clear(), dblst_delone(),

---

## Haven’t actually finished sort_5. Hihi February 22, 2022 {#72}

---

Spent an unholy amount of time on it, but I finally gathered what is the theoretical minimum of moves, and how I can make sure to never exceed it. The two sorting methods I have (try_pb, and double_pb (actually juste made by a recursive call to sort_5, so technically I should be able to configure try_pb to also attempt (pb x2), b/c it probably tries pushing the second or last element first and then sorting, which ultimately is slower)

- [ ]  Make the first move of try_pb be a push and try_swap resulting in another swap, collect the amount of moves, and compare it to pushing any other value first. Technically, then, it should try pushing any values twice, so it should be try_rotate; try_swap; try_pb ⇒ push_b[0]; try_pb; push_b[1]; try_pb; ...
- [I] Could template all my functions the same and have a dispatch() fct that would, when inited, take as input all the functions templated, and add them to a vector, or an array rather. Prototype could be

```c
void    init_dispatch_fct(int option, ...)
{
	void (**fct)(t_main_container *cont, int move);
	va_list ap;
	int nb_cmds;
	int i;

	va_start(ap, option);
	fct = NULL;
	if (option == INIT)
	{
		nb_cmds = va_arg(ap, int);
		fct = malloc((nb_cmds + 1) * sizeof(*fct));
		i = 0;
		while (i < nb_cmds)
		{
			fct[i] = (void *(t_main_container *, int)va_arg(ap, void *);
			i++;
		}
	}
	else if (option == FREE)
	va_end(ap);
}
```

  Then you could access the dispatch fct with a number of args

- What is the best way to try different algorithms on the same stack without losing the original stack, but also avoiding wasting too much memory and making too many computations. For example, is it better to create a virtual board for each algorithm, or to simply undo the moves as you do them?
    - int **moves() as part of the struct, that could basically be a vector or re-assignable length.
    - have a simulation that does the moves virtually (either to a copy of the stack, or by undoing the moves afterwards) then redo an outputted version with the chosen algorithm. Seems wasteful.
    - A better idea would be to have the algorithm progress, and if it is under a certain MAX_MOVES_FOR_X, it stops and outputs what’s given to it. Then the algo returns IS_SORTED (I like it better than true, somehow, but it is definitely more obfuscating). That’s as product-driven as it gets, and I kind of like that approach, even if I know I might get a lot of flack for it, because I think it aptly represents the most common real world requirements

Stopped here for the day, tired af : 

Need to implement:

- [ ]  moves_list vector "class" that dynamically reallocates memory
- [ ]  add_move(moves_list, move) to add a move to the list
- [ ]  undo_moves(moves_list) could be used to revert back to previous changes
- [ ]  adding a nb_moves parameter to the main container to know when a solution is good enough (i.e. nb_moves < MAX_MOVES_FOR_N)
- [ ]  invert_4(), but that should be easy enough (sa ra ra sa)

I'm stopping for the day because that seems like quite a lot of refactoring up ahead, and I need a fresh(er) mind

---

## Start sort_big February 23, 2022 {#73}

---

So it is currently 11:30am, and ahead of me lies have a full day of coding of which I want to make the most. So in order to not get too sidetracked, I want to stick to a schedule for the day:

- [ ]  Write the script to invert left windows and left-alt keys on Windows keyboards, and a script to reverse the layout.
    
    **30 minutes max**
    
- [ ]  Write moves_list for sort_5, and implement the MAX_MOVES_FOR_N. It should be quite simple, as the only functions (besides vector constructor and destructor) are add_move, print_moves_v and undo_moves_v
    
    **2 hours max**
    
    - Update : too me a little over 2 hours and a half, but I actually wrote a sort of vector class. It is dynamically sized in both directions, so that inserting at the beginning is no more costly than inserting at the end.
        - I might switch the vector data type to a void **, or even to a simple int *, since I solely intend on passing by value and not addresses.
- [ ]  Start sort_100
    - [ ]  Write a bubble_sort, or rather a simple insertion_sort
    
    **2 hours max**
    
    - [ ]  Watch a video or two on divide and conquer 
    [[Merge sort using divide and conquer](https://www.youtube.com/watch?v=9aWRNVB0NtY)]
    [[Quick sort using divide and conquer](https://www.youtube.com/watch?v=70CC8cDajBk)]
    - [ ]  Lay out a schematic view of the divide and conquer algo.

- [I] I could have a cont→a and cont→b that just point to different virtual stacks, so that the algorithms can use the same syntax independently, without having to refer to cont→algo→divide→a
                 Would need a setup_algo() fct that could point the appropriate stacks, and maybe even appropriate function pointers.
    - Could also implement more function pointers in general such as
    
    ```c
    typedef bool (*rotate_stack)(t_main_container*, int);
    // note that the typedef name is indeed rotate_stack
    
    typedef struct s_main_container {
        rotate_stack rotate_fct = rotate_a;
    } t_main_container;
    ```
    
- Could I make a vector iterator that would take inputs between `FORW, REV, BEGIN, REVEND` and only do a va_arg() when it’s `FORW` or `REV`
    - Iterator could be its own struct with an init() fct that would that would take as input a size, a position, and a direction. This way I could easily code helper functions for that struct that would iterate, or destroy an iterator, or modify the iterator.
    

---

## Vectors working, moves list working, onto t_iterator, and bigger things February 26, 2022 {#74}

---

So my refactoring seems to be done (although writing this “seems” makes me realize I should probably be doing more testing before I move onto more complex endeavours). I started coding a 2d vector yesterday, and I do believe that I was in the right direction, but turns out I don’t need a whole 2D vector class, since all I really needed was two moves_list ; one for the best set of moves, and one to hold the current attempt.

So the logic is as follows :

1. The main container has a t_vector member called final_moves_list. 
2. Once you call a certain sorting algorithm (e.g. sort_small), it will itself assign the smallest list of moves to final_moves_list. 
3. For bigger algorithms that require many different attempts, the same recursive logic will be applied, at the end of which the smallest_moves_list will be returned to the “main dispatch” fct 
    1. e.g. sort_big will be main_dispatch
    2. try_divide_and_conquer()
        1. temp for different sorting segments (for example)
        2. returns smallest_nb_moves
    3. try_sort_by_incremental_index() 
        1. temp for different stack_heads.
        2. temp for reverse_order or canonical_order
        3. returns smallest_nb_moves
    4. try_sort_by_incremental_value()
        1. temp for different stack_heads.
        2. temp for reverse_order or canonical_order
        3. returns smallest_nb_moves
    5. try_quick_sort()
        1. temp for which stack to keep values.
        2. returns smallest_nb_moves

### Iterators

The idea is quite simple : create a struct that could self-sufficiently iterate through a list of values 

- [I] For the recalculation of the prev_biggest & prev_smallest, I could simply call a update_ps_iterators() fct that would have static variables to hold the state of biggest/smallest, and update the iterators if and only if the biggest/smallest element in a stack has changed as the result of a push (b/c iterator updating works just fine for rotates and swaps

todo:

figuire out 0 3 1 4 2 (should be pb and swap)

change insert_b to favor insert values with smallest delta between insert_val_a and insert_val_b

- [I] If I class by index or value (like [the algo I saw on VBrazhnik’s github](https://github.com/VBrazhnik/Push_swap/wiki/Algorithm)), I should also check if I can swap the values before choosing between the two algos. Eaach potential swap increases the number of linked values by 0.5

---

## moves_list, t_insert_info, and more... March 2, 2022 {#75}

---

Okay so I have a lot to confess, I went all out on complexity, and I’m on the verge of making it work.

I have the insert_info living in the main cont, but being updated in insert_b by sub-functions init_insert_costs() calculate_insert_costs() and insert_elem_b(). There seems to still be a couple of bugs I need to work out, so I figured I might as well try and document them as best I can as I go. I feel like I’ve already been over a million already.

- Bug :
    - Description: weird segfault where my cont's values kept getting written over when going into undo_moves()
        - Case: ./push_swap_debug 4 3 2 0 1
    - Possible causes: seems to be caused by an unitialized value in undo_moves, but unsure of why it manifested itself only now.
    - Fix #1: removed t_insert_info from the main cont, to make it live locally in insert_b, as it is not needed elsewhere
        - Result: reverse_fcts array in main cont now appears to be NULL once it reaches undo_moves()
        - Thoughts: It seems to me like the cont gets corrupted somehwere upstream od undo_values, but there seems to b e
    - Fix #2: init the values in undo_moves
        - Result: Now the cont seems to be corrupted

```
Bad news, it now loops forever
                :)

```

Actually in the middle of splitting files rn, and I’m realizing that I absolutely never used the tail, only the head...... 

Should probs rename it to min_val too.

Should also add a value to iterators or  make min_

---

## Debug Galore March 3, 2022 {#76}

---

So I think it’s time for me to start implementing unit tests for each of the functions. I’ll start with the foundational ones, like calculate_insert_costs

- Bug:
    - Description: infinite loop of rra
        - Case: ./push_swap_debug 4 3 2 0 1
    - Possible causes: seems to be a faulty insert_b, since testing pb and try_swap it in isolation pinpointed the loop to insert_b
    - Fix #1: Added update_insert_info() to init_insert_info() when b is not empty
        - Result: now the function properly works in not inserting anything when not needed
    - Fix #2: properly updated a_info→dist0 in calc_insert_info()
        - oops
    - Fix #3: added recursive exit condition in try_sort_small
    if (try_sort_small()) return (true);
        - Result: Now seems to be working as intended
        
- Bug #1:
    - Description: seg fault when I change min nb_moves from 8 to 7
        - Case: ./push_swap 2 4 1 0 3
    - Possible causes: trying impossible solutions before reaching the correct one
    - Fix #1: added a condition for stack_a.size ≤ 3 after try_swap
        - Result:
            - fixed 2 4 1 0 3
            - fucked up 2 3 1 0 4
        - Thoughts: seems to be a an error in double rotation
    - Fix #2: change sense of rotation if equal in both directions
        
        ```c
        if ((ft_abs(b_info->revpos) == b_info->pos && a_info->dist0 < 0))
          b_info->dist0 = b_info->revpos;
        if ((ft_abs(a_info->revpos) == a_info->pos && b_info->dist0 < 0))
          a_info->dist0 = a_info->revpos;
        ```
        
        - Result:
            - fixed 2 3 1 0 4
            - fucked up 2 1 0 4 3
        - Thoughts: invert_4 doesn’t seem to be called
    - Fix #3: added sort in main
        - oops
- Issue #1:
    - Description: always seg faulted when min_moves !< 8. In other words, when the recursion was not stopped by a successful call to try_solution→check_if_min_moves.
    - Possible causes: the “false” branch of the recursion was not properly handling freeing and allocating memory
    - Fix #1: Adding discard_moves to try_solution
        - Result :
            - cleaned up when successful
            - more segfaults when unsuccessful
        - thoughts: discarding the solution should only happen when check_if_min_moves returns true, otherwise it’s up to the calling function to manage its memory freeing/allocation
    - Fix #2: Call discard_moves at the end of each solution, and new_deque at the beginning of every new one.
        - Result:
            - Malloc error: object being freed was not allocated left and right
            - List of curr_moves was never properly freed
        - Thoughts: I realized I was doing undo_n_moves AND calling discard_moves, which undid the moves.
    - Fix #3: don’t call discard_moves for try_sort_small
        - Result:
            - It’s fixed. it’s all fixed
            - except...  small leaks of 128 bytes on certain sorts
    - Fix #4: added a call to discard_moves() after try_swap
        - Result:
            - Voilà