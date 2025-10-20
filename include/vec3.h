#ifndef VEC3_H
#define VEC3_H


class vec3{
private:
    double v[3];

    vec3() : v{0, 0, 0}{}

    vec3(double& a, double& b, double& c) : v{a, b, c}{}

    double x() { return v[0]; }
    double y() { return v[1]; }
    double z() { return v[2]; }
};

#endif