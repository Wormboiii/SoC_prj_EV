
cmake_minimum_required(VERSION 3.15)
project(bsp)

# Use CMAKE_LIBRARY_PATH in link_directories
link_directories(${CMAKE_LIBRARY_PATH})
        
set(DRIVER_TARGETS gpio;iic;uartlite;bram)
set(DRIVER_LOCATIONS /media/wonhyeok/data/XILINX/2025.1/Vitis/data/embeddedsw/XilinxProcessorIPLib/drivers/gpio_v4_12;/media/wonhyeok/data/XILINX/2025.1/Vitis/data/embeddedsw/XilinxProcessorIPLib/drivers/iic_v3_13;/media/wonhyeok/data/XILINX/2025.1/Vitis/data/embeddedsw/XilinxProcessorIPLib/drivers/uartlite_v3_11;/media/wonhyeok/data/XILINX/2025.1/Vitis/data/embeddedsw/XilinxProcessorIPLib/drivers/bram_v4_12)

list(LENGTH DRIVER_TARGETS no_of_drivers)
set(index 0)

while(${index} LESS ${no_of_drivers})
    list(GET DRIVER_TARGETS ${index} drv)
    list(GET DRIVER_LOCATIONS ${index} drv_dir)
    set(exp_dir "${drv_dir}/examples")
    add_custom_target(
        ${drv}_example ALL
        COMMAND lopper -f -O /home/wonhyeok/VSC_works/Vitis_prj/PF_SoC_EV_test4/microblaze_riscv_0/standalone_microblaze_riscv_0/bsp/libsrc/${drv} /home/wonhyeok/VSC_works/Vitis_prj/PF_SoC_EV_test4/microblaze_riscv_0/standalone_microblaze_riscv_0/bsp/hw_artifacts/microblaze_riscv_0_baremetal.dts -- bmcmake_metadata_xlnx microblaze_riscv_0 ${exp_dir} drvcmake_metadata
        BYPRODUCTS x${drv}_exlist.yaml)
    MATH(EXPR index "${index}+1")
endwhile()
