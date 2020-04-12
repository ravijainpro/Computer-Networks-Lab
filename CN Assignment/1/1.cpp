#include <bits/stdc++.h>
using namespace std;

	
struct Node{
	string ip_addr;
	char network_name;
	string mac;
};
Node router1, router2;

class network {
	public:
		char network_name;
		int no_nodes; //max 255 nodes per network allowed
		string subnet_mask;
		string default_gateway;
		Node *Nodes;
	void gen_nodes() {
		this->Nodes= new Node[this->no_nodes];
		int start_ip_decider=int(this->network_name)-65+192;
		for (int i =0; i< this->no_nodes; i++) {
			this->Nodes[i].ip_addr=to_string(start_ip_decider)+":0:0:"+to_string(i+1);
			this->Nodes[i].network_name=this->network_name;
			this->Nodes[i].mac=to_string(int(network_name))+":A0:12:B2:15:"+to_string(10+i);
		}
		gen_sub_mask();
	}
	network(char network_name,int no_nodes,string default_gateway) {
		this->network_name=network_name;
		this->no_nodes=no_nodes;
		this->default_gateway=default_gateway;
		this->gen_nodes();
		this->gen_sub_mask();
	}
	void gen_sub_mask() {
		this->subnet_mask=to_string(int(this->network_name)-65+192)+":0:0:0";	
	}
	void display_details() {
		cout << "Network Name: " << this->network_name << "\n";
		cout << "Number of Nodes: " << this->no_nodes << "\n";
		cout << "Default Subnet Mask: " << this->subnet_mask << "\n";
		cout << "Default Gateway: " << this->default_gateway << "\n"; 
		cout << "Node Details\n";
		cout << "Node\t\t IP ADDR\t\t MAC ADDR\n";
		for (int i=0; i<this->no_nodes; i++) {
			cout << i+1 << "\t\t " << Nodes[i].ip_addr << "\t\t " << Nodes[i].mac << "\n";
		} 
		cout << "\n\n";
	}
};

network network_1('A',rand()%4,"193:0:0:0");
network network_2('D',rand()%4,"196:0:0:0");

void setup_router() {
	router1.network_name='A';
	router1.ip_addr="194:0:0:0";
	router1.mac="66:A0:12:B2:15:10";
	router2.network_name='B';
	router2.ip_addr="195:0:0:0";
	router2.mac="66:A0:12:B2:15:10";
}

void display_router_info() {
	cout << "==============ROUTER DETAILS=============";
	cout << "\nNo.\t\t IP ADDR\t\t MAC ADDR\n";
	cout << "1\t\t" << router1.ip_addr << "\t\t" << router1.mac << "\n";
	cout << "2\t\t" << router2.ip_addr << "\t\t" << router2.mac << "\n\n";
}

void display_network_info() {
	cout << "=============NETWORK DETAILS=============\n";
	network_1.display_details();
	network_2.display_details();
}

string source, destination;
void inputs() {
	cout << "Input Source IP: (from network A) " << "\n";
	cin >> source;
	cout << "Destination IP: (from network A/B) " << "\n";
	cin >> destination;	
}

