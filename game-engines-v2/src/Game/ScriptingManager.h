#pragma once

#include "/home/vboxuser/Desktop/juegos/MOVEMENTS-main/game-engines-v2/sol2/include/sol/sol.hpp"
#include <string>

class ScriptingManager {
public:
  static sol::state lua;

  static void init();
  static void runScript(const std::string& script);
  static void runScriptFile(const std::string& scriptFile);
};

