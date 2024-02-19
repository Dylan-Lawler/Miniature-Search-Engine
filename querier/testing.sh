# testing file for query program
#
# query results are printed to testing.out 
# 
# Dylan Lawler, CS50, Spring 2022
#

## TEST 0: no args
echo "Testing with no arguments"
./querier
echo -e "\n"

## TEST 1: Not a crawler produced directory
mkdir fakedir
echo "Testing a directory not produced by Crawler"
./querier fakedir errorfl
echo -e "\n"
rm -rf fakedir

## TEST 2: Unreadable file
tse_dir=/thayerfs/courses/22spring/cosc050/cs50tse/tse-output
touch fakefile
chmod -rx fakefile
echo "Testing an unreadable file"
./querier $tse_dir/letters-depth-6/ fakefile
echo -e "\n"
rm -rf fakefile

#TEST 3 Invalid queries in letters index depth 6
echo "Testing a series of bad queries (operand first and last, in sequence, non letter searches)"
echo -e "or this\nthis and\nthis and or that\n213\nbad-query\n" > badqueries
tse_dir=/thayerfs/courses/22spring/cosc050/cs50tse/tse-output
./querier $tse_dir/letters-depth-6/ $tse_dir/letters-index-6 < badqueries
echo -e "\n"
rm -rf badqueries

#TEST 4 Fuzzquery 10 valid queries
echo "Testing 10 fuzzqueries at letters index of depth six"
./fuzzquery $tse_dir/letters-index-6  10 0 | ./querier $tse_dir/letters-depth-6/ $tse_dir/letters-index-6

#TEST 5 Fuzzquery 10 valid queries
echo "Testing 10 fuzzqueries at letters index of depth six"
./fuzzquery $tse_dir/wikipedia-index-1  10 0 | ./querier $tse_dir/wikipedia-depth-1  $tse_dir/wikipedia-index-1 
