#ifndef GAME_CLIENT_SDLUTIL_H
#define GAME_CLIENT_SDLUTIL_H

#include <iostream>
#include <string>
#include <SDL.h>

std::string getResourcePath(const std::string &subDir = "")
{
    // The location of the base resource path.
    // Static because calling SDL_GetBasePath() is expensive.
    static std::string baseResourcePath;

    if (baseResourcePath.empty())
    {
        // SDL_GetBasePath returns NULL if something goes wrong
        char *basePath = SDL_GetBasePath();
        if (basePath)
        {
            baseResourcePath = basePath;
            SDL_free(basePath);
        }
        else
        {
            std::cerr << "SDL_GetBasePath Error: " << SDL_GetError() << std::endl;
            return "";
        }

        size_t pos = baseResourcePath.rfind("build");
        baseResourcePath = baseResourcePath.substr(0, pos) + "resources/";
    }

    // If a subdirectory is specified, append it
    if (subDir.empty())
    {
        return baseResourcePath;
    }
    else
    {
        return baseResourcePath + subDir + "/";
    }
}

#endif //GAME_CLIENT_SDLUTIL_H
