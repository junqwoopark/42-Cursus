#include "test.hpp"

int main() {
  // constructor
  {
    NAMESPACE::vector<int> first;                               // empty vector of ints
    NAMESPACE::vector<int> second(4, 100);                      // four ints with value 100
    NAMESPACE::vector<int> third(second.begin(), second.end()); // iterating through second
    NAMESPACE::vector<int> fourth(third);                       // a copy of third

    // the iterator constructor can also be used to construct from arrays:
    int myints[] = {16, 2, 77, 29};
    NAMESPACE::vector<int> fifth(myints, myints + sizeof(myints) / sizeof(int));

    std::cout << "The contents of fifth are:";
    for (NAMESPACE::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
      std::cout << ' ' << *it;
    std::cout << '\n';
  }

  // operator=
  {
    NAMESPACE::vector<int> foo(3, 0);
    NAMESPACE::vector<int> bar(5, 0);

    bar = foo;
    foo = NAMESPACE::vector<int>();

    std::cout << "Size of foo: " << int(foo.size()) << '\n';
    std::cout << "Size of bar: " << int(bar.size()) << '\n';
  }

  // begin(), end()
  {
    NAMESPACE::vector<int> myvector;
    for (int i = 1; i <= 5; i++)
      myvector.push_back(i);

    std::cout << "myvector contains:";
    for (NAMESPACE::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
      std::cout << ' ' << *it;
    std::cout << '\n';
  }

  // rbegin(), rend()
  {
    NAMESPACE::vector<int> myvector(5); // 5 default-constructed ints

    int i = 0;

    NAMESPACE::vector<int>::reverse_iterator rit = myvector.rbegin();
    for (; rit != myvector.rend(); ++rit)
      *rit = ++i;

    std::cout << "myvector contains:";
    for (NAMESPACE::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
      std::cout << ' ' << *it;
    std::cout << '\n';
  }

  // size()
  {
    NAMESPACE::vector<int> myints;
    std::cout << "0. size: " << myints.size() << '\n';

    for (int i = 0; i < 10; i++)
      myints.push_back(i);
    std::cout << "1. size: " << myints.size() << '\n';

    myints.insert(myints.end(), 10, 100);
    std::cout << "2. size: " << myints.size() << '\n';

    myints.pop_back();
    std::cout << "3. size: " << myints.size() << '\n';
  }

  // max_size(), capacity()
  {
    NAMESPACE::vector<int> myvector;

    // set some content in the vector:
    for (int i = 0; i < 100; i++)
      myvector.push_back(i);

    std::cout << "size: " << myvector.size() << '\n';
    std::cout << "capacity: " << myvector.capacity() << '\n';
    std::cout << "max_size: " << myvector.max_size() << '\n';
  }

  // resize()
  {
    NAMESPACE::vector<int> myvector;

    // set some initial content:
    for (int i = 1; i < 10; i++)
      myvector.push_back(i);

    myvector.resize(5);
    myvector.resize(8, 100);
    myvector.resize(12);

    std::cout << "myvector contains:";
    for (int i = 0; i < myvector.size(); i++)
      std::cout << ' ' << myvector[i];
    std::cout << '\n';
  }

  // empty()
  {
    NAMESPACE::vector<int> myvector;
    int sum(0);

    for (int i = 1; i <= 10; i++)
      myvector.push_back(i);

    while (!myvector.empty()) {
      sum += myvector.back();
      myvector.pop_back();
    }

    std::cout << "total: " << sum << '\n';
  }

  // reserve()
  {
    NAMESPACE::vector<int>::size_type sz;

    NAMESPACE::vector<int> foo;
    sz = foo.capacity();
    std::cout << "making foo grow:\n";
    for (int i = 0; i < 100; ++i) {
      foo.push_back(i);
      if (sz != foo.capacity()) {
        sz = foo.capacity();
        std::cout << "capacity changed: " << sz << '\n';
      }
    }

    NAMESPACE::vector<int> bar;
    sz = bar.capacity();
    bar.reserve(100); // this is the only difference with foo above
    std::cout << "making bar grow:\n";
    for (int i = 0; i < 100; ++i) {
      bar.push_back(i);
      if (sz != bar.capacity()) {
        sz = bar.capacity();
        std::cout << "capacity changed: " << sz << '\n';
      }
    }
  }

  // operator[]
  {
    NAMESPACE::vector<int> myvector(10); // 10 zero-initialized elements

    NAMESPACE::vector<int>::size_type sz = myvector.size();

    // assign some values:
    for (unsigned i = 0; i < sz; i++)
      myvector[i] = i;

    // reverse vector using operator[]:
    for (unsigned i = 0; i < sz / 2; i++) {
      int temp;
      temp = myvector[sz - 1 - i];
      myvector[sz - 1 - i] = myvector[i];
      myvector[i] = temp;
    }

    std::cout << "myvector contains:";
    for (unsigned i = 0; i < sz; i++)
      std::cout << ' ' << myvector[i];
    std::cout << '\n';
  }

  // at()
  {
    NAMESPACE::vector<int> myvector(10); // 10 zero-initialized ints

    // assign some values:
    for (unsigned i = 0; i < myvector.size(); i++)
      myvector.at(i) = i;

    std::cout << "myvector contains:";
    for (unsigned i = 0; i < myvector.size(); i++)
      std::cout << ' ' << myvector.at(i);
    std::cout << '\n';
  }

  // front(), back()
  {
    NAMESPACE::vector<int> myvector;

    myvector.push_back(78);
    myvector.push_back(16);

    // now front equals 78, and back 16

    myvector.front() -= myvector.back();

    std::cout << "myvector.front() is now " << myvector.front() << '\n';
  }

  // assign()
  {
    NAMESPACE::vector<int> first;
    NAMESPACE::vector<int> second;
    NAMESPACE::vector<int> third;

    first.assign(7, 100); // 7 ints with a value of 100

    NAMESPACE::vector<int>::iterator it;
    it = first.begin() + 1;

    second.assign(it, first.end() - 1); // the 5 central values of first

    int myints[] = {1776, 7, 4};
    third.assign(myints, myints + 3); // assigning from array.

    std::cout << "Size of first: " << int(first.size()) << '\n';
    std::cout << "Size of second: " << int(second.size()) << '\n';
    std::cout << "Size of third: " << int(third.size()) << '\n';
  }

  // insert()
  {
    NAMESPACE::vector<int> myvector(3, 100);
    NAMESPACE::vector<int>::iterator it;

    it = myvector.begin();
    it = myvector.insert(it, 200);

    myvector.insert(it, 2, 300);

    // "it" no longer valid, get a new one:
    it = myvector.begin();

    NAMESPACE::vector<int> anothervector(2, 400);
    myvector.insert(it + 2, anothervector.begin(), anothervector.end());

    int myarray[] = {501, 502, 503};
    myvector.insert(myvector.begin(), myarray, myarray + 3);

    std::cout << "myvector contains:";
    for (it = myvector.begin(); it < myvector.end(); it++)
      std::cout << ' ' << *it;
    std::cout << '\n';

    return 0;
  }

  // erase()
  {
    NAMESPACE::vector<int> myvector;

    // set some values (from 1 to 10)
    for (int i = 1; i <= 10; i++)
      myvector.push_back(i);

    // erase the 6th element
    myvector.erase(myvector.begin() + 5);

    // erase the first 3 elements:
    myvector.erase(myvector.begin(), myvector.begin() + 3);

    std::cout << "myvector contains:";
    for (unsigned i = 0; i < myvector.size(); ++i)
      std::cout << ' ' << myvector[i];
    std::cout << '\n';
  }

  // swap()
  {
    NAMESPACE::vector<int> foo(3, 100); // three ints with a value of 100
    NAMESPACE::vector<int> bar(5, 200); // five ints with a value of 200

    foo.swap(bar);

    std::cout << "foo contains:";
    for (unsigned i = 0; i < foo.size(); i++)
      std::cout << ' ' << foo[i];
    std::cout << '\n';

    std::cout << "bar contains:";
    for (unsigned i = 0; i < bar.size(); i++)
      std::cout << ' ' << bar[i];
    std::cout << '\n';
  }

  // clear()
  {
    NAMESPACE::vector<int> myvector;
    myvector.push_back(100);
    myvector.push_back(200);
    myvector.push_back(300);

    std::cout << "myvector contains:";
    for (unsigned i = 0; i < myvector.size(); i++)
      std::cout << ' ' << myvector[i];
    std::cout << '\n';

    myvector.clear();
    myvector.push_back(1101);
    myvector.push_back(2202);

    std::cout << "myvector contains:";
    for (unsigned i = 0; i < myvector.size(); i++)
      std::cout << ' ' << myvector[i];
    std::cout << '\n';
  }

  // get_allocator()
  {
    NAMESPACE::vector<int> myvector;
    int *p;
    unsigned int i;

    // allocate an array with space for 5 elements using vector's allocator:
    p = myvector.get_allocator().allocate(5);

    // construct values in-place on the array:
    for (i = 0; i < 5; i++)
      myvector.get_allocator().construct(&p[i], i);

    std::cout << "The allocated array contains:";
    for (i = 0; i < 5; i++)
      std::cout << ' ' << p[i];
    std::cout << '\n';

    // destroy and deallocate:
    for (i = 0; i < 5; i++)
      myvector.get_allocator().destroy(&p[i]);
    myvector.get_allocator().deallocate(p, 5);
  }
}
