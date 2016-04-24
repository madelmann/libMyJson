* Introduction:
  =============

JSON (JavaScript Object Notation) is a lightweight data-interchange format. 
It can represent integer, real number, string, an ordered sequence of 
value, and a collection of name/value pairs.

MyJson is a simple API to manipulate JSON value, handle serialization 
and unserialization to string.

It can also preserve existing comment in unserialization/serialization steps,
making it a convenient format to store user input files.

Unserialization parsing is user friendly and provides precise error reports.


* Building/Testing:
  =================

MyJson uses the CMake build system as well as it provides a Visual Studio
project and solution file.


CMake:
------

To build on CMake on would use the following command:

cmake [-G <your desired generator>] -DBUILD=Debug|Release <path-to-source>

i.e.
cmake -G "Eclipse CDT4 - Unix Makefiles" -DBUILD=Debug ../src/


Visual Studio:
--------------

Open the solution file that comes with MyJson and hit "Build".

