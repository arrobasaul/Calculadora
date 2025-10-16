module; // optional, only if you need to use #include

// all include statements must appear before first export keyword

#include <string>

export module Foo; // name of the module

export import PublicDependency; // will be imported for importers
import PrivateDependency; // will not be imported for importers

export struct Foo {
    std::string bar() const { return "hello modules!"; }
};