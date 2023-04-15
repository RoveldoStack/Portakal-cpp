#include "SceneDescriptorYamlSerializer.h"

namespace Portakal
{
    void SceneDescriptorYamlSerializer::Serialize(YAML::Emitter& emitter, const Class* pObject)
    {
        const SceneDescriptor* pTarget = (const SceneDescriptor*)pObject;

        emitter << YAML::BeginDoc;

        emitter << YAML::BeginMap;

        /*
        * Write resources
        */
        emitter << YAML::Key << "Resources";

        emitter << YAML::BeginSeq;
        for (unsigned int i = 0; i < pTarget->Resources.GetCursor(); i++)
        {
            const Guid resourceID = pTarget->Resources[i].ID;

            emitter << YAML::Value << *Guid::ToString(resourceID);

        }
        emitter << YAML::EndSeq;

        /*
        * Write aspects
        */
        emitter << YAML::Key << "Aspects";

        emitter << YAML::BeginSeq;
        for (unsigned int i = 0; i < pTarget->Aspects.GetCursor(); i++)
        {
            const String& aspectType = pTarget->Aspects[i].TypeName;
            emitter << YAML::Value << *aspectType;
        }
        emitter << YAML::EndSeq;

        /*
        * Write entities
        */
        emitter << YAML::Key << "Entities";

        emitter << YAML::BeginSeq;

        emitter << YAML::Value;
        for (unsigned int entityIndex = 0; entityIndex < pTarget->Entities.GetCursor(); entityIndex++)
        {
            const SceneEntityEntry& entityEntry = pTarget->Entities[entityIndex];

            emitter << YAML::BeginMap;

            emitter << YAML::Key << "Name";
            emitter << YAML::Value << *entityEntry.TagName;

            emitter << YAML::Key << "ID";
            emitter << YAML::Value << *Guid::ToString(entityEntry.ID);

            emitter << YAML::Key << "Components";

            emitter << YAML::BeginSeq;

            emitter << YAML::Value;

            for (unsigned int componentIndex = 0; componentIndex < entityEntry.Components.GetCursor(); componentIndex++)
            {
                const SceneComponentEntry& componentEntry = entityEntry.Components[componentIndex];

                emitter << YAML::BeginMap;

                emitter << YAML::Key << "Type";
                emitter << YAML::Value << *componentEntry.TypeName;

                emitter << YAML::Key << "Name";
                emitter << YAML::Value << *componentEntry.TagName;

                emitter << YAML::Key << "ID";
                emitter << YAML::Value << *Guid::ToString(componentEntry.ID);

                emitter << YAML::Key << "Fields";

                emitter << YAML::BeginSeq;
                emitter << YAML::Value;

                for (unsigned int fieldIndex = 0; fieldIndex < componentEntry.Fields.GetCursor(); fieldIndex++)
                {
                    const SceneComponentFieldEntry& fieldEntry = componentEntry.Fields[fieldIndex];

                    emitter << YAML::BeginMap;

                    emitter << YAML::Key << "Name";
                    emitter << YAML::Value << *fieldEntry.FieldName;

                    emitter << YAML::Key << "Type";
                    emitter << YAML::Value << (unsigned int)fieldEntry.Type;

                    emitter << YAML::Key << "Content";
                    emitter << YAML::Value << *fieldEntry.Content;

                    emitter << YAML::EndMap;
                }

                emitter << YAML::EndSeq;

                emitter << YAML::EndMap;
            }
            emitter << YAML::EndSeq;
            emitter << YAML::EndMap;
        }
        emitter << YAML::EndSeq;

        emitter << YAML::EndMap;

        emitter << YAML::EndDoc;
    }
    void SceneDescriptorYamlSerializer::Deserialize(const YAML::Node& node, Class* pObject)
    {
        SceneDescriptor* pTarget = (SceneDescriptor*)pObject;

        /*
        * Deserialize resources
        */
        const YAML::Node& resourcesNode = node["Resources"];
        for (YAML::const_iterator it = resourcesNode.begin(); it != resourcesNode.end(); it++)
        {
            SceneResourceEntry entry = {};
            const YAML::Node& resourceNode = *it;

            const String idStr = resourceNode.as<std::string>().c_str();
            const Guid id = Guid::FromString(resourceNode.as<std::string>().c_str());

            entry.ID = id;

            pTarget->Resources.Add(entry);
        }

        /*
        * Deserialize aspects
        */
        const YAML::Node& aspectsNode = node["Aspects"];
        for (YAML::const_iterator it = aspectsNode.begin(); it != aspectsNode.end(); it++)
        {
            SceneAspectEntry entry = {};
            const YAML::Node aspectNode = *it;

            entry.TypeName = aspectNode.as<std::string>().c_str();

            pTarget->Aspects.Add(entry);
        }

        /*
        * Deserialize entities
        */
        const YAML::Node& entitiesNode = node["Entities"];
        for (YAML::const_iterator entityIt = entitiesNode.begin(); entityIt != entitiesNode.end(); entityIt++)
        {
            SceneEntityEntry entityEntry = {};

            const YAML::Node& entityNode = *entityIt;

            entityEntry.TagName = entityNode["Name"].as<std::string>().c_str();
            entityEntry.ID = Guid::FromString(entityNode["ID"].as<std::string>().c_str());
            
            const YAML::Node& componentsNode = entityNode["Components"];
            for (YAML::const_iterator componentIt = componentsNode.begin(); componentIt != componentsNode.end(); componentIt++)
            {
                SceneComponentEntry componentEntry = {};

                const YAML::Node& componentNode = *componentIt;

                componentEntry.TypeName = componentNode["Type"].as<std::string>().c_str();
                componentEntry.TagName = componentNode["Name"].as<std::string>().c_str();
                componentEntry.ID = Guid::FromString(componentNode["ID"].as<std::string>().c_str());

                const YAML::Node& fieldsNode = componentNode["Fields"];
                for (YAML::const_iterator fieldIt = fieldsNode.begin(); fieldIt != fieldsNode.end(); fieldIt++)
                {
                    SceneComponentFieldEntry fieldEntry = {};
                    const YAML::Node& fieldNode = *fieldIt;

                    fieldEntry.Type = (SceneComponentFieldType)fieldNode["Type"].as<unsigned int>();
                    fieldEntry.FieldName = fieldNode["Name"].as<std::string>().c_str();
                    fieldEntry.Content = fieldNode["Content"].as<std::string>().c_str();

                    componentEntry.Fields.Add(fieldEntry);
                }

                entityEntry.Components.Add(componentEntry);
            }

            pTarget->Entities.Add(entityEntry);
        }
    }
}