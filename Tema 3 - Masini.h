//
// Created by Carina on 5/6/2020.
//

#ifndef UNTITLED_TEMA_3_MASINI_H
#define UNTITLED_TEMA_3_MASINI_H
#include <iostream>
#include <string>
#include <vector>
#include <exception>
using namespace std;

class LipsaProduse: public exception{
public:
    LipsaProduse(){
        cout << "Ati incercat sa achizitionati un produs inexistent: ";
    }
};

class PretDeAchizitieIncorect: public exception{
public:
    PretDeAchizitieIncorect(string s){
        cout << "Ati incercat sa achizitionati " << s << " cu o suma incorecta.\n";
    }
};

class Masina {
protected:
    string brand, model;
public:
    Masina(){};
    Masina(string b, string m): brand(b), model(m){}
    Masina(const Masina& M) = default;
    virtual ~Masina()= default;
    Masina& operator= (const Masina&);
    friend istream & operator>> ( istream&, Masina&);
    ///friend ostream& operator<< ( ostream&, const Masina&);
    virtual void print(ostream&);
    string getBrand() const{
        return brand;
    }
    string getModel() const{
        return model;
    }
};
///////////////////////////Metode Masina
Masina& Masina::operator= (const Masina& M){
    brand = M.brand;
    model = M.model;
    return *this;
}
istream& operator>> (istream& in, Masina& M){
    in >> M.brand >> M.model;
    return in;
}
void Masina::print(ostream& out){
    string n = typeid(*this).name();
    while( n[0] >= '0' && n[0] <= '9'){
        n.erase(n.begin());
    }
    out << n << ": " << brand << " " << model;
}

//////////////////////////Coupe


class Coupe : public Masina {
public:
    Coupe():Masina(){}
    Coupe(string b, string m): Masina(b, m){}
    Coupe(const Coupe& C): Masina(C.brand, C.model){}
    ~Coupe() override= default;
    Coupe& operator= (const Coupe&);
    friend istream& operator>> ( istream&, Coupe&);
    ///friend ostream& operator<< ( ostream&, const Coupe&);
    void print(ostream&) override;
};
//////////////////////////////Metode Coupe
Coupe& Coupe::operator= ( const Coupe& C){
    brand = C.brand;
    model = C.model;
    return *this;
}
istream& operator>> ( istream& in, Coupe& C){
    Masina& M = C;
    return in >> M;
}
void Coupe:: print(ostream& out){
    Masina::print(out);
}

///////////////////////////Supersport


class Supersport : public Coupe{
    int pret;
public:
    Supersport():Coupe(), pret(0){}
    Supersport(string b, string m, int p): Coupe(b, m), pret(p){}
    Supersport(const Supersport& S): Coupe( S.brand, S.model), pret(S.pret){}
    ~Supersport() override= default;
    Supersport& operator= ( const Supersport&);
    friend istream& operator>> (istream&, Supersport&);
    //friend ostream& operator<< (ostream&, const Supersport&);
    void print(ostream&) override;
    int getPret(){
        return pret;
    }
    void setPret(int p){
        pret = p;
    }
};
//////////////////////////////Metode Supersport
Supersport& Supersport::operator= ( const Supersport& S){
    brand = S.brand;
    model = S.model;
    pret = S.pret;
    return *this;
}
istream& operator>> ( istream& in, Supersport& S){
    Coupe& C = S;
    in >> C;
    int p;
    in >> p;
    S.setPret(p);
    return in;
}
void Supersport::print(ostream & out) {
    Coupe::print(out);
}

////////////////////////////Cabrio


class Cabrio: public Coupe{
public:
    Cabrio():Coupe(){}
    Cabrio(string b, string m): Coupe(b, m){}
    Cabrio(const Cabrio& C): Coupe(C.brand, C.model){}
    ~Cabrio() override= default;
    Cabrio& operator= (const Cabrio&);
    friend istream& operator>> ( istream&, Cabrio&);
    ///friend ostream& operator<< ( ostream&, const Cabrio&);
    void print(ostream&) override;
};
/////////////////////////////Metode Cabrio
Cabrio& Cabrio::operator= ( const Cabrio& C){
    brand = C.brand;
    model = C.model;
    return *this;
}
istream& operator>> ( istream& in, Cabrio& Ca){
    Coupe& Co = Ca;
    return in >> Co;
}
void Cabrio::print(ostream &out) {
    Coupe::print(out);
}

