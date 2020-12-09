/*gcc: warning: passing argument 1 of ‘f’ from incompatible pointer type*/
int f(int a[][10]){

}
int main(){
	int b[1][2][3];
	f(b[1]);
}