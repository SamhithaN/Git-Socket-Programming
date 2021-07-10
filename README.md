# Git-Socket-Programming

This project aims to automatically clone a remote repository to a local branch in the user's system. The user will require to enter the details of the main branch, local branch and url of the remote repository. 
It includes concepts of socket programming in java and C++, process creation in Windows OS, git and a little bit of frontend(html).

Working:
Client Side - 
The user is greeted with a frontend where the details of main branch, local branch and url of remote repository is entered.
A java servlet running on an apache tomcat server hosts the html page and produces a message once the user submits the required details.
The java program sends the information to the server program with the help of a socket. Socket programming concepts are incorporated here.

Server Side -
A C++ program receives the user data from the open socket sent by the java program.
The program then creates a new process. Here, the command prompt application is created and a batch file is run.
The batch file contains the git command to clone a repository. The git commands 
I am also learning how to use teamcity for the build configure of my project.
