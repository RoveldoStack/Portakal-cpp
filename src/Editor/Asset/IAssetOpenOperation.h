#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	class DomainFile;
	/// <summary>
	/// Interface for asset open implementation
	/// </summary>
	class PORTAKAL_API IAssetOpenOperation : public Class
	{
		GENERATE_CLASS(IAssetOpenOperation);
	public:
		IAssetOpenOperation() = default;
		~IAssetOpenOperation() = default;

		/// <summary>
		/// Called upon opening an asset
		/// </summary>
		virtual void OnOpen(DomainFile* pFile) = 0;
	};

	START_GENERATE_TYPE(IAssetOpenOperation);
	START_TYPE_PROPERTIES(IAssetOpenOperation);
	END_TYPE_PROPERTIES;
	NO_DEFAULT_CONSTRUCTOR;
	END_GENERATE_TYPE(IAssetOpenOperation);
}