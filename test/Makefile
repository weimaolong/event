
server:
	g++ -g -o udp_server ../core/event_epoll.cpp ../core/event_select.cpp ../core/event_event.cpp udp_server.cpp -std=c++0x

client:
	g++ -g -o udp_client udp_client.cpp

clean:
	rm -rf udp_server
	rm -rf udp_client
