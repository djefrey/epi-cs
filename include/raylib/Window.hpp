/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** Window
*/

#pragma once

#include <string>
#include "raylib.h"

namespace raylib {
    class Window {
        public:
        Window(int width = 640, int height = 480, const std::string &name = "Indie Studio")
        {
            InitWindow(width, height, name.c_str());
        };

        ~Window()
        {
            CloseWindow();
        }

        void setTargetFPS(int fps)
        {
            SetTargetFPS(fps);
        }

        Vector2 getWindowSize()
        {
            return getWindowSize();
        }
    };
}
