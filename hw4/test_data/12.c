/* gcc: valid, dim need to be >= 0 and integer*/
typedef int INT[0][2];
typedef INT INTT[0][2];
int main(){
	INTT a;
	a[0][0][0][0] = 1;
}