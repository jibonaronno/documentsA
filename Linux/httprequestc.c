int request(void) {

    char buffer[BUFSIZ];

    enum CONSTEXPR { MAX_REQUEST_LEN = 1024};

    char request[MAX_REQUEST_LEN];

    //char request_template[] = "GET /api/Common/StartDataCollector?luName=YHGLU&ipAddress=192.168.10.111&luType=G&equipmentName=SCBR1 HTTP/1.1\r\nHost: %s\r\n\r\n";

    char request_template[] = "GET /api/Common/StartDataCollector?luName=YHGLU&ipAddress=192.168.247.104&luType=G&equipmentName=SCBR1 HTTP/1.0\r\n\r\n";

	struct protoent *protoent;

    char *hostname = "192.168.10.132";

    in_addr_t in_addr;

    int request_len;

    int socket_file_descriptor;

    ssize_t nbytes_total, nbytes_last;

    struct hostent *hostent;

    struct sockaddr_in sockaddr_in;

    unsigned short server_port = 90;



    request_len = snprintf(request, MAX_REQUEST_LEN, request_template);

    if (request_len >= MAX_REQUEST_LEN) {

        fprintf(stderr, "request length large: %d\n", request_len);

        //exit(EXIT_FAILURE);

		return -1;

    }



    /* Build the socket. */

    protoent = getprotobyname("tcp");

    if (protoent == NULL) {

        perror("getprotobyname");

		return -1;

        //exit(EXIT_FAILURE);

    }

    socket_file_descriptor = socket(AF_INET, SOCK_STREAM, protoent->p_proto);

    if (socket_file_descriptor == -1) {

        perror("socket");

        //exit(EXIT_FAILURE);

		return -1;

    }



    /* Build the address. */

    hostent = gethostbyname(hostname);

    if (hostent == NULL) {

        fprintf(stderr, "error: gethostbyname(\"%s\")\n", hostname);

        //exit(EXIT_FAILURE);

		return -1;

    }

    

	//in_addr = inet_addr(inet_ntoa(*(struct in_addr*)*(hostent->h_addr_list)));

    in_addr = inet_addr("192.168.10.132");



	if (in_addr == (in_addr_t)-1) {

        fprintf(stderr, "error: inet_addr(\"%s\")\n", *(hostent->h_addr_list));

        //exit(EXIT_FAILURE);

		return -1;

    }

    sockaddr_in.sin_addr.s_addr = in_addr;

    sockaddr_in.sin_family = AF_INET;

    sockaddr_in.sin_port = htons(server_port);



    /* Actually connect. */

    if (connect(socket_file_descriptor, (struct sockaddr*)&sockaddr_in, sizeof(sockaddr_in)) == -1) {

        perror("connect");

        //exit(EXIT_FAILURE);

		return -1;

    }



    /* Send HTTP request. */

    nbytes_total = 0;

    while (nbytes_total < request_len) {

        nbytes_last = write(socket_file_descriptor, request + nbytes_total, request_len - nbytes_total);

        if (nbytes_last == -1) {

            perror("write");

            //exit(EXIT_FAILURE);

			return -1;

        }

        nbytes_total += nbytes_last;

    }



    /* Read the response. */

    fprintf(stderr, "debug: before first read\n");

    while ((nbytes_total = read(socket_file_descriptor, buffer, BUFSIZ)) > 0) 
    {
        fprintf(stderr, "debug: after a read\n");
        //write(STDOUT_FILENO, buffer, nbytes_total);
		printf("%s", buffer);
    }

    fprintf(stderr, "debug: after last read\n");

    if (nbytes_total == -1) 
    {
        perror("read");
        //exit(EXIT_FAILURE);
		return -1;
    }

    close(socket_file_descriptor);
	return 0;

}