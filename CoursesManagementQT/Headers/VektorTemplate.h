//
// Created by ultra on 06.06.2023.
//

#ifndef QTLAB_VEKTORTEMPLATE_H
#define QTLAB_VEKTORTEMPLATE_H


template<typename TElement>
class IteratorVektor;

template<typename TElement>
class Vektor {
private:
    int lenght;
    int capacity;
    TElement *elems;

    void ensure_cap();

public:
    //Constructor default
    Vektor();

    //Constructor - copy
    Vektor(const Vektor &ot);

    //destructor
    ~Vektor();

    /*
     * operator assignment
     * alloc and copy the elements from ot to this
     */
    Vektor &operator=(const Vektor &ot);

    /*
     * move constructor
     */
    Vektor(Vektor &&ot);


    /*
     * Move assignment
     *
     */
    Vektor& operator=(Vektor &&ot);

    /*
     * add an element
     */
    void add(const TElement &el);

    /*
     * return the element from the poz
     */
    TElement &get(int poz) const;

    /*
     * change an element on the poz with el
    */
    void set(int poz, const TElement &el);

    /*
     * return the size of the array
     */
    int size() const noexcept;

    friend class IteratorVektor<TElement>;

    IteratorVektor<TElement> begin();

    IteratorVektor<TElement> end();
};

template<typename TElement>
Vektor<TElement>::Vektor() :elems{new TElement[5]}, capacity{5}, lenght{0} {}

template<typename TElement>
Vektor<TElement>::Vektor(const Vektor<TElement> &ot) {
    elems = new TElement[ot.capacity];
    //copy the elements
    for (int i = 0; i < ot.capacity; i++) {
        elems[i] = ot.elems[i];
    }
    lenght = ot.lenght;
    capacity = ot.capacity;
}

template<typename TElement>
Vektor<TElement> &Vektor<TElement>::operator=(const Vektor<TElement> &ot) {
    if (this == &ot) {
        return *this;
    }
    delete[] elems;
    elems = new TElement[ot.capacity];
    for (int i = 0; i < ot.lenght; i++) {
        elems[i] = ot.elems[i];
    }
    lenght = ot.lenght;
    capacity = ot.capacity;
    return *this;
}

template<typename TElement>
Vektor<TElement>::~Vektor() {
    delete[] elems;
}

template<typename TElement>
Vektor<TElement>::Vektor(Vektor<TElement> &&ot) {
    elems = ot.elems;
    lenght = ot.lenght;
    capacity = ot.capacity;

    ot.elems = nullptr;
    ot.lenght = 0;
    ot.capacity = 0;

}

template<typename TElement>
Vektor<TElement> &Vektor<TElement>::operator=(Vektor<TElement> &&ot) {
    if (this == &ot) {
        return *this;

    }
    delete[] elems;
    elems = ot.elems;
    capacity = ot.capacity;
    lenght = ot.lenght;

    ot.elems = nullptr;
    ot.lenght = 0;
    ot.capacity = 0;
    return *this;
}

template<typename TElement>
void Vektor<TElement>::add(const TElement &el) {
    ensure_cap();
    elems[lenght++] = el;
}

template<typename TElement>
TElement &Vektor<TElement>::get(int poz) const {
    return elems[poz];
}

template<typename TElement>
void Vektor<TElement>::set(int poz, const TElement &el) {
    elems[poz] = el;
}

template<typename TElement>
int Vektor<TElement>::size() const noexcept {
    return lenght;
}

template<typename TElement>
void Vektor<TElement>::ensure_cap() {
    if (lenght < capacity) {
        return;
    }
    capacity *= 2;
    TElement *aux = new TElement[capacity];
    for (int i = 0; i < lenght; i++) {
        aux[i] = elems[i];
    }
    delete[] elems;
    elems = aux;
}

template<typename TElement>
IteratorVektor<TElement> Vektor<TElement>::begin() {
    return IteratorVektor<TElement>(*this);
}

template<typename TElement>
IteratorVektor<TElement> Vektor<TElement>::end() {
    return IteratorVektor<TElement>(*this, lenght);
}

template<typename TElement>
class IteratorVektor {
private:
    const Vektor<TElement> &v;
    int poz = 0;
public:
    //constructor
    IteratorVektor(const Vektor<TElement> &v) noexcept;

    //constructor with position specified
    IteratorVektor(const Vektor<TElement> &v, int poz) noexcept;

    //check if the iterator is stil valid
    bool valid() const;

    TElement &element() const;

    void next();

    TElement &operator*();

    IteratorVektor &operator++();

    bool operator==(const IteratorVektor &ot) noexcept;

    bool operator!=(const IteratorVektor &ot) noexcept;
};

template<typename TElement>
IteratorVektor<TElement>::IteratorVektor(const Vektor<TElement> &v) noexcept: v{v} {}

template<typename TElement>
IteratorVektor<TElement>::IteratorVektor(const Vektor<TElement> &v, int poz) noexcept: v{v} , poz{poz} {}

template<typename TElement>
bool IteratorVektor<TElement>::valid() const {
    return poz < v.lenght;
}

template<typename TElement>
TElement &IteratorVektor<TElement>::element() const {
    return v.elems[poz];
}

template<typename TElement>
void IteratorVektor<TElement>::next() {
    poz++;
}

template<typename TElement>
TElement& IteratorVektor<TElement>::operator*()  {
    return element();
}

template<typename TElement>
IteratorVektor<TElement> &IteratorVektor<TElement>::operator++() {
    next();
    return *this;
}

template<typename TElement>
bool IteratorVektor<TElement>::operator==(const IteratorVektor<TElement> &ot) noexcept {
    return poz == ot.poz;
}

template<typename TElement>
bool IteratorVektor<TElement>::operator!=(const IteratorVektor<TElement> &ot) noexcept {
    return !(*this == ot);
}

#endif //QTLAB_VEKTORTEMPLATE_H
