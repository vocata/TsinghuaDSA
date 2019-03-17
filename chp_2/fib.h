#ifndef FIB_H_
#define FIB_H_

namespace DSA {
class Fib {
private:
    unsigned long f, g;

public:
    Fib(unsigned long n)
    {
        f = 0;
        g = 1;
        while (g < n)
            next();
    }
    unsigned long get() { return g; }
    unsigned long next()
    {
        g += f;
        f = g - f;
        return g;
    }
    unsigned long pre()
    {
        f = g - f;
        g -= f;
        return g;
    }
};
}

#endif /* FIB_H_ */
