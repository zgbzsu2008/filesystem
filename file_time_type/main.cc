#include <chrono>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>

namespace fs = std::filesystem;
using namespace std::chrono_literals;

int main()
{
  fs::path p = fs::current_path() / "example.bin";
  std::ofstream(p.c_str()).put('a');
  auto ftime = fs::last_write_time(p);
  auto tmp = std::filesystem::_File_time_clock::now().time_since_epoch() - ftime.time_since_epoch();
  std::chrono::system_clock::time_point sys = std::chrono::system_clock::now() - tmp;

  std::time_t cftime = std::chrono::system_clock::to_time_t(sys);
  std::cout << "file write time is " << std::asctime(std::localtime(&cftime));
  
  fs::last_write_time(p, ftime + 1h);
  ftime = fs::last_write_time(p);

  tmp = std::filesystem::_File_time_clock::now().time_since_epoch() - ftime.time_since_epoch();
  sys = std::chrono::system_clock::now() - tmp;
  cftime = std::chrono::system_clock::to_time_t(sys);

  std::cout << "file write time is " << std::asctime(std::localtime(&cftime));
  fs::remove(p);

  return 0;
}

/*
file write time is Thu Apr 25 23:43:01 2019
file write time is Fri Apr 26 00:43:01 2019
*/