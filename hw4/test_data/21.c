/*gcc: valid*/
int f(int a) { return 0; }
float g() { return 0.0; }
int h(int x, int y) { return x + y; }
int main() {
  h(f(h(g(), g())), g());
}
