/**
 ** Code Copyright (C) 2011 Jason White <whitewaterssoftwareinfo@gmail.com>
 **                         White Waters Software - wwsoft.co.cc
 **
 ** Copying and distributing this source is prohibited without
 ** explicit authorization by the copyright holder: Jason White
 **/


#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "SDL.h"
#include "viewer.h"
#include "controller.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#include "vector"


enum engine_state
{
    RUNNING=1,
    UNINITED=0,
    ERRORS=-1
};

enum textquality
{
    solid,
    shaded,
    blended
};


struct game_map
 {
        std::string name;
        std::string description;
        int width;
        int height;
        long flags;
        std::vector<std::string> data;

};

namespace view
{
    extern int x;
    extern int y;
    extern int scale_width;
    extern int scale_height;
    extern int width;
    extern int height;
    extern int target_width;
    extern int target_height;
}

namespace play_area
{
    extern double scale;
    extern int scale_width;
    extern int scale_height;
    extern int width;
    extern int height;
}

namespace resources
{
    extern std::vector< ::controller*> control;
    extern std::vector<std::string> control_id;
    extern std::vector<viewer*> view;
    extern std::vector<std::string> view_id;
    extern std::vector<SDL_Surface*> surface;
    extern std::vector<std::string> surface_id;
    extern std::vector<Mix_Music*> music;
    extern std::vector<std::string> music_id;
    extern std::vector<Mix_Chunk*> sound;
    extern std::vector<std::string> sound_id;
    extern std::vector<TTF_Font*> font;
    extern std::vector<std::string> font_id;
}


class game_engine
{
    public:
//        int sound;
        game_engine(int width, int hieght);
        bool load(int width,int height,bool fullscreen, bool cursor);

        //load resource - addes resources to the engine, returns NULL on failure eg. missing file
        int load_font(std::string file, std::string id, int ptsize);
        int load_surface(std::string file, std::string id);
        int load_music(std::string file, std::string id);
        int load_sound(std::string file, std::string id);

        //get resource - seaches for resorce and returns, returns NULL if not found
        SDL_Surface * get_surface(unsigned int img_num);
        SDL_Surface * get_surface(std::string id);
        Mix_Music * get_music(unsigned int mus_num);
        Mix_Music * get_music(std::string id);
        Mix_Chunk * get_sound(unsigned int snd_num);
        Mix_Chunk * get_sound(std::string id);
        TTF_Font * get_font(unsigned int font_num);
        TTF_Font * get_font(std::string id);

        //get var
        std::string get_map_name();
        std::string get_map_description();
        int get_map_width();
        int get_map_height();
        long get_map_flags();

        // play

        bool play_music(std::string id,int loop=1);
        bool play_music(unsigned id,int loop=0);
        bool play_sound(std::string id, int loop=1);
        bool play_sound(unsigned id, int loop=0);

        SDL_Surface * render_text(std::string font, std::string texts, int fgR=255 , int fgG=255 , int fgB=255 , int fgA=255 ,int bgR=0 , int bgG=0 , int bgB=0 , int bgA=0 , textquality quality=solid);

        bool rect_collide(SDL_Rect a , SDL_Rect b);
        void * rect_collide_all(SDL_Rect rect,void * selfp,int number,void * ptr=NULL);

        bool update();
        void blit( float x, float y, SDL_Surface* source, bool free=0, bool no_move=0);
        bool event();
        virtual ~game_engine();

    protected:
    private:
        engine_state state;
        SDL_Surface * screen;


        //std::vector<game_map> map;

        SDL_Event * engine_event;

        int screen_width;
        int screen_height;
        SDL_PixelFormat * screen_format;

        game_map * map_data;

};

#endif // GAME_ENGINE_H
