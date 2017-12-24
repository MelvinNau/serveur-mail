#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
 
#include <stdio.h>
#include <string.h>
#include <unistd.h>
 
int my_socket;   
 
void snd(char *s)
{
	send(my_socket, s, strlen(s), 0); 
}
 
int printUsage(char *progname)
{
	printf("Usage: %s -t destination [-f from] [-s subject] -m message\n", progname); 
	return 1;
}	
 
int main(int argc, char *argv[])
{
	int ret;
	struct sockaddr_in my_addr;
 
	char *from=0, *to=0, *subject=0, *message=0;
	bool verbose = false;
	char optchar;
	while ((optchar = getopt (argc, argv, "f:t:s:m:v")) != -1)
	{
		switch (optchar)
		{
			case 'f':
				from = strdup(optarg);
				break;	
			case 't':
				to = strdup(optarg);
				break;	
			case 's':
				subject = strdup(optarg);
				break;	
			case 'm':
				message = strdup(optarg);
				break;	
			case 'v':
				verbose = true;
				break;
			default:
				return printUsage(argv[0]);
		}
	}	
 
	if(!to || !message)
		return printUsage(argv[0]);
 
	if(!subject)
		subject = strdup("No subject");
 
	if(!from)
		from = strdup("Unknown");
 
	if(verbose)
	{
		printf("From: %s\n", from);
		printf("To: %s\n", to);
		printf("Subject: %s\n", subject);
		printf("Message: %s\n", message);
	}	
 
 
    	my_addr.sin_family = AF_INET;
    	my_addr.sin_port = htons(25);
	my_addr.sin_addr.s_addr = inet_addr("134.214.100.11"); 
    	memset(&(my_addr.sin_zero), '\0', 8);
 
	my_socket = socket(AF_INET, SOCK_STREAM, 0);	
	if(my_socket == -1)
		printf("error while initialising socket\n");
 
	ret = connect(my_socket, (const struct sockaddr *)&my_addr, sizeof(my_addr));
	if(ret == -1)
		printf("unable to connect\n");
 
 
	int stage = 0;
	char buffer[4096];
	while(1)
	{
		ret = recv(my_socket, buffer, 4096, 0);
		if(ret != -1 && ret != 0)
		{
			buffer[ret] = '\0';
			if(strstr(buffer, "220") == buffer)
			{
				if(verbose)
					printf("Connected\n");
				snd("HELO smtp.univ-lyon1.fr\r\n"); 
			}	
 
			if(strstr(buffer, "250") == buffer)
			{
				switch(stage)
				{
					case 0:
						sprintf(buffer, "MAIL FROM: %s\r\n", from);
						snd(buffer); 
						stage++;
						break;
					case 1:
						sprintf(buffer, "RCPT TO: %s\r\n", to);
						snd(buffer); 
						stage++;
						break;
					case 2:
						snd("data\r\n"); 
						stage++;
						break;
					case 3:
						if(verbose)
							printf("Closing connection\n");
						snd("quit\r\n"); 
						stage++;
						break;
				}	
			}
 
			if(strstr(buffer, "354") == buffer)
			{
				if(verbose)
					printf("Sending message...");
				if(subject)
				{
					sprintf(buffer, "Subject: %s\r\n", subject);
					snd(buffer); 
				}	
				snd(message); 
				snd("\r\n.\r\n"); 
				if(verbose)
					printf("Ok.\n");
			}	
		}
		else
		break;
	}
 
	return 0;
}
