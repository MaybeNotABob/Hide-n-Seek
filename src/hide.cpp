#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <random>

#define MAX_DEPTH 10
#define MAX_DIRS 10

const char validSymbols[] = {"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890"};

unsigned int randomIntRange(const unsigned int minValue, const unsigned int maxValue)
{
  std::random_device                  rand_dev;
  std::mt19937                        generator(rand_dev());
  std::uniform_int_distribution<int>  distr(minValue, maxValue);
  return distr(generator);
}

std::string getRandomDirName()
{
  const unsigned int MAX_LEN_DIR_NAME = 7;
  unsigned int lenDirName = randomIntRange(1, MAX_LEN_DIR_NAME);
  std::string result;

  for (int i = 0; i < lenDirName; i++) {
    result += validSymbols[randomIntRange(0, sizeof(validSymbols))];
  }
  return result;
}

void generateDirs()
{
  std::filesystem::path pwd = std::filesystem::current_path();
  pwd /= "hideNseek";
  std::filesystem::create_directories(pwd.string());

  unsigned int depth_counter = 0;
  unsigned int num_dirs = 0;
  unsigned int index_dir_to_follow = 0;
  std::string rand_dir_name;
  std::string tmp_store_dir_name;

  for (depth_counter = 0; depth_counter < MAX_DEPTH; depth_counter++) {

    num_dirs = randomIntRange(1, MAX_DIRS);
    index_dir_to_follow = randomIntRange(1, num_dirs);

    for (int i = 1; i != num_dirs + 1; i++) {

      rand_dir_name = getRandomDirName().c_str();
      std::filesystem::create_directories(pwd.string() + "\\" + rand_dir_name);

      if (index_dir_to_follow == i){
        tmp_store_dir_name = rand_dir_name;
      }
    } 

    pwd /= tmp_store_dir_name;
  } ;
 
 
  std::string szFileName = pwd.string() + "\\treasure.txt";
  std::fstream fs (szFileName, fs.binary | fs.trunc | fs.in | fs.out);
  if (fs.is_open()){
    fs << "Arrghh!!! here be my cyber buried treasure mate!\n";
    fs.close();
  }   
 

  std::cout << pwd.string() << std::endl; 
  
}

int main()
{

generateDirs();

getchar();

}