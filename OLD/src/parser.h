#pragma once

#include <string>
#include <regex>
#include <algorithm>
#include "polynomial.h"

// Function declarations
Atom parseAtom(std::string term);
Polynomial parsePolynom(std::string poly);
