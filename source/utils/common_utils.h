#ifndef UTILS_NON_COPYABLE
#define UTILS_NON_COPYABLE

#include <memory>
#include <experimental/propagate_const>

namespace utils {

class NonCopyable {
protected:
    NonCopyable() {}
    ~NonCopyable() {}
private:
    NonCopyable(const NonCopyable&) = delete;
    void operator=(const NonCopyable&) = delete;
};

template<class T>
using ImplPtr = std::experimental::propagate_const<std::unique_ptr<T>>;

} // namespace utils
#endif // UTILS_NON_COPYABLE
