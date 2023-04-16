#include "GraphicsDeviceObject.h"
#include <Runtime/Graphics/GraphicsDevice.h>

namespace Portakal
{
 
    void GraphicsDeviceObject::Destroy()
    {
        if (mDestroyed)
            return;

        if (mOwnerDevice != nullptr)
        {
            OnDestroy();
            mOwnerDevice->_NotifyChildObjectDestroyed(this);
        }


        mDestroyed = true;
    }
}