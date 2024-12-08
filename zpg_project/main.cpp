/**
 * @file main.cpp
 *
 * @brief Main function
 *
 * @author Vojtěch Korduliak, kor0308
  **/
#include "Application.h"

int main(void)
{
    Application* app = new Application();

    app->initialization(); //OpenGL inicialization
    app->createScenes();
    app->run(); //Rendering 
}