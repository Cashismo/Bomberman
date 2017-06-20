#ifndef __CONFFILE_HPP__
#define __CONFFILE_HPP__

#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

class ConfFile {
public:
  enum Data {
    NB_AI,
    NB_PLAYERS,
    MAP,
    UP_1,
    DOWN_1,
    LEFT_1,
    RIGHT_1,
    BOMB_1,
    UP_2,
    DOWN_2,
    LEFT_2,
    RIGHT_2,
    BOMB_2,
    SPEC_MODE,
    GAME_MODE,
  };
  ConfFile(const std::string &name);
  void dumpData();
  const std::map<Data, std::string> &getMap();
  bool openFile();
  bool parseFile();
  bool defaultConfFile(const std::string &name);

private:
  std::map<Data, std::string> _datas;
  std::vector<std::string> _tokens;
  std::vector<std::string> _infos;
  std::string _name;
  std::ifstream _file;
};

#endif
