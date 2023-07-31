curl: curl.c
	gcc $< -o $@ -lcurl

clean:
	rm curl
