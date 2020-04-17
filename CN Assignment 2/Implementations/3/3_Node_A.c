#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <time.h>
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define PORT_A	 8080
#define PORT_B	 8081  
#define PORT_C 8082 
#define MAX_TTL 16
int main() { 
	int sockfd, sockfd1;  
	struct packet {
		/* header */
		short int color; //red->0, blue->1, green->2
		short int TTL;
		short int SID;
		short int SeqNo; 		
		short int UID; //10 || 20 || 30
		char IP[100]; 
	};
	srand(time(NULL));
	short int Start_SID=100;
	short int Start_SeqNO=0;
	struct packet to_send ={rand()%3, MAX_TTL, Start_SID++, Start_SeqNO++, 10,"197.0.0.1"};	
		
	struct packet *data = malloc(sizeof(struct packet));
	struct sockaddr_in A_addr, C_addr, B_addr; 
	
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("NODE A: Socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	memset(&A_addr, 0, sizeof(A_addr)); 
	memset(&B_addr, 0, sizeof(B_addr)); 
	memset(&C_addr, 0, sizeof(C_addr)); 
	
	A_addr.sin_family = AF_INET; 
	A_addr.sin_addr.s_addr = INADDR_ANY; 
	A_addr.sin_port = htons(PORT_A); 

	B_addr.sin_family = AF_INET; 
	B_addr.sin_addr.s_addr = INADDR_ANY; 
	B_addr.sin_port = htons(PORT_B); 
	
	C_addr.sin_family = AF_INET; 
	C_addr.sin_addr.s_addr = INADDR_ANY; 
	C_addr.sin_port = htons(PORT_C); 

	if (( bind(sockfd, (const struct sockaddr *)&A_addr, sizeof(A_addr)) < 0 ))
	{ 
		perror("NODE A: Socket connection failed"); 
		exit(EXIT_FAILURE); 
	}	
	sleep(10); 
	int len, n; 
	len = sizeof(A_addr); 
	while(1) {
		sleep(5);	
		sendto(sockfd, (struct packet*)&to_send, sizeof(to_send), 
		MSG_CONFIRM, (const struct sockaddr *) &B_addr, sizeof(B_addr)); 
		printf("NODE A: Message sent.\n"); 
		sleep(5);
		n = recvfrom(sockfd, (struct packet*)data, sizeof(*data), MSG_WAITALL, ( struct sockaddr *) &C_addr, &len); 

if(data->TTL==0) {
	printf("\nPacket with SID: %d\t UID: %d\t SEQ_NO %d has been dropped as TTL reached 0", data->SID, data->UID, data->SeqNo);
}
/*
When a red packet is received with source ID X, seq. num Y
o Its TTL is decremented
o Two new green packets are generated with the decremented TTL, but with the
same source ID X, and seq. num Y
o One of the green packets is sent clockwise, and the other is sent counter
clockwise
*/
else if(data->color==0) {
	data->TTL-=1;
	struct packet green_1 = {2, data->TTL-1, data->SID, data->SeqNo, 10, "197.0.0.1"};
	struct packet green_2 = {2, data->TTL-1, data->SID, data->SeqNo, 10, "197.0.0.1"};
	sendto(sockfd, (struct packet*)&green_1, sizeof(green_1), 
		MSG_CONFIRM, (const struct sockaddr *) &C_addr, sizeof(C_addr)); 
	printf("NODE A: Message sent.\n"); 	
	sendto(sockfd, (struct packet*)&green_2, sizeof(green_2), 
		MSG_CONFIRM, (const struct sockaddr *) &B_addr, sizeof(B_addr));
	printf("NODE A: Message sent.\n");  
}
/*
When a green packet is received with source ID X, seq. num Y
o With probability 1/2, decrement the TTL by 1
o If the TTL is now > 0, send the green packet onwards (with the same source
ID field X, and seq. num Y) in the same cyclical direction in which it was
received
o If the TTL is zero, generate a blue packet with the same source ID field X, and
send the blue packet along the same cyclical direction
*/
else if(data->color==2) {
	if((rand()%2)/2) {
		data->TTL-=1;
	}
	if(data->TTL>0) {
			struct packet green_pack = {2, data->TTL-1, data->SID, data->SeqNo, 10, "197.0.0.1"};
			if(data->UID==20) {
				sendto(sockfd, (struct packet*)&green_pack, sizeof(green_pack), 
		MSG_CONFIRM, (const struct sockaddr *) &C_addr, sizeof(C_addr)); 		
			}
			else {
				sendto(sockfd, (struct packet*)&green_pack, sizeof(green_pack), 
		MSG_CONFIRM, (const struct sockaddr *) &B_addr, sizeof(B_addr)); 
			}
		printf("NODE A: Message sent.\n"); 
	}	
}
/*
When a blue packet is received
o Print the source ID of the packet, its sequence number, and the IP address of
the machine from which it was received (i.e. just the previous hop's IP
address)
The application generates a red packet 5 seconds, with its own source ID (10, 20, or
30), and with TTL=8
*/
else if (data->color==1){
	printf("\nSource ID: %d \nSEQ_NO: %d \nIP ADDRESS: %s\n", data->SID, data->SeqNo, data->IP);
	sleep(5);
	struct packet red_pack = {2, 8, data->UID, Start_SeqNO++, 10, "197.0.0.1"};
	if(data->UID==20) {
				sendto(sockfd, (struct packet*)&red_pack, sizeof(red_pack), 
		MSG_CONFIRM, (const struct sockaddr *) &C_addr, sizeof(C_addr)); 		
	}
	else {
				sendto(sockfd, (struct packet*)&red_pack, sizeof(red_pack), 
		MSG_CONFIRM, (const struct sockaddr *) &B_addr, sizeof(B_addr)); 
	}
	printf("NODE A: Message sent.\n"); 
}
else {
	//error state
}
}	
	return 0; 
} 
