#include <bitset>
#include <fstream>
#include <iostream>

//#define WINDOWS_FILESYSTEM

#if !defined(WINDOWS_FILESYSTEM)
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#else
#include <filesystem>
namespace fs = std::filesystem;
#endif

void demo_perms(fs::perms p)
{
  std::cout << ((p & fs::perms::owner_read) != fs::perms::none ? "r" : "-")
            << ((p & fs::perms::owner_write) != fs::perms::none ? "w" : "-")
            << ((p & fs::perms::owner_exec) != fs::perms::none ? "x" : "-")
            << ((p & fs::perms::group_read) != fs::perms::none ? "r" : "-")
            << ((p & fs::perms::group_write) != fs::perms::none ? "w" : "-")
            << ((p & fs::perms::group_exec) != fs::perms::none ? "x" : "-")
            << ((p & fs::perms::others_read) != fs::perms::none ? "r" : "-")
            << ((p & fs::perms::others_write) != fs::perms::none ? "w" : "-")
            << ((p & fs::perms::others_exec) != fs::perms::none ? "x" : "-") << '\n';
}

int main()
{
  std::ofstream("abc.txt");
  std::cout << "created file with permissions: ";
  auto p = fs::status("abc.txt").permissions();
  demo_perms(p);

  fs::permissions("abc.txt", fs::perms::owner_all | fs::perms::group_all | p);
#if defined(WINDOWS_FILESYSTEM)
  fs::permissions("test.txt", fs::perms::owner_all | fs::perms::group_all, fs::perm_options::add);
#endif
  std::cout << "after adding o+rwx and g+rwx:  ";
  demo_perms(fs::status("abc.txt").permissions());

  fs::remove("abc.txt");
  return 0;
}

/* in linux
created file with permissions: rw-rw-r--
after adding o+rwx and g+rwx:  rwxrwxr--
*/