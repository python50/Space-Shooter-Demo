/**
 ** Code Copyright (C) 2011 Jason White <whitewaterssoftwareinfo@gmail.com>
 **                         White Waters Software - http://wwsoft.co.cc
 **
 ** modifying, copying and distribution of this source is prohibited without
 ** explicit authorization by the copyright holder: Jason White
 **/

extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

#include "algorithm"


#include "game_engine.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "error.h"
#include "math.h"
#include "game_math.h"
#include "main.h"
#include "ship.h"
#include "hud.h"
#include "astroid.h"
#include "misc.h"
#include <stdlib.h>
#include "SDL_rotozoom.h"
#include "tile.h"
#include "lua_object.h"
#include "map_parser.h"

namespace view
{
    int x=0;
    int y=0;
    int scale_width=0;
    int scale_height=0;
    int width=0;
    int height=0;
    int target_width=0;
    int target_height=0;
}

namespace play_area
{
    double scale=0;
    int scale_width=0;
    int scale_height=0;
    int width=0;
    int height=0;
}

namespace game
{
    int lives=0;
    bool pause=0;
    bool reset=0;
    bool over=0;
}

namespace global_lua
{
    lua_State * lua;
}

namespace resources
{
        std::vector< ::controller*> control;
        std::vector<std::string> control_id;
        std::vector<viewer*> view;
        std::vector<std::string> view_id;
        std::vector<SDL_Surface*> surface;
        std::vector<std::string> surface_id;
        std::vector<Mix_Music*> music;
        std::vector<std::string> music_id;
        std::vector<Mix_Chunk*> sound;
        std::vector<std::string> sound_id;
        std::vector<TTF_Font*> font;
        std::vector<std::string> font_id;
}


game_engine::game_engine(int width,int height)
{
    state=UNINITED;
}

