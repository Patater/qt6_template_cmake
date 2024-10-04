cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

find_program(iwyu NAMES include-what-you-use iwyu REQUIRED)

function(enable_iwyu target)
    option(ENABLE_IWYU "Enable checking includes with IWYU" FALSE)
    if(ENABLE_IWYU)
        set_property(TARGET ${target} PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu}
            -Xiwyu;--quoted_includes_first
            -Xiwyu;--error
        )
    endif()
endfunction()
