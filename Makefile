all: curl

curl.o: curl.c
	gcc -c curl.c -o curl.o -I./deps/curl/include

curl: curl.o
	gcc curl.o -o curl -lcurl

clean:
	rm curl curl.o
