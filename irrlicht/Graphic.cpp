#include "../include/Graphic.hpp"
#include "../include/Menu.hpp"
#include "../include/Object.hpp"
#include <unistd.h>

Graphic::Graphic() {
  n = 0;
  first_time = true;
  first_wall = true;
  device = createDevice(irr::video::EDT_OPENGL,
                        irr::core::dimension2d<irr::u32>(1700, 900), 60, false,
                        false, false, &receiver);
  driver = device->getVideoDriver();
  smgr = device->getSceneManager();
  engine = irrklang::createIrrKlangDevice();
  smgr->addCameraSceneNode(0, irr::core::vector3df(1000, 1000, 500),
                           irr::core::vector3df(100, -2500, 500), 0, true);
  env = device->getGUIEnvironment();
  player_life[0][0] = 1;
  player_life[1][0] = 1;
  player_life[2][0] = 1;
  player_life[3][0] = 1;
  nb_bomb[0][0] = 1;
  nb_bomb[1][0] = 1;
  nb_bomb[2][0] = 1;
  nb_bomb[3][0] = 1;

  last[0][0] = 0;
  last[1][0] = 0;
  last[2][0] = 0;
  last[3][0] = 0;

  player_type[0][0] = -1;
  player_type[1][0] = -1;
  player_type[2][0] = -1;
  player_type[3][0] = -1;

  irr::gui::IGUISkin *skin = env->getSkin();
  font = env->getFont("assets/font20.xml");
  if (!font)
    exit(-1);
  if (font)
    skin->setFont(font);
  skin->setFont(env->getBuiltInFont(), irr::gui::EGDF_TOOLTIP);

  red = driver->getTexture("assets/coeur_rouge.png");
  grey = driver->getTexture("assets/coeur-gris.png");
  stone = driver->getTexture("assets/wall_inc.jpg");
  wall = driver->getTexture("assets/wall_break.jpg");
  //floor = driver->getTexture("assets/floor_x4.png");
  floor = driver->getTexture("assets/floor.jpg");
  fire = driver->getTexture("assets/fire.jpg");
  aleat = driver->getTexture("assets/aleatoire.png");
  echap = driver->getTexture("assets/EchapMenu.png");
  gameover = driver->getTexture("assets/gameOver.png");
  bomb = driver->getTexture("assets/bomb.png");
  obj_bomb = smgr->getMesh("assets/bomb.obj");
  obj_cube = smgr->getMesh("assets/cube.obj");
  obj_fire = smgr->getMesh("assets/fire.obj");
  obj_aleat = smgr->getMesh("assets/aleat.obj");
  irr::scene::ISceneNode *skybox =
      smgr->addSkyBoxSceneNode(driver->getTexture("assets/irrlicht2_up.jpg"),
                               driver->getTexture("assets/irrlicht2_dn.jpg"),
                               driver->getTexture("assets/irrlicht2_lf.jpg"),
                               driver->getTexture("assets/irrlicht2_rt.jpg"),
                               driver->getTexture("assets/irrlicht2_ft.jpg"),
                               driver->getTexture("assets/irrlicht2_bk.jpg"));
  if (!skybox)
    exit(-1);
  if (!obj_fire)
    exit(-1);
  if (!obj_aleat)
    exit(-1);
  if (!red || !grey || !stone || !wall || !floor || !fire || !aleat || !echap)
    exit(-1);
  if (!bomb || !obj_bomb || !gameover || !obj_cube)
    exit(-1);
  fps = false;
}

void Graphic::init() {
  if (!env->addImage(driver->getTexture("assets/bande.png"),
                     irr::core::position2di(0, 800)))
    exit(-1);
}

void Graphic::gameOver() {
  smgr->drawAll();
  driver->draw2DImage(gameover, irr::core::position2di(0, 0),
                      irr::core::rect<irr::s32>(0, 0, 1700, 900), 0,
                      irr::video::SColor(255, 255, 255, 255), true);
  driver->endScene();
  std::this_thread::sleep_for(std::chrono::seconds(3));
}

