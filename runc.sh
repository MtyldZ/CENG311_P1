#!/bin/bash 
gcc main.c -o main_compiled -lm
./main_compiled
javac Homework.java && java -Xmx8g Homework
