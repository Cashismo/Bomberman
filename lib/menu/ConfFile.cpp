#include "ConfFile.hpp"

ConfFile::ConfFile(const std::string &name) {
  _name = name;
  _tokens.push_back("nb_ai");
  _tokens.push_back("nb_players");
  _tokens.push_back("map");
  _tokens.push_back("up");
  _tokens.push_back("down");
  _tokens.push_back("left");
  _tokens.push_back("right");
  _tokens.push_back("bomb");
  _tokens.push_back("up");
  _tokens.push_back("down");
  _tokens.push_back("left");
  _tokens.push_back("right");
  _tokens.push_back("bomb");
  _tokens.push_back("spec_mode");
  _tokens.push_back("game_mode");
  _datas[NB_AI] = "";
  _datas[NB_PLAYERS] = "";
  _datas[MAP] = "";
  _datas[UP_1] = "";
  _datas[DOWN_1] = "";
  _datas[LEFT_1] = "";
  _datas[RIGHT_1] = "";
  _datas[BOMB_1] = "";
  _datas[UP_2] = "";
  _datas[DOWN_2] = "";
  _datas[LEFT_2] = "";
  _datas[RIGHT_2] = "";
  _datas[BOMB_2] = "";
  _datas[SPEC_MODE] = "";
  _datas[GAME_MODE] = "";
  if (openFile() == false)
    return;
  if (parseFile() == false)
    return;
}

const std::map<ConfFile::Data, std::string> &ConfFile::getMap() {
  return _datas;
}

bool ConfFile::defaultConfFile(const std::string &name) {
  std::ofstream file;
  file.open(name);
  std::wstring str;
  if (file.is_open()) {
    file << "#Bomberman conf file" << std::endl;
    file << "#you can set:" << std::endl;
    file << "#map, nb_player, height, width, score_files" << std::endl;
    file << std::endl;
    file << "[OPTIONS]" << std::endl;
    file << "nb_ai=2" << std::endl;
    file << "nb_players=2" << std::endl;
    file << "map=map.txt" << std::endl;
    file << std::endl;
    file << "[PLAYER 1]" << std::endl;
    file << "up=Z" << std::endl;
    file << "down=S" << std::endl;
    file << "left=Q" << std::endl;
    file << "right=D" << std::endl;
    file << "bomb=X" << std::endl;
    file << std::endl;
    file << "[PLAYER 2]" << std::endl;
    file << "up=O" << std::endl;
    file << "down=K" << std::endl;
    file << "left=L" << std::endl;
    file << "right=M" << std::endl;
    file << "bomb=N" << std::endl;
    file << std::endl;
    file << "[OTHER]" << std::endl;
    file << "spec_mode=G" << std::endl;
    file << "game_mode=H" << std::endl;
  } else {
    return false;
  }
  return true;
}

bool ConfFile::openFile() {
  std::string line;
  _file.open(_name);
  if (_file.is_open()) {
    while (std::getline(_file, line))
      if (line.find("=") != std::string::npos)
        _infos.push_back(line);
    if (_tokens.size() != _infos.size()) {
      std::cerr << "ERROR: too much or enough infos." << std::endl;
      defaultConfFile("bomberman.conf");
      return true;
    }
  } else {
    defaultConfFile("bomberman.conf");
    std::cerr << "ERROR: fail open." << std::endl;
    return true;
  }
  return true;
}

bool ConfFile::parseFile() {
  auto index = 0;
  std::map<Data, std::string>::iterator indexMap = _datas.begin();
  for (const auto &e : _infos) {
    std::stringstream tmp;
    std::stringstream tmp2;
    for (size_t i = 0; i < e.find("="); i++)
      tmp << e[i];
    for (auto ii = e.find("=") + 1; ii < e.size(); ii++)
      tmp2 << e[ii];
    if (tmp.str() == _tokens[index]) {
      indexMap->second = tmp2.str();
      indexMap++;
    } else {
      defaultConfFile("bomberman.conf");
      std::cerr << "ERROR: corrupt file." << std::endl;
      return true;
    }
    index++;
  }
  return true;
}

void ConfFile::dumpData() {
  for (const auto &e : _datas) {
    std::cout << e.first << " -------- " << e.second << std::endl;
  }
}
