FLAGS=-lncurses -lpthread -lportaudio -std=c++11

client: client.cpp serializable.cpp serializable.hpp oo_model.cpp oo_model.hpp
	g++ -oclient client.cpp serializable.cpp oo_model.cpp $(FLAGS)
	./client

server: server.cpp serializable.cpp serializable.hpp
	g++ -oserver server.cpp serializable.cpp oo_model.cpp $(FLAGS)
	 ./server

serial: main_serialize.cpp serializable.cpp serializable.hpp
	g++ -oserial main_serialize.cpp serializable.cpp $(FLAGS)
	 ./serial
