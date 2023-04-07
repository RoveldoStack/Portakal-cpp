#pragma once
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	class DomainFile;

	/// <summary>
	/// Asset processor used after importing any asset
	/// </summary>
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

	//START_GENERATE_TYPE(IAssetProcessor);
	//START_TYPE_PROPERTIES(IAssetProcessor);
	//END_TYPE_PROPERTIES;
	//NO_DEFAULT_CONSTRUCTOR;
	//END_GENERATE_TYPE(IAssetProcessor);

#include "IAssetProcessor.reflect.h"
}