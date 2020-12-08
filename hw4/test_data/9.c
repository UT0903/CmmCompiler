/* gcc: warning: passing argument 1 of ‘func’ makes pointer from integer without a cast */
int func(int c[]){

}
int main(){
	int c;
	int b = func(c);
}