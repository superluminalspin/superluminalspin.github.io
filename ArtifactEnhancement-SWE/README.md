# Artifact Enhancement for Java based model/service program

The purpose of this enhancement was to convert the original program from Java to C++ and it's accompanying unit tests from JUnit to Google Test. This project should be linked to the /Tests repository.

This enhancement includes the following changes from the original artifact:

-Conversion of all Java class files to modular C++ header files.

-Conversions of most unit tests from JUnit to Google Test. Further information on tests can be found in the /Tests repository.

-Addition of a modular input validator class that sanitizes input from the user. In the original artifact, all input validation was handled within the model classes which can lead to numerous isues.

-Addition of a basic console menu both to dynamically test the ContactService class and it's associated input validator functions, and to give the user a visual idea of how the program functions.
