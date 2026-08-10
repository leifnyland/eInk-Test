#include <stdlib.h>     //exit()
#include <signal.h>     //signal()
// from test/examples
#include "DEV_Config.h"
#include "GUI_Paint.h"
#include "GUI_BMPfile.h"
#include "Debug.h"

#include <stdlib.h>#include <unistd.h>

void  Handler(int signo)
{
    //System Exit
    printf("\r\nHandler:exit\r\n");
    DEV_Module_Exit();

    exit(0);
}

int main()
{
    // Exception handling:ctrl + c
    signal(SIGINT, Handler);
    if(DEV_Module_Init()!=0){
        return -1;
    }
	printf("e-Paper Init and Clear...\r\n");
    EPD_5in83_V2_Init();

	Paint_DrawString_EN(10, 10, "hello world!", &Font16, BLACK, WHITE)

	sleep(10);
	EPD_5in83_V2_Clear();
	DEV_Module_Exit();
	return 0;
}