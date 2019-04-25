#include <experimental/filesystem>
#include <iostream>

namespace fs = std::experimental::filesystem;

int main()
{
  fs::space_info devi = fs::space("/dev/null");
  fs::space_info tmpi = fs::space("/tmp");

   std::cout << ".        Capacity       Free     Available\n"
              << "/dev:   " << devi.capacity << "   "
              << devi.free << "   " << devi.available  << '\n'
              << "/tmp: " << tmpi.capacity << " "
              << tmpi.free << " " << tmpi.available  << '\n';
  return 0;
}

/*
.        Capacity       Free     Available
/dev:   494755840   494751744   494751744
/tmp: 19674116096 17174028288 16151040000
*/
