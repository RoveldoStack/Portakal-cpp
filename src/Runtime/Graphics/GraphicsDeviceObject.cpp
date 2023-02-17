#include "GraphicsDeviceObject.h"
#include <Runtime/Graphics/GraphicsDevice.h>

namespace Portakal
{
    void GraphicsDeviceObject::DeleteDeviceObject()
    {
        mOwnerDevice->DeleteChildObject(this);
    }
}