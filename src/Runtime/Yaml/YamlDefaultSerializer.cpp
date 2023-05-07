#include "YamlDefaultSerializer.h"
#include <Runtime/Log/Log.h>
#include <Libs/Yaml/include/yaml-cpp/yaml.h>
#include <Runtime/Reflection/Reflection.h>
namespace Portakal
{
    void GenerateFieldYaml(YAML::Emitter& emitter, const void* pObject, const Field* pField);
    void GenerateObjectYaml(YAML::Emitter& emitter, const void* pObject, const Type* pType);
    void LoadAsObject(const YAML::Node& node, void* pObject, const Type* pType);

    void GeneratePrimitiveTypeYaml(YAML::Emitter& emitter, const void* pObject, const Type* pType)
    {
        switch (pType->GetTypeCode())
        {
        case Portakal::TypeCodes::String:
        {
            String* pStr = (String*)pObject;
            if (pStr->GetSource() != nullptr)
                emitter << YAML::Value << **((String*)pObject);
            else
                emitter << YAML::Value << '\0';

            break;
        }
        case Portakal::TypeCodes::Char:
            break;
        case Portakal::TypeCodes::UChar:
            break;
        case Portakal::TypeCodes::Int:
            break;
        case Portakal::TypeCodes::UInt:
        {
            UInt* pValue = (UInt*)pObject;
            emitter << YAML::Value << *pValue;

            break;
        }
        case Portakal::TypeCodes::Short:
            break;
        case Portakal::TypeCodes::UShort:
            break;
        case Portakal::TypeCodes::Float:
        {
            emitter << YAML::Value << *String::GetFromFloat(*(float*)pObject);
            break;
        }
        case Portakal::TypeCodes::Double:
            break;
        default:
            break;
        }
    }
    void GenerateEnumTypeYaml(YAML::Emitter& emitter, const void* pObject, const Type* pType)
    {
        const long long enumValue = *(long long*)pObject;
        LOG("en", "Value: %ld,%s", enumValue,*pType->GetTypeName());
        emitter << YAML::Value << (long long)enumValue;
    }

    void GenerateArrayYaml(YAML::Emitter& emitter, const void* pObject, const Type* pType,const Type* pElementType)
    {
        const Array<String>* pArray = (const Array<String>*)pObject;
        const unsigned int elementSize = pElementType->GetSize();

        /*
        * Generate composed objects
        */
        for (unsigned int i = 0; i < pArray->GetCursor(); i++)
        {
            GenerateObjectYaml(emitter, (Byte*)pArray->GetData() + elementSize * i, pElementType);
        }
    }


    void GenerateObjectYaml(YAML::Emitter& emitter,const void* pObject,const Type* pType)
    {
        emitter << YAML::BeginMap;

        /*
        * Iterate fields
        */
        const Array<Field*> fields = pType->GetFields();
        for (unsigned int fieldIndex = 0; fieldIndex < fields.GetCursor(); fieldIndex++)
        {
            const Field* pField = fields[fieldIndex];
            const Type* pFieldType = pField->GetFieldType();
            void* pLocation = (Byte*)pObject + pField->GetOffset();

            emitter << YAML::Key << *pField->GetFieldName();

            /*
            * Check if primitive type
            */
            if (pFieldType->IsPrimitive())
            {
                GeneratePrimitiveTypeYaml(emitter,pLocation, pFieldType);
                continue;
            }

            /*
            * Check if enum
            */
            if (pFieldType->IsEnum())
            {
                GenerateEnumTypeYaml(emitter, pLocation, pFieldType);
                continue;
            }

            /*
            * Check if array
            */
            if (pFieldType->IsArray())
            {
                emitter << YAML::BeginSeq;
                GenerateArrayYaml(emitter, pLocation, pType, pField->GetArrayElementType());
                emitter << YAML::EndSeq;
                continue;
            }

            /*
            * Then it's a composed type
            */
            GenerateObjectYaml(emitter, pLocation, pFieldType);
        }

        emitter << YAML::EndMap;
    }

