#include <stdlib.h>     //exit()
#include <signal.h>     //signal()
// from test/examples
#include "DEV_Config.h"
#include "GUI_Paint.h"
#include "GUI_BMPfile.h"
#include "Debug.h"
#include "EPD_5in83_V2.h"

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
    EPD_5in83_V2_Init();
    EPD_5in83_V2_Clear();  // clear panel before drawing, not after

    // 1. Allocate a buffer for the image
    UBYTE *BlackImage;
    UWORD Imagesize = ((EPD_5in83_V2_WIDTH % 8 == 0)? (EPD_5in83_V2_WIDTH / 8 ): (EPD_5in83_V2_WIDTH / 8 + 1)) * EPD_5in83_V2_HEIGHT;
    if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
        printf("Failed to apply for black memory...\r\n");
        return -1;
    }

    // 2. Tell Paint library about this buffer
	EPD_5in83_V2_Init();
    Paint_NewImage(BlackImage, EPD_5in83_V2_WIDTH, EPD_5in83_V2_HEIGHT, 0, WHITE);
    Paint_SelectImage(BlackImage);
    Paint_Clear(WHITE);

    // 3. Now draw into it
    Paint_DrawString_EN(10, 10, "hello world!", &Font16, BLACK, WHITE);

    // 4. Send buffer to the actual display
    EPD_5in83_V2_Display(BlackImage);

    DEV_Delay_ms(5000);
    EPD_5in83_V2_Clear();
    DEV_Module_Exit();
    free(BlackImage);
    BlackImage = NULL;
    return 0;
}