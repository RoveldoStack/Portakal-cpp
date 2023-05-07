#pragma once
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	class DomainFile;

	/// <summary>
	/// Asset authorization tool interface, used for displaying the asset specific configurations in the editor.
	/// </summary>
	PCLASS();
	class PORTAKAL_API IAssetAuthoringTool : public Class
	{
		GENERATE_CLASS(IAssetAuthoringTool,Virtual);
	public:
		IAssetAuthoringTool() = default;
		~IAssetAuthoringTool() = default;

		/// <summary>
		/// Called upon first initialization
		/// </summary>
		virtual void OnInitialize() = 0;

		/// <summary>
		/// Called upon painting every frame (if visible)
		/// </summary>
		/// <param name="pFile"></param>
		virtual void OnPaint(DomainFile* pFile) = 0;

		/// <summary>
		/// Called upon finalization
		/// </summary>
		virtual void OnFinalize() = 0;

	};

#include "IAssetAuthoringTool.reflect.h"
}