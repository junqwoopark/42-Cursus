#include <array>
#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

// 정수일때만 함수 코드를 생성하고 싶음
template <typename T>
typename enable_if<is_integral<T>::value, T>::type foo(T a) {
  cout << "T" << endl;

  return 0;
}

void foo(...) { cout << "not integer" << endl; }

int main() {
  std::stack<int> s1;
  std::stack<int> s2;
  cout << (s1 == s2) << endl;
  cout << (s1 > s2) << endl;
}
