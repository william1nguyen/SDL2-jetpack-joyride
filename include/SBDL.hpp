#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string>

using Sound = Mix_Chunk;
using Music = Mix_Music;
using Font = TTF_Font;

struct Texture {
    SDL_Texture *underneathTexture = NULL; // loaded with SDL but don't use directly in code

    int width;
    int height;
};

namespace SBDL {
    namespace Core {
        bool running = true;
        int keystate_size = -1;

        const Uint8 *keystate = NULL; // current keyboard state
        Uint8 *old_keystate = NULL; // old keyboard state

        SDL_Event event;
        SDL_Window *window = NULL;
        SDL_Renderer *renderer = NULL;
    };

    bool operator == (SDL_Rect &x, SDL_Rect &y) {
        return x.x == y.x && x.y == y.y && x.h == y.h && x.w == y.w;
    }

    struct Mouse {
        int x;
        int y;

        bool left; // left button state
        bool right; // right button state
        bool middle; // middle button state

        Uint8 state; // Press or Released
        Uint8 clicks;
        Uint8 button;

        /**
            check if mouse clicked with given conditions.
            button : check < SDL_BUTTON_LEFT,SDL_BUTTON_RIGHT,SDL_BUTTON_MIDDLE >
            clicks : number of click
            state : state of mouse < SDL_PRESSED, SDL_RELEASED >
        **/

        bool clicked (Uint8 button = SDL_BUTTON_LEFT, Uint8 clicks = 1, Uint8 state = SDL_PRESSED) {
			return this->button == button && this->clicks == clicks && this->state == state;
		}
    } Mouse;

    bool isRunning() {
        return Core::running;
    }

    void stop() {
        Core::running = false;
    }

    bool keyPressed (SDL_Scancode scanCode) {
        return !Core::old_keystate[scanCode] && Core::keystate[scanCode];
    }

    bool keyRelease (SDL_Scancode scanCode) {
        return Core::old_keystate[scanCode] && !Core::keystate[scanCode];
    }

    bool keyHold (SDL_Scancode scanCode) {
        return Core::old_keystate[scanCode] && Core::keystate[scanCode];
    }

    void updateEvents() {
		// update keyboard state
		if (Core::keystate_size == -1) {
			Core::keystate = SDL_GetKeyboardState(&Core::keystate_size);
			Core::old_keystate = new Uint8[Core::keystate_size];
			for (int i = 0; i < Core::keystate_size; i++)
				Core::old_keystate[i] = 0;
		}
		else {
			for (int i = 0; i < Core::keystate_size; i++)
				Core::old_keystate[i] = Core::keystate[i];
			Core::keystate = SDL_GetKeyboardState(&Core::keystate_size);
		}
		SDL_PumpEvents();

		// close app if ESCAPE pressed
		if (keyPressed(SDL_SCANCODE_ESCAPE)) {
			Core::running = false;
		}

		// reset event handler state for check it again
		Core::event = {};

		// returns true if there is an event in the queue, but will not remove it
		if (!SDL_PollEvent(nullptr)) {
			Mouse.left = Mouse.middle = Mouse.right = false;
			Mouse.button = 0;
			return;
		}
		while (SDL_PollEvent(&Core::event)) { // loop until there is a new event for handling
			if (Core::event.type == SDL_MOUSEBUTTONDOWN || Core::event.type == SDL_MOUSEBUTTONUP) {
				// update state of Mouse structure if it was changed
				switch (Core::event.button.button) {
				case 1:
					Mouse.left = true;
					Mouse.right = Mouse.middle = false;
					break;
				case 2:
					Mouse.middle = true;
					Mouse.right = Mouse.left = false;
					break;
				case 3:
					Mouse.right = true;
					Mouse.left = Mouse.middle = false;
					break;
				default:
					Mouse.left = Mouse.middle = Mouse.right = false;
				}

				Mouse.state = Core::event.button.state;
				Mouse.button = Core::event.button.button;
				Mouse.clicks = Core::event.button.clicks;
			}
			// update position of mouse if it was changed
			if (Core::event.type == SDL_MOUSEMOTION) {
				Mouse.x = Core::event.motion.x;
				Mouse.y = Core::event.motion.y;
			}
			if (Core::event.type == SDL_QUIT) {
				Core::running = false;
			}
		}
	}

    unsigned int getTime() {
        return SDL_GetTicks();
    }

    void updateRenderClear() {
        SDL_RenderPresent (Core::renderer);
    }

    void delay (Uint32 frameRate) {
        SDL_Delay (frameRate);
    }

    Font *loadFont (const std::string &path, int size) {
        return TTF_OpenFont (path.c_str(), size);
    }

    Texture loadTexture (const std::string &path) {
        SDL_Surface *pic = IMG_Load(path.c_str());

        Texture newTexture;
        newTexture.underneathTexture = SDL_CreateTextureFromSurface(Core::renderer, pic);

        newTexture.width = pic->w;
        newTexture.height = pic->h;

        SDL_FreeSurface(pic);

        return newTexture;
    }

    void playSound (Sound *sound, int count) {
        if (count != 0) // frequency of sound
            Mix_PlayChannel (-1, sound, (count > 0) ? count - 1 : -1);
    }

    void playMusic (Music *music, int count) {
        // count : frequency of music
        Mix_PlayMusic (music, count);
    }

    Sound *loadSound (const std::string path) {
        Sound *sound;
        sound = Mix_LoadWAV (path.c_str());
        return sound;
    }

    Music *loadMusic (const std::string path) {
        Music *music;
        music = Mix_LoadMUS (path.c_str());
        return music;
    }

    void stopMusic() {
        Mix_HaltMusic();
    }

    void stopAllSound() {
        Mix_HaltChannel(-1); // -1 for all
    }

    void freeSound (Sound* sound) {
        Mix_FreeChunk(sound);
    }

    void freeMusic (Music* music) {
        Mix_FreeMusic(music);
    }

    void freeTexture (Texture &texture) {
		SDL_DestroyTexture (texture.underneathTexture);
		texture.underneathTexture = NULL;
		texture.width = 0;
		texture.height = 0;
	}

    void showTexture (const Texture &texture, const SDL_Rect &destRect) {
		SDL_RenderCopy (Core::renderer, texture.underneathTexture, NULL, &destRect);
	}

    void showTexture (const Texture &texture, int x, int y) {
		SDL_Rect rect;
		rect.x = x;
		rect.y = y;
		rect.w = texture.width;
		rect.h = texture.height;
		showTexture (texture, rect);
	}

    Texture createFontTexture (Font *font, const std::string &text, Uint8 r, Uint8 g, Uint8 b) {
		SDL_Color color;
		color.r = r;
		color.g = g;
		color.b = b;
		SDL_Surface *temp = TTF_RenderText_Solid (font, text.c_str(), color);

		Texture newTexture;
		newTexture.underneathTexture = SDL_CreateTextureFromSurface (Core::renderer, temp);
		newTexture.width = temp->w;
		newTexture.height = temp->h;

		SDL_FreeSurface (temp);
		return newTexture;
	}

	bool hasIntersectionRect (SDL_Rect &firstRect, SDL_Rect &secondRect) {
		return SDL_HasIntersection (&firstRect, &secondRect) == SDL_TRUE;
	}

    bool pointInRect (int x, int y, const SDL_Rect &rect) {
		SDL_Point point;
		point.x = x;
		point.y = y;
		return SDL_PointInRect (&point, &rect) == SDL_TRUE;
	}

    bool mouseInRect (const SDL_Rect &rect) {
		return pointInRect (Mouse.x, Mouse.y, rect);
	}
};
