template <typename T> std::allocator<T> Vect<T>::alloc;

// Oslobodi zauzeti prostor (pomoću alokatora)
template <typename T> void Vect<T>::free()
{
    T* temp=this->mdata;
    size_t i=0;
    while (i<this->size()) {this->alloc.destroy(temp++); ++i;}
    this->alloc.deallocate(this->mdata, this->capacity());
    this->mfirst_free=NULL;
    this->mend=NULL;
    this->mdata=NULL;
    return;
}

// realociraj na novu lokaciju. Povećaj dimenziju vektora 2 puta; ako je
// vektor prazan alociraj jedan element.
template <typename T> void Vect<T>::reallocate()
{
    if(this->empty())
        {
            this->mdata=this->alloc.allocate(1);
            this->mfirst_free=this->mdata;
            this->mend=this->mdata;
            ++this->mend;
            return;
        }
    T* novi_mdata=this->alloc.allocate(this->capacity()*2);
    T* temp1=this->mdata;
    T* temp2=novi_mdata;
    while(temp1!=this->mfirst_free) {this->alloc.construct(temp2,*temp1); ++temp1; ++temp2;}
                                                                    //temp2 stao na mfirst_free
    size_t vel=this->capacity()*2;
    this->free();

    temp1=novi_mdata; size_t i=0;
    /*while(i<=vel) {++temp1; ++i;}*/
    temp1+=vel;

    this->mend=temp1;
    this->mfirst_free=temp2;
    this->mdata=novi_mdata;
    return;
}

// Ctor
template <typename T> Vect<T>::Vect(size_t n, T v)
{
    if(n==0)
        {
            this->mdata=NULL;
            this->mend=NULL;
            this->mfirst_free=NULL;
        }
     else
        {
            this->mdata=this->alloc.allocate(n);
            this->mend=this->mdata+n;
            /*size_t i=0;
            while(i<=n) {++i; ++this->mend;} GURA PREDALEKO*/
            this->mfirst_free=this->mdata;
            while(this->mfirst_free!=this->mend)
                {
                    this->alloc.construct(this->mfirst_free, v);
                    ++this->mfirst_free;
                }
        }
}
    // Kontrola kopiranja dolazi ovdje

    // CCtor
template <typename T> Vect<T>::Vect(const Vect<T>& vec)
{
    this->mdata=this->alloc.allocate(vec.capacity());
    this->mend=this->mdata;
    size_t i=0;
    while(i<vec.capacity()) {++i; ++this->mend;}
    this->mfirst_free=this->mdata;
    T* temp=vec.mdata;
    while(temp!=vec.mfirst_free)
        {
            this->alloc.construct(this->mfirst_free,*temp);
            ++this->mfirst_free;
            ++temp;
        }
}

    // MCtor
template <typename T> Vect<T>::Vect(Vect<T>&& vec) noexcept
: mfirst_free(vec.mfirst_free), mdata(vec.mdata), mend((vec.mend))
{
    vec.mdata=NULL;
    vec.mfirst_free=NULL;
    vec.mend=NULL;
}

    // OP
template <typename T> Vect<T>& Vect<T>::operator=(const Vect<T>& vec)
{
    if(this->mdata==vec.mdata) {return *this;}
    this->free();
    this->mdata=this->alloc.allocate(vec.size());
    T* temp=vec.mdata;
    this->mfirst_free=this->mdata;
    while(temp!=vec.mfirst_free)
        {
            this->alloc.construct(this->mfirst_free,*temp);
            ++this->mfirst_free;
            ++temp;
        }
    this->mend=this->mdata+vec.size();
    return *this;
}
    // MOP
template <typename T> Vect<T> Vect<T>::operator=(Vect<T>&& vec) noexcept
{
    if(this->mdata==vec.mdata) {return *this;}
    this->free();
    this->mdata=vec.mdata;
    this->mfirst_free=vec.mfirst_free;
    this->mend=vec.mend;
    vec.mdata=NULL;
    vec.mfirst_free=NULL;
    vec.mend=NULL;
    return *this;
}

    // DTOR