///////////////////////////HotHatch


class HotHatch : public Masina{
public:
    HotHatch():Masina(){}
    HotHatch(string b, string m): Masina(b, m){}
    HotHatch(const HotHatch& C): Masina(C.brand, C.model){}
    ~HotHatch() override= default;
    HotHatch& operator= (const HotHatch&);
    friend istream& operator>> ( istream&, HotHatch&);
    void print(ostream&) override;
};
//////////////////////////Metode HotHatch
HotHatch& HotHatch::operator= ( const HotHatch& H){
    brand = H.brand;
    model = H.model;
    return *this;
}
istream& operator>> ( istream& in, HotHatch& H){
    Masina & M = H;
    return in >> M;
}
void HotHatch::print(ostream & out) {
    Masina::print(out);
}

//////////////////////////Expozitie sablon


template < class T>
class Expozitie {
    unsigned int nr;
    vector <pair<T*,int>> colectie;
public:
    Expozitie():nr(0){}
    explicit Expozitie(vector<T> v):nr(v.size()){
        for( auto m: v)
            colectie.push_back(new T(m));
    }
    ///Constructor de copiere? Operator de atribuire? Sunt necesare?
    ~Expozitie(){
        for( auto m : colectie)
            delete(m.first);
        colectie.clear();
    }
    void operator+= ( T& m){
        colectie.emplace_back(new T(m), -1);
        nr++;
    }
    vector <pair<T*,int>> getColectie(){
        return colectie;
    }
    unsigned int getNr(){
        return nr;
    }
    void print ( ostream& out);
};

template <class T>
void Expozitie<T>::print ( ostream& out) {
    for( auto x : colectie){
        x.first->print(out);
        out << " " << x.second << "\n";
    }
}


//////////////////////////Expozitie specializare Supersport


template <>
class Expozitie <Supersport>{
    unsigned int nr_expuse, nr_vandute;
    vector <pair <Supersport*, int> > vandute, expuse;
public:
    Expozitie(): nr_expuse(0), nr_vandute(0){}
    ~Expozitie(){
        for( auto m : expuse){
            delete(m.first);
        }
        expuse.clear();
        for( auto m : vandute){
            delete(m.first);
        }
        vandute.clear();
    }
    void operator += ( Supersport& s);
    void operator -= ( Supersport& s);
    vector <pair<Supersport*,int>> getExpuse(){
        return expuse;
    }
    vector <pair <Supersport*,int>> getVandute(){
        return vandute;
    }
    unsigned int getNr_expuse(){
        return nr_expuse;
    }
    unsigned int getNr_vandute(){
        return nr_vandute;
    }
    void print ( ostream& out);
};

void Expozitie<Supersport>::operator += ( Supersport& s){
    expuse.emplace_back( new Supersport(s), -1);
    nr_expuse++;
}
void Expozitie<Supersport>::operator -= ( Supersport& s){
    if( nr_expuse == 0)
        throw LipsaProduse();
    for ( int i = 0; i < nr_expuse; i++){
        if( expuse[i].first->getBrand() == s.getBrand() && expuse[i].first->getModel() == s.getModel()){
            if ( s.getPret() != expuse[i].first->getPret()) {
                throw PretDeAchizitieIncorect(s.getBrand()+" "+s.getModel());
            }
            vandute.emplace_back(new Supersport(s), s.getPret());
            nr_vandute++;
            delete(expuse[i].first);
            if( i != nr_expuse-1){
                expuse[i].first = expuse[nr_expuse-1].first;
                expuse[nr_expuse-1].first = nullptr;
            }
            expuse.pop_back();
            break;
        }
        if ( i == nr_expuse - 1){
            throw LipsaProduse();
        }
    }
    nr_expuse--;
}

void Expozitie<Supersport>::print ( ostream& out) {
    for( auto x : expuse){
        x.first->print(out);
        out << " " << x.second << "\n";
    }
    for( auto x : vandute){
        x.first->print(out);
        out << " " << x.second << "\n";
    }
}


#endif //UNTITLED_TEMA_3_MASINI_H
