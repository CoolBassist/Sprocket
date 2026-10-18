#pragma once

#include "../utils/saveData.hpp"
#include <filesystem>

namespace sprocket::managers {

class SaveManager {
public:
  static void save(const std::filesystem::path &path,
                   const sprocket::utils::SaveData &data);

  static void load(const std::filesystem::path &path,
                   sprocket::utils::SaveData &data);
};

} // namespace sprocket::managers
