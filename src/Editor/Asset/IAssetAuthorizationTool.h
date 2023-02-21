#pragma once
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	class DomainFile;

	/// <summary>
	/// Asset authorization tool interface, used for displaying the asset specific configurations in the editor.
	/// </summary>
	class PORTAKAL_API IAssetAuthorizationTool : public Class
	{
		GENERATE_CLASS(IAssetAuthorizationTool);
	public:
		IAssetAuthorizationTool() = default;
		~IAssetAuthorizationTool() = default;

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

	START_GENERATE_TYPE(IAssetAuthorizationTool);
	START_TYPE_PROPERTIES(IAssetAuthorizationTool);
	END_TYPE_PROPERTIES;
	NO_DEFAULT_CONSTRUCTOR;
	END_GENERATE_TYPE(IAssetAuthorizationTool);
}