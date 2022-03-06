1. [Project journal](#journalhead)
    1. [Start solve5](#journal0)
    2. [Refactor](#journal1)
    3. [Haven’t actually finished sort_5. Hihi](#journal2)
    4. [Start sort_big](#journal3)
    5. [Vectors working, moves list working, onto t_iterator, and bigger things](#journal4)
    6. [moves_list, t_insert_info, and more...](#journal5)
    7. [Debug Galore](#journal6)
	8. [Tracking down what’s left of the bugs](#journal7)
	9. [Starting sort_big](#journal8)
	10. [La nuit a porté conseil](#journal9)


<a name="journalhead"></a>
# Project Journal

More of a collection of ramblings than anything else, but it's a copy of my Notion page where I dump my thoughts

<a name="journal0"></a>
## Start solve5 February 17, 2022

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

<a name="journal1"></a>
### Refactor

- Allocate 3x the memory needed for both stacks, this way rotates and pushes will only necessitate a change of index, no reindexation. It is not memory efficiant (requires 300% of the memory), but it will max out at 8000 bytes too many for a stack of 500 (500 entries x 2 stacks x 2 times too big x 4 bytes per int = 8000), and it will save a trmendous amount of reindexation.
- Then move on to circular doubly linked list, which will require quite a large amount of refactorization, plus writing some core functions in the libft (dblst_addback(), dblst_addfront(), dblst_new(), dblst_clear(), dblst_delone(),

---

<a name="journal2"></a>
## Haven’t actually finished sort_5. Hihi February 22, 2022

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

<a name="journal3"></a>
## Start sort_big February 23, 2022

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

<a name="journal4"></a>
## Vectors working, moves list working, onto t_iterator, and bigger things February 26, 2022

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

<a name="journal5"></a>
## moves_list, t_insert_info, and more... March 2, 2022

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

<a name="journal6"></a>
## Debug Galore March 3, 2022 

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

---

<a name="journal7"></a>
## Tracking down what’s left of the bugs March 4, 2022

---

So I was rightfully ecstatic yesterday when I realized that my insert_b algorithm alone seemed to be good enough to reach the threshold for a perfect score, but it’s still not time to pop the champagne, and even further is the time to close the browser tabs. I’ve got work to do :)

<aside>
💡 Debug technique
  1. Find a case where it fails
    a. Try to pinpoint the failing points in a couple of examples to see if you can notice the issue right away with the data available
    b. If you can notice a pattern, good, but either way, try to find an isolated case, and reproduce the situation.
e.g. push_swap gave error on min_cost for "10 5 1 9 6 4 3 7 2 8”, so I reproduce the state of the stack at that time (”5 4 0 8 9 1 2 3 6 7” + 3 x pb), and I now have the isolated solution to study

</aside>

Bug #1

```
| [A] | [B] |
+-----+-----+
| 8   | 0   |
| 9   | 4   |
| 1   | 5   |
| 2   |     |
| 3   |     |
| 6   |     |
| 7   |     |
+-----+-----+

```

becomes

```
| [A] | [B] |
+-----+-----+
| 4   | 5   |
| 7   | 0   |
| 8   |     |
| 9   |     |
| 1   |     |
| 2   |     |
| 3   |     |
| 6   |     |
+-----+-----+
```

Turns out I just had ft_max instead of ft_min in calc_delta_inserts...

- fixed by recoding calc_delta_inserts, and testing it independently. Now I know it works
- I’m still unsure of what to do when delta_inserts and val_inserts are equal... Could try both.

Bug #2

```
| [A] | [B] |
+-----+-----+
| 1   | 5   |
| 2   | 7   |
| 3   | 6   |
| 5   |     |
| 8   |     |
| 9   |     |
| 0   |     |
+-----+-----+

```

becomes 

```
| [A] | [B] |
+-----+-----+
| 7   | 6   |
| 9   | 5   |
| 0   |     |
| 1   |     |
| 2   |     |
| 3   |     |
| 4   |     |
| 8   |     |
+-----+-----+
```

Unsure as to why, insert_info seems to be fine at the moment of insertion, so probably an insert_b error

Error!
68 9 76 89 58 30 75 86 64 10 98 28 29 72 88 27 13 7 4 21 11 92 35 50 24 100 40 31 25 71 87 69 43 2 91 23 84 12 39 53 38 81 73 19 8 74 49 3 32 94 6 42 57 96 37 45 52 83 26 34 56 55 14 78 15 16 65 97 36 93 17 48 54 1 41 62 77 44 80 67 47 70 82 90 59 60 66 46 79 5 63 51 33 85 22 20 18 99 61 95
AVG: 574
MAX:  649

The fix was............ simple.

```
if (a_info->revpos_best >= 0)
		do_rrb(cont, moves_buff);
else if (b_info->revpos_best >= 0)
		do_rra(cont, moves_buff);
```

   

      ⇒

```
if (a_info->revpos_best > 0)
		do_rrb(cont, moves_buff);
else if (b_info->revpos_best > 0)
		do_rra(cont, moves_buff);
```

 

<aside>
💡 Could maybe have some sort of quarters when I push my values into stack_b *while* sorting by index or value. 

1. Assign stay/leave by index/value
2. Check if sa/ss is beneficial
3. Push ***only the biggest half*** the values (constantly updated and stored to a control variable, but maybe indeed recalculated every time a swap happens) first, then the other half afterwards, so that both stacks would have high values at bottom and low values on top, since the values in a will already be sorted. Sounds counter-intuitive, but maximizes the amount of double-rotates. Might give it a try.

</aside>

Everything works 🙂 

Now running benchmarks in the background while I start coding the algo to insert_b. This way I can try and optimize the insert_b as I’m working on insert_a

Doing my calculate_delta_costs does absolutely nothing :(   5163 vs 5166 AVG

<aside>
💡 Idea for greater_than sorting mode!

Check recursively for which greater than value to include or not (e.g. 
1 76 92 11 53 40 85 30 4 83 57 62 12 81 78 20 98 89 91 27 87 19 3 52 22 72 97 96 28 95 10 25 26 13

</aside>

---

<a name="journal8"></a>
## Starting sort_big March 5, 2022

---

Tasks for the day:

1. Implement sort_small so that it tries all the possibilities every time
    - [ ]  Modify tester to show average.
    - [ ]  Check current average
    - [ ]  Modify sort_small to try all values instead of stopping at good enough
    - [ ]  Track bug: sort_small hanging infinitely for large numbers
    
    <aside>
    💡 What if I splitted the insert process in two?
    
    </aside>
    
    1. Find stack_head and flag values in stack_a with a bool `is_staying` control variable
    2. Define the middle of the first half of values as `size - (size_of_half - size_of_half)` aka `3 * size / 4`
        1. This way, `pos_0` is at the middle of the vals that will be pushed, which allows stack to rotate in both directions
    3. Split the `!is_staying` values in two so that you have the same amount on each side of pos_0, and flag them with a bool `is_first_half` control variable
    4. Sort that first half using a reverse insert_b (spoilers: it will probably be called insert_a)
    
    Nevermind, that’s a little dumb. I don’t think I gain anything since I will have to send all to b anyways. what I could do though is send the *biggest* values first, but then I would need to 
    
    - [I] Maybe Alex was right and I could indeed start by allowing only the next biggest to be selected, then a range of two, then three, etc.
        - This way I would have a nice way of controlling when to stop searching :
            
            ```c
            if (range * range > size)
            	return ;
            ```
            
        - Then I could also add in my recursive fct
            
            ```c
            if (nb_bigger_values < curr_max)
            	return ;
            ```
            
    - [N] Can easily (and should) be tested in isolation before implementing. Could work with a known stack, and manually compare.
        - Should write a print_state() helper fct
    
    <aside>
    💡 Need to store previous optimal heads
    
    </aside>
    
    - I need to avoid trying the same solution more than once, so I should avoid the same next_biggest than the previous iteration
    - 
    
    <aside>
    💡 Motherfuckin duh, but stack_heads are pacman-like as well....
    
    Meanin that a stack head like 5 8 9 6 7 4 3 0 1 2 CAN go back to 0 after having flagged next_biggest of 9
                                                       x-x-x-———-x x x
    
    </aside>
    
    So I need 
    
    1. A pos_of_val[] array
    2. a next_biggest, with a has_looped bool ctrl var
        
        ```c
        if (curr_val > next_biggest) || (!has_looped && curr_val > head)
        	is_staying[curr_pos] = true;
        ```
        
    
    First optimization that is quite simple to put in is 
    
    - calculate nb_sorted for each head.
    
    Everything else could and should be considered too complicated to attempt for the returned benefit
    
    - e.g. all the bullshit I’m breaking my head over about moving the next_biggest
    - BUT, having a max_delta seems smart, to prevent from excluding too many values.
        - Should put it very high at first, because I might be surprised, and then slowly lower it and benchmark
    
    Could check as I’m inserting a into b whether an insert_value is nearby
    

---

<a name="journal9"></a>
## La nuit a porté conseil March 6, 2022

---

Two big ideas:

1. Optimizing 500:
The “insertion sort” I’m current using seems to be much slower for 500 values, so I might need a completely different algorithms for large values. 
Since I don’t need to sort it in stack_b right away but only need to increase the order. That’s why I think I might want to try radix sort:
    1. Starting with the leftmost bit that allows you to gather more than half of the date (8th bit, in case of 500 values)
    
2. “Sorting by index”: is really just sorting by greater_than with a range of 1... So if VBrazhnik incorporated it, it’s because in some cases it’s better. This being said, I don’t believe that `1` is ever the optimal range to get the biggest value. For now I think should be tried
    1. No range (so directly next biggest)
        1. Excludes nothing, and might result in the best nb_staying, but HIGHLY unlikely, I believe. 
        2. Cases like `1 97 3 5 99 8 ...` would fuck that up, b/c `97` clearly needs to go
        3. Therefore I would need some sort of intermediary range ? NO!
            1. I think that before diving into optimizing the range, I’m much better off spending my time and energy in moving the heads, but  I don’t believe even that would be worth the time. Try to forget about it. 
            
            <aside>
            💡 it’s easy to get stuck on your first idea, but it’s important to recognize when it’s obsolete
                If you were looking for a wake up call: ring ring.
            
            </aside>
            
    2. range = sqrt(size) 
        1. For the few tests that I’ve done so far manually (it’s a pain in the ass, would love to find a better tool to draw, a simple drawing pad would be nice, although I truly would love having a drawing pad, it might help me become more comfortable with drawing, which I’ve always wanted for myself)
3. a
    
    
    ### Preliminary satisfying Results
    
    Using a bitwise comparison to push the biggest half first:
    
    500 values:
    
    Nb tests done: 100
    Average nb of moves: 4846
    Worst nb of moves: 5243
    Nb of moves above 5500 : 0
    
    Nb tests done: 1000
    Average nb of moves: 4870
    Worst nb of moves: 5275
    Nb of moves above 5500 : 0
    
    Nb tests done: 1000
    Average nb of moves: 4867
    Worst nb of moves: 5296
    Nb of moves above 5500 : 0
    
    - Things are looking good, to say the least.
    
    Next optimizations for 500:
    
    1. USE A MODDED insert_a to push the values that I want to stack_b, but not while sorting them
        1. Basically all I need to check is
            
            ```c
            if (size - furthest_pos_in_div_x) < (closest_pos_in_div_x)
            	do_rra();
            ```
            
        2. The vase amount of `ra/rra` that I will have to do can and should be joined to `rr/rrr` to pre-sort the values as much as possible.
        **Note:** here the next_insert_val will be defined as next_smallest
            
            <aside>
            💡 I should have a sorted stack control variable of values currently in b to lighten the load of calculating next_biggest/next_smallest, b/c it’s wildly inefficient rn
            This control stack should probably be a linked list, b/c there will be only exclusively random insertions
            
            </aside>
            
        
        ```c
        //the first condition makes it inserted, the second incresases the proximity to its corresponding val
        if (dist0_b - dist0_a <= 0) || (dist0_b - dist0_a < revpos_b)
        	while (dist0_b)
        		do_rr
        	else while (dist0_a)
        		do_ra
        
        ```
        
    2.  Play with the number of divisions I want. 
        1. I’m pretty sure that I need to send the biggest ones first, and have no more than ~4 divisions, but we’ll see ! 
        2. Chances are that I might need as many divisions as there are bits used in size (e.g. 8 divisions for 500, 6 divisions for 100)