#!/bin/bash

green_format='\033[0;32m'
red_format='\033[0;31m'
reset_format='\033[0m'

sp_tests_dir="sp_tests"

tests=$(for i in `ls ${sp_tests_dir}/*`; do echo `basename $i` | awk -F. '{print $1;}' ; done | sort -u);

total_tests=0
passing_tests=0
failing_tests=0

for i in $tests; do
	./test_shortest_path ${sp_tests_dir}/$i.environment ${sp_tests_dir}/$i.guards ${sp_tests_dir}/$i.result
	if [ $? -ne 0 ]; then
		echo "Test Failure."
		failing_tests=$(( failing_tests + 1 ))
	else
		echo "Test Passed."
		passing_tests=$(( passing_tests + 1 ))
	fi
	total_tests=$(( total_tests + 1 ))
done

echo "Result:"
echo -e "${green_format}Passing Tests: ${passing_tests}"
echo -e "${red_format}Failing Tests: ${failing_tests}"
echo -e "${reset_format}Total   Tests: ${total_tests}"
exit 0