bool game_engine::load(int width,int height,bool fullscreen, bool cursor)
{
    atexit(SDL_Quit);

    screen_width=width;
    screen_height=height;

    view::x=0;
    view::y=0;
    view::width=width;
    view::height=height;
    view::target_width=320;
    view::target_height=240;
    view::scale_width=(view::width/view::target_width);
    view::scale_height=(view::height/view::target_height);

    play_area::scale=(double) (view::width/view::target_width);

    play_area::width=640;
    play_area::height=480;
    play_area::scale_width=play_area::width*play_area::scale;//*(view::width/view::target_width);
    play_area::scale_height=play_area::height*play_area::scale;//*(view::height/view::target_height);


    if ( SDL_Init( SDL_INIT_EVERYTHING) < 0 )
    {
        std::string errorm="Unable to init SDL: ";
        new error(FATAL_ERROR,errorm+SDL_GetError());
        state=ERRORS;
        return 0;
    }

    if (fullscreen)
        screen = SDL_SetVideoMode(width, height, 32,SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
    else
        screen = SDL_SetVideoMode(width, height, 32,SDL_HWSURFACE|SDL_DOUBLEBUF);

    if (screen==NULL)
    {
        std::string errorm="Unable to create window: ";
        new error(FATAL_ERROR,errorm+SDL_GetError());
        state=ERRORS;
        return 0;
    }

    new error(INFO_H,"New window created: "+convert_int_string(screen_width)+" "+convert_int_string(screen_height)+"");

    screen_format=screen->format;

    if (Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,1024)<0)
    {
        new error(FATAL_ERROR,"Unable to init SDL_Mixer");
        state=ERRORS;
        return 0;
    }

    //Mix_Volume(-1,0);;

    TTF_Init();

    SDL_ShowCursor(cursor);

    load_sound("data/sound/beep0.ogg","beep0");
    load_sound("data/sound/beep1.ogg","beep1");
    load_sound("data/sound/beep1_short.ogg","beep1_short");
    load_sound("data/sound/thud_0.ogg","thud_0");

    load_font("data/font/JuraMedium.ttf","jura_medium-24",scale_value(24));
    load_font("data/font/JuraMedium.ttf","jura_medium-12",scale_value(14));

    gmath_randomize();

    load_surface("data/image/ship0.png","ship0.png");

    load_surface("data/image/ship0_0.png" ,"ship0_0.png");
    load_surface("data/image/ship0_1.png" ,"ship0_1.png");
    load_surface("data/image/ship0_2.png" ,"ship0_2.png");
    load_surface("data/image/ship0_3.png" ,"ship0_3.png");
    load_surface("data/image/ship0_4.png" ,"ship0_4.png");
    load_surface("data/image/ship0_5.png" ,"ship0_5.png");
    load_surface("data/image/ship0_6.png" ,"ship0_6.png");
    load_surface("data/image/ship0_7.png" ,"ship0_7.png");
    load_surface("data/image/ship0_8.png" ,"ship0_8.png");
    load_surface("data/image/ship0_9.png" ,"ship0_9.png");
    load_surface("data/image/ship0_10.png","ship0_10.png");
    load_surface("data/image/ship0_11.png","ship0_11.png");
    load_surface("data/image/ship0_12.png","ship0_12.png");
    load_surface("data/image/ship0_13.png","ship0_13.png");
    load_surface("data/image/ship0_14.png","ship0_14.png");
    load_surface("data/image/ship0_15.png","ship0_15.png");

    load_surface("data/image/tile0.png","tile0.png");
    load_surface("data/image/starfield.png","starfield.png");
    load_surface("data/image/filled.png","filled.png");

    load_surface("data/image/drawing-2.png","hud0");

    load_surface("data/image/ship1.png","ship1");
    load_surface("data/image/shot0.png","shot0.png");
    load_surface("data/image/astroid0.png","astroid0.png");

    engine_event = new SDL_Event();

    //controller.push_back(new ship());
    //load_font("daya/lib-mono-regular.ttf","mono-regular-8",8);
;
    std::cout << "SCALE VALUE:" << scale_value(240) << " " << scale_value(320) << "\n" ;
/*    for (int y=0;y < play_area::scale_height;y+=scale_value(240))
    {
        for (int x=0;x < play_area::scale_width;x+=scale_value(320))
        {
            std::cout << x << " [] " << y << "\n";
            resources::control.push_back(new tile(this,x,y,"starfield.png"));
        }
    }
//gmath_random(,256)

    for (int i=0;i < 24;i++)
        resources::control.push_back(new astroid(this));

    resources::control.push_back(new ship(this,32,32));

    resources::control.push_back(new hud(this));*/
    //resources::control.push_back(new lua_object(this,"./object.lua"));

    map_parser parser(this,"map.lua");//data/maps/map.lua");

    game_map tmp_map;
    tmp_map.width=width;
    tmp_map.height=height;
    tmp_map.name="";
    tmp_map.description="";
    tmp_map.flags=0;

    map_data=&tmp_map;

    global_lua::lua=lua_open();
    luaL_openlibs(global_lua::lua);

    state=RUNNING;
    return 1;
}


int game_engine::load_font(std::string file, std::string id, int ptsize)
{
    char * cstr = new char [file.size()+1];
    strcpy (cstr, file.c_str());

    TTF_Font *font_file;
    font_file=TTF_OpenFont(cstr, ptsize);

    if (!font_file)
    {
        delete[] cstr;
        return NULL;//throw (string) TTF_GetError();
    }

    resources::font.push_back(font_file);
    resources::font_id.push_back(id);
//        if (DEBUG_LEVEL > 1)
//            cout <<  "Event: Font Loaded, " << file << " ID " << id << " Added, Index " << sge::resource::font.size()-1 << "\n";
    delete[] cstr;
    return 1;
    //}
    /*catch(string str)
    {
        cout << "ERROR [FONT LOAD]: " << str << endl;

        //if (DEBUG_LEVEL > 0)
        //    cout << "WARNING: THIS CAN CAUSE A CRASH" << endl;
    }*/

    return 0;
}

