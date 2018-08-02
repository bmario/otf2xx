/*
 * This file is part of otf2xx (https://github.com/tud-zih-energy/otf2xx)
 * otf2xx - A wrapper for the Open Trace Format 2 library
 *
 * Copyright (c) 2013-2016, Technische Universität Dresden, Germany
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

/*
 * otf2xx - reference.hpp
 *
 * Copyright (c) 2014 TU Dresden
 *
 * All rights reserved.
 *
 * author: Mario Bielert <mario.bielert@tu-dresden.de>
 *
 */

#ifndef INCLUDE_OTF2XX_REFERENCE_GENERATOR_HPP
#define INCLUDE_OTF2XX_REFERENCE_GENERATOR_HPP

#include <otf2xx/reference.hpp>
#include <otf2xx/traits/reference.hpp>

#include <otf2xx/exception.hpp>

#include <cassert>
#include <type_traits>

namespace otf2
{

/**
 * @brief gives a free reference number for a set of definitions
 *
 * This class generates free reference numbers for definitons. For this
 * task, it needs to know every used reference number first.
 *
 * Therefore you need to register every definition.
 *
 * \note The algorithm for generating a number is undefined.
 *
 * \tparam Definition The definition for which it should generate numbers
 */
template <typename RefType>
class reference_generator
{
public:
    typedef RefType ref_type;

    template <typename Definition>
    void register_definition(const Definition& def)
    {
        static_assert(
            std::is_same<
                otf2::traits::reference_t<Definition>,
                RefType>::value,
            "Trying to register a definition with a different id space");

        register_reference(def.ref());
    }

    void register_reference(ref_type ref)
    {
        if (old_max == ref_type::undefined())
        {
            old_max = ref.get();
            return;
        }

        using std::max;

        old_max = max(ref.get(), old_max);
    }

    ref_type next()
    {
        if (ref_type::undefined() == old_max + 1)
        {
            make_exception("Cannot generate a new unused reference number");
        }

        return ++old_max;
    }

private:
    typename ref_type::ref_type old_max = -1;
};

class trace_reference_generator;

namespace detail
{
    template <typename T_Reference>
    class generate_ref
    {
    public:
        T_Reference
        operator()(trace_reference_generator& gen);
    };
} // namespace detail

class trace_reference_generator
{
public:
    void register_definition(const otf2::definition::location& def)
    {
        location_refs_.register_definition(def);
    }

    void register_definition(const otf2::definition::location_group& def)
    {
        location_group_refs_.register_definition(def);
    }

    void register_definition(const otf2::definition::system_tree_node& def)
    {
        system_tree_node_refs_.register_definition(def);
    }

    void register_definition(const otf2::definition::comm& def)
    {
        comm_refs_.register_definition(def);
    }

    void register_definition(const otf2::definition::region& def)
    {
        region_refs_.register_definition(def);
    }

    void register_definition(const otf2::definition::attribute& def)
    {
        attribute_refs_.register_definition(def);
    }

    void register_definition(const otf2::definition::parameter& def)
    {
        parameter_refs_.register_definition(def);
    }

    void register_definition(const otf2::definition::string& def)
    {
        string_refs_.register_definition(def);
    }

    void register_definition(const otf2::definition::source_code_location& def)
    {
        source_code_location_refs_.register_definition(def);
    }

    void register_definition(const otf2::definition::calling_context& def)
    {
        calling_context_refs_.register_definition(def);
    }

    void register_definition(const otf2::definition::interrupt_generator& def)
    {
        interrupt_generator_refs_.register_definition(def);
    }

    void register_definition(const otf2::definition::io_regular_file& def)
    {
        io_file_refs_.register_definition(def);
    }

    void register_definition(const otf2::definition::io_directory& def)
    {
        io_file_refs_.register_definition(def);
    }

    void register_definition(const otf2::definition::io_handle& def)
    {
        io_handle_refs_.register_definition(def);
    }

    void register_definition(const otf2::definition::io_paradigm& def)
    {
        io_paradigm_refs_.register_definition(def);
    }

    void register_definition(const otf2::definition::io_pre_created_handle_state& def)
    {
        io_handle_refs_.register_definition(def.handle());
    }

    void register_definition(const otf2::definition::metric_member& def)
    {
        metric_member_refs_.register_definition(def);
    }

    void register_definition(const otf2::definition::marker& def)
    {
        marker_refs_.register_definition(def);
    }

    void register_definition(const otf2::definition::metric_class& def)
    {
        metric_refs_.register_definition(def);
    }

    void register_definition(const otf2::definition::metric_instance& def)
    {
        metric_refs_.register_definition(def);
    }

    template <typename Definition, otf2::common::group_type GroupType>
    void register_definition(const otf2::definition::group<Definition, GroupType>& def)
    {
        group_refs_.register_definition(def);
    }

    template <typename Definition>
    void operator()(const Definition& def)
    {
        register_definition(def);
    }

