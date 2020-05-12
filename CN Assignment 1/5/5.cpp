#include <bits/stdc++.h>
#include <ctime>
#define MAX_HOP 16
using namespace std;

struct packet {
    string source_ip, destination_ip;
    string data;
    int hop_count=0;
};
void simulate_RIP(packet frame) {
    //let for simulation source ip and destination ip be represented with a number 197:0:x:10
    // x being element of [0,50]
    srand(time(NULL));
    int temp=rand()%51;
    frame.source_ip="197:0:55:127";
    frame.destination_ip="197:0:"+to_string(temp)+":10";
    bool check=true; //make it false when destination is reached
    while(check && frame.hop_count<MAX_HOP) {
        frame.hop_count++;
        cout << "Hop " << frame.hop_count << "\n";
        if(rand()%51==temp) {
            check=false;
        }
    }
    if (check) {
        cout << "\n\nFrame discarded\n\n";
    }
    else {
            cout << "Frame received successfully by the destination in " << frame.hop_count << " hops\n\n";
    }
}

int main() {
    packet frame;
    frame.data = "Hey";
    simulate_RIP(frame);
    return 0;
}