int game_engine::load_music(std::string file, std::string id)
{

    //file=sge::var::data_dir+"music/"+file;
    char * cstr = new char [file.size()+1];
    strcpy (cstr, file.c_str());

    Mix_Music *musics;
    musics=Mix_LoadMUS(cstr);
    if (!musics)
    {
        delete[] cstr;
        return 0;//throw Mix_GetError();
    }

    resources::music.push_back(musics);
    resources::music_id.push_back(id);
//        if (DEBUG_LEVEL > 1)
//            cout <<  "Event: Music Loaded, " <<file << " ID " << id << " Added, Index " << sge::resource::music.size()-1 << "\n";
    delete[] cstr;
    return 1;
    /*}
    catch(string str)
    {
        cout << "ERROR [MUSIC LOAD]: " << str << endl;

        if (DEBUG_LEVEL > 0)
            cout << "WARNING: THIS CAN CAUSE A CRASH" << endl;

    }*/

    return 0;
}


int game_engine::load_surface(std::string file, std::string id)
{

    char * cstr = new char [file.size()+1];
    strcpy (cstr, file.c_str());

    SDL_Surface *image;
    image=IMG_Load(cstr);

    if (!image)
    {
        delete[] cstr;
        return NULL;//throw IMG_GetError();
    }

    //if (colorkey==1)
    //{
    //    long colorkey = SDL_MapRGB(sge::var::format, 255, 0, 255);
    //    SDL_SetColorKey(image, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    //}

    //if (colorkey==1)
    //    surface.push_back(SDL_DisplayFormat(image));
    //else

    image=zoomSurface(image, (double) view::width/view::target_width, (double) view::height/view::target_height, 0);
    resources::surface.push_back(SDL_DisplayFormatAlpha(image));

    resources::surface_id.push_back(id);

    //if (DEBUG_LEVEL > 1)
    //    cout <<  "Event: Image Loaded, " <<file << " ID " << id << " Added, Index " << sge::resource::image.size()-1 << "\n";

    delete[] cstr;
    return 1;
    /*}
    catch(string str)
    {
        cout << "ERROR [IMAGE LOAD]: " << str << endl;

        if (DEBUG_LEVEL > 0)
            cout << "WARNING: THIS CAN CAUSE A CRASH" << endl;
    }*/
}

int game_engine::load_sound(std::string file, std::string id)
{
    //try
    //{
    //file=sge::var::data_dir+"sound/"+file;
    char * cstr = new char [file.size()+1];
    strcpy (cstr, file.c_str());

    Mix_Chunk * sounds;
    sounds=Mix_LoadWAV(cstr);
    if (!sounds)
    {
        std::cout << "sound load error\n";
        delete[] cstr;
        return 0;//throw Mix_GetError();
    }


    resources::sound.push_back(sounds);
    resources::sound_id.push_back(id);

    //if (DEBUG_LEVEL > 1)
    //    cout <<  "Event: Sound Loaded, " << file << " ID " << id << " Added, Index " << sge::resource::sound.size()-1 << "\n";

    delete[] cstr;
    return 1;//sge::resource::sound.size()+1;
    /*}
    catch(string str)
    {
        cout << "ERROR [SOUND LOAD]: " << str << endl;

        if (DEBUG_LEVEL > 0)
            cout << "WARNING: THIS CAN CAUSE A CRASH" << endl;
    }*/

    return 0;
}

/** Get Functions **/

SDL_Surface * game_engine::get_surface(unsigned int img_num)
{
    if ( ((unsigned int) resources::surface_id.size()-1) >= img_num and ((unsigned int) resources::surface.size()-1) >= img_num)
    {
        return resources::surface.at(img_num);
    }
    else
        return NULL ;//SDL_CreateRGBSurface(SDL_HWSURFACE, 32, 32, 32, 0, 0, 0, 0xFFFFFFFF); //32x32, 32 bit black square
}

SDL_Surface * game_engine::get_surface(std::string id)
{
    for (unsigned int i=0; i <= resources::surface_id.size(); i+=1)
    {
        if (resources::surface_id.at(i)==id)
        {

            if ((resources::surface.size()-1) >= i)
                return resources::surface.at(i);
        }
    }

    return NULL;
}

