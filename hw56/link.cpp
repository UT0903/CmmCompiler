#include <iostream>
#include <iomanip>
using namespace std;
void write( int    a) {cout << a;}
void write( double a) {cout << std::fixed << std::setprecision(6) << a;}
void write( float a) {cout << std::fixed << std::setprecision(6) << a;}
void write( bool   a) {cout << a;}
void write( const char* a) {cout << a;}
int read(){
    int a;
    scanf("%d", &a);
    return a;
}
float fread(){int a;
    scanf("%d", &a);
    return a;
    }
int MAIN();
int main(){
    MAIN();
}
