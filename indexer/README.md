# CS50 Spring 2022, Indexer 
## Dylan Lawler

Indexer is a program that takes a Crawler produced Directory and a writable file. The program iterates over all over the crawler files, makes webpages from their information, then iterates over all of the words of each webpage, inserting them into an inverted index along with the file number and number of occurrences. This index is then written into the given file. 

### Compilation 
To build both indexer and indextest, run `make` or `make all`

To clean up, run `make clean`.

To test, run `make test` (testing results output to testing.out)

### Assumptions 
- The hashtable used to make the index is a static size of 200 slots
- See common README.md for assumptions made about filename string sizes 
- Last test in testing.sh includes an indextest test where the program takes an old file and a new file, loads an index from the old file and rewrites it to the new file to ensure index_load and index_save API's work. They are compared by sorting them and then uses the diff command.