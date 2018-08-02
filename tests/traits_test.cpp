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

#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include <otf2xx/traits/reference.hpp>
#include <otf2xx/definition/fwd.hpp>

#include <otf2/OTF2_GeneralDefinitions.h>

TEST_CASE("test types of references")
{

    REQUIRE(std::is_same<otf2::traits::reference_type<otf2::definition::attribute>::type,
                         OTF2_AttributeRef>::value);
    REQUIRE(std::is_same<otf2::traits::reference_type<otf2::definition::comm>::type,
                         OTF2_CommRef>::value);
    REQUIRE(std::is_same<otf2::traits::reference_type<otf2::definition::location>::type,
                         OTF2_LocationRef>::value);
    REQUIRE(std::is_same<otf2::traits::reference_type<otf2::definition::location_group>::type,
                         OTF2_LocationGroupRef>::value);
    REQUIRE(std::is_same<otf2::traits::reference_type<otf2::definition::parameter>::type,
                         OTF2_ParameterRef>::value);
    REQUIRE(std::is_same<otf2::traits::reference_type<otf2::definition::region>::type,
                         OTF2_RegionRef>::value);
    REQUIRE(std::is_same<otf2::traits::reference_type<otf2::definition::string>::type,
                         OTF2_StringRef>::value);
    REQUIRE(std::is_same<otf2::traits::reference_type<otf2::definition::system_tree_node>::type,
                         OTF2_SystemTreeNodeRef>::value);

    REQUIRE(std::is_same<otf2::traits::reference_type<otf2::definition::source_code_location>::type,
                         OTF2_SourceCodeLocationRef>::value);
    REQUIRE(std::is_same<otf2::traits::reference_type<otf2::definition::calling_context>::type,
                         OTF2_CallingContextRef>::value);
    REQUIRE(std::is_same<otf2::traits::reference_type<otf2::definition::interrupt_generator>::type,
                         OTF2_InterruptGeneratorRef>::value);
    REQUIRE(std::is_same<otf2::traits::reference_type<otf2::definition::io_handle>::type,
                         OTF2_IoHandleRef>::value);
    REQUIRE(std::is_same<otf2::traits::reference_type<otf2::definition::io_regular_file>::type,
                         OTF2_IoFileRef>::value);
    REQUIRE(std::is_same<otf2::traits::reference_type<otf2::definition::io_directory>::type,
                         OTF2_IoFileRef>::value);
    REQUIRE(std::is_same<otf2::traits::reference_type<otf2::definition::io_paradigm>::type,
                         OTF2_IoParadigmRef>::value);

    REQUIRE(std::is_same<otf2::traits::reference_type<otf2::definition::locations_group>::type,
                         OTF2_GroupRef>::value);
    REQUIRE(std::is_same<otf2::traits::reference_type<otf2::definition::regions_group>::type,
                         OTF2_GroupRef>::value);
    REQUIRE(std::is_same<otf2::traits::reference_type<otf2::definition::comm_locations_group>::type,
                         OTF2_GroupRef>::value);
    REQUIRE(std::is_same<otf2::traits::reference_type<otf2::definition::comm_group>::type,
                         OTF2_GroupRef>::value);
    REQUIRE(std::is_same<otf2::traits::reference_type<otf2::definition::comm_self_group>::type,
                         OTF2_GroupRef>::value);

    REQUIRE(std::is_same<otf2::traits::reference_type<otf2::definition::metric_member>::type,
                         OTF2_MetricMemberRef>::value);
    REQUIRE(std::is_same<otf2::traits::reference_type<otf2::definition::metric_class>::type,
                         OTF2_MetricRef>::value);
    REQUIRE(std::is_same<otf2::traits::reference_type<otf2::definition::metric_instance>::type,
                         OTF2_MetricRef>::value);
}
