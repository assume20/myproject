1. 定义结构体封装坐标数据。
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