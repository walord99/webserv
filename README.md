# A basic HTTP 1.1 webserver #

Based on the requirements of 42 school's project [webserv](https://github.com/walord99/webserv/blob/main/subject/webserver.pdf)

TLDR: Syscalls available to use are limited to a certain set, all I/O needs to be-nonblocking and limited to 1 poll/epoll/select list. Only a certain of features and commands need to be implemented. See document for more detail. 

## linux build

no libraries needed, run make in the directory