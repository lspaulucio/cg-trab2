#include "circulo.h"

Circulo::Circulo()
{
    radius = 0;
    xc = yc = 0;
    drawResolution = 100;
}

Circulo::Circulo(const Circulo &c)
{
    this->radius = c.radius;
    this->xc = c.xc;
    this->yc = c.yc;
    this->setRGBColors(c.getRGBColors());
    this->id = c.id;
    this->drawResolution = c.drawResolution;
}

float Circulo::getRadius() const
{
    return this->radius;
}

void Circulo::setDrawResolution(int new_resolution)
{
    this->drawResolution = new_resolution;
}

int Circulo::getDrawResolution() const
{
    return this->drawResolution;
}

void Circulo::setRadius(float radius)
{
    this->radius = radius;
}

const float* Circulo::getRGBColors() const
{
    return RGBColors;
}

const float Circulo::getRGBColors(COLOR_ID id) const
{
    return RGBColors[id];
}

int Circulo::colorVerification(std::string color) //Check the color's name
{
    if(!color.compare("white")) //If color is white
        return WHITE;
    if(!color.compare("black")) //If color is black
        return BLACK;
    if(!color.compare("red")) //If color is red
        return RED;
    if(!color.compare("green")) //If color is green
        return GREEN;
    if(!color.compare("blue")) //If color is blue
        return BLUE;

    return -1;
}

void Circulo::setRGBColors(std::string color_name)
{
    float colors[3] = {0.0};

    switch(this->colorVerification(color_name)) //Choose RGB values for each color's type
    {
        case BLACK:
            this->setRGBColors(colors);
            break;
        case WHITE:
            colors[RED]= colors[GREEN] = colors[BLUE] = 1.0;
            this->setRGBColors(colors);
            break;
        case RED:
            colors[RED] = 1.0;
            this->setRGBColors(colors);
            break;
        case GREEN:
            colors[GREEN] = 1.0;
            this->setRGBColors(colors);
            break;
        case BLUE:
            colors[BLUE] = 1.0;
            this->setRGBColors(colors);
            break;
        default:
            std::cout << "Unknown color" << std::endl;
            return;
    }
}

void Circulo::setRGBColors(const float colors[3])
{
    for(int i = 0; i < 3; i++)
    this->RGBColors[i] = colors[i];
}

float Circulo::getXc() const
{
    return xc;
}

void Circulo::setXc(float xc)
{
    this->xc = xc;
}

float Circulo::getYc() const
{
    return yc;
}

void Circulo::setYc(float yc)
{
    this->yc = yc;
}

const std::string &Circulo::getId() const
{
    return id;
}

void Circulo::setId(const std::string &id)
{
    this->id = id;
};

void Circulo::translate(float dx, float dy)
{
    this->xc += dx;
    this->yc += dy;
}

bool Circulo::insideCircle(float x, float y) const
{
    float dx, dy, dist;

    dx = this->xc - x;
    dy = this->yc - y;

    dist = sqrt((dx*dx) + (dy*dy));

    if(dist <= this->radius) {
        return true;
    }
    else {
        return false;
    }
}

bool Circulo::insideCircle(Circulo &circ) const
{
    float dx, dy, dist;

    dx = this->xc - circ.getXc();
    dy = this->yc - circ.getYc();

    dist = sqrt((dx*dx) + (dy*dy));
    if(dist <= abs(this->radius - circ.getRadius()))
    {
        return true;
    }
    else return false;
}

bool Circulo::outsideCircle(Circulo &circ) const
{
    float dx, dy, dist;

    dx = this->xc - circ.getXc();
    dy = this->yc - circ.getYc();

    dist = sqrt((dx*dx) + (dy*dy));
    if(dist > (this->radius + circ.getRadius()))
    {
        return true;
    }
    else return false;

}

Circulo::~Circulo(){};
