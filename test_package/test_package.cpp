#include <boost/bind.hpp>
#include <cstdlib>
#include <iostream>

#if defined(_MSVC_LANG) || defined(__INTEGRITY)
    #include <boost/mem_fn.hpp>
    #include <boost/shared_ptr.hpp>
    using boost::mem_fn;
    using boost::shared_ptr;
#else
    #include <functional>
    #include <memory>
    using std::mem_fn;
    using std::shared_ptr;
#endif


struct X
{
    mutable unsigned int hash;

    X()
        : hash(0)
    {}

    int f0()
    {
        f1(17);
        return 0;
    }

    int g0() const
    {
        g1(17);
        return 0;
    }

    int f1(int a1)
    {
        hash = (hash * 17041 + a1) % 32768;
        return 0;
    }

    int g1(int a1) const
    {
        hash = (hash * 17041 + a1 * 2) % 32768;
        return 0;
    }
};

static int sum_of_three(int a, int b, int c) { return a + b + c; }

int main()
{
    using boost::bind;

    X x;
    X const& rcx = x;
    X const* pcx = &x;
    shared_ptr<X> sp(new X);

    mem_fn(&X::f0)(x);
    mem_fn(&X::f0)(&x);
    mem_fn(&X::f0)(sp);
    mem_fn(&X::g0)(rcx);
    mem_fn(&X::g0)(pcx);

    mem_fn(&X::f1)(x, 1);
    mem_fn(&X::f1)(&x, 1);
    mem_fn(&X::f1)(sp, 1);
    mem_fn(&X::g1)(rcx, 1);
    mem_fn(&X::g1)(pcx, 1);

    std::cout << "X:hash(x) == " << mem_fn(&X::hash)(x) << std::endl;

    std::cout << "1 + 2 + 3 = " << bind(sum_of_three, 1, 2, _1)(3)
              << std::endl;

    return EXIT_SUCCESS;
}
