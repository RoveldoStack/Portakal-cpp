#include "YamlDefaultSerializer.h"

namespace Portakal
{
    void YamlDefaultSerializer::Serialize(YAML::Emitter& emitter, const Class* pObject)
    {
        Type* pType = pObject->GetType();
        const Array<Field*> fields = pType->GetFields();

        emitter << YAML::BeginDoc;

        for (unsigned int i = 0; i < fields.GetCursor(); i++)
        {
            const Field* pField = fields[i];
            const Type* pFieldType = pField->GetFieldType();

            emitter << YAML::Key << *pField->GetFieldName();

            if (pFieldType == typeof(String))
            {
                const String value = pField->GetValue<String>((void*)pObject);
                emitter << YAML::Value << *value;
            }
            else if (pFieldType == typeof(int))
            {
                const int value = pField->GetValue<int>((void*)pObject);
                const String text = String::GetFromInteger(value);
                emitter << YAML::Value << *text;
            }
            else if (pFieldType == typeof(float))
            {
                const float value = pField->GetValue<float>((void*)pObject);
                const String text = String::GetFromFloat(value);
                emitter << YAML::Value << *text;
            }
            else
            {
                emitter << YAML::Key << "DefaultValue";
            }
        }
        emitter << YAML::EndDoc;
    }
    void YamlDefaultSerializer::Deserialize(const YAML::Node& node, Class* pObject)
    {

    }
}