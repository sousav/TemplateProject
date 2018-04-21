include_directories(
  PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/Includes/
)

target_sources(${NAME}
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/Includes/SimpleGlob.h
        ${CMAKE_CURRENT_LIST_DIR}/Includes/ICreator.h
        ${CMAKE_CURRENT_LIST_DIR}/Includes/ACreator.h
        ${CMAKE_CURRENT_LIST_DIR}/Sources/ACreator.cpp
)
