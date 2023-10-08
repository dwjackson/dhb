#!/bin/sh

TEST_CASES='test_cases.tab'

test() {
	expected="$1"
	actual="$2"
	if [ "$expected" != "$actual" ]
	then
		echo "FAIL; expected $expected, got $actual"
		exit 1
	fi
}

while read test_case
do
	dec=`echo "$test_case" | awk -e '{ print $1 }'`
	hex=`echo "$test_case" | awk -e '{ print $2 }'`
	bin=`echo "$test_case" | awk -e '{ print $3 }'`

	dec2hexresult=`./dhb "$dec" | awk -e '{ print $2 }'`
	test "$hex" "$dec2hexresult" 

	dec2binresult=`./dhb "$dec" | awk -e '{ print $3 }'`
	test "$bin" "$dec2binresult" 

	hex2decresult=`./dhb "$hex" | awk -e '{ print $1 }'`
	test "$dec" "$hex2decresult" 

	bin2decresult=`./dhb "$bin" | awk -e '{ print $1 }'`
	test "$dec" "$bin2decresult" 
done < "$TEST_CASES"
