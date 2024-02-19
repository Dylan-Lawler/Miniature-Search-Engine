# CS50 Spring 2022, Querier 
## Dylan Lawler

Querier is a Program that relies on the Crawler and Indexer programs. It takes a Crawler directory and Indexer file as command line arguments and prompts the user to search for words. It then searches the crawler file to see which, if any, files match the user's query and prints the documents from the Crawler directory in a ranked order based on word frequency. See Design and Implementation for specific details.

### Compilation 
To build both querier and fuzzquery, run `make` or `make all`

To clean up, run `make clean`.

To test, run `make test` (testing results output to testing.out)

### Assumptions 
- The hashtable used to make and index is a static size of 200 slots
- See common README.md for assumptions made about filename string sizes 
- All test inputs for querier are done through redirection or piping
- Querier sustains the assumption that no index file ID number is larger than ten digits long