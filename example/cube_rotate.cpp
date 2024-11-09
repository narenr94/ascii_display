#include "ascii_display.h"

#define CUBE_ROTATE_FRAME_HEIGHT 7
#define CUBE_ROTATE_FRAME_WIDTH 12
#define CUBE_ROTATE_FRAME_RATE 2

#define CUBE_ROTATE_NUM_FRAMES 2


unsigned char frame0[CUBE_ROTATE_FRAME_HEIGHT][CUBE_ROTATE_FRAME_WIDTH] = {
' ',' ',' ','.','+','-','-','-','-','-','-','+',\
' ','.','\'',' ','|',' ',' ',' ',' ',' ',' ','|',\
'+',' ',' ',' ','|',' ',' ',' ',' ',' ',' ','|',\
'|',' ',' ',' ','|',' ',' ','|',' ',' ',' ','|',\
'|',' ',' ',',','+','-','-','+','-','-','-','+',\
'|','.','\'',' ',' ',' ',' ','|',' ','.','\'',' ',\
'+','-','-','-','-','-','-','+','\'',' ',' ',' '
};

unsigned char frame1[CUBE_ROTATE_FRAME_HEIGHT][CUBE_ROTATE_FRAME_WIDTH] = {
'+','-','-','-','-','-','-','+',' ',' ',' ',' ',\
'|','`','.',' ',' ',' ',' ','|',' ','`','.',' ',\
'|',' ',' ','`','+','-','-','+','-','-','-','+',\
'|',' ',' ',' ','|',' ',' ','|',' ',' ',' ','|',\
'+','-','-','-','+','-','-','+',' ',' ',' ','|',\
' ','`','.',' ','|',' ',' ',' ','`','.',' ','|',\
' ',' ',' ','`','+','-','-','-','-','-','-','+'
};

int main()
{
    ASCII_Display* Display1 = ASCII_Display::getInstance();
    Display1->init(CUBE_ROTATE_FRAME_HEIGHT, CUBE_ROTATE_FRAME_WIDTH, CUBE_ROTATE_FRAME_RATE);

    unsigned char*** displayBuffBuff = (unsigned char ***)malloc(sizeof(unsigned char **) * CUBE_ROTATE_NUM_FRAMES);

    unsigned int i = 0;

    for(i = 0; i < CUBE_ROTATE_NUM_FRAMES; i++)
    {
        displayBuffBuff[i] = (unsigned char**)malloc(sizeof(unsigned char *) * CUBE_ROTATE_FRAME_HEIGHT);
    }

    unsigned int j = 0;

    for(i = 0; i < CUBE_ROTATE_NUM_FRAMES; i++)
    {
        for(j = 0; j < CUBE_ROTATE_FRAME_HEIGHT; j++)
        {
            displayBuffBuff[i][j] = (unsigned char*)malloc(sizeof(unsigned char) * CUBE_ROTATE_FRAME_WIDTH);
        }
    }


    for(i = 0; i < CUBE_ROTATE_FRAME_HEIGHT; i++)
    {
        for(j = 0; j < CUBE_ROTATE_FRAME_WIDTH; j++)
        {
            displayBuffBuff[0][i][j] = frame0[i][j];
        }
    }

    for(i = 0; i < CUBE_ROTATE_FRAME_HEIGHT; i++)
    {
        for(j = 0; j < CUBE_ROTATE_FRAME_WIDTH; j++)
        {
            displayBuffBuff[1][i][j] = frame1[i][j];
        }
    }
    
    Display1->update_display_at_framerate(displayBuffBuff, CUBE_ROTATE_NUM_FRAMES, true);


    return 0;
}