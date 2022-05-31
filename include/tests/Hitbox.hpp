/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** Hitbox
*/

#pragma once

#include "raylib.h"
#include "raymath.h"

struct Hitbox
{
    Vector3 min;
    Vector3 max;

    Hitbox() : min({ 0 }), max({ 0 }) {};
    Hitbox(Vector3 min, Vector3 max) : min(min), max(max) {};

    BoundingBox getBoundingBox(Transform &transform)
    {
        Matrix mat = MatrixTranslate(transform.translation.x, transform.translation.y, transform.translation.z);
        mat = MatrixMultiply(mat, QuaternionToMatrix(transform.rotation));
        mat = MatrixMultiply(mat, MatrixScale(transform.scale.x, transform.scale.y, transform.scale.z));

        return BoundingBox { Vector3Transform(min, mat), Vector3Transform(max, mat) };
    };
};
