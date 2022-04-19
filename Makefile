# Build proto file

.PHONY: all clean

all: message main

clean:
	rm -f main
	rm -f msg.pb.cc msg.pb.h

message: msg.proto
	protoc $$PROTO_PATH --cpp_out=. msg.proto

main: main.cc
	pkg-config --cflags protobuf  # fails if protobuf is not installed
	c++ -std=c++11 main.cc msg.pb.cc -o main `pkg-config --cflags --libs protobuf`
