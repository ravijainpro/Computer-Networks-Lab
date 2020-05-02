#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#define NO_OF_PACKETS 7


int Random_Number(int no)
{
    int random_val = (random() % 10) % no; //to generate a no. b/w 0 to 9
    if(random_val!=0) {
        return random_val;
    }
    else {
        return 1;
    }
}

int simulate(int bucket_size, int op_rate) {
    int packet_size[NO_OF_PACKETS], i, clock, packet_size_remaining=0, p_sz, process_time, op;
    for(i = 0; i<NO_OF_PACKETS; ++i)
        packet_size[i] = Random_Number(6) * 10;
    for(i = 0; i<NO_OF_PACKETS; ++i)
    {
        printf("\n\nPacket %d of size(%dB) arrived:", i+1, packet_size[i]);
        if( (packet_size[i] + packet_size_remaining) > bucket_size)
            if(packet_size[i] > bucket_size)/*compare the packet siz with bucket size*/
                printf("\n\n\tPACKET DROPPED -> Packet size greater than bucket capacity");
            else
                printf("\n\n\tPACKET DROPPED -> Bucket Full");
        else
        {
            packet_size_remaining += packet_size[i];
            printf("\n\t#Bytes remaining: %d", packet_size_remaining);
            process_time = Random_Number(4) * 10;
            printf("\n\tTime left: %d", process_time);
            for(clock = 0; clock <= process_time; clock += 10)
            {
                sleep(1);
                if(packet_size_remaining)
                {
                    if(packet_size_remaining <= op_rate)/*packet size remaining comparing with output rate*/
                        op = packet_size_remaining, packet_size_remaining = 0;
                    else
                        op = op_rate, packet_size_remaining -= op_rate;
                    printf("\n\tPacket of size %d transmitted", op);
                    printf("\n\t\tBytes Remaining: %d", packet_size_remaining);
                }
                else
                {
                    break;
                }
            }
        }
    }
}

int main()
{   
    int bucket_size, op_rate;
    printf("\nEnter the Output rate: ");
    scanf("%d", &op_rate);
    printf("Enter the Bucket Size: ");
    scanf("%d", &bucket_size);
    simulate(bucket_size,op_rate);
    printf("\n\n");
    return 0;
}
