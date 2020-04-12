#include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct Node{
	char IP_addr[16];
	int no_physical;
	int no_host_per_physical;
}var;

void input() {
	cout << "Enter the IP Address\n";
	cin.getline(var.IP_addr,16);
	cout << "Enter #Physical Org\n";
	cin >> var.no_physical;
	cout << "Enter #Nodes per Org\n";
	cin >> var.no_host_per_physical;
}

char check_best_class() {
	int net_node=var.no_physical*var.no_host_per_physical;
	if(net_node<=pow(2,8)-2) {
		return 'C';
	}
	if(net_node<=pow(2,16)-2) {
		return 'B';
	}
	if(net_node<=pow(2,24)-2) {
		return 'A';
	}
}

char check_IP_class() {
	char temp;
	int arr[3];
	int ptr=0;
	while(true) {
		temp=var.IP_addr[ptr];
		if(temp=='.') {
			break;
		}
		arr[ptr]=int(temp)-48;
		ptr++;
	}
	int val=0;
	int temp1=0;
	for(int i=ptr-1; i>=0; i--) {
		val=val+arr[i]*pow(10,temp1);
		temp1++;
	}
	if(val>=0 && val<=127) {
		return 'A';
	}
	if(val>=128 && val<=191) {
		return 'B';
	}
	if(val>=192 && val<=223) {
		return 'C';
	}
}

bool will_fit() {
	char best=check_best_class();
	char IP_class=check_IP_class();
	if(int(best)<int(IP_class)) {
		return false;
	}
	return true;
}

int no_subnets_bits() {
	return ceil(log(var.no_physical)/log(2));
}

void print_subnet_masks() {
	int temp=int(check_best_class())-65;
	int temp1=pow(2,8-no_subnets_bits());
	for(int j=0; j<var.no_physical; j++) {

		cout << "Subnet Mask " << j+1 << ":    ";
		for(int i=0; i<=temp; i++) {
			cout << "255.";
		}
		cout << temp1*(j+1) << "\n";
	}
} 

int no_host_per_subnet() {
	int temp=int(check_best_class())-65;
	int temp1;
	if(temp==0) {
		temp1=24;
	}
	if(temp==1) {
		temp1=16;
	}
	if(temp==2) {
		temp1=8;
	}
	temp1-=no_subnets_bits();
	return pow(2,temp1)-2;
}

void print_first_host_id() {
	int temp=int(check_best_class())-65;
	int temp1=pow(2,8-no_subnets_bits());
	for(int i=0; i<var.no_physical; i++) {
		cout << "First Host ID (" << i+1 << "):  "; 	
		if(temp==0) {
			cout << "x."<< temp1*(i+1) <<".0.1\n";
		}
		if(temp==1) {
			cout << "x.y." << temp1*(i+1)  <<".1\n";
		}
		if(temp==2) {
			cout << "x.y.z."<< temp1*(i+1)+1 << "\n";
		}
	}
}


void print_last_host_id() {
	int temp=int(check_best_class())-65;
	int temp1=0;
	int temp2=pow(2,8-no_subnets_bits());
	for(int i=0; i<8-no_subnets_bits();i++){
		temp1+=pow(2,i);
	}
	for(int i=0; i<var.no_physical; i++) {
		cout << "Last Host ID (" << i+1 << "):  "; 	
		if(temp==0) {
			cout << "x."<< temp2*(i+1)+temp1 <<".255.254\n";
		}
		if(temp==1) {
			cout << "x.y." << temp2*(i+1)+temp1  <<".254\n";
		}
		if(temp==2) {
			cout << "x.y.z."<< temp2*(i+1)+temp1-1 << "\n";
		}
	}
} 


void print_broadcast_host_id() {
	int temp=int(check_best_class())-65;
	int temp1=0;
	int temp2=pow(2,8-no_subnets_bits());
	for(int i=0; i<8-no_subnets_bits();i++){
		temp1+=pow(2,i);
	}
	for(int i=0; i<var.no_physical; i++) {
		cout << "Broadcast Host ID (" << i+1 << "):  "; 	
		if(temp==0) {
			cout << "x."<< temp2*(i+1)+temp1 <<".255.255\n";
		}
		if(temp==1) {
			cout << "x.y." << temp2*(i+1)+temp1  <<".255\n";
		}
		if(temp==2) {
			cout << "x.y.z."<< temp2*(i+1)+temp1 << "\n";
		}
	}
} 

int main() {
	input();
	cout << "\n";
	cout << "Best class: " << check_best_class() << "\n";
	if(will_fit()) {
		cout << "The given IP can fit all the nodes\n";
		if(check_best_class()!=check_IP_class()) {
			cout << "The given IP belongs to class " <<  check_IP_class() << " but class " << check_best_class() << " is best for this case\n";
		}
		else {
			cout << "The given IP belongs to class " <<  check_IP_class() << " and is best for this case\n";
		}
	}
	else {
		cout << "The given IP cannot fit all the nodes\n";	
	}
	cout << "Number of Subnet Bits: " << no_subnets_bits() << "\n";
	cout << "Number of hosts per subnet: " << no_host_per_subnet() << "\n";
	cout << "==============SUBNET MASKS==============\n";
	print_subnet_masks();
	cout << "\n===================FIRST HOST IP OF EACH SUBNET===================\n";
	print_first_host_id();
	cout << "\n===================LAST HOST IP OF EACH SUBNET===================\n";
	print_last_host_id();
	cout << "\n===================BROADCAST HOST IP OF EACH SUBNET===================\n";
	print_broadcast_host_id();

	return 0;
}