Node s, d;
void simulate_arp() {
	inputs();
	cout << "\nARP SIMULATION\n";
	for(int i=0; i< network_1.no_nodes; i++) {
		if(source.compare(network_1.Nodes[i].ip_addr)==0) {
			s.ip_addr = source;
			s.network_name = network_1.Nodes[i].network_name;
			s.mac = network_1.Nodes[i].mac;
		}
		if(destination.compare(network_1.Nodes[i].ip_addr)==0) {
			d.ip_addr = destination;
			d.network_name = network_1.Nodes[i].network_name;
			d.mac = network_1.Nodes[i].mac;
		}
	}
	for(int i=0; i<network_2.no_nodes; i++) {
		if(source.compare(network_2.Nodes[i].ip_addr)==0) {
			s.ip_addr = source;
			s.network_name = network_2.Nodes[i].network_name;
			s.mac = network_2.Nodes[i].mac;
		}
		if(destination.compare(network_2.Nodes[i].ip_addr)==0) {
			d.ip_addr = destination;
			d.network_name = network_2.Nodes[i].network_name;
			d.mac = network_2.Nodes[i].mac;
		}
	}
	if(s.network_name==d.network_name) {
		cout << "Source and Destination are in same network (Subnet mask of Source Metwork AND OPERATED with Destination IP is equal to Destination IP)\n";
		cout << "ARP Broadacst from source in network\n";
		cout << "ARP REQUEST PACKET:\nSource IP: " << s.ip_addr << " Source Mac: " << s.mac << "\n";
		cout << "Destination IP: " << d.ip_addr << " Destination Mac: ff:ff:ff:ff:ff:ff"<< "\n\n";
		cout << "ARP unicast reply from destination back to source: " << "\n";
		cout << "ARP REPLY PACKET:\nSource IP: " << d.ip_addr << " Source Mac: " << d.mac << "\n";
		cout << "Destination IP: " << s.ip_addr << " Destination Mac: "<< s.mac <<"\n\n";
		cout << "DATA SENT from source to destination\n\n";
	}
	else {
		cout << "Source and Destination are in different network (Subnet mask of Source Network AND OPERATED with destination IP is not equal to Destination IP)\n";
		cout << "IP address of default gateway set in ARP request packet\n";
		cout << "ARP REQUEST PACKET:\nSource IP: " << s.ip_addr << " Source Mac: " << s.mac << "\n";
		cout << "Destination IP: " << router1.ip_addr << " Destination Mac: ff:ff:ff:ff:ff:ff" << " (Router 1 IP)\n";
		cout << "ARP unicast reply from destination (router1) back to source: " << "\n";
		cout << "ARP REPLY PACKET:\nSource IP: " << router1.ip_addr << " Source Mac: " << router1.mac << "\n";
		cout << "Destination IP: " << s.ip_addr << " Destination Mac: "<< s.mac <<"\n";
		cout << "ARP REQUEST FROM ROUTER 1 to ROUTER 2\n";
		cout << "ARP REQUEST PACKET:\nSource IP: " << router1.ip_addr << " Source Mac: " << router1.mac << "\n";
		cout << "Destination IP: " << router2.ip_addr << " Destination Mac: ff:ff:ff:ff:ff:ff" << " (Router 2 IP)\n";
		cout << "ARP unicast reply from destination (router1) back to source(router 1): " << "\n";
		cout << "ARP REPLY PACKET:\nSource IP: " << router2.ip_addr << " Source Mac: " << router2.mac << "\n";
		cout << "Destination IP: " << router1.ip_addr << " Destination Mac: "<< router1.mac << "\n";
		cout << "ARP Broadacst from router 2 to destination in network (Subnet mask of network AND with destination IP is equal to destination IP)\n";
		cout << "ARP REQUEST PACKET:\nSource IP: " << router2.ip_addr << " Source Mac: " << router2.mac << "\n";
		cout << "Destination IP: " << d.ip_addr << " Destination Mac: ff:ff:ff:ff:ff:ff"<< "\n";
		cout << "ARP unicast reply from destination back to source(router 2): " << "\n";
		cout << "ARP REPLY PACKET:\nSource IP: " << d.ip_addr << " Source Mac: " << d.mac << "\n";
		cout << "Destination IP: " << router2.ip_addr << " Destination Mac: "<< router2.mac <<"\n\n";
		cout << "DATA SENT from source to destination\n\n";
	}
}

void RARP_simulation() {
	cout << "\nRARP SIMULATION\n";
	cout << "RARP REQUEST FROM " << source << "\n";
	cout << "RARP RESPONSE: " << "IP: " << source << " MAC: " << s.mac << "\n";
}

int main() {
	setup_router();
	display_router_info();
	display_network_info();
	simulate_arp();
	RARP_simulation();
	return 0;
}