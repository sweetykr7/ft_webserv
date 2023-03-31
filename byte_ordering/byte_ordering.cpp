#pragma comment(lib, "ws2_32")
#include <stdio.h>
#include <netinet/in.h>

int main(int argc, char **argv)
{
	unsigned short x1 = 0x1234;
	unsigned long y1 = 0x12345678;
	unsigned short x2;
	unsigned long y2;

	//host >> network byte
	printf("host >> network byte\n");
	printf("x1 : %x, x2 : %x\n",x1, x2= htons(x1));
	printf("y1 : %lx, y2 : %lx\n",y1, y2= htonl(y1));



}