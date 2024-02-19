# testing file for crawler program
#
# new directory is made for every test
# 
# Dylan Lawler, CS50, Spring 2022
#

mkdir dirtesterr
url="http://cs50tse.cs.dartmouth.edu/tse/letters/index.html"


## TEST 0: no args
echo "Testing with no arguments"
./crawler
echo -e "\n"

## TEST 1: too big of depth size
echo "Testing out of range maxDepth"
./crawler ${url} dirtesterr 20
echo -e "\n"

## TEST 2: wrong order of args
echo "Testing with incorrect order of arguments (depth seed pagedir)"
./crawler 0 ${url} dirtesterr
echo -e "\n"

## TEST 3: correct url, wrong order of pagedir and depth
echo "Testing with incorrect order of arguments (seed depth pagedir)"
./crawler ${url} 0 dirtesterr
echo -e "\n"

## TEST 4: fake url
echo "Testing a fake URL"
./crawler fake.com dirtesterr 0
echo -e "\n"

## TEST 5 external url
echo "Testing an external URL"
./crawler http://cs5049tse.cs.dartmouth.edu/tse/toscrape/index.html dirtesterr 0
echo -e "\n"

url="http://cs50tse.cs.dartmouth.edu/tse/letters/index.html"

# TEST 6: valid letters url at depth zero
mkdir dirtest6
echo "Testing valid ${url} at depth 0"
./crawler ${url} dirtest6 0
echo -e "\n"

# TEST 7: valid letters url at depth one
mkdir dirtest7
echo "Testing valid ${url} at depth 1"
./crawler ${url} dirtest7 1
echo -e "\n"

# TEST 8: valid letters url at depth two
mkdir dirtest8
echo "Testing valid ${url} at depth 2"
./crawler ${url} dirtest8 2
echo -e "\n"

# TEST 9: valid letters url at depth three
mkdir dirtest9
echo "Testing valid ${url} at depth 3"
./crawler ${url} dirtest9 3
echo -e "\n"

# TEST 10: valid letters url at depth four
mkdir dirtest10
echo "Testing valid ${url} at depth 4"
./crawler ${url} dirtest10 4
echo -e "\n"

# TEST 11: valid letters url at depth five
mkdir dirtest11
echo "Testing valid ${url} at depth 5"
./crawler ${url} dirtest11 5
echo -e "\n"

url="http://cs50tse.cs.dartmouth.edu/tse/letters/B.html"

# TEST 12: valid letters B url at depth zero
mkdir dirtest12
echo "Testing valid ${url} at depth 0"
./crawler ${url} dirtest12 0
echo -e "\n"

# TEST 13: valid letters B url at depth one
mkdir dirtest13
echo "Testing valid ${url} at depth 1"
./crawler ${url} dirtest13 1
echo -e "\n"

# TEST 14: valid letters B url at depth two
mkdir dirtest14
echo "Testing valid ${url} at depth 2"
./crawler ${url} dirtest14 2
echo -e "\n"

# TEST 15: valid letters B url at depth three
mkdir dirtest15
echo "Testing valid ${url} at depth 3"
./crawler ${url} dirtest15 3
echo -e "\n"

# TEST 16: valid letters B url at depth four
mkdir dirtest16
echo "Testing valid ${url} at depth 4"
./crawler ${url} dirtest16 4
echo -e "\n"

# TEST 17: valid letters B url at depth five
mkdir dirtest17
echo "Testing valid ${url} at depth 5"
./crawler ${url} dirtest17 5
echo -e "\n"


url="http://cs50tse.cs.dartmouth.edu/tse/wikipedia/Elementary_function_arithmetic.html#Related_systems"

# TEST 18: valid wikipedia url at depth 0
mkdir dirtest18
echo "Testing valid ${url} at depth 0"
./crawler ${url} dirtest18 0
echo -e "\n"

# TEST 19: valid wikipedia url at depth 1
mkdir dirtest19
echo "Testing valid ${url} at depth 1"
./crawler ${url} dirtest19 1
echo -e "\n"





