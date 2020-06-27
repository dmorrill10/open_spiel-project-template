# `add_library` is used when you have a list of `.cc` files that you want
# to export as a library that can be consumed by other objects or executables.
# E.g., the object file generated from `code.cc` will be added to a new
# library called `open_spiel_project_template_example` and can be referenced
# as `$<TARGET_OBJECTS:open_spiel_project_template_example>`.
add_library(open_spiel_project_template_example OBJECT code.cc)

# `add_executable` and `target_link_libraries` are used to build
# executables, including tests.
add_executable(code_test
  code_test.cc
  $<TARGET_OBJECTS:open_spiel_project_template_example>
  ${OPEN_SPIEL_OBJECTS})
target_link_libraries(code_test ${ABSL})

# If the executable you are building is a test, you can use `add_test` so that
# cmake will register it as such. Then it will be executed when you run
# `ctest`.
add_test(code_test code_test)
