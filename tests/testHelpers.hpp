/*
 * This file is part of otf2xx (https://github.com/tud-zih-energy/otf2xx)
 * otf2xx - A wrapper for the Open Trace Format 2 library
 *
 * Copyright (c) 2013-2018, Technische Universitaet Dresden, Germany
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef INCLUDE_OTF2XX_TEST_HELPERS_HPP
#define INCLUDE_OTF2XX_TEST_HELPERS_HPP

#include <otf2xx/exception.hpp>
#include <stdexcept>

namespace otf2
{
struct test_error: std::runtime_error
{
    explicit test_error(std::string arg) : std::runtime_error(std::move(arg))
    {
    }
};
}

// Macro usable for checking test conditions: TEST(1 == 1)
#define TEST(cond) do{                                                   \
    if(!(cond))                                                          \
        throw otf2::test_error(otf2::detail::concat_args(                \
            "Test '", #cond, "' failed at ", __FILE__, ":", __LINE__));  \
    }while(false)

#endif
