# CS50 Spring 2022, Crawler 
## Dylan Lawler

Crawler is a program that takes a URL, directory, and depth and saves all URLs from the given seed URL into unique files in the given directory until the given depth is reached. See DESIGN and IMPLEMENTATION specs for specific details. 

### Compilation 
To build, run `make`.

To clean up, run `make clean`.

To test, rn `make test` (testing results output to testing.out)

### Assumptions 
- The hashtable used to store checked URL's is a static size of 100 slots
- See common README.md for assumptions made about is_valid and page_save functions referenced in crawler