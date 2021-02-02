/*
=========A VisiLibity Example Program=========
This program provides a text interface which will

(1) read an environment and guard locations from files given as
command line arguments,

(2) check the geometric validity of these inputs (edges of the
environment do not cross each other, guards are contained in the
environment, etc.),

(3) display environment and guards' data and statistics, and

(4) compute and display the shortest path between two guards
    chosen by the user.

The environment representation and the guard locations can be read
from any files in the (human-readable) format demonstrated in
example.environment and example.guards.

Instructions: use the accompanying makefile to compile, then from
command line run
./shortest_main [environment file] [guards file]
,e.g., using the example files included with your VisiLibity download,
./shortest_main example.environment example.guards
*/

#include "visilibity.hpp"  //VisiLibity header file
#include <cmath>         //Puts math functions in std namespace
#include <cstdlib>       //Gives rand, srand, exit
#include <ctime>         //Gives Unix time
#include <fstream>       //File I/O
#include <iostream>      //std I/O
#include <cstring>       //Gives C-string manipulation
#include <string>        //Gives string class
#include <sstream>       //Gives string streams
#include <vector>        //std vectors
//#define NDEBUG           //Turns off assert.
#include <cassert>


//ASCII escape sequences for colored terminal text.
std::string alert("\a");       //Beep
std::string normal("\x1b[0m"); //Designated fg color default bg color
std::string red("\x1b[31m");         
std::string red_blink("\x1b[5;31m");
std::string black("\E[30;47m");
std::string green("\E[32m");
std::string yellow("\E[33;40m");
std::string blue("\E[34;47m");
std::string magenta("\x1b[35m");
std::string cyan("\E[36m");
std::string white_bold("\E[1;37;40m");
std::string clear_display("\E[2J");
  

//=========================Main=========================//
int main(int argc, char *argv[])
{
  assert(argc == 4);

  VisiLibity::UnitTest::set_output_precision();
  VisiLibity::UnitTest::seed_random();

  //Set geometric robustness constant
  //:WARNING: 
  //may need to modify epsilon for Environments with greatly varying
  //scale of features
  double epsilon = 0.000000001;
  std::cout << green << "The robustness constant epsilon is set to "
	    << epsilon << normal << std::endl;


  /*----------Load Geometry from Files----------*/


  //Load geometric environment model from file
  std::cout << "Loading test environment file ";
  //Print environment filename to screen
  std::cout << argv[1] << " . . . ";
  //Construct Environment object from file
  VisiLibity::Environment test_environment(argv[1]);
  std::cout << "OK" << std::endl;

  //Load guard positions from file
  std::cout << "Loading test guards file ";
  //Print guards filename to screen
  std::cout << argv[2] << " . . . ";
  //Construct Guards object from file
  VisiLibity::Guards test_guards(argv[2]);
  std::cout << "OK" << std::endl;

  //Load the expected shortest path coordinates from file
  std::cout << "Loading expected results file ";
  //Print the expected shortest path coordinates filename to screen
  std::cout << argv[3] << " . . . ";
  //Construct the Polyline of the expected shortest path from the file
  VisiLibity::Polyline expected_shortest_path(argv[3]);
  std::cout << "OK" << std::endl;

  /*----------Check Validity of Geometry----------*/

  assert(VisiLibity::ShortestPathTest::validate(test_environment, epsilon, test_guards));
	 
  //Compute and display visibility polygon
  VisiLibity::Polyline actual_shortest_path = test_environment.shortest_path(test_guards[0], test_guards[1], epsilon);
  std::cout << "The (actual) shortest path is" << std::endl
	    << magenta << actual_shortest_path << normal
	    << std::endl;
  std::cout << "The (expected) shortest path is" << std::endl
	    << magenta << expected_shortest_path << normal
	    << std::endl;

  if (actual_shortest_path == expected_shortest_path) {
    std::cout << "Passed" << std::endl;
    return 0;
  } else {
    std::cout << "Failed" << std::endl;
    return 1;
  }
}
