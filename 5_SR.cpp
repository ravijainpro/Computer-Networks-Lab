#include <iostream>
#include <bits/stdc++.h> 
#define FRAMES 10
using namespace std;

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
	return 1;
}

int main() {
	int n;
	cout << "Sender Window Size: ";
	cin >> n;
	cout << "\n";
	cin >> to_drop;
	list<int> list{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	std::queue<int> pushlist;
	while(!list.empty()) {
		int x;
		for(int i=0; i<n && !list.empty() && x<=FRAMES; i++) {
			x=list.front();
			if(sender(x)==0) {
				pushlist.push(x);
			}
			list.remove(x);
		}
		while(!pushlist.empty()) {
		    int t=pushlist.front();
		    list.push_front(t);
		    pushlist.pop();
		}
	}
	cout << "\n\nAll Frames Sent\n\nTotal Number of Transmission: " << no_transmission << "\n\nEfficiency: " << (float)FRAMES/no_transmission*100.01 << "\n\n";
	return 0;
}
