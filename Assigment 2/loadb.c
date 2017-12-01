#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/utsname.h>

int main(int args, char **argv)
{

FILE *svrlist = fopen("svrlist", "r");
if(svrlist == NULL) {
printf("ERROR opening svrlist\n");
exit(1);
}

char line[1024], *lineptr;
struct sockaddr_in svr[1024];
int svrcount = 0;
while(lineptr == fgets(line, sizeof line, svrlist)) {
if(*lineptr == '#')
continue;
++svrcount;
char *token;
for(int i = 0; (token = strsep(&lineptr, " ")) && i < 2; ++i) {
if(strcmp(token, "") == 0)
continue;
svr[svrcount - 1].sin_family = AF_INET;
if(i == 0)
svr[svrcount - 1].sin_addr.s_addr = inet_addr(token);
else
svr[svrcount - 1].sin_port = htons(atoi(token));
}
}

int ldbsock;

if((ldbsock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
printf("Load balancer socket creation failed\n");
exit(2);
}

struct sockaddr_in ldb;
bzero(&ldb,sizeof ldb);
ldb.sin_family = AF_INET;
ldb.sin_port = htons(atoi(argv[1]));
ldb.sin_addr.s_addr = htonl(INADDR_ANY);

if(bind(ldbsock, (struct sockaddr *)&ldb, sizeof ldb) < 0) {
printf("Bind failed\n");
exit(3);
}

listen(ldbsock, 4);
struct sockaddr_in cli;
int c = sizeof ldb;

for(;;) {
int csockd;
csockd = accept(ldbsock,(struct sockaddr*) &cli,(socklen_t*) &c);
if(csockd < 0 ){
printf("Connection with client failed\n");
exit(4);
}

char svri[1024];
if(recv(csockd, svri, sizeof svri, 0) < 0) {
printf("Message from retrieval from client failed\n");
exit(5);
}
int ssockd;
if((ssockd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
printf("Server socket creation failed\n");
exit(6);
}

if(connect(ssockd, (struct sockaddr *) &svr[atoi(svri)],
sizeof svr[atoi(svri)]) < 0) {
char errmsg[1024] = "Server not available..";
strcat(errmsg, "\n");
send(csockd, errmsg, sizeof errmsg, 0);
continue;

}

char svrres[1024];
recv(ssockd, svrres, sizeof svrres, 0);
send(csockd, svrres, sizeof svrres, 0);
close(ssockd);
close(csockd);
}
}

