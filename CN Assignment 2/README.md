**Questions**

1. IP currently uses 32-bit addresses. If we could redesign IP to use the 6-byte MAC
address instead of the 32-bit address, would we be able to eliminate the need for
ARP? Explain why or why not.

2. Describe the significance of MAC and IP addresses in following scenarios, and run
the Address Resolution Protocol.
a. Two hosts of same network wants to communicate
b. Two hosts of different networks (one from network 1 and another from network 2)
wants to communicate

**Implementations**

**Task 1:** Optimal Shortest Path First Algorithm

**Task 2:** 
Install Wireshark
Start a packet capture
Run your favorite network application
Stop the capture
Note what protocols were used most

**Task 3:** UDP socket programming
Consider three machines A, B, C arranged logically in a cyclical order (clockwise: A,
B, C)
You have to write an application using UDP socket programming to achieve the
following functionality
1. The application should have a header of its own, with at least the following fields: an
8bit field representing a colour logically, and an 8bit field representing the TTL (time
to live), an 8bit sequence number, an 8bit source ID field
2. The application level source IDs for the three machines can be 10, 20, and 30
3. Packets can be of colours red, blue, green (say integer values 0, 1, 2)
4. The application uses the following rules:
When a red packet is received with source ID X, seq. num Y
o Its TTL is decremented
o Two new green packets are generated with the decremented TTL, but with the
same source ID X, and seq. num Y
o One of the green packets is sent clockwise, and the other is sent counter
clockwise
When a green packet is received with source ID X, seq. num Y
o With probability 1/2, decrement the TTL by 1
o If the TTL is now > 0, send the green packet onwards (with the same source
ID field X, and seq. num Y) in the same cyclical direction in which it was
received
o If the TTL is zero, generate a blue packet with the same source ID field X, and
send the blue packet along the same cyclical direction
When a blue packet is received
o Print the source ID of the packet, its sequence number, and the IP address of
the machine from which it was received (i.e. just the previous hop's IP
address)
The application generates a red packet 5 seconds, with its own source ID (10, 20, or
30), and with TTL=8
