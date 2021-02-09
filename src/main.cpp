// Copyright (c) 2021 Sergey Bazhnev <SBazhnev@gmail.com>
// Licensed under the MIT License
//

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
  std::cout << "The simple customized boost logger" << std::endl;

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
