#pragma once
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	class DomainFile;

	/// <summary>
	/// Asset processor used after importing any asset
	/// </summary>
	PCLASS();
	class PORTAKAL_API IAssetProcessor : public Class
	{
		GENERATE_CLASS(IAssetProcessor,Virtual);
	public:
		IAssetProcessor() = default;
		~IAssetProcessor() = default;

		/// <summary>
		/// Called on processing the asset
		/// </summary>
		/// <param name="pFile"></param>
		virtual void OnProcess(DomainFile* pFile) = 0;
	};
#include "IAssetProcessor.reflect.h"
}