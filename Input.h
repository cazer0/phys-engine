#ifndef DEF_INPUT
#define DEF_INPUT

// Include

#include <SDL2/SDL.h>


// Classe

class Input
{
    public:

    Input();
    ~Input();

    void updateEvents();
    bool terminate() const;
    void displayCursor(bool bDisplay) const;
    void captureCursor(bool bCapture) const;

    bool isKeyPressed(const SDL_Scancode key) const;
    bool isButtonPressed(const Uint8 button) const;
    bool hasMouseMoved() const;

    int getX() const;
    int getY() const;

    int getXRel() const;
    int getYRel() const;


    private:

    SDL_Event m_event;
    bool m_keys[SDL_NUM_SCANCODES];
    bool m_buttons[8];

    int m_x;
    int m_y;
    int m_xRel;
    int m_yRel;

    bool m_terminate;
};

#endif

