/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** 2D
*/

#pragma once

#include "raylib.h"
#include "ecs/World.hpp"
#include "ecs/System.hpp"
#include "raylib/Camera.hpp"

struct Position2D {
    float x;
    float y;

    Position2D() : x(0), y(0) {};
    Position2D(float x, float y) : x(x), y(y) {};
};

struct Hitbox2D {
    float width;
    float height;

    Hitbox2D() : width(0), height(0) {};
    Hitbox2D(float width, float height) : width(width), height(height) {};
};

struct Text2D {
    std::string text;
    Color color;
    uint fontSize;

    Text2D() : text(""), color(BLACK), fontSize(0) {};
    Text2D(const std::string &text, Color color = BLACK, uint fontSize = 24)
        : text(text), color(color), fontSize(fontSize) {};
};

struct Button2D {
    std::string text;
    Vector2 size;
    Color color;
    uint fontSize;

    Button2D() : text(""), size({0}), color(BLACK), fontSize(0) {};
    Button2D(const std::string &text, Vector2 size, Color color = BLACK, uint fontSize = 24)
        : text(text), size(size), color(color), fontSize(fontSize) {};
};

class DrawTextSystem : public ecs::ASystem {
    public:
    DrawTextSystem() { _stage = ecs::Stages::DRAW_HUD; };

    void setSignature(ecs::ComponentManager &component)
    {
        _signature = component.generateSignature<Position2D, Text2D>();
    }

    void update(ecs::World &world)
    {
        raylib::Camera &cam = world.getRessource<raylib::Camera>();

        for (ecs::Entity entity : _entities) {
            Position2D &pos = world.getComponent<Position2D>(entity);
            Text2D &text = world.getComponent<Text2D>(entity);

            DrawText(text.text.c_str(), pos.x, pos.y, text.fontSize, text.color);
        }
    }
};

class DrawButtonSystem : public ecs::ASystem {
    public:
    DrawButtonSystem() { _stage = ecs::Stages::DRAW_HUD; };

    void setSignature(ecs::ComponentManager &component)
    {
        _signature = component.generateSignature<Position2D, Button2D, Tint>();
    }

    void update(ecs::World &world)
    {
        raylib::Camera &cam = world.getRessource<raylib::Camera>();

        for (ecs::Entity entity : _entities) {
            Position2D &pos = world.getComponent<Position2D>(entity);
            Button2D &button = world.getComponent<Button2D>(entity);
            Tint &bkgdTint = world.getComponent<Tint>(entity);
            int textSize = MeasureText(button.text.c_str(), button.fontSize);

            DrawRectangle(pos.x, pos.y, button.size.x, button.size.y, bkgdTint);
            DrawText(button.text.c_str(), pos.x + button.size.x / 2 - textSize / 2,
            pos.y + button.size.y / 2 - button.fontSize / 2, button.fontSize, button.color);
        }
    }
};