Mix_Music * game_engine::get_music(unsigned int mus_num)
{

    if ( ((unsigned int)resources::music_id.size()-1) >= mus_num and ((unsigned int)resources::music.size()-1))
    {
        return resources::music.at(mus_num);
    }
    else
        return NULL;
}

Mix_Music * game_engine::get_music(std::string id)
{
    for(unsigned int i=0; i <= resources::music_id.size(); i+=1)
    {
        if (resources::music_id.at(i)==id)
        {
            if ((resources::music.size()-1) >= i)
                return resources::music.at(i);
        }
    }

    return NULL;
}


Mix_Chunk * game_engine::get_sound(unsigned int snd_num)
{
    if ( ((unsigned int)resources::sound_id.size()-1) >= snd_num and ((unsigned int)resources::sound.size()-1) >= snd_num)
    {
        return resources::sound.at(snd_num);
    }
    else
        return NULL;
}

Mix_Chunk * game_engine::get_sound(std::string id)
{
    for(unsigned int i=0; i <= resources::sound_id.size(); i+=1)
    {
        if (resources::sound_id.at(i)==id)
        {
            if ((resources::sound.size()-1) >= i)
                return resources::sound.at(i);
        }
    }

    return NULL;
}

TTF_Font * game_engine::get_font(unsigned int font_num)
{
    if ( ((unsigned int)resources::font_id.size()-1) >= font_num and ((unsigned int)resources::font.size()-1) >= font_num)
    {
        return resources::font.at(font_num);
    }
    else
        return NULL;
}


TTF_Font * game_engine::get_font(std::string id)
{
    for(unsigned int i=0; i <= resources::font_id.size(); i+=1)
    {
        if (resources::font_id.size()==0)
            break;

        if (resources::font_id.at(i)==id)
        {
            if ((resources::font.size()-1) >= i)
                return resources::font.at(i);
        }
    }

    return NULL;
}

/** misc get**/

bool load_map(std::string)
{
    for (int i=0; i < resources::control.size();i++)
    {
        controller * ctrl=resources::control.at(i);
        if (ctrl->persistant==0)
        {
            ctrl->~controller();
            resources::control.erase(resources::control.begin()+i);
            //resources::control_id.erase(resources::control_id.begin()+i);
        }

    }
}

double game_engine::scale_value(double value)
{
    return value* play_area::scale;
}

/** update **/

/*template<typename Object>

struct PointerComp
{
    bool operator()(const Object* obj1, const Object* obj2)const
    {
        return obj1->z < obj2->z;
    }
};

*/

/**
    implemented Z buffering !!!
**/

bool sort_control(controller *obj1, controller * obj2)
{
    if (obj1==NULL || obj2==NULL)
        return NULL;

    return obj1->z > obj2->z;
}

bool game_engine::update()
{
    if (!state==RUNNING)
        return 0;

    if (event()==0)
        return 0;

    SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

    if (!resources::control.size()==0)
        std::sort(resources::control.begin(),resources::control.end(),sort_control);

    std::vector<controller *> new_control2;

    for (unsigned int i=0; i <= resources::control.size()-1; i++)
    {
        if (resources::control.size()==0)
            break;

        if (resources::control.at(i)==NULL)
            continue;
        //new error(INFO_HIGH,"Control"+convert_int_string(i));
        //std::cout << resources::control.at(i) <<"\n";
        resources::control.at(i)->update();//this);

        if (resources::control.at(i)->delete_this)
        {
            resources::control.at(i)->~controller();
            resources::control.at(i)=NULL;
        }

        new_control2.push_back(resources::control.at(i));
    }

    resources::control.swap(new_control2);

    //for (unsigned int i=0; i < resources::view.size(); i++)
    //{
        //view.at(i)->draw();
    // }

    std::vector<controller *> new_control;

    if (game::reset)
    {
        for (unsigned int ii=0; ii <= resources::control.size()-1; ii++)
        {

            resources::control.at(ii)->reset();

            std::cout << ii << " " << resources::control.at(ii)->id_type << " " <<  resources::control.at(ii)->delete_this;

            /**
                NOTE: Make note in git commit about increased efficeny in object execution loop
            **/

            if (resources::control.at(ii)->delete_this)
            {
                std::cout << " deleted\n";
                resources::control.at(ii)->~controller();
            }
            else
            {
                new_control.push_back(resources::control.at(ii));
            }
        }

        resources::control.swap(new_control);

        game::reset=false;
        for (int i=0;i < 10;i++)
            resources::control.push_back(new astroid(this));
    }

    //blit(320-56,0,get_surface("hud0.png"),0,1);


    SDL_Flip(screen);
    return 1;
}

