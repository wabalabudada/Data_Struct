@echo off
path = %path%;.\;
g++ main.cpp -o main
main.exe test.in
