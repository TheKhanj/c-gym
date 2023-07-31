#include <curl/curl.h>
#include <stdio.h>

int main() {
	CURL *curl;
	CURLcode res;

	// Initialize the libcurl library
	curl = curl_easy_init();

	if (curl) {
		// Set the URL you want to make a request to
		curl_easy_setopt(curl, CURLOPT_URL, "https://google.com");

		// Perform the request
		res = curl_easy_perform(curl);

		if (res != CURLE_OK) {
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
							curl_easy_strerror(res));
		}

		// Clean up and release resources
		curl_easy_cleanup(curl);
	}

	return 0;
}
