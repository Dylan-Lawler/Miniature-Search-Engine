# testing file for indexers program
#
# new file is made for every test, uses the directories from Crawler's testing.sh
# 
# Dylan Lawler, CS50, Spring 2022
#

touch errorfl
## TEST 0: no args
echo "Testing with no arguments"
./indexer
echo -e "\n"

## TEST 1: Not a crawler produced directory
mkdir fakedir
echo "Testing a directory not produced by Crawler"
./indexer fakedir errorfl
echo -e "\n"

## TEST 2: non writable file
chmod -wx errorfl
echo "Testing with a non writable index file"
./indexer ../crawler/dirtest6 errorfl
echo -e "\n"

## TEST 3: letters depth 0
touch letters-index-0
echo "Testing letters index at depth 0"
./indexer ../crawler/dirtest6 letters-index-0
echo -e "\n"

## TEST 4: letters depth 1
touch letters-index-1
echo "Testing letters index at depth 1"
./indexer ../crawler/dirtest7 letters-index-1
echo -e "\n"

## TEST 5: letters depth 2
touch letters-index-2
echo "Testing letters index at depth 2"
./indexer ../crawler/dirtest8 letters-index-2
echo -e "\n"

## TEST 6: letters depth 3
touch letters-index-3
echo "Testing letters index at depth 3"
./indexer ../crawler/dirtest9 letters-index-3
echo -e "\n"

## TEST 7: letters depth 4
touch letters-index-4
echo "Testing letters index at depth 4"
./indexer ../crawler/dirtest10 letters-index-4
echo -e "\n"

## TEST 8: letters depth 5
touch letters-index-5
echo "Testing letters index at depth 5"
./indexer ../crawler/dirtest11 letters-index-5
echo -e "\n"

## TEST 9: wikipedia depth 
echo "Testing wikipedia index at depth 1"
./indexer ../crawler/dirtest19 wikipedia-Elementary_function_arithmetic-1
echo -e "\n"

## TEST 10: indextest (testing page_load and page_save)
touch page-save-fl
echo "Testing indextest with letters-index-5"
./indextest letters-index-5 page-save-fl
sort letters-index-5 > oldfl
sort page-save-fl > newfl
DIFF=$(diff oldfl newfl) 
    echo "Comparing letters-index-5 and page-save-fl"
    if [ ! -z "$DIFF" ]
    then 
        echo "$DIFF"
        exit 
    else 
        echo "No differences."
    fi
echo -e "\n"
