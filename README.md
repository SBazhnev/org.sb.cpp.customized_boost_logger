# Simple customized logger based on Boost.Log v2

The Boost.Log documentation doesn't contain enough information (especially for beginners) on using and setting up.
I collected from different sources this simple example.

## Logger settings

`severity_level >= trace` by default and `severity_level >= info` if NDEBUG is defined.

## Example of use

```cpp
// main.cpp

#include <iostream>

#include "logger.h"

class Class {
public:
  void PublicMethod() {
    LNAMED_SCOPE("The class public method scope")

    LDEBUG << "This class public method debug message!";

    PrivateMethod();
  }

private:
  void PrivateMethod() {
    LNAMED_SCOPE("The class private method scope")

    LDEBUG << "This class private method debug message!";
  }

};

int main(int argc, char **argv) {

  LTRACE << "This trace message!";
  LDEBUG << "This debug message!";
  LINFO << "This info message!";
  LWARNING << "This warning message!";
  LERROR << "This error message!";
  LFATAL << "This fatal message!";

  Class obj;

  obj.PublicMethod();

  return 0;
}
```

## Output

```console
16:13:22.702259 [trace] []: This trace message!
16:13:22.714258 [debug] []: This debug message!
16:13:22.714635 [info] []: This info message!
16:13:22.714879 [warning] []: This warning message!
16:13:22.715020 [error] []: This error message!
16:13:22.715151 [fatal] []: This fatal message!
16:13:22.715444 [debug] [The class public method scope]: This class public method debug message!
16:13:22.716000 [debug] [The class public method scope->The class private method scope]: This class private method debug message!
```

## Example build

```console
mkdir build

cd build

cmake ..

cmake --build .
```
