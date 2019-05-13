#ifndef _VECT_H_IS_INCLUDED_
#define _VECT_H_IS_INCLUDED_

#include <iostream>
#include <string>
#include <cmath>
#include <ostream>
#include <cstdlib>
#include <memory>
using namespace std;

// deklaracija potrebna za testiranje
template <typename> class VectTest;

template <typename T>
class Vect
{
    friend class VectTest<T>;  // da testovi mogu dohvatiti privatne varijable
    friend class VectTestPair;
public:
    // Ctor
    explicit Vect(size_t n = 0, T v= {});
    // Kontrola kopiranja dolazi ovdje
    // CCtor
    Vect(const Vect& vec);
    // MCtor
    Vect(Vect&& vec) noexcept;
    // OP
    Vect<T>& operator=(const Vect& vec);
    // MOP
    Vect<T> operator=(Vect&& vec) noexcept;
    // DTOR
    ~Vect();

    // dohvat elemenata (operator [])
    T& operator[](int i);
    T operator[](int i) const;
    // push_back metoda
    void push_back(T x);

     // info rutine size() i capacity()
     size_t size() const;
     size_t capacity() const;

     // operatori +=, -=, *=
     Vect<T>& operator+=(const Vect& vec);
     Vect<T>& operator-=(const Vect& vec);
     Vect<T>& operator*=(const T x);         //argument je konvertibilan u tip T
     // euklidska norma vraća double !
     double two_norm() const;
private:
        T *mdata;       // pokazivač na prvi element
        T *mfirst_free; // pokazivač na prvo slobodno mjesto
        T *mend;        // pokazivač na kraj alociranog prostora
                             // (jedno mjesto iza posljednjeg)

        // Oslobodi zauzeti prostor (pomoću alokatora)
        void free();

      	// realociraj na novu lokaciju. Povećaj dimenziju vektora 2 puta; ako je
        // vektor prazan alociraj jedan element.
        void reallocate();

        // dodati vlastite privatne metode.
        bool empty() const;

        // alokator ne mora imati pristup varijablama članicama klase pa ga činimo
        // statičkim. Ne zaboraviti definirati ga.
        static std::allocator<T> alloc;
};

// Deklaracija operator +, - i <<
template <typename T> Vect<T> operator+(const Vect<T>& vec1, const Vect<T>& vec2);
template <typename T> Vect<T> operator-(const Vect<T>& vec1, const Vect<T>& vec2);
template <typename T> ostream& operator<<(ostream& ost, const Vect<T>& vec);

// Implementacija je u posebnoj .h datoteci
#include "vect_impl.h"

#endif
