# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "perception: 4 messages, 0 services")

set(MSG_I_FLAGS "-Iperception:/home/helshafe/ECE418_Project/src/perception/msg;-Igeometry_msgs:/opt/ros/noetic/share/geometry_msgs/cmake/../msg;-Isensor_msgs:/opt/ros/noetic/share/sensor_msgs/cmake/../msg;-Istd_msgs:/opt/ros/noetic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(perception_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/helshafe/ECE418_Project/src/perception/msg/Observation.msg" NAME_WE)
add_custom_target(_perception_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "perception" "/home/helshafe/ECE418_Project/src/perception/msg/Observation.msg" ""
)

get_filename_component(_filename "/home/helshafe/ECE418_Project/src/perception/msg/Observations.msg" NAME_WE)
add_custom_target(_perception_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "perception" "/home/helshafe/ECE418_Project/src/perception/msg/Observations.msg" "perception/Observation"
)

get_filename_component(_filename "/home/helshafe/ECE418_Project/src/perception/msg/Landmark.msg" NAME_WE)
add_custom_target(_perception_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "perception" "/home/helshafe/ECE418_Project/src/perception/msg/Landmark.msg" ""
)

get_filename_component(_filename "/home/helshafe/ECE418_Project/src/perception/msg/Landmarks.msg" NAME_WE)
add_custom_target(_perception_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "perception" "/home/helshafe/ECE418_Project/src/perception/msg/Landmarks.msg" "perception/Landmark"
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(perception
  "/home/helshafe/ECE418_Project/src/perception/msg/Observation.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/perception
)
_generate_msg_cpp(perception
  "/home/helshafe/ECE418_Project/src/perception/msg/Observations.msg"
  "${MSG_I_FLAGS}"
  "/home/helshafe/ECE418_Project/src/perception/msg/Observation.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/perception
)
_generate_msg_cpp(perception
  "/home/helshafe/ECE418_Project/src/perception/msg/Landmark.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/perception
)
_generate_msg_cpp(perception
  "/home/helshafe/ECE418_Project/src/perception/msg/Landmarks.msg"
  "${MSG_I_FLAGS}"
  "/home/helshafe/ECE418_Project/src/perception/msg/Landmark.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/perception
)

### Generating Services

### Generating Module File
_generate_module_cpp(perception
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/perception
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(perception_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(perception_generate_messages perception_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/helshafe/ECE418_Project/src/perception/msg/Observation.msg" NAME_WE)
add_dependencies(perception_generate_messages_cpp _perception_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/helshafe/ECE418_Project/src/perception/msg/Observations.msg" NAME_WE)
add_dependencies(perception_generate_messages_cpp _perception_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/helshafe/ECE418_Project/src/perception/msg/Landmark.msg" NAME_WE)
add_dependencies(perception_generate_messages_cpp _perception_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/helshafe/ECE418_Project/src/perception/msg/Landmarks.msg" NAME_WE)
add_dependencies(perception_generate_messages_cpp _perception_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(perception_gencpp)
add_dependencies(perception_gencpp perception_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS perception_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(perception
  "/home/helshafe/ECE418_Project/src/perception/msg/Observation.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/perception
)
_generate_msg_eus(perception
  "/home/helshafe/ECE418_Project/src/perception/msg/Observations.msg"
  "${MSG_I_FLAGS}"
  "/home/helshafe/ECE418_Project/src/perception/msg/Observation.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/perception
)
_generate_msg_eus(perception
  "/home/helshafe/ECE418_Project/src/perception/msg/Landmark.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/perception
)
_generate_msg_eus(perception
  "/home/helshafe/ECE418_Project/src/perception/msg/Landmarks.msg"
  "${MSG_I_FLAGS}"
  "/home/helshafe/ECE418_Project/src/perception/msg/Landmark.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/perception
)

### Generating Services

### Generating Module File
_generate_module_eus(perception
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/perception
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(perception_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(perception_generate_messages perception_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/helshafe/ECE418_Project/src/perception/msg/Observation.msg" NAME_WE)
add_dependencies(perception_generate_messages_eus _perception_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/helshafe/ECE418_Project/src/perception/msg/Observations.msg" NAME_WE)
add_dependencies(perception_generate_messages_eus _perception_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/helshafe/ECE418_Project/src/perception/msg/Landmark.msg" NAME_WE)
add_dependencies(perception_generate_messages_eus _perception_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/helshafe/ECE418_Project/src/perception/msg/Landmarks.msg" NAME_WE)
add_dependencies(perception_generate_messages_eus _perception_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(perception_geneus)
add_dependencies(perception_geneus perception_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS perception_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(perception
  "/home/helshafe/ECE418_Project/src/perception/msg/Observation.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/perception
)
_generate_msg_lisp(perception
  "/home/helshafe/ECE418_Project/src/perception/msg/Observations.msg"
  "${MSG_I_FLAGS}"
  "/home/helshafe/ECE418_Project/src/perception/msg/Observation.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/perception
)
_generate_msg_lisp(perception
  "/home/helshafe/ECE418_Project/src/perception/msg/Landmark.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/perception
)
_generate_msg_lisp(perception
  "/home/helshafe/ECE418_Project/src/perception/msg/Landmarks.msg"
  "${MSG_I_FLAGS}"
  "/home/helshafe/ECE418_Project/src/perception/msg/Landmark.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/perception
)

### Generating Services

### Generating Module File
_generate_module_lisp(perception
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/perception
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(perception_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(perception_generate_messages perception_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/helshafe/ECE418_Project/src/perception/msg/Observation.msg" NAME_WE)
add_dependencies(perception_generate_messages_lisp _perception_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/helshafe/ECE418_Project/src/perception/msg/Observations.msg" NAME_WE)
add_dependencies(perception_generate_messages_lisp _perception_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/helshafe/ECE418_Project/src/perception/msg/Landmark.msg" NAME_WE)
add_dependencies(perception_generate_messages_lisp _perception_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/helshafe/ECE418_Project/src/perception/msg/Landmarks.msg" NAME_WE)
add_dependencies(perception_generate_messages_lisp _perception_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(perception_genlisp)
add_dependencies(perception_genlisp perception_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS perception_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(perception
  "/home/helshafe/ECE418_Project/src/perception/msg/Observation.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/perception
)
_generate_msg_nodejs(perception
  "/home/helshafe/ECE418_Project/src/perception/msg/Observations.msg"
  "${MSG_I_FLAGS}"
  "/home/helshafe/ECE418_Project/src/perception/msg/Observation.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/perception
)
_generate_msg_nodejs(perception
  "/home/helshafe/ECE418_Project/src/perception/msg/Landmark.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/perception
)
_generate_msg_nodejs(perception
  "/home/helshafe/ECE418_Project/src/perception/msg/Landmarks.msg"
  "${MSG_I_FLAGS}"
  "/home/helshafe/ECE418_Project/src/perception/msg/Landmark.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/perception
)

### Generating Services

### Generating Module File
_generate_module_nodejs(perception
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/perception
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(perception_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(perception_generate_messages perception_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/helshafe/ECE418_Project/src/perception/msg/Observation.msg" NAME_WE)
add_dependencies(perception_generate_messages_nodejs _perception_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/helshafe/ECE418_Project/src/perception/msg/Observations.msg" NAME_WE)
add_dependencies(perception_generate_messages_nodejs _perception_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/helshafe/ECE418_Project/src/perception/msg/Landmark.msg" NAME_WE)
add_dependencies(perception_generate_messages_nodejs _perception_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/helshafe/ECE418_Project/src/perception/msg/Landmarks.msg" NAME_WE)
add_dependencies(perception_generate_messages_nodejs _perception_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(perception_gennodejs)
add_dependencies(perception_gennodejs perception_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS perception_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(perception
  "/home/helshafe/ECE418_Project/src/perception/msg/Observation.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/perception
)
_generate_msg_py(perception
  "/home/helshafe/ECE418_Project/src/perception/msg/Observations.msg"
  "${MSG_I_FLAGS}"
  "/home/helshafe/ECE418_Project/src/perception/msg/Observation.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/perception
)
_generate_msg_py(perception
  "/home/helshafe/ECE418_Project/src/perception/msg/Landmark.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/perception
)
_generate_msg_py(perception
  "/home/helshafe/ECE418_Project/src/perception/msg/Landmarks.msg"
  "${MSG_I_FLAGS}"
  "/home/helshafe/ECE418_Project/src/perception/msg/Landmark.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/perception
)

### Generating Services

### Generating Module File
_generate_module_py(perception
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/perception
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(perception_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(perception_generate_messages perception_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/helshafe/ECE418_Project/src/perception/msg/Observation.msg" NAME_WE)
add_dependencies(perception_generate_messages_py _perception_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/helshafe/ECE418_Project/src/perception/msg/Observations.msg" NAME_WE)
add_dependencies(perception_generate_messages_py _perception_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/helshafe/ECE418_Project/src/perception/msg/Landmark.msg" NAME_WE)
add_dependencies(perception_generate_messages_py _perception_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/helshafe/ECE418_Project/src/perception/msg/Landmarks.msg" NAME_WE)
add_dependencies(perception_generate_messages_py _perception_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(perception_genpy)
add_dependencies(perception_genpy perception_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS perception_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/perception)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/perception
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(perception_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()
if(TARGET sensor_msgs_generate_messages_cpp)
  add_dependencies(perception_generate_messages_cpp sensor_msgs_generate_messages_cpp)
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(perception_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/perception)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/perception
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_eus)
  add_dependencies(perception_generate_messages_eus geometry_msgs_generate_messages_eus)
endif()
if(TARGET sensor_msgs_generate_messages_eus)
  add_dependencies(perception_generate_messages_eus sensor_msgs_generate_messages_eus)
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(perception_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/perception)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/perception
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(perception_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()
if(TARGET sensor_msgs_generate_messages_lisp)
  add_dependencies(perception_generate_messages_lisp sensor_msgs_generate_messages_lisp)
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(perception_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/perception)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/perception
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_nodejs)
  add_dependencies(perception_generate_messages_nodejs geometry_msgs_generate_messages_nodejs)
endif()
if(TARGET sensor_msgs_generate_messages_nodejs)
  add_dependencies(perception_generate_messages_nodejs sensor_msgs_generate_messages_nodejs)
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(perception_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/perception)
  install(CODE "execute_process(COMMAND \"/usr/bin/python3\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/perception\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/perception
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(perception_generate_messages_py geometry_msgs_generate_messages_py)
endif()
if(TARGET sensor_msgs_generate_messages_py)
  add_dependencies(perception_generate_messages_py sensor_msgs_generate_messages_py)
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(perception_generate_messages_py std_msgs_generate_messages_py)
endif()
