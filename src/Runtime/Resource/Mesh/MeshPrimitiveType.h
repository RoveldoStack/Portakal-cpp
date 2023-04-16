#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	enum class PORTAKAL_API MeshPrimitiveType
	{
        /** A point primitive.
         *
         * This is just a single vertex in the virtual world,
         * #aiFace contains just one index for such a primitive.
         */
        Point = 0x1,

        /** A line primitive.
         *
         * This is a line defined through a start and an end position.
         * #aiFace contains exactly two indices for such a primitive.
         */
        Line = 0x2,

        /** A triangular primitive.
         *
         * A triangle consists of three indices.
         */
        Triangle = 0x4,

        /** A higher-level polygon with more than 3 edges.
         *
         * A triangle is a polygon, but polygon in this context means
         * "all polygons that are not triangles". The "Triangulate"-Step
         * is provided for your convenience, it splits all polygons in
         * triangles (which are much easier to handle).
         */
        Polygon = 0x8,

        /**
         * A flag to determine whether this triangles only mesh is NGON encoded.
         *
         * NGON encoding is a special encoding that tells whether 2 or more consecutive triangles
         * should be considered as a triangle fan. This is identified by looking at the first vertex index.
         * 2 consecutive triangles with the same 1st vertex index are part of the same
         * NGON.
         *
         * At the moment, only quads (concave or convex) are supported, meaning that polygons are 'seen' as
         * triangles, as usual after a triangulation pass.
         *
         * To get an NGON encoded mesh, please use the aiProcess_Triangulate post process.
         *
         * @see aiProcess_Triangulate
         * @link https://github.com/KhronosGroup/glTF/pull/1620
         */
        NGONEncodingFlag = 0x10,

        /* This value is not used. It is just here to force the
         *  compiler to map this enum to a 32 Bit integer.
         */
        Force32Bit = INT_MAX
	};

    GENERATE_FLAG_OPERATORS(MeshPrimitiveType, long long);
}