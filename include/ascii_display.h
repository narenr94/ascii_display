#ifndef ASCII_DISPLAY
#define ASCII_DISPLAY


#include <mutex>
#include <iostream>
#include <unistd.h>
#include <ncurses.h>



#define MAX_ASCII_DISPLAY_HEIGHT 1000
#define MAX_ASCII_DISPLAY_Width 1000
#define ASCII_DISPLAY_USEC_FACTOR 1000000

#define ASCII_DISPLAY_START_Y 10
#define ASCII_DISPLAY_START_X 10

#define ASCII_DISPLAY_WINDOW_OFFSET 2

class ASCII_Display {
private:
    // Member variables
    bool m_bstopped = false;

    unsigned int m_height = 0;

    unsigned int m_width = 0;

    bool m_initialized = false;

    unsigned int m_frameRate = 0;

    unsigned char* m_pucDisplayBuff = NULL;

    WINDOW * win = NULL;

    // Static pointer to the Singleton instance
    static ASCII_Display* instancePtr;

    // Mutex to ensure thread safety
    static std::mutex mtx;

    std::mutex mtx_displayUpdate;

    // Private Constructor
    ASCII_Display() {}

    

    unsigned int convertFrameRateToMicroSec();

public:
    // Deleting the copy constructor to prevent copies
    ASCII_Display(const ASCII_Display& obj) = delete;

    // Static method to get the Singleton instance
    static ASCII_Display* getInstance() {
        if (instancePtr == nullptr) {
            std::lock_guard<std::mutex> lock(mtx);
            if (instancePtr == nullptr) {
                instancePtr = new ASCII_Display();
            }
        }
        return instancePtr;
    }

    // initialize
    void init(unsigned int height, unsigned int width, unsigned int frameRate);

    void update_frame(unsigned char** displayBuff);

    void update_display_at_framerate(unsigned char*** displayBuffBuff, unsigned int noFrames, bool loop);





};




#endif