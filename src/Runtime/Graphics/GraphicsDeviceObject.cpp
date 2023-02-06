#include "GraphicsDeviceObject.h"

namespace Portakal
{
    void GraphicsDeviceObject::DeleteDeviceObject()
    {
        OnDestroy();
    }
}