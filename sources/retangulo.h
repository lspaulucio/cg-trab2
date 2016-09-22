#ifndef CRETANGULO_H
#define RETANGULO_H


#include "types.h"
#include <iostream>

class Retangulo
{
private:
    float width, height;
    float RGBColors[3];
    float vertices[4][3];
    float xc, yc; //first rectangle vertice (top left)
    std::string id;

public:

    Retangulo();

    float getWidth() const;

    void setWidth(float);

    float getHeight() const;

    void setHeight(float height);

    const float* getRGBColors() const;

    const float getRGBColors(COLOR_ID) const;

    void setRGBColors(const float[3]);

    float getXc() const;

    void setXc(float xc);

    float getYc() const;

    void setYc(float yc);

    const std::string &getId() const;

    void setId(const std::string&);

    const float* getVertices(int n) const;

    const float getVertices(int, AXES) const;

    void translate(float, float);

    void updateVertices();

    bool insideSquare(float, float) const;

    ~Retangulo();

};


#endif //RETANGULO_H
