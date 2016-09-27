#ifndef CIRCULO_H
#define CIRCULO_H

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "types.h"

class Circulo
{
    private:
        float radius;
        float RGBColors[3];
        float xc, yc;
        int drawResolution;
        std::string id;

    public:

        Circulo();

        Circulo(const Circulo&);

        float getRadius() const;

        void setRadius(float);

        int getDrawResolution() const;

        void setDrawResolution(int);

        const float* getRGBColors() const;

        const float getRGBColors(COLOR_ID) const;

        int colorVerification(std::string);

        void setRGBColors(const float[3]);

        void setRGBColors(std::string);

        float getXc() const;

        void setXc(float);

        float getYc() const;

        void setYc(float);

        const std::string &getId() const;

        void setId(const std::string&);

        void translate(float, float);

        bool insideCircle(float, float) const;

        bool insideCircle(Circulo&) const;

        bool outsideCircle(Circulo&) const;

        ~Circulo();

};



#endif //CIRCULO_H