void Graphic::end() { device->drop(); }

void Graphic::loadbar(std::string bar) {
  smgr->drawAll();
  irr::video::ITexture *image = driver->getTexture(bar.c_str());

  if (!image)
    return;
  driver->beginScene(true, true, irr::video::SColor(1, 1, 1, 1));
  driver->draw2DImage(image, irr::core::position2di(0, 0),
                      irr::core::rect<irr::s32>(0, 0, 1700, 900), 0,
                      irr::video::SColor(255, 255, 255, 255), true);
  driver->endScene();
}

bool Graphic::setClickZone(int x1, int x2, int y1, int y2) {
  if (receiver.GetMouseState().Position.X > x1 &&
      receiver.GetMouseState().Position.X < x2 &&
      receiver.GetMouseState().Position.Y > y1 &&
      receiver.GetMouseState().Position.Y < y2)
    return true;
  return false;
}

int Graphic::echapView() {

  smgr->drawAll();
  driver->draw2DImage(echap, irr::core::position2di(0, 0),
                      irr::core::rect<irr::s32>(0, 0, 1700, 900), 0,
                      irr::video::SColor(255, 255, 255, 255), true);
  if (setClickZone(595, 1105, 190, 295) == true)
    driver->draw2DImage(bomb, irr::core::position2di(1100, 200),
                        irr::core::rect<irr::s32>(0, 0, 100, 100), 0,
                        irr::video::SColor(255, 255, 255, 255), true);
  if (setClickZone(595, 1105, 345, 445) == true)
    driver->draw2DImage(bomb, irr::core::position2di(1100, 350),
                        irr::core::rect<irr::s32>(0, 0, 100, 100), 0,
                        irr::video::SColor(255, 255, 255, 255), true);
  if (setClickZone(595, 1105, 495, 600) == true)
    driver->draw2DImage(bomb, irr::core::position2di(1100, 500),
                        irr::core::rect<irr::s32>(0, 0, 100, 100), 0,
                        irr::video::SColor(255, 255, 255, 255), true);
  if (getReceiver().GetMouseState().LeftButtonDown == true) {
    _event.EventType = irr::EET_MOUSE_INPUT_EVENT;
    _event.MouseInput.Event = irr::EMIE_LMOUSE_LEFT_UP;
    if (setClickZone(595, 1105, 190, 295) == true)
      return 1;
    if (setClickZone(595, 1105, 345, 445) == true) {
      Menu menu(this);
      menu.start();
      return 1;
    }
    if (setClickZone(595, 1105, 495, 600) == true)
      std::exit(0);
    std::cout << "X: " << receiver.GetMouseState().Position.X
              << " Y: " << receiver.GetMouseState().Position.Y << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    receiver.OnEvent(_event);
  }
  driver->endScene();
  return 0;
}

void Graphic::setEnv(irr::gui::IGUIEnvironment *_env) { env = _env; }

std::vector<Object> Graphic::create_column(int id) {
  std::vector<Object> column;

  column.reserve(map->getMap()[id].size());
  for (size_t i = 0; i < map->getMap()[id].size(); ++i) {
    Object tmp;
    column.emplace_back(tmp);
  }
  return column;
}

void Graphic::init_objects() {
  objects.reserve(map->getMap().size());
  for (size_t i = 0; i < map->getMap().size(); ++i) {
    auto tmp = create_column(i);
    tmp.shrink_to_fit();
    objects.emplace_back(std::move(tmp));
  }
}

void Graphic::disp_nb_bomb() {
  font->draw(std::to_wstring(nb_bomb[0][0]).c_str(),
             irr::core::rect<irr::s32>(60, 860, 1550, 900),
             irr::video::SColor(255, 255, 255, 255));
  if (fps == false)
    font->draw(std::to_wstring(nb_bomb[1][0]).c_str(),
               irr::core::rect<irr::s32>(485, 860, 1550, 900),
               irr::video::SColor(255, 255, 255, 255));
}