    template <typename Definition>
    otf2::traits::reference_t<Definition> next()
    {
        return detail::generate_ref<otf2::traits::reference_t<Definition>>()(*this);
    }

    reference_generator<otf2::location_ref> location_refs_;
    reference_generator<otf2::location_group_ref> location_group_refs_;
    reference_generator<otf2::system_tree_node_ref> system_tree_node_refs_;
    reference_generator<otf2::group_ref> group_refs_;
    reference_generator<otf2::comm_ref> comm_refs_;
    reference_generator<otf2::region_ref> region_refs_;
    reference_generator<otf2::attribute_ref> attribute_refs_;
    reference_generator<otf2::parameter_ref> parameter_refs_;
    reference_generator<otf2::string_ref> string_refs_;
    reference_generator<otf2::source_code_location_ref>
        source_code_location_refs_;
    reference_generator<otf2::calling_context_ref> calling_context_refs_;
    reference_generator<otf2::interrupt_generator_ref>
        interrupt_generator_refs_;
    reference_generator<otf2::io_file_ref> io_file_refs_;
    reference_generator<otf2::io_handle_ref> io_handle_refs_;
    reference_generator<otf2::io_paradigm_ref> io_paradigm_refs_;
    reference_generator<otf2::metric_member_ref> metric_member_refs_;
    reference_generator<otf2::metric_ref> metric_refs_;
    reference_generator<otf2::marker_ref> marker_refs_;
};

namespace detail
{
    template <>
    inline otf2::location_ref
    generate_ref<otf2::location_ref>::operator()(trace_reference_generator& gen)
    {
        return gen.location_refs_.next();
    }

    template <>
    inline otf2::location_group_ref
    generate_ref<otf2::location_group_ref>::operator()(trace_reference_generator& gen)
    {
        return gen.location_group_refs_.next();
    }

    template <>
    inline otf2::system_tree_node_ref
    generate_ref<otf2::system_tree_node_ref>::operator()(trace_reference_generator& gen)
    {
        return gen.system_tree_node_refs_.next();
    }

    inline otf2::group_ref
    generate_ref<otf2::group_ref>::operator()(trace_reference_generator& gen)
    {
        return gen.group_refs_.next();
    }

    template <>
    inline otf2::comm_ref
    generate_ref<otf2::comm_ref>::operator()(trace_reference_generator& gen)
    {
        return gen.comm_refs_.next();
    }

    template <>
    inline otf2::region_ref
    generate_ref<otf2::region_ref>::operator()(trace_reference_generator& gen)
    {
        return gen.region_refs_.next();
    }

    template <>
    inline otf2::attribute_ref
    generate_ref<otf2::attribute_ref>::operator()(trace_reference_generator& gen)
    {
        return gen.attribute_refs_.next();
    }

    template <>
    inline otf2::parameter_ref
    generate_ref<otf2::parameter_ref>::operator()(trace_reference_generator& gen)
    {
        return gen.parameter_refs_.next();
    }

    template <>
    inline otf2::string_ref
    generate_ref<otf2::string_ref>::operator()(trace_reference_generator& gen)
    {
        return gen.string_refs_.next();
    }

    template <>
    inline otf2::source_code_location_ref
    generate_ref<otf2::source_code_location_ref>::operator()(trace_reference_generator& gen)
    {
        return gen.source_code_location_refs_.next();
    }

    template <>
    inline otf2::calling_context_ref
    generate_ref<otf2::calling_context_ref>::operator()(trace_reference_generator& gen)
    {
        return gen.calling_context_refs_.next();
    }

    template <>
    inline otf2::interrupt_generator_ref
    generate_ref<otf2::interrupt_generator_ref>::operator()(trace_reference_generator& gen)
    {
        return gen.interrupt_generator_refs_.next();
    }

    template <>
    inline otf2::io_file_ref
    generate_ref<otf2::io_file_ref>::operator()(trace_reference_generator& gen)
    {
        return gen.io_file_refs_.next();
    }

    template <>
    inline otf2::io_handle_ref
    generate_ref<otf2::io_handle_ref>::operator()(trace_reference_generator& gen)
    {
        return gen.io_handle_refs_.next();
    }

    template <>
    inline otf2::io_paradigm_ref
    generate_ref<otf2::io_paradigm_ref>::operator()(trace_reference_generator& gen)
    {
        return gen.io_paradigm_refs_.next();
    }

    template <>
    inline otf2::metric_member_ref
    generate_ref<otf2::metric_member_ref>::operator()(trace_reference_generator& gen)
    {
        return gen.metric_member_refs_.next();
    }

    template <>
    inline otf2::metric_ref
    generate_ref<otf2::metric_ref>::operator()(trace_reference_generator& gen)
    {
        return gen.metric_refs_.next();
    }

    template <>
    inline otf2::marker_ref
    generate_ref<otf2::marker_ref>::operator()(trace_reference_generator& gen)
    {
        return gen.marker_refs_.next();
    }
} // namespace detail

} // namespace otf2

#endif // INCLUDE_OTF2XX_REFERENCE_GENERATOR_HPP
