#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
    /// <summary>
    /// Available mesh topologies
    /// </summary>
    enum class PORTAKAL_API MeshTopology
    {
        TriangleList,
        TriangleStrip,
        LineList,
        LineStrip,
        PointList
    };
}