template <typename T> Vect<T>::~Vect()
{
    T* temp=this->mdata;
    while(temp!=this->mfirst_free) {this->alloc.destroy(temp++);}
    this->alloc.deallocate(this->mdata, this->capacity());
    this->mdata=NULL;
    this->mend=NULL;
    this->mfirst_free=NULL;
}

    // dohvat elemenata (operator [])
template <typename T> T& Vect<T>::operator[](int i) {return this->mdata[i];}
template <typename T> T Vect<T>::operator[](int i) const {return this->mdata[i];}

    // push_back metoda
template <typename T> void Vect<T>::push_back(T x)
{
    if(this->size()==this->capacity() || this->empty()) {this->reallocate();}
    this->alloc.construct(this->mfirst_free, x); ++this->mfirst_free;
}

template<typename T> bool Vect<T>::empty() const
{
    if(this->mdata==NULL) return 1;
    return 0;
}

     // info rutine size() i capacity()
template <typename T> size_t Vect<T>::size() const
{
    if(this->empty()) return 0;
/*    T* temp=this->mdata; size_t i=0;
    while (temp!=this->mfirst_free) {++i; ++temp;}  */
    return mfirst_free-mdata;
}
template <typename T> size_t Vect<T>::capacity() const
{
    if(this->empty()) return 0;
/*    T *t=this->mdata; size_t i=0;
    while (t++!=this->mend) i++;    */
    //return i;
    return mend-mdata;
}

     // euklidska norma vraća double!
template <typename T> double Vect<T>::two_norm() const
{
    if(this->empty()) return 0;
    T* temp=this->mdata;
    double sum=0;
    for(size_t i=0; i<this->size(); ++i) {sum+=mdata[i]*mdata[i];}
    return sqrt(sum);
}

template <typename T> Vect<T> operator+(const Vect<T>& vec1, const Vect<T>& vec2)
{
    if(vec1.size()!=vec2.size()) {/*throw runtime_error("Nizovi razlicite duljine, ne mogu zbrojiti.\n");*/ exit(-1);}
    Vect<T> ret(vec1);
    size_t j=0;
    while(j<vec2.size()) {ret[j]+=vec2[j]; ++j;}
    return ret;
}
template <typename T> Vect<T> operator-(const Vect<T>& vec1, const Vect<T>& vec2)
{
    if(vec1.size()!=vec2.size()) {/*throw runtime_error("Nizovi razlicite duljine, ne mogu oduzeti.\n");*/ exit(-1);}
    Vect<T> ret(vec1);
    size_t j=0;
    while(j<vec2.size()) {ret[j]-=vec2[j]; ++j;}
    return ret;
}
template <typename T> ostream& operator<<(ostream& ost, const Vect<T>& vec)
{
    ost<<"[";
    if(vec.size()!=0)
        {
            bool prvi=1;
            size_t i=0;
            while(i<vec.size())
                {
                    if(prvi) {prvi=0;}
                     else {ost<<",";}
                    ost<<vec[i];
                    ++i;
                }
        }
    ost<<"]";
    return ost;
}

     // operatori +=, -=, *=
template <typename T> Vect<T>& Vect<T>::operator+=(const Vect<T>& vec2)
{
    if(this->size()!=vec2.size()) {/*throw runtime_error("Nizovi razlicite duljine, ne mogu zbrojiti.\n");*/ exit(-1);}
    for(size_t i=0; i<this->size(); ++i) {mdata[i]+=vec2[i];}
    return *this;
}
template <typename T> Vect<T>& Vect<T>::operator-=(const Vect<T>& vec2)
{
    if(this->size()!=vec2.size()) {/*throw runtime_error("Nizovi razlicite duljine, ne mogu oduzeti.\n");*/ exit(-1);}
    for(size_t i=0; i<this->size(); ++i) {mdata[i]-=vec2[i];}
    return *this;
}
template <typename T> Vect<T>& Vect<T>::operator*=(const T x)
{
    for(size_t i=0; i<this->size(); ++i) {mdata[i]*=x;}
    return *this;
}         //argument je konvertibilan u tip T
