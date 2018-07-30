#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

#include "cJSON.h"

typedef struct
{
	//int id;
	int  type;
	char time[32];
	char le_guid[32];
	char tagid[64];
	//int age;
	float xcoord;
	float ycoord;
	float zcoord;
}location;

void dofile(char *filename);/* Read a file, parse, render back, etc. */

int main(int argc, char **argv)
{

//	dofile("json_str1.txt");
//	dofile("json_str2.txt");
	//dofile("json_str3.txt");
	FILE *f;
		int len;
		char *data;
		
		f=fopen("D:\\wlrun.log","rb");
		fseek(f,0,SEEK_END);
		len=ftell(f);
		fseek(f,0,SEEK_SET);
		data=(char*)malloc(len+1);
		fread(data,1,len,f);
		fclose(f);
		
		printf("read json_str3.txt complete, len=%d.\n",len);
	
	//	char str_name[40];
	//	int ret = cJSON_to_str(data, str_name);
	
	//	people person;
	//	int ret = cJSON_to_struct(data, &person);
	
		location worker[1]={0};
		cJSON_to_struct_array(data, worker);
	
		free(data);

	return 0;
}





//parse a struct array
int cJSON_to_struct_array(char *text, location worker[])
{
	cJSON *json,*arrayItem,*item,*object;
	int i;

	json=cJSON_Parse(text);
	if (!json)
	{
		printf("Error before: [%s]\n",cJSON_GetErrorPtr());
	}
	else
	{
		object=cJSON_GetObjectItem(json,"location");
		if(object!=NULL)
		{
			//int size=cJSON_GetArraySize(arrayItem);
			//printf("cJSON_GetArraySize: size=%d\n",size);

			for(i=0;i<1;i++)
			{
				//printf("i=%d\n",i);
				//object=cJSON_GetArrayItem(arrayItem,i);

                //type
                item=cJSON_GetObjectItem(object,"type");
				if(item!=NULL)
				{
					printf("cJSON_GetObjectItem: type=%d, string is %s, valueint=%d\n",item->type,item->string,item->valueint);
					worker[i].type=item->valueint;
				}
				else
				{
					printf("cJSON_GetObjectItem: get age failed\n");
				}
				
				//time
				item=cJSON_GetObjectItem(object,"time");
				if(item!=NULL)
				{
					printf("cJSON_GetObjectItem: type=%d, string is %s, time=%s\n",item->type,item->string,item->valuestring);
					memcpy(worker[i].time,item->valuestring,strlen(item->valuestring));
				}

                //le_guid
				item=cJSON_GetObjectItem(object,"le_guid");
				if(item!=NULL)
				{
					printf("cJSON_GetObjectItem: type=%d, string is %s, le_guid=%s\n",item->type,item->string,item->valuestring);
					memcpy(worker[i].le_guid,item->valuestring,strlen(item->valuestring));
				}

                //tagid
				item=cJSON_GetObjectItem(object,"tagid");
				if(item!=NULL)
				{
					printf("cJSON_GetObjectItem: type=%d, string is %s, tagid=%s\n",item->type,item->string,item->valuestring);
					memcpy(worker[i].tagid,item->valuestring,strlen(item->valuestring));
				}

				//xcoord
				item=cJSON_GetObjectItem(object,"xcoord");
				if(item!=NULL)
				{
					printf("cJSON_GetObjectItem: type=%d, string is %s, xcoord=%f\n",item->type,item->string,item->valuedouble);
					worker[i].xcoord=item->valuedouble;
 				}

				//ycoord
                item=cJSON_GetObjectItem(object,"ycoord");
				if(item!=NULL)
				{
					printf("cJSON_GetObjectItem: type=%d, string is %s, ycoord=%f\n",item->type,item->string,item->valuedouble);
					worker[i].ycoord=item->valuedouble;
 				}
				
				//zcoord
				item=cJSON_GetObjectItem(object,"zcoord");
				if(item!=NULL)
				{
					printf("cJSON_GetObjectItem: type=%d, string is %s, zcoord=%f\n",item->type,item->string,item->valuedouble);
					worker[i].zcoord=item->valuedouble;
 				}
			}
		}

		for(i=0;i<1;i++)
		{
			printf("type=%d,time=%s,le_guid=%s,tagid=%s,xcoord=%f,ycoord=%f,zcoord=%f\n",
				    worker[i].type,
					worker[i].time,
					worker[i].le_guid,
					worker[i].tagid,
					worker[i].xcoord,
                    worker[i].ycoord,
                    worker[i].zcoord
			);
		}

		cJSON_Delete(json);
	}
	return 0;
}

#if 0
// Read a file, parse, render back, etc.
void dofile(char *filename)
{
	FILE *f;
	int len;
	char *data;
	
	f=fopen(filename,"rb");
	fseek(f,0,SEEK_END);
	len=ftell(f);
	fseek(f,0,SEEK_SET);
	data=(char*)malloc(len+1);
	fread(data,1,len,f);
	fclose(f);
	
	printf("read file %s complete, len=%d.\n",filename,len);

//	char str_name[40];
//	int ret = cJSON_to_str(data, str_name);

//	people person;
//	int ret = cJSON_to_struct(data, &person);

	people worker[3]={{0}};
	cJSON_to_struct_array(data, worker);

	free(data);
}
#endif

