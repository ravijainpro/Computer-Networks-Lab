#include <iostream>
#define FRAMES 10
using namespace std;

int check=0;
int sender(int x) {
	cout << "Sending Packet " << x << "\n";
	//delay(1000);
	if(check) {
		return 1;
	}
	return rand()%2;
}

int receiver(int x) {
	cout << "Receiving Packet " << x << "\n";
	//delay(1000);
	if(check) {
		return 1;
	}
	return rand()%2;
}

int main() {
	int to_sent=1, limit, temp=0;
	cout << "Acceptable Failed Attempt per frame\n";
	cin >> limit;
	while(to_sent <= FRAMES) {
		if(temp > limit) {
			check=1;
		}
		if(sender(to_sent)==1) {
			cout << "Sent Successfuly\n";
			if(receiver(to_sent)==1) {
				cout << "Received Successfuly\n";
				temp=0;
				check=0;
				to_sent++;
			}
			else {
				temp++;
				cout << "Receive Failure\n";
			}
		}
		else {
			temp++;
			cout << "Sent Fail\nRe-";
		}
	}
	return 0;
}
