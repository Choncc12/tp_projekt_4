#include "planar_quadrotor_visualizer.h"

PlanarQuadrotorVisualizer::PlanarQuadrotorVisualizer(PlanarQuadrotor *quadrotor_ptr): quadrotor_ptr(quadrotor_ptr) {}

/**
 * TODO: Improve visualizetion
 * 1. Transform coordinates from quadrotor frame to image frame so the circle is in the middle of the screen
 * 2. Use more shapes to represent quadrotor (e.x. try replicate http://underactuated.mit.edu/acrobot.html#section3 or do something prettier)
 * 3. Animate proppelers (extra points)
 */
void PlanarQuadrotorVisualizer::render(std::shared_ptr<SDL_Renderer> &gRenderer) {
    Eigen::VectorXf state = quadrotor_ptr->GetState();
    float q_x, q_y, q_theta;

    /* x, y, theta coordinates */
    /*ulepszyć tak aby nie trzeba było jeszcze raz deklarować w simulate.cpp*/
    const int SCREEN_WIDTH = 1280; 
    const int SCREEN_HEIGHT = 720;

    q_x = state[0]+(0.5*SCREEN_WIDTH);
    q_y = state[1]+(0.5*SCREEN_HEIGHT);
    q_theta = state[2];
    //przerobić na prostokąt, brać rotacje
    SDL_Texture* tekstura = SDL_CreateTexture(gRenderer.get(), SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 30, 10);
    SDL_Rect bodydron; //kształt i lokacja ciała drona
    bodydron.w = 60;
    bodydron.h = 20;
    bodydron.x = q_x - (bodydron.w/2);
    bodydron.y = q_y - (bodydron.h/2);
    SDL_Point srodek = {bodydron.w/2,bodydron.h/2}; //srodek ciala drona
    
    SDL_Rect wirnikl; //kształt i lokacja wirnika drona
    wirnikl.w = 20;
    wirnikl.h = 10;
    wirnikl.x = q_x - (wirnikl.w / 2) + cos(q_theta) * -30 - sin(q_theta) * (10);
    wirnikl.y = q_y - (wirnikl.h / 2) - sin(q_theta) * -30 - cos(q_theta) * (10);
    SDL_Point srodek_wirnikl = {wirnikl.w/2,wirnikl.h/2};

    SDL_Rect wirnikr; //kształt i lokacja wirnika drona
    wirnikr.w = 20;
    wirnikr.h = 10;
    wirnikr.x = q_x - (wirnikr.w / 2) + cos(q_theta) * 30 - sin(q_theta) * (10);
    wirnikr.y = q_y - (wirnikr.h / 2) - sin(q_theta) * 30 - cos(q_theta) * (10);
    SDL_Point srodek_wirnikr = {wirnikr.w/2,wirnikr.h/2};

    //Render ciała
    SDL_SetRenderDrawColor(gRenderer.get(), 0, 0, 0, 0xFF);
    //Uwaga, dron wariuje gdy na początku otrzymanego zadania ("przeskakuje" do robienia nowej operacji)
    SDL_RenderCopyEx(gRenderer.get(), tekstura, nullptr, &bodydron, q_theta * -(180 / M_PI), &srodek, SDL_FLIP_NONE); //qtheta jest w radianach i trzeba zamienić na stopnie
    //Render wirników
    SDL_SetRenderDrawColor(gRenderer.get(), 128, 128, 128, 0xFF);
    SDL_RenderCopyEx(gRenderer.get(), tekstura, nullptr, &wirnikl, q_theta * -(180 / M_PI), &srodek_wirnikl, SDL_FLIP_NONE);
    SDL_RenderCopyEx(gRenderer.get(), tekstura, nullptr, &wirnikr, q_theta * -(180 / M_PI), &srodek_wirnikr, SDL_FLIP_NONE);
    //filledCircleColor(gRenderer.get(), q_x, q_y, 30, 0xFF0000FF); Oryginalna wersja z kropką
    //filledEllipseColor(gRenderer.get(), q_x+30, q_y-30, 10, 5, 0xFF0000FF); //szablon wirnika
}