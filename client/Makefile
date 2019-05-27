comp = c++
flags = -std=c++17
objs = Connection.o ClientSocket.o ../shared/md5.o -lcrypto

client: main.cpp $(objs)
	$(comp) $(flags) -o client main.cpp $(objs)
Connection.o: ../shared/Connection.cpp ../shared/Connection.hpp
	$(comp) $(flags) -c ../shared/Connection.cpp
ClientSocket.o: ClientSocket.cpp ClientSocket.hpp
	$(comp) $(flags) -c ClientSocket.cpp