add_custom_target(docs)

if(SPHINX_FOUND)
  add_subdirectory(sphinx)
endif()

find_package(Doxygen QUIET)
if(DOXYGEN_FOUND)
  add_subdirectory(doxygen)
endif()

if(NOT SPHINX_FOUND AND NOT DOXYGEN_FOUND)
  message(WARNING "ENABLE_DOCUMENTATION=On, but Sphinx or Doxygen not found. \
    Documentation won't be built.")
endif()
