#ifndef INTERVAL_H
#define INTERVAL_H
#include <limits>

class interval{
public:
    const double infinity = std::numeric_limits<double>::infinity();
    interval() : max{infinity}, min{-infinity} {}
    interval(const double& l, const double& h) : max{h}, min{l} {}

    bool surrounds(const double& x) const{
        if( (x < max) && (x > min) ) return true;
        else return false;
    }
    double max;
    double min;

};

#endif