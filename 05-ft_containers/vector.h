#include <memory>
#include <vector>
namespace ft {

template <typename Tp, typename Alloc = std::allocator<Tp>> class vector {
private:
  typedef Tp value_type;
  typedef value_type *pointer;
  typedef const value_type *const_pointer;

  typedef value_type &reference;
  typedef const value_type &const_reference;

  typedef size_t size_type;

  typedef Alloc allocator_type;
  typedef typename allocator_type::value_type valutype;
};

int main(void) { std::allocator<ft::vector<int>> a; }

} // namespace ft
