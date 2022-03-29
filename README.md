# OpSys
OpSys is a multi-tasking operating system designed for use in embedded systems.

This operating system allows the user to define tasks, control the execution of tasks via blocking semaphores, queues, mailboxes, and bit flags.

The operating system is almost entirely written in C++, and maintains a common programmer interface between different operating systems. Certain exceptions to this include the parts of the operating system that swaps stack pointers, which is always written in assembler and those classes that are specific to one operating system, such as interrupt counter timers.

OpSys implements a collection of classes that allow multi-tasking programs to be implemented. These classes will execute code at pre-specified times, pass data between tasks or threads of execution, and reschedule tasks/threads of execution as needed. Each class is documented in following sections.


