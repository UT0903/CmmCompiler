int p(int i){write(i);write("\n");return i;}
int MAIN(){
	int a,b,c;
	a = p(0) && p(1);
	b = p(2) || p(3);
	c = p(4) && p(0);
	write(a);
	write(b);
	write(c);
}
