#include <stdlib.h>     //exit()
#include <signal.h>     //signal()
// from test/examples
#include "DEV_Config.h"
#include "GUI_Paint.h"
#include "GUI_BMPfile.h"
#include "Debug.h"
#include "EPD_5in83g.h"

#include <stdlib.h>
#include <unistd.h>

void  Handler(int signo)
{
    //System Exit
    printf("\r\nHandler:exit\r\n");
    DEV_Module_Exit();

    exit(0);
}

int main()
{
    signal(SIGINT, Handler);
	printf("hello world test demo\r\n");
    if(DEV_Module_Init()!=0){
        return -1;
    }
	printf("Init and Clear\r\n");
    EPD_5IN83G_Init();
    EPD_5IN83G_Clear(EPD_5IN83G_WHITE);  // clear panel before drawing, not after
	DEV_Delay_ms(2000);

    // 1. Allocate a buffer for the image
    UBYTE *BlackImage;
    UDOUBLE Imagesize = ((EPD_5IN83G_WIDTH % 4 == 0)? (EPD_5IN83G_WIDTH / 4 ): (EPD_5IN83G_WIDTH / 4 + 1)) * EPD_5IN83G_HEIGHT;
    if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
        printf("Failed to apply for black memory...\r\n");
        return -1;
    }

    // 2. Tell Paint library about this buffer
	printf("Paint_NewImage\r\n");
    Paint_NewImage(BlackImage, EPD_5IN83G_WIDTH, EPD_5IN83G_HEIGHT, 0, EPD_5IN83G_WHITE);
	Paint_SetScale(4);
	Paint_SelectImage(BlackImage);
    Paint_Clear(EPD_5IN83G_WHITE);

    // 3. Now draw into it
    Paint_DrawString_EN(10, 10, "hello world!", &Font16, EPD_5IN83G_WHITE, EPD_5IN83G_BLACK);

    // 4. Send buffer to the actual display
    EPD_5IN83G_Display(BlackImage);
	DEV_Delay_ms(5000);

	printf("Clearing\r\n");
	EPD_5IN83G_Init();
    EPD_5IN83G_Clear(EPD_5IN83G_WHITE);
	DEV_Delay_ms(2000);

    printf("Goto Sleep...\r\n");
    EPD_5IN83G_Sleep();
    free(BlackImage);
    BlackImage = NULL;
    DEV_Delay_ms(2000);//important, at least 2s
    // close 5V
    printf("close 5V, Module enters 0 power consumption ...\r\n");
    DEV_Module_Exit();

    return 0;
}