    String YamlDefaultSerializer::ToYaml(const Class* pObject)
    {
        if (pObject == nullptr)
            return String();

        const Type* pObjectType = pObject->GetType();

        YAML::Emitter emitter;

        emitter << YAML::BeginDoc;

        GenerateObjectYaml(emitter,pObject,pObjectType);

        emitter << YAML::EndDoc;

        return emitter.c_str();
    }
    void LoadAsPrimitive(const YAML::Node& node, void* pObject, const Type* pType)
    {

        switch (pType->GetTypeCode())
        {
            case Portakal::TypeCodes::Composed:
                break;
            case Portakal::TypeCodes::String:
            {
                const std::string nodeStr = node.as<std::string>();
                const String value = nodeStr.c_str();
                *(String*)pObject = value;
            }
            case Portakal::TypeCodes::Char:
                break;
            case Portakal::TypeCodes::UChar:
                break;
            case Portakal::TypeCodes::Int:
                break;
            case Portakal::TypeCodes::UInt:
                break;
            case Portakal::TypeCodes::Short:
                break;
            case Portakal::TypeCodes::UShort:
                break;
            case Portakal::TypeCodes::Float:
            {
                const float value = node.as<float>();
                *(float*)pObject = value;
                break;
            }
            case Portakal::TypeCodes::Double:
                break;
            case Portakal::TypeCodes::Long:
                break;
            case Portakal::TypeCodes::LongLong:
                break;
            case Portakal::TypeCodes::ULong:
                break;
            case Portakal::TypeCodes::ULongLong:
                break;
            default:
                break;
        }
    }

    void LoadAsEnum(const YAML::Node& node, void* pObject, const Field* pField)
    {
        const long long value = node.as<long long>();

        *(long long*)pObject = value;

        //pField->SetValue<long long>(pObject,value);
    }
    void LoadAsArray(const YAML::Node& node, void* pObject,const Type* pElementType)
    {
        const unsigned int elementSize = pElementType->GetSize();
        const unsigned int elementCount = node.size();

        /*
        * Allocate array
        */
        Array<char>* pArray = (Array<char>*)pObject;
        pArray->ClearIndirect();
        pArray->CreateIndirect(elementCount);

        void* pArrayStart = pArray->GetData();

        /*
        * Iterate and fill data
        */
        unsigned int index = 0;
        for (YAML::const_iterator it = node.begin(); it != node.end(); it++)
        {
            const YAML::Node elementNode = *it;
            if (!elementNode.IsDefined())
            {
                index++;
                continue;
            }

            void* pLocation = (Byte*)pArrayStart + elementSize * index;
            LoadAsObject(elementNode, pLocation, pElementType);

            index++;
        }
    }
    
    void LoadAsObject(const YAML::Node& node, void* pObject, const Type* pType)
    {
        const Array<Field*> fields = pType->GetFields();

        for (unsigned int i = 0; i < fields.GetCursor(); i++)
        {
            const Field* pField = fields[i];
            const Type* pFieldType = pField->GetFieldType();
            const unsigned int offset = pField->GetOffset();
            void* pLocation = (Byte*)pObject + pField->GetOffset();

            /*
            * Validate if this map has a valid field name
            */
            const YAML::Node fieldNode = node[*pField->GetFieldName()];
            if (!fieldNode.IsDefined())
                continue;

            /*
             * Check if field is a primitive type
             */
            if (pFieldType->IsPrimitive())
            {
                LoadAsPrimitive(fieldNode, pLocation, pFieldType);
                continue;
            }

            /*
            * Check if enum
            */
            if (pFieldType->IsEnum())
            {
                LoadAsEnum(fieldNode, pLocation, pField);
                continue;
            }

            /*
            * Check if array
            */
            if (pFieldType->IsArray())
            {
                LoadAsArray(fieldNode, pLocation,pField->GetArrayElementType());
                continue;
            }

            /*
            * Then load as object
            */
            LoadAsObject(fieldNode, pLocation, pFieldType);
        }
    }
    void YamlDefaultSerializer::ToObject(const String& yamlString, Class* pObject)
    {
        if (pObject == nullptr)
            return;

        /*
        * Load yaml node
        */
        YAML::Node rootNode = YAML::Load(*yamlString);

        /*
        * Validate if it starts with map node
        */
        if (!rootNode.IsMap())
            return;

        LoadAsObject(rootNode,pObject,pObject->GetType());
    }
}