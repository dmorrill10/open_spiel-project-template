#ifndef EXAMPLE_CODE_H_
#define EXAMPLE_CODE_H_

#include "open_spiel/spiel.h"

namespace example {
std::shared_ptr<const open_spiel::Game> LoadKuhnPoker();
}  // namespace example

#endif  // EXAMPLE_CODE_H_
