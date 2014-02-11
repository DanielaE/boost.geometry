// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_TURNS_PRINT_TURNS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_TURNS_PRINT_TURNS_HPP

#include <boost/geometry/algorithms/detail/overlay/traversal_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/turn_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/debug_turn_info.hpp>
#include <boost/foreach.hpp>
#include <boost/geometry/geometry.hpp>

namespace boost { namespace geometry
{

namespace detail { namespace turns
{



template <typename Geometry1, typename Geometry2, typename Turns>
static inline void print_turns(Geometry1 const& g1,
                               Geometry2 const& g2,
                               Turns const& turns)
{
    typedef typename point_type<Geometry1>::type Point1;
    typedef overlay::traversal_turn_info<Point1> turn_info;

    std::cout << geometry::wkt(g1) << std::endl;
    std::cout << geometry::wkt(g2) << std::endl;
    int index = 0;
    BOOST_FOREACH(turn_info const& turn, turns)
    {
        //            std::ostringstream out;
        std::ostream& out = std::cout;
        out << index
            << ": " << geometry::method_char(turn.method);

        if ( turn.is_discarded() )
            out << " (discarded)\n";
        else if ( turn.blocked() )
            out << " (blocked)\n";
        else
            out << '\n';

        out << geometry::operation_char(turn.operations[0].operation)
            <<": seg: " << turn.operations[0].seg_id.source_index
            << ", m: " << turn.operations[0].seg_id.multi_index
            << ", r: " << turn.operations[0].seg_id.ring_index
            << ", s: " << turn.operations[0].seg_id.segment_index << ", ";
        out << "other: " << turn.operations[0].other_id.source_index
            << ", m: " << turn.operations[0].other_id.multi_index
            << ", r: " << turn.operations[0].other_id.ring_index
            << ", s: " << turn.operations[0].other_id.segment_index;
        out << ' ' << geometry::dsv(turn.point) << ' ';

        out << '\n';

        out << geometry::operation_char(turn.operations[1].operation)
            << ": seg: " << turn.operations[1].seg_id.source_index
            << ", m: " << turn.operations[1].seg_id.multi_index
            << ", r: " << turn.operations[1].seg_id.ring_index
            << ", s: " << turn.operations[1].seg_id.segment_index << ", ";
        out << "other: " << turn.operations[1].other_id.source_index
            << ", m: " << turn.operations[1].other_id.multi_index
            << ", r: " << turn.operations[1].other_id.ring_index
            << ", s: " << turn.operations[1].other_id.segment_index;
        out << ' ' << geometry::dsv(turn.point) << ' ';

        ++index;
        std::cout << std::endl;
    }
}




}} // namespace detail::turns

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_TURNS_PRINT_TURNS_HPP
