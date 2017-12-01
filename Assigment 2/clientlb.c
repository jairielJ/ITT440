#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc, char **argv)
{
int sockd;
if((sockd = socket(AF_INET,SOCK_STREAM, 0)) ==1 ) {
fprintf(stderr,"Socket creation failed\n");
return 1;
}
struct sock addr_in svr;
svr.sin_addr.s_addr = inet_addr(argv[1]);
svr.sin_family = AF_INET;
svr.sin_port = htons(atoi(argv[2]));

printf("Connectiong to %s:%s\n", argv[1], argv[2]);
if(connect(sockd, (struct sockaddr *)&svr, sizeof svr) < 0) {
fprintf(stderr, "Connection error\n");
return 2;
}
char svri[10];
strcpy(svri,argv[3]);
strcat(svri,"\n");
send(sockd, svri, sizeof svri, 0);
char msg[100];
if(recv(sockd, msg, sizeof msg, 0) < 0 )
fprintf(stderr, "Retrieval failed\n");
else
printf(msg);
}
