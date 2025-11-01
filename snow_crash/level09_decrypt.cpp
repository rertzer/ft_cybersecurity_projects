#include <fstream>
#include <iostream>
#include <string>

int main(int ac, char **av) {
  std::string line;
  std::string res;
  std::ifstream file(av[1]);

  if (file.is_open()) {
    while (std::getline(file, line)) {
      int i = 0;
      while (line[i]) {
        res += line[i] - i;
        i++;
      }
      std::cout << res << std::endl;
    }
    file.close();
  } else {
    std::cout << "Unable to open file";
  }

  return 0;
}
