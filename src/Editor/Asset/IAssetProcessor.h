#pragma once
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	class DomainFile;
	class PORTAKAL_API IAssetProcessor : public Class
	{
		GENERATE_CLASS(IAssetProcessor);
	public:
		IAssetProcessor() = default;
		~IAssetProcessor() = default;

		virtual void OnProcess(DomainFile* pFile) = 0;
	};

	START_GENERATE_TYPE(IAssetProcessor);
	START_TYPE_PROPERTIES(IAssetProcessor);
	END_TYPE_PROPERTIES;
	NO_DEFAULT_CONSTRUCTOR;
	END_GENERATE_TYPE(IAssetProcessor);
}