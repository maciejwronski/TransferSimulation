#include <fstream>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <string.h>

#define INPUT_NAME "test.txt"
#define OUTPUT_NAME "output.txt"

#define PACKET_SIZE 1

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

    int SizeOfBuffer;
    if(last_packet == 0)
        SizeOfBuffer = packet_num*sizeof(packet) + size;
    else if(last_packet != 0 && packet_num > 0)
        SizeOfBuffer = (packet_num+1)*sizeof(packet) + size;
    else if(last_packet != 0 && packet_num != 0)
        SizeOfBuffer = sizeof(packet) + last_packet;

    char* buffer1 = new char[SizeOfBuffer];
    if(last_packet == 0){
            for(int i=0; i<packet_num; i++){
                char* MyPackage = new char[sizeof(packet) + PACKET_SIZE];
                packet* p = (packet*)MyPackage;
                (*p).ID = i;
                (*p).psize = PACKET_SIZE;
                buffer1[i] = MyPackage[i];
        }
    }
    else if(last_packet != 0 && packet_num > 0){
            for(int i=0; i<packet_num+1; i++){
                if(i<packet_num){
                    char* MyPackage = new char[sizeof(packet) + PACKET_SIZE];
                    packet* p = (packet*)MyPackage;
                    (*p).ID = i;
                    (*p).psize = PACKET_SIZE;
                    buffer1[i] = MyPackage[i];
                }
                else if(i==packet_num){
                    char* MyPackage = new char[sizeof(packet) + last_packet];
                    packet* p = (packet*)MyPackage;
                    (*p).ID = i;
                    (*p).psize = last_packet;
                    buffer1[i] = MyPackage[i];
                }
        }
    }
    else if(last_packet != 0 && packet_num == 0){
                char* MyPackage = new char[sizeof(packet) + last_packet];
                packet* p = (packet*)MyPackage;
                (*p).ID = 0;
                (*p).psize = last_packet;
                buffer1[0] = MyPackage[0];
    }
    return 0;
}
