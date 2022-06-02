/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** Text3D
*/

#include "ecs/components/Text3D.hpp"

#include "raylib.h"
#include "rlgl.h"

#include "raylib/Camera.hpp"
#include "raylib/Matrix.hpp"

void ecs::Draw3DTextSystem::drawText3D(const std::string &str, raylib::Font &font, float fontSize, float fontSpacing, Color color)
{
    int bytesProcessed = 0;
    float offset = 0;
    float scale = fontSize / ((float) font.getBaseSize());

    for (int i = 0; i < str.length();) {
        int codepoint = font.getCodepoint(&str.c_str()[i], &bytesProcessed);
        int glyphIndex = font.getGlyphIndex(codepoint);
        GlyphInfo &glyph = font.getGlyph(glyphIndex);

        if (codepoint != ' ' && codepoint != '\t' && codepoint != '\n')
            drawTextCodepoint3D(codepoint, font, offset, fontSize, color);

        if (glyph.advanceX == 0)
            offset += (fontSpacing + font.getRect(glyphIndex).width) / (float) font.getBaseSize() * scale;
        else
            offset += (fontSpacing + glyph.advanceX) / (float) font.getBaseSize() * scale;

        i += bytesProcessed;
    }
}

void ecs::Draw3DTextSystem::drawTextCodepoint3D(int codepoint, raylib::Font &font, float offset, float fontSize, Color color)
{
    int glyphIndex = font.getGlyphIndex(codepoint);
    GlyphInfo &glyph = font.getGlyph(glyphIndex);
    Rectangle rect = font.getRect(glyphIndex);

    float scale = fontSize / ((float) font.getBaseSize());
    offset += (glyph.offsetX - font.getPadding()) / (float) font.getBaseSize() * scale;

    Rectangle srcRec = {rect.x - font.getPadding(), rect.y - font.getPadding(),
    rect.width + 2 * font.getPadding(), rect.height + 2 * font.getPadding()};

    float width = rect.width / (float) font.getBaseSize() * scale;
    float height = rect.height / (float) font.getBaseSize() * scale;
    raylib::Texture texture = font.getTexture();

    float tx = srcRec.x / (float) texture.getWidth();
    float ty = (srcRec.y + srcRec.height) / (float) texture.getHeight();
    float tw = (srcRec.x + srcRec.width) / (float) texture.getWidth();
    float th = srcRec.y / (float) texture.getHeight();

    rlCheckRenderBatchLimit(8);
    rlSetTexture(texture.getTexture().id);

    rlPushMatrix();
    rlBegin(RL_QUADS);

    rlColor4ub(color.r, color.g, color.b, color.a);

    rlNormal3f(0.0f, 0.0f, 1.0f);

    rlTexCoord2f(tx, ty);
    rlVertex3f(offset, 0, 0);

    rlTexCoord2f(tx, th);
    rlVertex3f(offset, height, 0);

    rlTexCoord2f(tw, th);
    rlVertex3f(offset + width, height, 0);

    rlTexCoord2f(tw, ty);
    rlVertex3f(offset + width, 0, 0);

    rlNormal3f(0.0f, 0.0f, -1.0f);

    rlTexCoord2f(tx, ty);
    rlVertex3f(offset, 0, 0);

    rlTexCoord2f(tw, ty);
    rlVertex3f(offset + width, 0, 0);

    rlTexCoord2f(tw, th);
    rlVertex3f(offset + width, height, 0);

    rlTexCoord2f(tx, th);
    rlVertex3f(offset, height, 0);

    rlEnd();
    rlPopMatrix();

    rlSetTexture(0);
}

void ecs::Draw3DTextSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<Transform, Text3D, FontRef>();
}

void ecs::Draw3DTextSystem::update(ecs::World &world)
{
    raylib::Camera &cam = world.getRessource<raylib::Camera>();

    cam.begin3DMode();
    for (ecs::Entity entity : _entities) {
        Transform &transform = world.getComponent<Transform>(entity);
        Text3D &text = world.getComponent<Text3D>(entity);
        FontRef &font = world.getComponent<FontRef>(entity);
        raylib::Matrix mat = raylib::Matrix::fromTransform(transform) * raylib::Matrix::fromTranslate(text.offset);

        rlPushMatrix();
        rlMultMatrixf(mat.getValues().v);
        drawText3D(text.text, *font.font, text.fontSize, text.fontSpacing, text.color);
        rlPopMatrix();
    }
    cam.end3DMode();
}
