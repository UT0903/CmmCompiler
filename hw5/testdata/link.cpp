#include <iostream>
#include <iomanip>
using namespace std;
void write( int    a) {cout << a;}
void write( double a) {cout << std::fixed << std::setprecision(6) << a;}
void write( float a) {cout << std::fixed << std::setprecision(6) << a;}
void write( bool   a) {cout << a;}
void write( const char* a) {cout << a;}
int global_num = 1;
int read(){return global_num++;}
float fread(){return global_num++;}
int MAIN();
int main(){
    MAIN();
}
