/*
 * This file is part of GLShaderDev.
 *
 * GLShaderDev is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GLShaderDev is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GLShaderDev.  If not, see <http://www.gnu.org/licenses/>
 */

#ifndef MATH_HPP
#define MATH_HPP

#ifndef M_PI
#   define M_PI 3.14159265358979323846
#endif

inline float DegToRad(const float deg)
{
    return (deg * (2.0f * M_PI) / 360.0f);
}

inline float RadToDeg(const float rad)
{
    return (rad * 360.0f / (2.0f * M_PI));
}

#endif // MATH_HPP
