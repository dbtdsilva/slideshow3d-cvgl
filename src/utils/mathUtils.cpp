/*
 * mathUtils.c
 *
 * Ficheiro de implementacao do modulo MATH_UTILS.
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

#include <math.h>
#include <string.h>
#include "mathUtils.hpp"


/* PARA AS TRANSFORMACOES */


float Cotangent(float angle)
{
	return (float)(1.0 / tan(angle));
}

float DegreesToRadians(float degrees)
{
	return degrees * (float)(PI / 180.0);
}


float RadiansToDegrees(float radians)
{
	return radians * (float)(180.0 / PI);
}


float *multiplyPointByMatrix(const mat4x4 *m, const float *p)
{
	unsigned int row;
	float point[4];
	float *res = (float *) calloc(4, sizeof(float));
	for (row = 0; row < 3; row++)
	{
		point[row] = p[row];
	}
	point[3] = 1.0;
	for (row = 0; row < 4; ++row)
	{
		res[row] = m->m[row + 0]  * point[0] +
				   m->m[row + 4]  * point[1] +
				   m->m[row + 8]  * point[2] +
				   m->m[row + 12] * point[3];
	}
	return res;
}


float *multiplyVectorByMatrix(const mat4x4 *m, const float *v)
{
	unsigned int row;
	float vector[4];
	float *res = (float *) calloc(4, sizeof(float));
	for (row = 0; row < 3; row++)
	{
		vector[row] = v[row];
	}
	vector[3] = 0.0;
	for (row = 0; row < 4; ++row)
	{
		res[row] = m->m[row + 0]  * vector[0] +
				   m->m[row + 4]  * vector[1] +
				   m->m[row + 8]  * vector[2] +
				   m->m[row + 12] * vector[3];  // Dispensavel !!
	}
	return res;
}


mat4x4 *MultiplyMatrices(const mat4x4 *m1, const mat4x4 *m2)
{
	unsigned int row, column;
	mat4x4 *out = (mat4x4 *) malloc(sizeof(struct Matrix));
	for (row = 0; row < 4; ++row)
		for (column = 0; column < 4; ++column)
			/* Correccao para multiplicar a direita - J. Madeira */
			out->m[column * 4 + row] =
				(m1->m[row + 0] * m2->m[column * 4 + 0]) +
				(m1->m[row + 4] * m2->m[column * 4 + 1]) +
				(m1->m[row + 8] * m2->m[column * 4 + 2]) +
				(m1->m[row + 12] * m2->m[column * 4 + 3]);
	return out;
}


void RotateAboutX(mat4x4 *m, float angle)
{
	mat4x4 rotation = IDENTITY_MATRIX;
	float sine = (float)sin(angle);
	float cosine = (float)cos(angle);
	rotation.m[5] = cosine;
	rotation.m[6] = sine;
	rotation.m[9] = -sine;
	rotation.m[10] = cosine;

	mat4x4 *out = MultiplyMatrices(m, &rotation);
	memcpy(m->m, out->m, sizeof(m->m));
	free(out);
}


void RotateAboutY(mat4x4 *m, float angle)
{
	mat4x4 rotation = IDENTITY_MATRIX;
	float sine = (float)sin(angle);
	float cosine = (float)cos(angle);
	rotation.m[0] = cosine;
	rotation.m[8] = sine;
	rotation.m[2] = -sine;
	rotation.m[10] = cosine;

	mat4x4 *out = MultiplyMatrices(m, &rotation);
	memcpy(m->m, out->m, sizeof(m->m));
	free(out);
}


void RotateAboutZ(mat4x4 *m, float angle)
{
	mat4x4 rotation = IDENTITY_MATRIX;
	float sine = (float)sin(angle);
	float cosine = (float)cos(angle);
	rotation.m[0] = cosine;
	rotation.m[1] = sine;
	rotation.m[4] = -sine;
	rotation.m[5] = cosine;

	mat4x4 *out = MultiplyMatrices(m, &rotation);
	memcpy(m->m, out->m, sizeof(m->m));
	free(out);
}


