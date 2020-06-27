#include "example/code.h"

#include <functional>
#include <string>
#include <unordered_set>

namespace example {
namespace {

static void _ForEachState(
    std::unordered_set<std::string>& already_observed,
    const open_spiel::State& state,
    const std::function<void(const open_spiel::State&)>& f, int player) {
  if (state.IsTerminal()) {
    return;
  } else if (state.IsChanceNode()) {
    for (const auto [chance_action, _] : state.ChanceOutcomes()) {
      _ForEachState(already_observed, *state.Child(chance_action), f, player);
    }
    return;
  }
  const std::string info_state = state.InformationStateString();
  if (player < 0 || player == state.CurrentPlayer()) {
    if (already_observed.find(info_state) == already_observed.end()) {
      f(state);
      already_observed.emplace(std::move(info_state));
    };
  }
  for (auto action : state.LegalActions()) {
    _ForEachState(already_observed, *state.Child(action), f, player);
  }
}

static void ForEachState(const open_spiel::State& state,
                         const std::function<void(const open_spiel::State&)>& f,
                         int player) {
  std::unordered_set<std::string> already_observed;
  _ForEachState(already_observed, state, f, player);
}

void PrintKuhnHistories() {
  std::shared_ptr<const open_spiel::Game> game = LoadKuhnPoker();
  std::unique_ptr<open_spiel::State> root = game->NewInitialState();

  std::vector<std::string> expected_strings = {
      "0 1", "0 1 0", "0 1 0 1", "0 1 1", "0 2 0", "0 2 1",
      "1 0", "1 0 0", "1 0 0 1", "1 0 1", "2 0",   "2 0 0 1"};
  size_t i = 0;
  ForEachState(
      *root,
      [&i, &expected_strings](const open_spiel::State& state) {
        std::cout << state.HistoryString() << std::endl;
        SPIEL_CHECK_EQ(state.HistoryString(), expected_strings[i]);
        ++i;
      },
      -1);
  std::cout
      << "Success, all Kuhn history strings printed in the expected order."
      << std::endl;
}

}  // namespace
}  // namespace example

int main(int argc, char** argv) { example::PrintKuhnHistories(); }
