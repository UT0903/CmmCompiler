#include <iostream>
#include <iomanip>
using namespace std;
void write( int    a) {cout << a;}
void write( double a) {cout << std::fixed << std::setprecision(6) << a;}
void write( float a) {cout << std::fixed << std::setprecision(6) << a;}
void write( bool   a) {cout << a;}
void write( const char* a) {cout << a;}
int read(){return 1;}
float fread(){return 1.0;}
int MAIN();
int main(){
    MAIN();
}
