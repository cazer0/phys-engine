#include "Input.h"


// Constructor and Destructor

Input::Input() : m_x(0), m_y(0), m_xRel(0), m_yRel(0), m_terminate(false)
{
    for(int i(0); i < SDL_NUM_SCANCODES; i++)
        m_keys[i] = false;

    for(int i(0); i < 8; i++)
        m_buttons[i] = false;
}


Input::~Input()
{

}


// Methodes

void Input::updateEvents()
{
    m_xRel = 0;
    m_yRel = 0;


    // Events loop
    while(SDL_PollEvent(&m_event))
    {
        switch(m_event.type)
        {
            // Keyboard
            case SDL_KEYDOWN:
                m_keys[m_event.key.keysym.scancode] = true;
            break;

            case SDL_KEYUP:
                m_keys[m_event.key.keysym.scancode] = false;
            break;


            // Mouse
            case SDL_MOUSEBUTTONDOWN:

                m_buttons[m_event.button.button] = true;

            break;

            case SDL_MOUSEBUTTONUP:

            	m_buttons[m_event.button.button] = false;

            break;


            // Mouse moved
            case SDL_MOUSEMOTION:

                m_x = m_event.motion.x;
                m_y = m_event.motion.y;

                m_xRel = m_event.motion.xrel;
                m_yRel = m_event.motion.yrel;

            break;


            // Window closed
            case SDL_WINDOWEVENT:

                if(m_event.window.event == SDL_WINDOWEVENT_CLOSE)
                    m_terminate = true;

            break;


            default:
            break;
        }
    }
}


bool Input::terminate() const
{
    return m_terminate;
}


void Input::displayCursor(bool bDisplay) const
{
    if(bDisplay)
        SDL_ShowCursor(SDL_ENABLE);
    else
        SDL_ShowCursor(SDL_DISABLE);
}


void Input::captureCursor(bool bCapture) const
{
    if(bCapture)
        SDL_SetRelativeMouseMode(SDL_TRUE);
    else
        SDL_SetRelativeMouseMode(SDL_FALSE);
}



// Getters

bool Input::isKeyPressed(const SDL_Scancode key) const
{
    return m_keys[key];
}


bool Input::isButtonPressed(const Uint8 button) const
{
    return m_buttons[button];
}


bool Input::hasMouseMoved() const
{
    if(m_xRel == 0 && m_yRel == 0)
        return false;
    else
        return true;
}


int Input::getX() const
{
    return m_x;
}

int Input::getY() const
{
    return m_y;
}

int Input::getXRel() const
{
    return m_xRel;
}

int Input::getYRel() const
{
    return m_yRel;
}
