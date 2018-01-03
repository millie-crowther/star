#ifndef MATHS_H
#define MATHS_H

namespace maths {
    const double epsilon = 0.00001;

    inline bool approx(double a, double b){
        return abs(a - b) <= epsilon;
    }
}

#endif
