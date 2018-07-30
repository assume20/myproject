#ifndef _COMMUNICATION_MOD
#define _COMMUNICATION_MOD

#include "stdafx.h"
#include <WINSOCK2.H>
//#include <windows.h>

#pragma comment(lib,"ws2_32.lib")

#define DEBUG 0
#if DEBUG
 #define LE_DEBUG 1 
#endif 
typedef struct
{
	int  type;           //data type
	char time[32];       //current time
	char le_guid[32];    //engine service id
	char tagid[64];      //tag id
	double xcoord;       //x coordinate
	double ycoord;       //y coordinate
	double zcoord;       //z coordinate
}clLocation;

int SendCommand(SOCKET clientSocket, char *recBuffer, int len );
SOCKET createClient(char *ipaddr,char *port);
int jsonParseMod(SOCKET clientSocket,char *recBuffer,int len);

#endif //_COMMUNICATION_MOD