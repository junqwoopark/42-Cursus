#include "test.hpp"

int main() {
  // constructor
  {
    std::deque<int> mydeque(3, 100);    // deque with 3 elements
    std::vector<int> myvector(2, 200);  // vector with 2 elements

    NAMESPACE::stack<int> first;                              // empty stack
    NAMESPACE::stack<int, std::deque<int> > second(mydeque);  // stack initialized to copy of deque

    NAMESPACE::stack<int, std::vector<int> > third;  // empty stack using vector
    NAMESPACE::stack<int, std::vector<int> > fourth(myvector);

    std::cout << "size of first: " << first.size() << '\n';
    std::cout << "size of second: " << second.size() << '\n';
    std::cout << "size of third: " << third.size() << '\n';
    std::cout << "size of fourth: " << fourth.size() << '\n';
  }

  // empty()
  {
    NAMESPACE::stack<int> mystack;
    int sum(0);

    for (int i = 1; i <= 10; i++) mystack.push(i);

    while (!mystack.empty()) {
      sum += mystack.top();
      mystack.pop();
    }

    std::cout << "total: " << sum << '\n';
  }

  // size()
  {
    NAMESPACE::stack<int> myints;
    std::cout << "0. size: " << myints.size() << '\n';

    for (int i = 0; i < 5; i++) myints.push(i);
    std::cout << "1. size: " << myints.size() << '\n';

    myints.pop();
    std::cout << "2. size: " << myints.size() << '\n';
  }

  // top()
  {
    NAMESPACE::stack<int> mystack;

    mystack.push(5);
    mystack.push(2);

    mystack.top() -= 3;

    std::cout << "mystack.top() is now " << mystack.top() << '\n';
  }

  // push(), pop()
  {
    NAMESPACE::stack<int> mystack;

    for (int i = 0; i < 5; i++) mystack.push(i);

    std::cout << "Popping out elements...";
    while (!mystack.empty()) {
      std::cout << ' ' << mystack.top();
      mystack.pop();
    }
    std::cout << '\n';
  }

  // swap()
  {
    NAMESPACE::stack<int> foo, bar;
    foo.push(10);
    foo.push(20);
    bar.push(100);
    bar.push(200);

    foo.swap(bar);

    std::cout << "foo contains:";
    while (!foo.empty()) {
      std::cout << ' ' << foo.top();
      foo.pop();
    }

    std::cout << '\n';

    std::cout << "bar contains:";
    while (!bar.empty()) {
      std::cout << ' ' << bar.top();
      bar.pop();
    }

    std::cout << '\n';
  }
}
