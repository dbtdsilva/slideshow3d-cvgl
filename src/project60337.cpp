/*
 * project60337.cpp
 *
 * Ficheiro main
 *
 * Author: Diogo Silva (dbtds@ua.pt)
 *
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define GLEW_STATIC /* Necessario se houver problemas com a lib */
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "globals.hpp"
#include "callbacks.hpp"
#include "init.hpp"
#include "shaders/shaders.hpp"

int main(int argc, char **argv)
{
	if (argc != 2) {
		fprintf(stderr, "Invalid number of arguments\nUsage: ./slideshow3d imagesDir");
		exit(EXIT_FAILURE);
	} 
	GLenum glewInitResult;
	/* Inicializacao do GLUT */
	glutInit(&argc, argv);
	/* Inicializacao do GLEW */	
	inicializarJanela();
	glutHideWindow();
	glewInitResult = glewInit();
	if (GLEW_OK != glewInitResult)
	{
		fprintf(stderr, "ERROR: %s\n", glewGetErrorString(glewInitResult));
		exit(EXIT_FAILURE);
	}
	/* Qual a versao do OpenGL? */
	fprintf(stdout, "INFO: OpenGL Version: %s\n", glGetString(GL_VERSION));
	/* Inicializar o estado da aplicacao */
	
	inicializarEstado();
	/* Inicializar a cena */
	inicializarPlanoProjeccao();
	inicializarModelos(string(argv[1]));
	/* Inicializar os shaders */
	glutShowWindow();
	if (initResources() == 1) {
		/* Registando callback functions se OK */
		registarCallbackFunctions();
		fprintf(stdout, "\n Para Terminar: usar as teclas Q ou ESC\n\n");
		glutMainLoop();
	}
	/* Housekeeping */
	freeResources();
	libertarArraysGlobais();
	return EXIT_SUCCESS;
}
