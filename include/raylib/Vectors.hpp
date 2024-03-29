/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** Vectors
*/

#pragma once

#include "Matrix.hpp"
#include "raymath.h"

Vector3 operator+(Vector3 lhs, const Vector3 &rhs)
{
    return Vector3Add(lhs, rhs);
}

Vector3 operator-(Vector3 lhs, const Vector3 &rhs)
{
    return Vector3Subtract(lhs, rhs);
}

Vector3 operator*(Vector3 lhs, const raylib::Matrix &mat)
{
    return Vector3Transform(lhs, mat.getMatrix());
}