void Graphic::run() {
  int i = 0;
  if (first_time == true) {
    for (const auto &tmp : text) {
      env->addStaticText(
          tmp.c_str(),
          irr::core::rect<irr::s32>(pos[i].first, pos[i].second, 1550, 900));
      i += 1;
    }
    if (i == 2 || i == 1) {
      first_time = false;
    }
  }
  driver->beginScene(true, true, irr::video::SColor(120, 120, 120, 120));
  device->run();
  smgr->drawAll();
  env->drawAll();
  disp_life();
  disp_nb_bomb();
  driver->endScene();
}

void Graphic::disp_life() {
  font->draw(std::to_wstring(player_life[0][0]).c_str(),
             irr::core::rect<irr::s32>(60, 830, 1550, 900),
             irr::video::SColor(255, 255, 255, 255));
  if (fps == false)
    font->draw(std::to_wstring(player_life[1][0]).c_str(),
               irr::core::rect<irr::s32>(485, 830, 1550, 900),
               irr::video::SColor(255, 255, 255, 255));
}

void Graphic::display_first() {
  unsigned x = 0;
  unsigned y = 0;

  for (const auto &vector : map->getMap()) {
    x = 0;
    for (const auto &elem : vector) {
      if (elem->getSym() == 'x' && first_wall == true) {
        Object obj(smgr, driver, obj_cube, stone);
        obj.getObject()->setPosition(irr::core::vector3df(y, 35, x));
      } else if (elem->getSym() == 'w') {
        create(y / 47, x / 47, 'w');
      }
      if (first_wall == true) {
        Object obj(smgr, driver, obj_cube, floor);
        obj.getObject()->setPosition(irr::core::vector3df(y, 0, x));
      }
      x += 47;
    }
    y += 47;
  }
  first_wall = false;
}

void Graphic::remove(unsigned y, unsigned x) {
  objects[y][x].getObject()->remove();
}

void Graphic::create(unsigned y, unsigned x, char c) {
  if (c == 'a') {
    objects[y][x].create(smgr, driver, obj_aleat, aleat);
    objects[y][x].getObject()->setPosition(
        irr::core::vector3df(y * 47, 47, x * 47));
  } else if (c == 'b') {
    objects[y][x].create(smgr, driver, obj_bomb, NULL);
    objects[y][x].getObject()->setPosition(
        irr::core::vector3df(y * 47, 47, x * 47));
  } else if (c == 'e') {
    objects[y][x].create(smgr, driver, obj_fire, fire);
    objects[y][x].getObject()->setPosition(
        irr::core::vector3df(y * 47, 47, x * 47));
  } else if (c == 'w') {
    objects[y][x].create(smgr, driver, obj_cube, wall);
    objects[y][x].getObject()->setPosition(
        irr::core::vector3df(y * 47, 35, x * 47));
  }
}

void Graphic::addText(std::wstring buf, int x, int y) {
  std::pair<int, int> tmp;

  tmp.first = x;
  tmp.second = y;
  pos.push_back(tmp);
  text.push_back(buf);
}

void Graphic::setLife(int place, int nb_vie) { player_life[place][0] = nb_vie; }

void Graphic::setBomb(int place, int nb_vie) { nb_bomb[place][0] = nb_vie; }

void Graphic::resetSmgr() {
  smgr->clear();
  smgr = device->getSceneManager();
  smgr->addCameraSceneNode(0, irr::core::vector3df(1000, 1000, 500),
                           irr::core::vector3df(100, -2500, 500), 0, true);
  irr::scene::ISceneNode *skybox =
      smgr->addSkyBoxSceneNode(driver->getTexture("assets/irrlicht2_up.jpg"),
                               driver->getTexture("assets/irrlicht2_dn.jpg"),
                               driver->getTexture("assets/irrlicht2_lf.jpg"),
                               driver->getTexture("assets/irrlicht2_rt.jpg"),
                               driver->getTexture("assets/irrlicht2_ft.jpg"),
                               driver->getTexture("assets/irrlicht2_bk.jpg"));
  if (!skybox)
    exit(-1);
  skybox->setVisible(true);
}
