#include <string>
#include <list>

namespace ns1 {
struct Struct1 {
  int field1 = 7;

  int fn1() { return 9; }
};

class Class1 {
  char charBuffer[1024];
  int intField1;
  int intField2;
  std::string stringField3;
public:
  Class1(int x = 3) : intField1(x) {}

  std::string fn1(std::list<int> items) {
    if (intField1 == 7)
      return "seven";
    else
      return "something";
  }

  int fnInt() {
    return intField1;
  }
};

int takesClass1(Class1 class1Param) {
  return 3;
}

}


int main(int, char **) {
  using namespace ns1;
  auto m = Class1(7);
  auto n = takesClass1(m);
  return m.fnInt();
}
