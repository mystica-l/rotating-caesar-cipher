# Project 3 MakeFile
# Ofast flag is used on all compilations to optimize and speed up code
compile:
	make compileQueue
	make compileCipher
	make compileCipherAdvanced
	g++ Project3.cpp Queue.o Cipher.o CipherAdvanced.o -Wall -Ofast -o project3.out
compileQueue:
	g++ Queue.cpp -Ofast -Wall -c
compileCipher:
	g++ Cipher.cpp -Ofast -Wall -c
compileCipherAdvanced:
	g++ CipherAdvanced.cpp -Ofast -Wall -c
run:
	./project3.out
