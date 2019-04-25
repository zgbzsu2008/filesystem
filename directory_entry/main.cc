#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include <experimental/filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::experimental::filesystem;

void demo_status(const fs::path& p, fs::file_status s);

int main()
{
  fs::create_directory("sandbox");      // 1
  std::ofstream("sandbox/file");        // 2
  fs::create_directory("sandbox/dir");  // 3
  ::mkfifo("sandbox/pipe", 0644);       // 4
  struct sockaddr_un addr;
  addr.sun_family = AF_UNIX;
  std::strcpy(addr.sun_path, "sandbox/sock");  // 5
  int fd = ::socket(PF_UNIX, SOCK_STREAM, 0);
  ::bind(fd, (struct sockaddr*)&addr, sizeof(addr));
  fs::create_symlink("file", "sandbox/symlink");  // 6

  for (auto it = fs::directory_iterator("sandbox"); it != fs::directory_iterator(); ++it) {
    demo_status(*it, it->symlink_status());
  }

  demo_status("/dev/null", fs::status("/dev/null"));
  demo_status("/dev/sda", fs::status("/dev/sda"));
  demo_status("/sandbox/no", fs::status("/sandbox/no"));

  ::close(fd);
  fs::remove_all("sandbox");
  return 0;
}

void demo_status(const fs::path& p, fs::file_status s)
{
  std::cout << p;
  if (fs::is_regular_file(s)) {
    std::cout << " is a regular file\n";
  }
  if (fs::is_directory(s)) {
    std::cout << " is a directory\n";
  }
  if (fs::is_block_file(s)) {
    std::cout << " is a block device\n";
  }
  if (fs::is_character_file(s)) {
    std::cout << "is a character device\n";
  }
  if (fs::is_fifo(s)) {
    std::cout << "is a name IPC pipe\n";
  }
  if (fs::is_socket(s)) {
    std::cout << "is a named IPC socket\n";
  }
  if (fs::is_symlink(s)) {
    std::cout << "is a symlink\n";
  }
  if (!fs::exists(s)) {
    std::cout << "does not exists\n";
  }

  /*
  switch (s.type()) {
    case fs::file_type::regular:
      std::cout << " is a regular file\n";
      break;
    case fs::file_type::directory:
      std::cout << " is a directory\n";
      break;
    case fs::file_type::block:
      std::cout << " is a block device\n";
      break;
    case fs::file_type::character:
      std::cout << "is a character device\n";
      break;
    case fs::file_type::fifo:
      std::cout << "is a name IPC pipe\n";
      break;
    case fs::file_type::socket:
      std::cout << "is a named IPC pipe\n";
      break;
    case fs::file_type::symlink:
      std::cout << "is a symlink\n";
      break;
    default:
      std::cout << "does not exists\n";
      break;
  }
  */
}

/*
"sandbox/file" is a regular file
"sandbox/symlink"is a symlink
"sandbox/pipe"is a name IPC pipe
"sandbox/dir" is a directory
"sandbox/sock"is a named IPC socket
"/dev/null"is a character device
"/dev/sda" is a block device
"/sandbox/no"does not exists
*/