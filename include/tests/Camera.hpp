/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** Camera
*/

#pragma once

#include "raylib/raylib.h"

namespace raylib {
    class Camera {
        Camera3D _cam;

        public:
            Camera()
            {
                _cam.position.x = 0.0f;
                _cam.position.y = 3.0f;
                _cam.position.z = -3.0f;

                _cam.target.x = 0.0f;
                _cam.target.y = 1.0f;
                _cam.target.z = 0.0f;

                _cam.up.x = 0.0f;
                _cam.up.y = 1.0f;
                _cam.up.z = 0.0f;

                _cam.fovy = 80.0f;
            };

            Vector3 getPosition() { return _cam.position; };
            void setPosition(Vector3 pos) { _cam.position = pos; };
            void translate(Vector3 vec)
            {
                _cam.position.x += vec.x;
                _cam.position.y += vec.y;
                _cam.position.z += vec.z;
            }

            Vector3 getTarget() { return _cam.target; };
            void setTarget(Vector3 target) { _cam.target = target; };

            void begin3DMode() { BeginMode3D(_cam); }
            void end3DMode() { EndMode3D(); }

        protected:
        private:
    };
}
