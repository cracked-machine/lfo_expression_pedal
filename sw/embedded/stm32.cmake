message("\n** Configuring STM32 Environment **")
message("** Selected Kit: ${CMAKE_C_COMPILER} **\n")

set(DEVICE              STM32G071xx)
set(MCU_CORE		    -mcpu=cortex-m0plus)
set(LINKER_SCRIPT       ${CMAKE_SOURCE_DIR}/sw/embedded/src/STM32G071CBUX_FLASH.ld)
set(WARNINGS            -Wall)
set(NANO_SPECS          --specs=nano.specs)
set(SOFT_FP             -mfloat-abi=soft )
set(HEX_NAME            build.hex)
set(THUMB               -mthumb)
set(GNU_VER             -std=gnu11)
set(MAP_NAME            build.map)

# Set the device target otherwise `CMSIS/Device/ST/STM32L0xx/Include/stm32l0xx.h` complains.
add_compile_definitions(${DEVICE})

target_compile_options(${BUILD_NAME} PRIVATE
    # # C 
    $<$<COMPILE_LANGUAGE:C>:
        ${MCU_CORE}
        ${THUMB}
        ${WARNINGS} 
        ${NANO_SPECS}
        ${SOFT_FP}
        ${GNU_VER}
        -fstack-usage 
        -ffunction-sections 
        -fdata-sections
        -Wl,--gc-sections

    >
    $<$<AND:$<COMPILE_LANGUAGE:C>,$<CONFIG:DEBUG>>:
        -g3
        -O0
    >
    
    # # C++
    $<$<COMPILE_LANGUAGE:CXX>:
        ${MCU_CORE}
        ${WARNINGS} 
        ${NANO_SPECS}
        ${SOFT_FP}
        ${THUMB}
        -Wno-volatile
    >
    $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CONFIG:DEBUG>>:
        -g3
        -O0
    >
    # Asm
    $<$<COMPILE_LANGUAGE:ASM>:
        ${MCU_CORE}
        ${NANO_SPECS}
        ${SOFT_FP}
        ${THUMB}
        -c 
        -x assembler-with-cpp          
   

    >
    $<$<AND:$<COMPILE_LANGUAGE:ASM>,$<CONFIG:DEBUG>>:
        -g3
        -O0
        -DDEBUG
    >

)

# Linker settings
set(CMAKE_EXE_LINKER_FLAGS  "-T${LINKER_SCRIPT} -Wl,-Map=${MAP_NAME} ${NANO_SPECS} ${MCU_CORE} ${THUMB} " CACHE INTERNAL "exe link flags")


# target_link_options(${BUILD_NAME} PUBLIC "-mcpu=cortex-m0plus -T${LINKER_SCRIPT} --specs=nosys.specs -Wl,-Map=${MAP_NAME} -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group")

# This must come after compiler/linker settings
enable_language(C)
enable_language(CXX)
enable_language(ASM)




