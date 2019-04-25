#include <assert.h>
#include <iostream>
#include <string>

//#define WINDOWS_FILESYSTEM

#if !defined(WINDOWS_FILESYSTEM)
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#else
#include <filesystem>
namespace fs = std::filesystem;
#endif

int main()
{
  fs::path p, q;
  fs::path s = "sandbox/abc.txt";
  fs::path t = "sandbox\\123.txt";

  // #01
  std::cout << "#01 @current_path = " << fs::current_path() << '\n';

  // #02
  p.assign(s);
  std::cout << "#02 @assign " << p << '\n';
  // #03
  p = s;
  s.make_preferred();
  std::cout << "#03 " << p << "  @make_preferred: = " << s << '\n';

  // #04
  p = s;
  q = p.filename();
  std::cout << "#04 " << s << " @filename: = " << q << '\n';

  // #05
  p = s;
  p.remove_filename();
  std::cout << "#05 " << s << " @remove_filename: = " << p << '\n';

  // #06
  p = s;
  p.append(t.string());  // p /= q;
  std::cout << "#06 " << s << " @append: " << t << " = " << p << '\n';

  // #07
  p = s;
  p.concat(t.string());  // p += t;
  std::cout << "#07 " << s << " @concat: " << t << " = " << p << '\n';

  // #08
  p = s;
  p.replace_filename("123.txt");
  std::cout << "#08 " << s << " @replace_filename: 123.txt = " << p << '\n';

  // #09
  p = s;
  p.replace_extension(".zip");
  std::cout << "#09 " << s << " @replace_extension: .zip= " << p << '\n';

  // #10
  p = s;
  int rc = p.compare(t);
  if (rc > 0) {
    std::cout << "#10 " << p << " @compare > " << t << '\n';
  } else if (rc == 0) {
    std::cout << p << " @compare = " << t << '\n';
  } else {
    std::cout << p << " @compare < " << t << '\n';
  }

#if defined(WINDOWS_FILESYSTEM)
  // #11
  p = "foo/./bar/..";
  q = p.lexically_normal();
  std::cout << "#11 " << p << " @lexically_normal: = " << q << '\n';

  // #12
  p = s.lexically_relative(t);
  std::cout << "#12 " << s << " @lexically_relative: " << t << " = " << p << '\n';
#endif

  // #13
  p = fs::absolute(s);
  std::cout << "#13 " << p << "\n @root_name = " << p.root_name() << '\n'
            << " @root_directory = " << p.root_directory() << '\n'
            << " @root_path = " << p.root_path() << '\n'
            << " @relative_path = " << p.relative_path() << '\n'
            << " @parent_path = " << p.parent_path() << '\n'
            << " @filename = " << p.filename() << '\n'
            << " @stem = " << p.stem() << '\n'
            << " @extension = " << p.extension() << '\n';

  // #14
  std::cout << "#14 " << p << "\n @begin, @end\n";
  for (auto it = p.begin(); it != p.end(); ++it) {
    std::cout << *it << '\n';
  }
  std::cout << '\n';

  return 0;
}

/*
#01 @current_path = "D:\\c++\\filesystem\\path"
#02 @assign "sandbox/abc.txt"
#03 "sandbox/abc.txt"  @make_preferred: = "sandbox\\abc.txt"
#04 "sandbox\\abc.txt" @filename: = "abc.txt"
#05 "sandbox\\abc.txt" @remove_filename: = "sandbox\\"
#06 "sandbox\\abc.txt" @append: "sandbox\\123.txt" = "sandbox\\abc.txt\\sandbox\\123.t
#07 "sandbox\\abc.txt" @concat: "sandbox\\123.txt" = "sandbox\\abc.txtsandbox\\123.txt
#08 "sandbox\\abc.txt" @replace_filename: 123.txt = "sandbox\\123.txt"
#09 "sandbox\\abc.txt" @replace_extension: .zip= "sandbox\\abc.zip"
#10 "sandbox\\abc.txt" @compare > "sandbox\\123.txt"
#11 "foo/./bar/.." @lexically_normal: = "foo\\"
#12 "sandbox\\abc.txt" @lexically_relative: "sandbox\\123.txt" = "..\\abc.txt"
#13 "D:\\c++\\filesystem\\path\\sandbox\\abc.txt"
 @root_name = "D:"
 @root_directory = "\\"
 @root_path = "D:\\"
 @relative_path = "c++\\filesystem\\path\\sandbox\\abc.txt"
 @parent_path = "D:\\c++\\filesystem\\path\\sandbox"
 @filename = "abc.txt"
 @stem = "abc"
 @extension = ".txt"
#14 "D:\\c++\\filesystem\\path\\sandbox\\abc.txt"
 @begin, @end
"D:"
"\\"
"c++"
"filesystem"
"path"
"sandbox"
"abc.txt"
*/