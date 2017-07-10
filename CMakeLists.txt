cmake_minimum_required(VERSION 2.8)

if(NOT HOSTFILE)
  if(CMAKE_SYSTEM_NAME STREQUAL Linux)
    set(HOSTFILE etc/linux.c)
  elseif(CMAKE_SYSTEM_NAME STREQUAL SunOS)
    set(HOSTFILE etc/solaris.c)
  elseif(CMAKE_SYSTEM_NAME STREQUAL Windows)
    set(HOSTFILE etc/win32.c)
  else()
    message(WARNING "Platform detection failed, assuming HOSTFILE=etc/linux.c")
    set(HOSTFILE etc/linux.c)
  endif()
endif()

if(NOT CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()

add_definitions(-DLCCDIR="${CMAKE_INSTALL_PREFIX}/lib/lcc/")
include_directories(src)

add_executable(bprint etc/bprint.c)
add_executable(cpp
               cpp/cpp.c cpp/eval.c cpp/getopt.c cpp/hideset.c cpp/include.c
               cpp/lex.c cpp/macro.c cpp/nlist.c cpp/tokens.c cpp/unix.c)
add_executable(lburg lburg/lburg.c lburg/gram.c)
add_executable(lcc etc/lcc.c ${HOSTFILE})
add_executable(ops etc/ops.c)
add_executable(rcc
               ${CMAKE_BINARY_DIR}/alpha.c ${CMAKE_BINARY_DIR}/dagcheck.c
               ${CMAKE_BINARY_DIR}/mips.c ${CMAKE_BINARY_DIR}/sparc.c
               ${CMAKE_BINARY_DIR}/x86.c ${CMAKE_BINARY_DIR}/x86linux.c
               src/alloc.c src/bind.c src/bytecode.c src/dag.c src/decl.c
               src/enode.c src/error.c src/event.c src/expr.c src/gen.c
               src/init.c src/inits.c src/input.c src/lex.c src/list.c
               src/main.c src/null.c src/output.c src/prof.c src/profio.c
               src/simp.c src/stab.c src/stmt.c src/string.c src/sym.c
               src/symbolic.c src/trace.c src/tree.c src/types.c)

install(TARGETS lcc DESTINATION bin)
install(TARGETS rcc DESTINATION lib/lcc)

if(HOSTFILE MATCHES linux.c)
  install(TARGETS cpp DESTINATION lib/lcc/gcc)
else()
  install(TARGETS cpp DESTINATION lib/lcc)
endif()

macro(lburg x)
  add_custom_command(
      COMMAND lburg ${CMAKE_SOURCE_DIR}/src/${x}.md ${CMAKE_BINARY_DIR}/${x}.c
      DEPENDS lburg ${CMAKE_SOURCE_DIR}/src/${x}.md
      OUTPUT ${CMAKE_BINARY_DIR}/${x}.c)
endmacro()

lburg(alpha)
lburg(dagcheck)
lburg(mips)
lburg(sparc)
lburg(x86)
lburg(x86linux)
