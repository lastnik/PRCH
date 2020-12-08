function(set_common_options target)

    target_compile_options(${target}
            PRIVATE
            $<$<CONFIG:RELEASE>:-Ofast>
            $<$<CONFIG:DEBUG>:-O0>
            $<$<CONFIG:DEBUG>:-ggdb3>
            -Wall -Werror -Wno-error=maybe-uninitialized
            -mavx2 -mfma -march=sandybridge -mtune=intel
            -std=c++2a
            -funroll-loops #optimization, probably should be only for release target
            -fstack-protector-strong  #probably is not needed in release build #-fstack-protector-all for debug build might be a good idea
            -mcmodel=medium #not obvious whether this option is needed
            -pipe
            -pthread
            -fno-strict-aliasing #also not clear why we use it
            )

    target_compile_definitions(${target}
            PRIVATE
            $<$<CONFIG:RELEASE>:NDEBUG>
            $<$<CONFIG:RELEASE>:BOOST_DISABLE_ASSERTS>
            )

    # _enable_sanitizers_if_needed(${target})

endfunction()