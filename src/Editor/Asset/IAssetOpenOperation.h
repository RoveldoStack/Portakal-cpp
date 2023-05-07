#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	class DomainFile;

	/// <summary>
	/// Interface for asset open implementation
	/// </summary>
	PCLASS();
	class PORTAKAL_API IAssetOpenOperation : public Class
	{
		GENERATE_CLASS(IAssetOpenOperation,Virtual);
	public:
		IAssetOpenOperation() = default;
		~IAssetOpenOperation() = default;

		/// <summary>
		/// Called upon opening an asset
		/// </summary>
		virtual void OnOpen(DomainFile* pFile) = 0;
	};


#include "IAssetOpenOperation.reflect.h"
}