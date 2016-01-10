#include <SDL/SDL.h>

class input
{
private:
        Uint8* keyArray;
        bool mouseArray[3];
        int x, y;
        SDL_Event event;

        void getButtonStates()
        {
                // 1 = Left 2 = Center 3 = Right
                SDL_PollEvent(&event);
                if(event.type == SDL_MOUSEBUTTONDOWN)
                        mouseArray[event.button.button - 1] = true;
                if(event.type == SDL_MOUSEBUTTONUP)
                        mouseArray[event.button.button - 1] = false;
        }
public:
        input()
        {
                SDL_PumpEvents();
                keyArray = SDL_GetKeyState(NULL);
                x = y = 0;
                for(int i = 0; i < 3; i++)
                        mouseArray[i] = false;
        }

        void update()
        {
                SDL_PumpEvents();
                keyArray = SDL_GetKeyState(NULL);
                //Gets mouse location
                SDL_GetMouseState(&x, &y);
                //Gets mouse button states
                getButtonStates();
        }

        bool isKeyTapped(SDLKey key)
        {
                if(keyArray[key] == 1)
                {
                        keyArray[key] = 0;
                        return true;
                }
                return false;
        }


        bool isKeyDown(SDLKey key)
        {
                if(keyArray[key] == 1)
                        return true;
                return false;
        }

        bool getMouseButton(int index)
        {
                if(index <= 3 && index >= 1)
                        return mouseArray[index-1];
                return false;
        }

        SDL_Event getEvent()
        {
                return event;
        }


        int getX(){return x;}

        int getY(){return y;}
};
