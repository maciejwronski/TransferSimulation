#include <fstream>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <string.h>

#define INPUT_NAME "test.txt"
#define OUTPUT_NAME "output.txt"

#define PACKET_SIZE 4

using namespace std;

typedef struct {
    int ID;
    int psize;
} packet;
int main()
{
    srand(time(NULL));
    ifstream infile (INPUT_NAME,std::ifstream::binary);
    ofstream outfile (OUTPUT_NAME,std::ofstream::binary);

    infile.seekg (0,infile.end);
    long size = infile.tellg();
    infile.seekg (0);

    int packet_num = size/PACKET_SIZE;
    int last_packet = size % PACKET_SIZE;

    cout << " Number of full packets: " << packet_num << " last packet: " << last_packet << " //: " << endl;


   // packet * pointer = new packet();

    if(last_packet == 0){
        packet * pointer = new packet[packet_num];
        packet Packets[packet_num];
            for(int i=0; i<packet_num; i++){
            (*pointer).ID = i;
            (*pointer).psize = PACKET_SIZE;
            printf("Number:%d/%d\tSize:%d\n",(*pointer).ID, packet_num, (*pointer).psize);
        }
    }
    else if(last_packet != 0 && packet_num > 0){
         packet * pointer = new packet[packet_num+1];
            for(int i=0; i<packet_num+1; i++){
            (*pointer).ID = i;
            if(i < packet_num) (*pointer).psize = PACKET_SIZE;
            if(i == packet_num) (*pointer).psize = last_packet;
            printf("Number:%d/%d\tSize:%d\n",(*pointer).ID, packet_num, (*pointer).psize);
        }
    }
    else if(last_packet != 0 && packet_num == 0){
         packet * pointer = new packet[1];
            (*pointer).ID = 0;
            (*pointer).psize = last_packet;
            printf("Number:%d/%d\tSize:%d\n",(*pointer).ID, packet_num, (*pointer).psize);

    }

    return 0;
}
