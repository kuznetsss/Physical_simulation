#ifndef UTILS_NON_COPYABLE
#define UTILS_NON_COPYABLE

namespace utils {

class NonCopyable {
protected:
    NonCopyable() {}
    ~NonCopyable() {}
private:
    NonCopyable(const NonCopyable&) = delete;
    void operator=(const NonCopyable&) = delete;
};

} // namespace utils
#endif // UTILS_NON_COPYABLE
