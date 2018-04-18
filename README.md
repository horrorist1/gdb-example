GDB Tutorial

To build:
g++ -std=c++14 -g -Og main.cpp -lpthread -o gdb-ex

To run under gdb:
$ gdb --args ./gdb-ex 5

To detect threading problems run under valgrind helgrind:
$ valgrind --tool=helgrind ./gdb-ex 5

To detect memory problems run under valgrind memcheck:
$ valgrind --tool=memcheck ./gdb-ex 5
