#include <iostream>

int Factorial(int x) {
  int result = 1;
  for (int i = 2; i <= x; ++i) {
    result *= i;
  }
  return result;
}

int Factorial_rec(int x) {
  if (x <= 1) {
    return 1;
  } else {
    return x * Factorial_rec(x - 1);
  }
}


int main {
    int x;
    cin >> x;
    cout << Factorial(x);
    return 0;
}