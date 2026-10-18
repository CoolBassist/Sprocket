#include "saveManager.hpp"

#include <fstream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <string_view>

namespace sprocket::managers {

constexpr std::string_view alphabet =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

std::string encodeBase64(std::string_view input) {
  std::string output;
  for (std::size_t i = 0; i < input.size(); i += 3) {
    const auto a = static_cast<unsigned char>(input[i]);
    const auto b =
        i + 1 < input.size() ? static_cast<unsigned char>(input[i + 1]) : 0;
    const auto c =
        i + 2 < input.size() ? static_cast<unsigned char>(input[i + 2]) : 0;
    output += alphabet[a >> 2];
    output += alphabet[((a & 3) << 4) | (b >> 4)];
    output += i + 1 < input.size() ? alphabet[((b & 15) << 2) | (c >> 6)] : '=';
    output += i + 2 < input.size() ? alphabet[c & 63] : '=';
  }
  return output;
}

std::string decodeBase64(std::string_view input) {
  const auto invalid = [] {
    throw std::invalid_argument("Invalid Base64 save data");
  };
  if (input.size() % 4 != 0) {
    invalid();
  }
  std::string output;
  for (std::size_t i = 0; i < input.size(); i += 4) {
    unsigned int values[4] = {};
    for (std::size_t j = 0; j < 4; ++j) {
      if (input[i + j] == '=' && j >= 2) {
        continue;
      }
      const auto value = alphabet.find(input[i + j]);
      if (value == std::string_view::npos) {
        invalid();
      }
      values[j] = static_cast<unsigned int>(value);
    }
    const bool pad2 = input[i + 2] == '=';
    const bool pad3 = input[i + 3] == '=';
    if ((pad2 && !pad3) || ((pad2 || pad3) && i + 4 != input.size()) ||
        (pad2 && (values[1] & 15)) || (pad3 && !pad2 && (values[2] & 3))) {
      invalid();
    }
    output += static_cast<char>((values[0] << 2) | (values[1] >> 4));
    if (!pad2) {
      output += static_cast<char>((values[1] << 4) | (values[2] >> 2));
    }
    if (!pad3) {
      output += static_cast<char>((values[2] << 6) | values[3]);
    }
  }
  return output;
}

void detail::writeSaveFile(const std::filesystem::path &path,
                           const sprocket::utils::SaveData &data) {
  const auto encoded = encodeBase64(data.toJson().dump());
  std::ofstream file(path, std::ios::binary | std::ios::trunc);
  if (!file) {
    throw std::runtime_error("Unable to open save file for writing");
  }
  file << encoded;
  file.close();
  if (!file) {
    throw std::runtime_error("Unable to write save file");
  }
}

void detail::readSaveFile(const std::filesystem::path &path,
                          sprocket::utils::SaveData &data) {
  std::ifstream file(path, std::ios::binary);
  if (!file) {
    if (!std::filesystem::exists(path)) {
      return;
    }
    throw std::runtime_error("Unable to open save file for reading");
  }
  const std::string encoded{std::istreambuf_iterator<char>(file),
                            std::istreambuf_iterator<char>()};
  if (file.bad()) {
    throw std::runtime_error("Unable to read save file");
  }
  data.fromJson(nlohmann::json::parse(decodeBase64(encoded)));
}

} // namespace sprocket::managers
