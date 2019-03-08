a.out: cstack.o main.o csimplelist.o ccard.o csimplelistcard.o cplayer.o
	g++ cstack.o main.o ccard.o csimplelist.o csimplelistcard.o cplayer.o

main.o: main.cpp cstack.h ccard.h csimplelist.h 
	g++ -c main.cpp

cstack.o: cstack.cpp cstack.h ccard.h csimplelistcard.h
		g++ -c cstack.cpp

ccard.o: ccard.cpp ccard.h cstack.h csimplelist.h
		g++ -c ccard.cpp

csimplelist.o: csimplelist.cpp csimplelist.h
	 g++ -c csimplelist.cpp

csimplelistcard.o: csimplelistcard.cpp csimplelistcard.h
	g++ -c csimplelistcard.cpp

cplayer.o: cplayer.cpp cplayer.h cstack.h ccard.h csimplelistcard.h
	g++ -c cplayer.cpp
