#pragma once
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	class DomainFile;
	class PORTAKAL_API IAssetAuthorizationTool : public Class
	{
		GENERATE_CLASS(IAssetAuthorizationTool);
	public:
		IAssetAuthorizationTool() = default;
		~IAssetAuthorizationTool() = default;

		virtual void OnInitialize() = 0;
		virtual void OnPaint(DomainFile* pFile) = 0;
		virtual void OnFinalize() = 0;

	};

	START_GENERATE_TYPE(IAssetAuthorizationTool);
	START_TYPE_PROPERTIES(IAssetAuthorizationTool);
	END_TYPE_PROPERTIES;
	NO_DEFAULT_CONSTRUCTOR;
	END_GENERATE_TYPE(IAssetAuthorizationTool);
}