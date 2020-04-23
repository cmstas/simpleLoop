CC = g++
CFlAGS = -g -std=c++17 -I$$ROOTSYS/include -lpthread
LIB = `root-config --libs `
INCLUDE = -I./Include

Analysis: main.o Analysis.o makeHists.o ElectronSelection.o MuonSelection.o IsolationTools.o
	$(CC) $(CFLAGS) $(LIB) $(INCLUDE) -o Task.exe ./Obj/*.o

main.o: ./Control/main.C ./Include/State.h
	$(CC) $(CFlAGS) $(LIB) $(INCLUDE) -o ./Obj/main.o -c ./Control/main.C 

Analysis.o: ./Include/Analysis.h ./Src/Analysis.C
	$(CC) $(CFlAGS) $(LIB) $(INCLUDE) -o ./Obj/Analysis.o -c ./Src/Analysis.C

makeHists.o: ./Include/makeHists.h ./Src/makeHists.C
	$(CC) $(CFlAGS) $(LIB) $(INCLUDE) -o ./Obj/makeHists.o -c ./Src/makeHists.C

ElectronSelection.o: ./Include/Analysis.h ./Src/ElectronSelection.C
	$(CC) $(CFlAGS) $(LIB) $(INCLUDE) -o ./Obj/ElectronSelection.o -c ./Src/ElectronSelection.C

MuonSelection.o: ./Include/Analysis.h ./Src/MuonSelection.C
	$(CC) $(CFlAGS) $(LIB) $(INCLUDE) -o ./Obj/MuonSelection.o -c ./Src/MuonSelection.C

IsolationTools.o: ./Include/Analysis.h ./Src/IsolationTools.C
	$(CC) $(CFlAGS) $(LIB) $(INCLUDE) -o ./Obj/IsolationTools.o -c ./Src/IsolationTools.C



.PHONY : clean
clean: 
	rm Task.exe ./Obj/*
