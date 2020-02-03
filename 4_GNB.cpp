#include <iostream>
#define FRAMES 10
using namespace std;

int last_sent=0;
int no_transmission=0;
int to_drop;

int receiver(int x) {
	cout << "Receiving Packet " << x << "\n";
	return 1;
}

int sender(int x) {
	cout << "Sending Packet " << x << "\n";
	no_transmission++;
	if(no_transmission%to_drop==0) {
		cout << "Packet Dropped\n";
		return 0;
	}
	receiver(x);
	last_sent++;
	return 1;
}

int main() {
	int n;
	cout << "Sender Window Size: ";
	cin >> n;
	cout << "\n";
	cout << "Packets to x multiples will be drop\nEnter -1 for ideal case\n";
	cin >> to_drop;
	while(last_sent!=FRAMES) {
		int temp=0;
		int x=last_sent+1;
		int i;
		for(i=0; i<n && x<=FRAMES; i++) {
			if(temp==1) {
				cout << "Fail sent frame no " << x << "\n"; 
				no_transmission++;
			}
			else if(sender(x)==0) {
				i=0;
				temp=1;
			}
			x++;
		}
	}
	cout << "\n\nAll Frames Sent\n\nTotal Number of Transmission: " << no_transmission << "\n\nEfficiency: " << (float)FRAMES/no_transmission*100.01 << "\n\n";
	return 0;
}
