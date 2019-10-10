CXX = g++
CXXFLAGS = -Wall -g -std=c++11
CXXH = -c
all:client awsout.o serverA.o serverB.o serverC.o

client: client.cpp msg.o
	$(CXX) $(CXXFLAGS) client.cpp msg.o -o client

awsout.o: aws.cpp msg.o
	$(CXX) $(CXXFLAGS) aws.cpp msg.o -o awsout.o

serverA.o: serverA.cpp dbclass.o msg.o udpServer.o
	$(CXX) $(CXXFLAGS) serverA.cpp dbclass.o msg.o udpServer.o -o serverA.o

serverB.o: serverB.cpp dbclass.o msg.o udpServer.o
	$(CXX) $(CXXFLAGS) serverB.cpp dbclass.o msg.o udpServer.o -o serverB.o

serverC.o: serverC.cpp msg.o computeClass.o udpServer.o
	$(CXX) $(CXXFLAGS) serverC.cpp msg.o computeClass.o udpServer.o -o serverC.o 

msg.o: msg.cpp
	$(CXX) $(CXXFLAGS) $(CXXH) msg.cpp -o msg.o

dbclass.o: dbclass.cpp msg.o udpServer.o
	$(CXX) $(CXXFLAGS) $(CXXH) dbclass.cpp msg.o udpServer.o -o dbclass.o

udpServer.o: udpServer.cpp msg.o
	$(CXX) $(CXXFLAGS) $(CXXH) udpServer.cpp msg.o -o udpServer.o

computeClass.o: computeClass.cpp msg.o udpServer.o
	$(CXX) $(CXXFLAGS) $(CXXH) computeClass.cpp msg.o udpServer.o -o computeClass.o

.PHONY: clean
clean:
	@rm -f *.o serverA serverB serverC client awsout


.PHONY: serverA
serverA:
	./serverA.o

.PHONY: serverB
serverB:
	./serverB.o

.PHONY: serverC
serverC:
	./serverC.o

.PHONY: aws
aws:
	./awsout.o