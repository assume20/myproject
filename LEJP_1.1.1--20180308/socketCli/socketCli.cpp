// socketCli.cpp : 定义控制台应用程序的入口点。
//
#include "comParse.h"
#include "stdio.h"
#include <iostream>
using namespace std;

int main()
{
	char recBuffer[190],ipaddr[20],port[10];
	int len=190;
    SOCKET clientSocket;

	printf("Please enter target ip address to connect:\n");
	cin>>ipaddr;	
    printf("Please enter port number:\n");
    cin>>port;
	//Create socket client
	clientSocket = createClient((char *)ipaddr, (char *)port);

	//create JSON parse module
    jsonParseMod(clientSocket,(char *)recBuffer,len);

    closesocket(clientSocket);
    WSACleanup();
}
#if 0
//CW#18030701 -edit- Create Socket client and receive location information from server>+
int SendCommand(SOCKET clientSocket,char *recBuffer,int len)
{
     int count=len;
     recv(clientSocket,recBuffer,count,0);
	 recBuffer[count-1]='\0';
	 return 1;
}
//CW#18030701+<

SOCKET createClient()
{ 
	int err;
	WORD versionRequired;
    WSADATA wsaData;
	versionRequired=MAKEWORD(1,1);
    err=WSAStartup(versionRequired,&wsaData);//protocol library version information
    if (!err)
    {
        printf("The client startup successful!\n");
    }else{
        printf("The client startup failed\n");
        return -1;
    }
    SOCKET clientSocket=socket(AF_INET,SOCK_STREAM,0);
	if (clientSocket == INVALID_SOCKET)
	{
		printf("socket() failed : %d !\n" , WSAGetLastError());
		return 0;
	}
    SOCKADDR_IN clientsock_in;
    clientsock_in.sin_addr.S_un.S_addr=inet_addr("192.168.1.253");
    clientsock_in.sin_family=AF_INET;
    clientsock_in.sin_port=htons(13107);
    connect(clientSocket,(SOCKADDR*)&clientsock_in,sizeof(SOCKADDR));//startup connect

	return clientSocket;
}

int jsonParseMod(SOCKET clientSocket,char *recBuffer,int len)
{
    //CW#18030701 -edit- add JSON parse module>++
	int count;
	char *data;
	cJSON *json,*item,*object;
	clLocation worker={0};
	//CW#18030701<+

	while(1)
	{
LABEL:
	    memset(recBuffer,0,sizeof(recBuffer)); //clear Array
	    SendCommand(clientSocket,(char *)recBuffer,len );
	    data=recBuffer;
	    json = cJSON_Parse(data);
	    if(NULL != json)
		{
     	    printf("%s\n",cJSON_Print(json));
		    count = cJSON_GetArraySize(json);
		    printf("Array count = [%d]\n", count);
		    object = cJSON_GetArrayItem(json,0);

    		//type
		    item = cJSON_GetObjectItem(object,"type");
		    if(NULL != item)
		    {
			    if(0 == item->valueint)
		        { 
					worker.type=item->valueint;
                    #ifdef LE_DEBUG
					printf("cJSON_GetObjectItem: type=%d, string is %s, type=%s\n",item->type,item->string,item->valueint);
                    #endif
				}else
					goto LABEL;
		    }
		    //time
		    item=cJSON_GetObjectItem(object,"time");
		    if(NULL != item)
		    {
                #ifdef LE_DEBUG
			    printf("cJSON_GetObjectItem: type=%d, string is %s, time=%s\n",item->type,item->string,item->valuestring);
                #endif
				memcpy(worker.time,item->valuestring,strlen(item->valuestring));
		    }
    		//le_guid
			item=cJSON_GetObjectItem(object,"le_guid");
			if(NULL != item)
			{
				#ifdef LE_DEBUG
				printf("cJSON_GetObjectItem: type=%d, string is %s, le_guid=%s\n",item->type,item->string,item->valuestring);
                #endif
				memcpy(worker.le_guid,item->valuestring,strlen(item->valuestring));
			}
				
            //tagid
			item=cJSON_GetObjectItem(object,"tagid");
			if(NULL != item)
			{
				#ifdef LE_DEBUG
				printf("cJSON_GetObjectItem: type=%d, string is %s, tagid=%s\n",item->type,item->string,item->valuestring);
                #endif
				memcpy(worker.tagid,item->valuestring,strlen(item->valuestring));
			}

			//xcoord
			item=cJSON_GetObjectItem(object,"xcoord");
			if(NULL != item)
			{
                #ifdef LE_DEBUG
				printf("cJSON_GetObjectItem: type=%d, string is %s, xcoord=%f\n",item->type,item->string,item->valuedouble);
                #endif
				worker.xcoord=item->valuedouble;
 			}
	
			//ycoord
            item=cJSON_GetObjectItem(object,"ycoord");
			if(NULL != item)
			{
                #ifdef LE_DEBUG
				printf("cJSON_GetObjectItem: type=%d, string is %s, ycoord=%f\n",item->type,item->string,item->valuedouble);
                #endif 
				worker.ycoord=item->valuedouble;
 			}
				
			//zcoord
			item=cJSON_GetObjectItem(object,"zcoord");
			if(NULL != item)
			{
                #ifdef LE_DEBUG
				printf("cJSON_GetObjectItem: type=%d, string is %s, zcoord=%f\n",item->type,item->string,item->valuedouble);
                #endif	
			    worker.zcoord=item->valuedouble;
 			}
	    
		}
#if 1
		printf("{\n");
	    printf("    type=%d\n",worker.type);
	    printf("    time=%s\n",worker.time);
	    printf("    le_guid=%s\n",worker.le_guid);
	    printf("    tagid=%s\n",worker.tagid);
	    printf("    xcoord=%f\n",worker.xcoord);
        printf("    ycoord=%f\n",worker.ycoord);
        printf("    zcoord=%f\n",worker.zcoord);
		printf("}\n");
#endif	
	    //Sleep(500);
    }
 
    return 1;
}
#endif