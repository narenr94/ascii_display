#include "ascii_display.h"

// Initialize static members
ASCII_Display* ASCII_Display::instancePtr = nullptr;
std::mutex ASCII_Display::mtx;


void ASCII_Display::init(unsigned int height, unsigned int width, unsigned int frameRate)
{
    m_height = height;
    m_width = width;
    m_frameRate = frameRate;
    m_pucDisplayBuff = new unsigned char[m_height * m_width];
    m_initialized = true;
    initscr();
    win = newwin(height + ASCII_DISPLAY_WINDOW_OFFSET, width + ASCII_DISPLAY_WINDOW_OFFSET, ASCII_DISPLAY_START_Y, ASCII_DISPLAY_START_X);
    refresh();
    box(win, 0 ,0);
    wrefresh(win);
    
}



void ASCII_Display::update_frame(unsigned char** displayBuff)
{
    std::unique_lock<std::mutex>lock(mtx_displayUpdate);
    unsigned int i = 0;
    unsigned int j = 0;

    m_bstopped = false;


    for(i = 0; i < m_height; i++)
    {
        for(j = 0; j < m_width; j++)
        {
            //std::cout<<displayBuff[i][j];
            mvwprintw(win,i+1,j+1,"%c",displayBuff[i][j]);
        }
        
    }
    
    wrefresh(win);

}


void ASCII_Display::update_display_at_framerate(unsigned char*** displayBuffBuff, unsigned int noFrames, bool loop)
{
    unsigned int currFrameIdx = 0;

    unsigned int sleepTime = convertFrameRateToMicroSec();

    do{

        if(currFrameIdx >= noFrames)
        {
            currFrameIdx = 0;
        }
        update_frame(displayBuffBuff[currFrameIdx]);
        currFrameIdx++;
        usleep(sleepTime);

    }while((loop || (currFrameIdx < noFrames)) && (!m_bstopped));
}

unsigned int ASCII_Display::convertFrameRateToMicroSec()
{
    unsigned int uSec = 0;

    uSec = ASCII_DISPLAY_USEC_FACTOR/m_frameRate;

    return uSec;
}


