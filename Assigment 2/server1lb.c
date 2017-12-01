#include <stdlib.h>//atoi() ascii to integer
#include <unistd.h>//close() close socket
#include <stdio.h>
#include <sys/socket.h>//socket(), bind(), listen, accept() - socket func.
#include <sys/types.h>
#include <string.h>//strcat() concatenate string
#include <arpa/inet.h>//htons() host to network short
#include <netinet/in.h>//struct sockaddr_in
#include <sys/utsname.h>//uname() get node name

int main(int args, char **argv)
{
    int ssockd;//Server socket descriptor

    if((ssockd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
	fprintf(stderr, "Socket creation failed\n");
	return 1;
    }
    
    struct sockaddr_in svr;

    bzero(&svr,sizeof svr);
    svr.sin_family = AF_INET;
    svr.sin_port = htons(atoi(argv[1]));//Assign port number from command
					//+line argument
    svr.sin_addr.s_addr = htonl(INADDR_ANY);//INADDR_ANY allow connection from
					    //+ any host

    if(bind(ssockd, (struct sockaddr *)&svr, sizeof svr) < 0) {
	fprintf(stderr, "Bind failed\n");
	return 2;
    }

    listen(ssockd,4);
    struct sockaddr_in cli;
    int c = sizeof svr;
    
    for(;;) { //Indefinite loop that always wait for connection from client
	int csockd;//Socket descriptor of the client
	csockd = accept(ssockd,(struct sockaddr*)&cli,(socklen_t*) &c);
	
	if(csockd < 0) {
	    fprintf(stderr, "Connection failed\n");
	    return 3;
	}
	struct utsname host;//Stores host details
	uname(&host);

	char msg[100] = "Connected to ";
	strcat(msg, host.nodename);
	strcat(msg, "\n");
	send(csockd, msg, sizeof msg, 0);
	close(csockd);
    }
}

