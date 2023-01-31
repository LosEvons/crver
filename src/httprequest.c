#include "httprequest.h"

#include "../../datastructurelib/src/queue.h"

#include <string.h>
#include <stdlib.h>

int method_select(char *method){
	if (strcmp(method, "GET")){
		return GET;
	}
	else if (strcmp(method, "POST")){
		return POST;
	}
	else if (strcmp(method, "PUT")){
		return PUT;
	}
	else if (strcmp(method, "HEAD")){
		return HEAD;
	}
	else if (strcmp(method, "PATCH")){
		return PATCH;
	}
	else if (strcmp(method, "DELETE")){
		return DELETE;
	}
	else if (strcmp(method, "CONNECT")){
		return CONNECT;
	}
	else if (strcmp(method, "OPTIONS")){
		return OPTIONS;
	}
	else if (strcmp(method, "TRACE")){
		return TRACE;
	}
}

struct HTTPRequest http_request_constructor(char *requestStr){
	struct HTTPRequest request;
	// Arg string literal immutable. Make mutable:
	char requestString[strlen(requestStr)];
	strcpy(requestString, requestStr);

	// Separate body and header
	for (int i = 0; i < strlen(requestString) - 2; i++){
		if (requestString[i] == '\n' && requestString[i + 1] == '\n'){
			requestString[i + 1] = '|';
		}
	}

	// Get first line of header
	char *requestLine = strtok(requestString, "\n");
	char *headerFields = strtok(NULL, "|");
	char *body = strtok(NULL, "|");

	char *method = strtok(requestLine, " ");
	request.method = method_select(method);

	char *URI = strtok(NULL, " ");
	request.URI = URI;

	char *HTTPVersion = strtok(NULL, " ");
	HTTPVersion = strtok(HTTPVersion, "/");
	HTTPVersion = strtok(NULL, "/");
	request.HTTPVersion = (float)atof(HTTPVersion);

	request.headerFields = dictionary_constructor(compare_string_keys);

	struct Queue headers = queue_constructor();

	char *token = strtok(headerFields, "\n");
	while (token){
		headers.push(&headers, token, sizeof(*token));
		token = strtok(NULL, "\n");
	}

	char *header = (char *)headers.peek(&headers);
	while (header){
		char *key = strtok(header, ";");
		char *value = strtok(NULL, "|"); // Rest of the string (could split with any character not in string)
		request.headerFields.insert(&request.headerFields, 
					key, sizeof(*key), 
					value, sizeof(*value));
		headers.pop(&headers);
		header = (char *)headers.peek(&headers);
	}

	return request;
}