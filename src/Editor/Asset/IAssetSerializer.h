#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Containers/String.h>
#include <Runtime/Reflection/Reflection.h>
#include <Runtime/Memory/ByteBlock.h>

namespace Portakal
{
	class DomainFile;
	class ResourceSubObject;

	/// <summary>
	/// Asset serializer interface, used for serializing the asset into editor and package formats also for deserialization of the raw format
	/// </summary>
	class PORTAKAL_API IAssetSerializer : public Class
	{
		GENERATE_CLASS(IAssetSerializer);
	public:
		IAssetSerializer() = default;
		~IAssetSerializer() = default;

		/// <summary>
		/// Serializes to the editor format
		/// </summary>
		/// <param name="pObject"></param>
		virtual void SerializeToEditor(const ResourceSubObject* pObject) = 0;

		/// <summary>
		/// Serializes to the package format
		/// </summary>
		/// <param name="pObject"></param>
		virtual void SerializeToPackage(const ResourceSubObject* pObject) = 0;

		/// <summary>
		/// Deserializes from the raw file format
		/// </summary>
		/// <param name="pFile"></param>
		/// <returns></returns>
		virtual ResourceSubObject* Deserialize(const DomainFile* pFile) = 0;
	};

	START_GENERATE_TYPE(IAssetSerializer);
	START_TYPE_PROPERTIES(IAssetSerializer);
	END_TYPE_PROPERTIES;
	NO_DEFAULT_CONSTRUCTOR;
	END_GENERATE_TYPE(IAssetSerializer)
}