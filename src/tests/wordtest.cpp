/* 
 * File:   wordtest.cpp
 * Author: starling13
 *
 * Created on 26.10.2015, 17:25:43
 */

#include <stdlib.h>
#include <iostream>

/*
 * Simple C++ Test Suite
 */

void test1()
{
	std::cout << "wordtest test 1" << std::endl;
}

void test2()
{
	std::cout << "wordtest test 2" << std::endl;
	std::cout << "%TEST_FAILED% time=0 testname=test2 (wordtest) message=error message sample" << std::endl;
}

int main(int argc, char** argv)
{
	std::cout << "%SUITE_STARTING% wordtest" << std::endl;
	std::cout << "%SUITE_STARTED%" << std::endl;

	std::cout << "%TEST_STARTED% test1 (wordtest)" << std::endl;
	test1();
	std::cout << "%TEST_FINISHED% time=0 test1 (wordtest)" << std::endl;

	std::cout << "%TEST_STARTED% test2 (wordtest)\n" << std::endl;
	test2();
	std::cout << "%TEST_FINISHED% time=0 test2 (wordtest)" << std::endl;

	std::cout << "%SUITE_FINISHED% time=0" << std::endl;

	return (EXIT_SUCCESS);
}

