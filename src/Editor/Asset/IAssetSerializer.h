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
	PCLASS();
	class PORTAKAL_API IAssetSerializer : public Class
	{
		GENERATE_CLASS(IAssetSerializer,Virtual);
	public:
		IAssetSerializer() = default;
		~IAssetSerializer() = default;

		/// <summary>
		/// Serializes to the editor format
		/// </summary>
		/// <param name="pObject"></param>
		virtual void SerializeToEditor(const ResourceSubObject* pObject,ByteBlock& outBlock) = 0;

		/// <summary>
		/// Serializes to the package format
		/// </summary>
		/// <param name="pObject"></param>
		virtual void SerializeToPackage(const ResourceSubObject* pObject, ByteBlock& outBlock) = 0;
	};
	
#include "IAssetSerializer.reflect.h"
}