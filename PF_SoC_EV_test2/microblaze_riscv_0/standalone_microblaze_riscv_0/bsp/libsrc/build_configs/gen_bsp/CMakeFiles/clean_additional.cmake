# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "")
  file(REMOVE_RECURSE
  "/home/wonhyeok/VSC_works/Vitis_prj/PF_SoC_EV_test2/microblaze_riscv_0/standalone_microblaze_riscv_0/bsp/include/sleep.h"
  "/home/wonhyeok/VSC_works/Vitis_prj/PF_SoC_EV_test2/microblaze_riscv_0/standalone_microblaze_riscv_0/bsp/include/xiltimer.h"
  "/home/wonhyeok/VSC_works/Vitis_prj/PF_SoC_EV_test2/microblaze_riscv_0/standalone_microblaze_riscv_0/bsp/include/xtimer_config.h"
  "/home/wonhyeok/VSC_works/Vitis_prj/PF_SoC_EV_test2/microblaze_riscv_0/standalone_microblaze_riscv_0/bsp/lib/libxiltimer.a"
  )
endif()
