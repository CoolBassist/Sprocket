#pragma once

#include <nlohmann/json.hpp>

namespace sprocket::utils {

class SaveData {
public:
  virtual ~SaveData() = default;
  virtual nlohmann::json toJson() const = 0;
  virtual void fromJson(const nlohmann::json &json) = 0;
};

} // namespace sprocket::utils
