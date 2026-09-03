*This activity has been created as part of the 42 curriculum by klafi*

# Description
This exercise is a simulation for the Dining Philosophers problem of syncronization. Those are the rules of the simulation:
- One or more coders sit in a circular inclusive co-working hub. In the center, there is a shared Quantum Compiler.
- The coders alternatively compile, debug, or refactor. While compiling, they are not debugging nor refactoring; while debugging, they are not compiling nor refactoring; and, of course, while refactoring, they are not compiling nor debugging.
- There are USB dongles on the table. There are as many dongles as coders.
- Compiling quantum code requires two dongles plugged in simultaneously, one in each hand: a coder takes their left and right dongles to compile.
- When a coder finishes compiling, they put both dongles back on the table and start debugging. Once debugging is done, they start refactoring. The simulation stops when a coder burns out due to lack of compiling.
- Every coder needs to compile regularly and should never burn out.
- Coders do not communicate with each other.
- Coders do not know if another coder is about to burn out.
- Needless to say, coders should avoid burnout!

With the use of **Pthreads**, I assigned each a coder a thread of execution, where each coder contests to acquire dongles which were implemented as *mutexs*. 

# Blocking cases handled
## Deadlock prevention and Coffman’s conditions
The Coffman conditions are the four system properties that—when they all hold simultaneously—make a deadlock possible. They do not guarantee that a deadlock will occur, but they identify the structural prerequisites.

1. Mutual exclusion
At least one resource involved in each request is non-shareable; it can be held by only one task at a time.
2. Hold-and-wait
Tasks already holding one or more resources may request additional resources and wait while still holding their current allocations.
3. No pre-emption
Resources cannot be forcibly removed from a task; release is voluntary.
4. Circular wait
There exists a closed chain of k ≥ 2 tasks {T₁, T₂, … , Tₖ} such that each Tᵢ holds a resource needed by Tᵢ₊₁ (with Tₖ needing a resource held by T₁).

To make the possibility of deadlocks zero, we have to prevent on of the aforementioned properties from holding true.
A circular wait may only happen if all coders tried to hold their right(or left) dongles first then the left one(or right one). In my program, an asymmetric approach was followed; that is, and odd coder picks up first his left dongle and then his right dongle, whereas an even coder picks up his right dongle and then his left dongle. That way, a circular wait could never happen.
## Starvation prevention
A priority queue (heap) was used to determine which coder needs to compile the most, using the fifo scheduling algorithm, the coder the tries to acquire the dongle first gets it. Whereas in edf scheduling, the coder closest to burnout takes the dongle.
## Cooldown handling
Each dongle has a cooldown timestamp that gets updated whenever a coder finishes compiling and puts down the dongle. When any coder tries to acquire a dongle, it checks on the dongle's cooldown timestamp for whether it has elapsed yet or not.
## precise burnout detection
A monitor thread executes in parallel with all coder threads whose main purpose is to check for burnout deadlines and number of compiles done yet and stops execution if one of the coders burned out or when all coders reach the number of compiles needed. Since the monitor thread runs in parallel with the other threads; the delay of burnout detection is usually less then 1 ms.
## Log serialization
Each thread can print to the terminal the state of its corresponding coder's state via a universal function called print_state. In order to prevent multiple threads print on the terminal at the same time mixing up the logs, print_state locks a mutex designated to protect the output stream from simultaneous accesses.

# Thread synchronization mechanisms
Each of the dongles, priority queues, and the output stream was protected via `pthread_mutex_t`'s to prevent race conditions. Of course, each coder run via `pthread_create` such that each coder was sent to latter function as a `pthread_t` variable. The monitor checks on the burnout deadlines for each coder via a pointer array that includes pointers for all `t_coder` variables.

# Instructions
You can compile and run the program using a Makefile with those rules:
- all (default): compiles all source files(stored in src/ directory) and creates an executable named "codexion".
- clean: deletes all object files(stored in objects directory).
- fclean: calls *clean* rule and deletes the executable.
- re: deletes all object files and recompiles the program.
You can use make like:
`make 'rule'`
For the executable, it receives multiple arguments (listed in order):
-  number_of_coders: The number of coders and also the number of dongles.
- time_to_burnout (in milliseconds): If a coder did not start compiling within time_to_burnout milliseconds since the beginning of their last compile or the beginning of the simulation, they burn out.
- time_to_compile (in milliseconds): The time it takes for a coder to compile. During
that time, they must hold two dongles.
- time_to_debug (in milliseconds): The time a coder will spend debugging.
- time_to_refactor (in milliseconds): The time a coder will spend refactoring. After
completing the refactoring phase, the coder will immediately attempt to acquire
dongles and start compiling again.
- number_of_compiles_required: If all coders have compiled at least this many
times, the simulation stops. Otherwise, it stops when a coder burns out.
- dongle_cooldown (in milliseconds): After being released, a dongle is unavailableuntil its cooldown has passed.
- scheduler: The arbitration policy used by dongles to decide who gets them when
multiple coders request them.
The value must be exactly one of: fifo or edf.fifo means First In, First Out: the dongle is granted to the coder whose request
arrived first.edf means Earliest Deadline First with deadline = last_compile_start + time_to_burnout.

A run executable would look like this:
```
./codexion 5 3000 200 200 200 10 400 fifo
```
# Resources
- https://youtu.be/FYUi-u7UWgw?si=QYuEJSS5FI5eYavz
- https://youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2&si=1Jhvb6EbexkAmP7j
*AI Usage*: There was no code generated by AI. AI was only used for revision purposes.