objects = Main.o

SiteUpdater.exe: $(objects)
	g++ -O3 -fwhole-program -D DNDEBUG -o "SiteUpdater.exe" $(objects) 

Main.o: SiteUpdater.cpp 
	g++ -c -O3 "SiteUpdater.cpp" -w -o Main.o

.PHONY : clean
clean :
	-del "SiteUpdater.exe" $(objects)
