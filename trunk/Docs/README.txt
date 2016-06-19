Introduction:
=============

JSON (JavaScript Object Notation) is a lightweight data-interchange format. 
It can represent integer, real number, string, an ordered sequence of 
value, and a collection of name/value pairs.

libMyJson is a simple API to manipulate JSON value, handle serialization 
and unserialization to string.

Trivia:
-------

libMyJson is a small (as in lines of code) and leightweight (as in memory
footprint) JSON implementation which has been written and used as a data
interchange interface as part of a commercial project for a leading medical
university in austria.


Building:
=========

libMyJson uses the CMake build system as well as it provides a Visual Studio
project and solution file.


CMake:
------

To build with CMake one would use the following command:

cmake [-G <your desired generator>] -DBUILD=Debug|Release <path-to-source>

i.e.
cmake -G "Eclipse CDT4 - Unix Makefiles" -DBUILD=Debug ../src/


Visual Studio:
--------------

Open the solution file that comes with libMyJson and hit "Build".


Testing:
========

libMyJson comes with a very little testing program, that has been used to compare
its parsing performance with other JSON libraries. Spoiler: if you're looking
for speed consider using json-cpp which is way faster than libMyJson.

