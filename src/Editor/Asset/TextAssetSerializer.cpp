#include "TextAssetSerializer.h"

namespace Portakal
{
	void TextAssetSerializer::SerializeToEditor(const ResourceSubObject* pObject)
	{
	}
	void TextAssetSerializer::SerializeToPackage(const ResourceSubObject* pObject)
	{
	}
	ResourceSubObject* TextAssetSerializer::DeserializeFromEditor(const String& text)
	{
		return nullptr;
	}
	ResourceSubObject* TextAssetSerializer::DeserializeFromRaw(const ByteBlock& block)
	{
		return nullptr;
	}
}