// Play_<item>
bool game_engine::play_music(std::string id,int loop)
{
    return Mix_PlayMusic(get_music(id),loop)+1; // return 0 on error, 1 otherwise
}

bool game_engine::play_music(unsigned id,int loop)
{
    return Mix_PlayMusic(get_music(id),loop)+1;
}

bool game_engine::play_sound(std::string id,int loop)
{
    return Mix_PlayChannel(-1,get_sound(id),loop)+1;
}

bool game_engine::play_sound(unsigned id, int loop)
{
    return Mix_PlayChannel(-1,get_sound(id),loop)+1;
}

SDL_Surface * game_engine::render_text(std::string font, std::string texts, int fgR , int fgG , int fgB , int fgA ,int bgR , int bgG , int bgB , int bgA , textquality quality)
{
    TTF_Font * fonttodraw=get_font(font);

    if (fonttodraw==NULL)
        return SDL_CreateRGBSurface(0x00000000,1,1,32,0,0,0,0); //depth argument must be fixed to change with diffrenent screen bit depths

    char * text = new char [texts.size()+1];
    strcpy (text, texts.c_str());

    SDL_Color tmpfontcolor = {fgR,fgG,fgB,fgA};
    SDL_Color tmpfontbgcolor = {bgR, bgG, bgB, bgA};
    SDL_Surface *resulting_text;

    if (quality == solid) resulting_text = TTF_RenderText_Solid(fonttodraw, text, tmpfontcolor);
    else if (quality == shaded) resulting_text = TTF_RenderText_Shaded(fonttodraw, text, tmpfontcolor, tmpfontbgcolor);
    else if (quality == blended) resulting_text = TTF_RenderText_Blended(fonttodraw, text, tmpfontcolor);

    return resulting_text;
}

void game_engine::blit( float x, float y, SDL_Surface* source, bool free, bool no_move)
{
    SDL_Rect rect;
    if (no_move)
    {
        rect.x=round(x);
        rect.y=round(y);
    }
    else
    {
        rect.x=round(x)-view::x;
        rect.y=round(y)-view::y;
    }

    SDL_BlitSurface(source, 0, screen, &rect);

    if (free)
        SDL_FreeSurface(source);
}


bool game_engine::event()
{
    while (SDL_PollEvent(engine_event))
    {
        switch (engine_event->type)
        {
        case SDL_QUIT:
        {
            return 0;
            break;
        }

        case SDL_KEYDOWN:
        {
            if (engine_event->key.keysym.sym == SDLK_ESCAPE)
            {
                return 0;
                break;
            }

            if (engine_event->key.keysym.sym == SDLK_q)
            {
                return 0;
                break;
            }


            if (engine_event->key.keysym.sym == SDLK_PRINT)
            {
                /*time_t rawtime;
                time ( &rawtime );
                string stimes="./data/screenshots/screen"+convertintstr(rawtime)+" "+convertintstr(drip_random(0,99999))+".bmp";
                SDL_SaveBMP(screen, stimes.c_str());
                cout << "Screenshot: " << stimes << " added\n";*/
            }

            if (engine_event->key.keysym.sym == SDLK_PAUSE)
            {
                break;
            }

        }
        }
    }

    return 1;
}

game_engine::~game_engine()
{
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
}
