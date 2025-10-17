
i) Tests directory contains unit tests for ArtifactEnhancement-SWE services.

ii) AVLTests directory contains unit tests for the AVL Tree and Binary Search Tree classes.


Capstone Artifact Enhancements

Changelog:

9/18/2025 19:46 -- Initial commit of artifact enhancement files for the software engineering artifact.

9/20/2025 21:21 -- Second commit with nearly completed project files and unit tests. Added a .gitignore and cleaned the repo of excess large files.
                    half implemented a main function and input handler class but not sure if I will complete it as it only functions with the
                    ContactService class at this point. Input validation was removed from the original Java model classes when converting to C++ and
                    moved into the main method and input handler classes.

9/21/2025 16:16 -- Last commit before submission. Adjusted code commenting and structure issues as well as added in the narrative .docx to the repository.

9/23/2025 19:45 -- Initial commit for DSA artifact enhancement which includes converting a binary search tree into an AVL tree. Also added original artifacts.

10/12/2025 17:54 -- Add the original DB artifact into the repo as well as the finished initial enhancments to the artifact, also committed changes to the 
SWE artifact which include the following: 

-Reordered variables of ContactManager function

-Fixed switch case logic

-Added check for attempting to print empty list of contacts

-Refactored the menu into the DisplayMenu function

-Replaced basic cin >> input calls so that they can take in whitespace and clear the input buffer

-Added constructor for Contact class to take accept an ID that isn't auto genned

-Refactored each switch case to remove as much redundant code as possible, removed about 300-350 lines.

-Ran cppcheck and fixed all issues that can be fixed at the moment.

-Fully implemented ContactService in menu loop
