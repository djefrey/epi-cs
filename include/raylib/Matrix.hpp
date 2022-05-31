/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** Matrix
*/

#pragma once

#include "raymath.h"

namespace raylib {
    using RaylibMatrix = ::Matrix;

    class Matrix {
        RaylibMatrix _mat;

        public:
        Matrix() : _mat(MatrixIdentity()) {};
        Matrix(const RaylibMatrix &mat) : _mat(mat) {};

        static Matrix fromTranslate(Vector3 &translate)
        {
            return Matrix(MatrixTranslate(translate.x, translate.y, translate.z));
        }

        static Matrix fromQuaternion(Quaternion &quat)
        {
            return Matrix(QuaternionToMatrix(quat));
        }

        static Matrix fromScale(Vector3 &scale)
        {
            return Matrix(MatrixScale(scale.x, scale.y, scale.z));
        }

        Matrix &operator*(const Matrix &other)
        {
            _mat = MatrixMultiply(_mat, other._mat);
            return *this;
        }

        const RaylibMatrix &getMatrix() const
        {
            return _mat;
        }
    };
}
