#include "example/code.h"

#include "open_spiel/spiel.h"

namespace example {
std::shared_ptr<const open_spiel::Game> LoadKuhnPoker() {
  return open_spiel::LoadGame("kuhn_poker");
}
}  // namespace example
