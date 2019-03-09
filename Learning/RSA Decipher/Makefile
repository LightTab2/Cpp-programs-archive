objects = Main.o

RSA Decipher.exe: $(objects)
	g++ -O3 -fwhole-program -D DNDEBUG -o "RSA Decipher.exe" $(objects) 

Main.o: RSA\ Decipher.cpp 
	g++ -c -O3 "RSA Decipher.cpp" -w -o Main.o

.PHONY : clean
clean :
	-del "RSA Decipher.exe" $(objects)
