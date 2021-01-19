void f1(int a, float b){
    write(a);
    write("\n");
    write(b);
}

float f3(float a, float c){
    return a + c;
}
int MAIN(){
    f1(3 + (1 || 2), f3(f3(1.1, 1.3), 1.2));
}