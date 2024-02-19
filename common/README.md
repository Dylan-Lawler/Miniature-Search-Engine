# CS50 Spring 2022, Common Directory 
## Dylan Lawler

Common Directory holds a function that checks the validity of a directory and another function that saves webpage info to a given file in that directory. See pagedir.h. 

### Compilation 
To build, run `make`.

To clean up, run `make clean`.

### Assumptions 
- The user is aware is_valid function inserts a .crawler file into their checked directory 
- A unique file ID is never longer than 8 digits (string size 10 including '/' and '/0')