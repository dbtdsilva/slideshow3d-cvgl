/*
 * mathUtils.h
 *
 * Ficheiro cabecalho do modulo MATH_UTILS.
 *
 * Referencia: http://openglbook.com/the-book/chapter-4-entering-the-third-dimension/
 *
 *             Copyright (C) 2011 by Eddy Luten
 *
 *             Permission is hereby granted, free of charge, to any person obtaining a copy
 *	           of this software and associated documentation files (the "Software"), to deal
 *             in the Software without restriction, including without limitation the rights
 *             to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *             copies of the Software, and to permit persons to whom the Software is
 *             furnished to do so, subject to the following conditions:
 *
 *             The above copyright notice and this permission notice shall be included in
 *             all copies or substantial portions of the Software.
 *
 */


#ifndef _math_utils_h
#define _math_utils_h

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

static const double PI = 3.14159265358979323846;

typedef struct Matrix
{
	float m[16];
} mat4x4;

static const mat4x4 IDENTITY_MATRIX = { {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	}
};


float Cotangent(float angle);
float DegreesToRadians(float degrees);
float RadiansToDegrees(float radians);
float *multiplyPointByMatrix(const mat4x4 *m, const float *p);
float *multiplyVectorByMatrix(const mat4x4 *m, const float *v);
mat4x4 *MultiplyMatrices(const mat4x4 *m1, const mat4x4 *m2);
void RotateAboutX(mat4x4 *m, float angle);
void RotateAboutY(mat4x4 *m, float angle);
void RotateAboutZ(mat4x4 *m, float angle);
void Scale(mat4x4 *m, float x, float y, float z);
void Translate(mat4x4 *m, float x, float y, float z);
mat4x4 CreateProjectionMatrix(float fovy,
                              float aspect_ratio,
                              float near_plane,
                              float far_plane);
float *computeMidPoint(float *p1, float *p2);
float *addVector(float *v1, float *v2);
float *subtractVector(float *v1, float *v2);
float *computeSymmetricVector(float *v);
float computeVectorNorm(float *v);
float computeScalarProduct(float *v1, float *v2);
float *computeVectorProduct(float *v1, float *v2);
void convertToUnitVector(float *v);
float *computeUnitNormalToTriangle(float *arrayVertices);

#endif
