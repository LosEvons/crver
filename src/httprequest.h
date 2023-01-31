#ifndef HTTPREQUEST_H_
#define HTTPREQUEST_H_

#include "../../datastructurelib/src/dictionary.h"

// Define available HTTP request methods
enum HTTPMEthods{
	GET,
	POST,
	PUT,
	HEAD,
	PATCH,
	DELETE,
	CONNECT,
	OPTIONS,
	TRACE,
};

struct HTTPRequest{
	int method;
	char *URI;
	float HTTPVersion;
	struct Dictionary headerFields;
};

struct HTTPRequest http_request_constructor(char * requestString);

#endif