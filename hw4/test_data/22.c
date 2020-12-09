/*gcc: error: invalid use of void expression*/
int f(int a) { return 0; }
float g() { return 0.0; }
void k(){}
int h(int x, int y) { return x + y; }
int main() {
  h(f(h(g(), k())), g());
}
