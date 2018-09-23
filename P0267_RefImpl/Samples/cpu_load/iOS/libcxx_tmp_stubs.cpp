#include <optional>
#include <variant>

// These are temporary stubs to work around the outdated LIBC++ which comes with XCode 

std::bad_optional_access::~bad_optional_access() noexcept = default;
const char* std::bad_optional_access::what() const noexcept { return ""; }
const char* std::bad_variant_access::what() const noexcept { return ""; }
