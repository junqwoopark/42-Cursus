#include <iostream>
#include <vector>

// test of vector comparison
int main() {
  std::vector<int> v1(5, 42);
  std::vector<int> v2(5, 42);

  std::cout << "v1 == v2 ? " << (v1 == v2) << std::endl;
}
