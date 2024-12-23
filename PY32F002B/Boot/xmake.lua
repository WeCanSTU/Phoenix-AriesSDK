add_rules("mode.debug", "mode.release")
set_targetdir("$(projectdir)/output")
add_linkdirs("User",
             "../../Sdk/AriesSDK/ARM-GCC")

target("Boot-HAL")
    set_kind("binary")
    set_extension(".elf")
    add_defines("PY32F002Bx5", "USE_HAL_DRIVER")

    set_optimize("smallest")
    add_ldflags
    (
        "-Tpy32f002bx5.ld",
        "-mcpu=cortex-m0plus",
        "-Wl,--gc-sections",
        "--specs=nano.specs",
        {force = true}
    )

    add_cflags
    (
        "-mcpu=cortex-m0plus",
        "-mthumb",
        "-Wall",
        "-Os",
        "-fdata-sections",
        "-ffunction-sections",
        "--specs=nano.specs"
    )

    add_cxxflags
    (
        "-mcpu=cortex-m0plus",
        "-mthumb",
        "-Wall",
        "-Os",
        "-fdata-sections",
        "-ffunction-sections"
    )

    add_asflags
    (
        "-mcpu=cortex-m0plus",
        "-mthumb",
        "-Wall",
        "-Os",
        "-fdata-sections",
        "-ffunction-sections",
        "-specs=nano.specs"
    )
        
    add_includedirs("User",
                    "../../Sdk/AriesSDK")
    add_includedirs("../../Sdk/Py32f002b/Drivers/CMSIS/Include",
                    "../../Sdk/Py32f002b/Drivers/CMSIS/Device/PY32F0xx/Include",
                    "../../Sdk/Py32f002b/Drivers/PY32F002B_HAL_Driver/Inc")

    add_files("../../Sdk/Py32f002b/Drivers/PY32F002B_HAL_Driver/Src/py32f002b_ll_i2c.c",
              "../../Sdk/Py32f002b/Drivers/PY32F002B_HAL_Driver/Src/py32f002b_ll_utils.c",
              "../../Sdk/Py32f002b/Drivers/PY32F002B_HAL_Driver/Src/py32f002b_ll_gpio.c",
              "../../Sdk/Py32f002b/Drivers/PY32F002B_HAL_Driver/Src/py32f002b_hal.c",
              "../../Sdk/Py32f002b/Drivers/PY32F002B_HAL_Driver/Src/py32f002b_hal_cortex.c",
              "../../Sdk/Py32f002b/Drivers/PY32F002B_HAL_Driver/Src/py32f002b_hal_flash.c",
              "../../Sdk/Py32f002b/Drivers/PY32F002B_HAL_Driver/Src/py32f002b_hal_gpio.c",
              "../../Sdk/Py32f002b/Drivers/PY32F002B_HAL_Driver/Src/py32f002b_hal_i2c.c",
              "../../Sdk/Py32f002b/Drivers/PY32F002B_HAL_Driver/Src/py32f002b_hal_rcc.c",
              "../../Sdk/Py32f002b/Drivers/PY32F002B_HAL_Driver/Src/py32f002b_hal_rcc.c")

    add_links("AriesSDC-DFU",
             "AriesSDC-CDC")

    add_files("User/startup_py32f002bxx_gcc.s",
              "User/*.c",
              "../Port/*.c",
              "../../Sdk/AriesSDK/crc32.c")

    after_build(function(target)
        print("---------- Complete Build ---------")
        local out = target:targetfile() or ""
        local bin_out = target:targetdir().."/"..target:basename()..".bin"
        local hex_out = target:targetdir().."/"..target:basename()..".hex"
        os.exec(get_config("sdk").."/bin/arm-none-eabi-size "..target:targetfile())
        os.exec(get_config("sdk").."/bin/arm-none-eabi-objcopy -Obinary "..out.." "..bin_out)
        os.exec(get_config("sdk").."/bin/arm-none-eabi-objcopy -O ihex "..out.." "..hex_out)
    end)

--
-- If you want to known more usage about xmake, please see https://xmake.io
--
-- ## FAQ
--
-- You can enter the project directory firstly before building project.
--
--   $ cd projectdir
--
-- 1. How to build project?
--
--   $ xmake
--
-- 2. How to configure project?
--
--   $ xmake f -p [macosx|linux|iphoneos ..] -a [x86_64|i386|arm64 ..] -m [debug|release]
--
-- 3. Where is the build output directory?
--
--   The default output directory is `./build` and you can configure the output directory.
--
--   $ xmake f -o outputdir
--   $ xmake
--
-- 4. How to run and debug target after building project?
--
--   $ xmake run [targetname]
--   $ xmake run -d [targetname]
--
-- 5. How to install target to the system directory or other output directory?
--
--   $ xmake install
--   $ xmake install -o installdir
--
-- 6. Add some frequently-used compilation flags in xmake.lua
--
-- @code
--    -- add debug and release modes
--    add_rules("mode.debug", "mode.release")
--
--    -- add macro definition
--    add_defines("NDEBUG", "_GNU_SOURCE=1")
--
--    -- set warning all as error
--    set_warnings("all", "error")
--
--    -- set language: c99, c++11
--    set_languages("c99", "c++11")
--
--    -- set optimization: none, faster, fastest, smallest
--    set_optimize("fastest")
--
--    -- add include search directories
--    add_includedirs("/usr/include", "/usr/local/include")
--
--    -- add link libraries and search directories
--    add_links("tbox")
--    add_linkdirs("/usr/local/lib", "/usr/lib")
--
--    -- add system link libraries
--    add_syslinks("z", "pthread")
--
--    -- add compilation and link flags
--    add_cxflags("-stdnolib", "-fno-strict-aliasing")
--    add_ldflags("-L/usr/local/lib", "-lpthread", {force = true})
--
-- @endcode
--