void Scale(mat4x4 *m, float x, float y, float z)
{
	mat4x4 scale = IDENTITY_MATRIX;
	scale.m[0] = x;
	scale.m[5] = y;
	scale.m[10] = z;

	mat4x4 *out = MultiplyMatrices(m, &scale);
	memcpy(m->m, out->m, sizeof(m->m));
	free(out);	
}


void Translate(mat4x4 *m, float x, float y, float z)
{
	mat4x4 translation = IDENTITY_MATRIX;
	translation.m[12] = x;
	translation.m[13] = y;
	translation.m[14] = z;
	
	mat4x4 *out = MultiplyMatrices(m, &translation);
	memcpy(m->m, out->m, sizeof(m->m));
	free(out);
}


mat4x4 CreateProjectionMatrix(float fovy,
							  float aspect_ratio,
							  float near_plane,
							  float far_plane)
{
	mat4x4 out = { { 0 } };
	const float y_scale = Cotangent(DegreesToRadians(fovy / 2));
	const float x_scale = y_scale / aspect_ratio;
	const float frustum_length = far_plane - near_plane;
	out.m[0] = x_scale;
	out.m[5] = y_scale;
	out.m[10] = (-(far_plane + near_plane) / frustum_length);
	out.m[11] = -1;
	out.m[14] = ((-2 * near_plane * far_plane) / frustum_length);
	return out;
}


/* PARA O REFINAMENTO DE MODELOS */


float *computeMidPoint(float *p1, float *p2)
{
	float *res = (float *) calloc(3, sizeof(float));
	res[0] = (p1[0] + p2[0]) / 2.0;
	res[1] = (p1[1] + p2[1]) / 2.0;
	res[2] = (p1[2] + p2[2]) / 2.0;
	return res;
}


float *addVector(float *v1, float *v2)
{
	int i;
	float *res = (float *) calloc(3, sizeof(float));
	for (i = 0; i < 3; i++)
	{
		res[i] = v1[i] + v2[i];
	}
	return res;
}


float *subtractVector(float *v1, float *v2)
{
	int i;
	float *res = (float *) calloc(3, sizeof(float));
	for (i = 0; i < 3; i++)
	{
		res[i] = v1[i] - v2[i];
	}
	return res;
}


float *computeSymmetricVector(float *v)
{
	int i;
	float *res = (float *) calloc(3, sizeof(float));
	for (i = 0; i < 3; i++)
	{
		res[i] = - v[i];
	}
	return res;
}

float computeVectorNorm(float *v)
{
	float aux = 0.0;
	int i;
	for (i = 0; i < 3; i++)
		aux += v[i] * v[i];
	return sqrt(aux);
}


float computeScalarProduct(float *v1, float *v2)
{
	int i;
	float res = 0;
	for (i = 0; i < 3; i++)
	{
		res += v1[i] * v2[i];
	}
	return res;
}


float *computeVectorProduct(float *v1, float *v2)
{
	float *res = (float *) calloc(3, sizeof(float));
	res[0] = v1[1] * v2[2] - v1[2] * v2[1];
	res[1] = - (v1[0] * v2[2] - v1[2] * v2[0]);
	res[2] = v1[0] * v2[1] - v1[1] * v2[0];
	return res;
}


void convertToUnitVector(float *v)
{
	float norm = computeVectorNorm(v);
	int i;
	if (norm > 0.0)
	{
		for (i = 0; i < 3; i++)
			v[i] /= norm;
	}
}


float *computeUnitNormalToTriangle(float *arrayVertices)
{
	float v1[3];
	float v2[3];
	float *result;
	float *p0 = arrayVertices;
	float *p1 = arrayVertices + 3;
	float *p2 = arrayVertices + 6;
	v1[0] = p1[0] - p0[0];
	v1[1] = p1[1] - p0[1];
	v1[2] = p1[2] - p0[2];
	v2[0] = p2[0] - p0[0];
	v2[1] = p2[1] - p0[1];
	v2[2] = p2[2] - p0[2];
	result = computeVectorProduct(v1, v2);
	convertToUnitVector(result);
	return result;
}


