#pragma once

#include <iostream>
#include <fstream>
#include <mutex>
#include <thread>
#include <memory>
#include <string>
#include <string_view>
#include <chrono>
#include <ctime>
#include <format>
#include <asio.hpp>


#define BUFFER_SIZE (1024 >> 4)
#define Q_SIZE 1024
