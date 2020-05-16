#include <iostream>
#include <vector>
#include "Tema 3 - Masini.h"
#include <fstream>
#include <string>
using namespace std;

int main() {
    ifstream in ("Masini.in");
    ofstream out ("Masini.out");
    Expozitie<Supersport> super;
    Expozitie<Coupe> coupe;
    Expozitie<Cabrio> decap;
    Expozitie<HotHatch> hothatch;
    int n;
    in >> n;
    for ( int i = 0; i < n; i++){
        string s;
        in >> s;
        if( s == "Coupe"){
            Coupe c;
            in >> c;
            coupe += c;
        } else if( s == "Cabrio"){
            Cabrio c;
            in >> c;
            decap += c;
        } else if ( s == "Hot-Hatch" ){
            HotHatch h;
            in >> h;
            hothatch += h;
        } else{
            Supersport sp;
            in >> sp;
            super += sp;
        }
    }
    int v;
    in >> v;
    while( v != 0){
        Supersport sp;
        in >> sp;
        try { super -= sp;
        } catch (PretDeAchizitieIncorect&){}
        catch(LipsaProduse&){
            sp.print(cout);
            cout << "\n";
        };
        v--;
    }
    super.print(out);
    hothatch.print(out);
    return 0;
}
