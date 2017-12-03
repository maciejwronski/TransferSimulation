#include <fstream>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <string.h>

/// problem z dwoma pakietami!!!!
#define INPUT_NAME "test.txt"
#define OUTPUT_NAME "output.txt"

#define PACKET_SIZE 2

using namespace std;

typedef struct {
    int ID;
    int psize;
} packet;
int main() {
    srand(time(NULL));
    ifstream infile (INPUT_NAME,std::ifstream::binary);
    ofstream outfile (OUTPUT_NAME,std::ofstream::binary);

    infile.seekg (0,infile.end);
    long size = infile.tellg();
    infile.seekg (0);
    char* buffer = new char[size];
    infile.read(buffer, size);
    int packet_num = size/PACKET_SIZE;
    int last_packet = size % PACKET_SIZE;
    cout << " Number of full packets: " << packet_num << " last packet: " << last_packet << " //: " << endl;

    int SizeOfBuffer;
    if(last_packet == 0 && packet_num > 1)
        SizeOfBuffer = packet_num*sizeof(packet) + size;
    else if(last_packet != 0 && packet_num > 0)
        SizeOfBuffer = (packet_num+1)*sizeof(packet) + size;
    else if((last_packet != 0 && packet_num == 0) || packet_num == 1)
        SizeOfBuffer = sizeof(packet)+size;

    char* buffer1 = new char[SizeOfBuffer];
    if(last_packet == 0 && packet_num > 1) {
        for(int i=0; i<packet_num; i++) {
            char* MyPackage = new char[sizeof(packet) + PACKET_SIZE];
            packet* p = (packet*)MyPackage;
            (*p).ID = i;
            (*p).psize = PACKET_SIZE;
            for(int j=sizeof(packet); j<sizeof(packet) + PACKET_SIZE; j++) {
                MyPackage[j] = buffer[j - sizeof(packet) + PACKET_SIZE] ;
            }
            for(int k = 0; k < sizeof(packet) + PACKET_SIZE; k++) {
                buffer1[k+i*(sizeof(packet) + PACKET_SIZE)] = MyPackage[k];
            }
            delete MyPackage;
            printf("PACZKA ROWNA\n");
        }
    } else if(last_packet != 0 && packet_num > 0) {
        int PacketTotalSize = sizeof(packet) + PACKET_SIZE;
        for(int i=0; i<=packet_num; i++) {
            if(i<packet_num) {
                    char* MyPackage = new char[sizeof(packet) + PACKET_SIZE];
                    packet* p = (packet*)MyPackage;
                    (*p).ID = i;
                    (*p).psize = PACKET_SIZE;
                    for(int j=sizeof(packet); j<sizeof(packet) + PACKET_SIZE; j++) {
                        MyPackage[j] = buffer[j - sizeof(packet) + PACKET_SIZE] ;
                    }
                    for(int k = 0; k < sizeof(packet) + PACKET_SIZE; k++) {
                        buffer1[k+i*(sizeof(packet) + PACKET_SIZE)] = MyPackage[k];
                    }
                    printf("%d %d \n", (*p).ID, (*p).psize);
                    delete MyPackage;
                }
                else if(i==packet_num) {
                    char* MyPackage = new char[sizeof(packet) + last_packet];
                    packet* p = (packet*)MyPackage;
                    (*p).ID = i;
                    (*p).psize = last_packet;
                    for(int j=sizeof(packet); j<sizeof(packet) + last_packet; j++) {
                        MyPackage[j] = buffer[j - sizeof(packet) + last_packet] ;
                    }
                    for(int k = 0; k < sizeof(packet) + last_packet; k++) {
                        buffer1[k+i*(sizeof(packet) + PACKET_SIZE)] = MyPackage[k];
                    }
                    printf("%d %d \n", (*p).ID, (*p).psize);
                    delete MyPackage;
                }
            }
            printf("paczka nierowna\n");
        }
        else if((last_packet != 0 && packet_num == 0) || packet_num == 1) {
            char* MyPackage = new char[sizeof(packet) + size];
            last_packet = size;
            packet* p = (packet*)MyPackage;
            (*p).ID = 0;
            (*p).psize = last_packet;
            for(int i=0; i<sizeof(packet) + size; i++) {
                if(i<sizeof(packet))
                    buffer1[i] = MyPackage[i];
                else
                    buffer1[i] = buffer[i-sizeof(packet)];
            }
            delete MyPackage;
            printf("PACZKA POJEDYNCZA\n");
        }
        for(int i=0; i<SizeOfBuffer; i++) {
            printf("%d : %c,\n ", i, buffer1[i]);
        }
        return 0;
    }
