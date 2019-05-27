comp = c++
flags = -std=c++17
objs = Connection.o ServerSocket.o ../shared/md5.o -lcrypto

server: main.cpp $(objs)
	$(comp) $(flags) -o server main.cpp $(objs)
Connection.o: ../shared/Connection.cpp ../shared/Connection.hpp
	$(comp) $(flags) -c ../shared/Connection.cpp
ServerSocket.o: ServerSocket.cpp ServerSocket.hpp
	$(comp) $(flags) -c ServerSocket.cpp