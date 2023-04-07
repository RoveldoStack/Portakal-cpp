using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ReflectionParserTool
{
    public class ObjectEntry
    {
        public ObjectEntry(string name,string headerFilePath, string fileContent, ObjectType type, bool ısVirtual)
        {
            Name = name;
            Type = type;
            HeaderFilePath = headerFilePath;
            Folder = Path.GetDirectoryName(headerFilePath);
            _baseObjects = new List<ObjectEntry>();
            _classAttributes = new List<AttributeEntry>();
            _fields = new List<FieldEntry>();
            FileContent = fileContent;
            IsVirtual = ısVirtual;
        }

        public string Name { get; private init; }
        public string HeaderFilePath { get; private init; }
        public string? Folder { get; private init; }
        public string FileContent { get; private init; }
        public ObjectType Type { get; private init; }
        public IReadOnlyCollection<ObjectEntry> BaseObjects { get => _baseObjects; }
        public IReadOnlyCollection<AttributeEntry> ClassAttributes { get => _classAttributes; }
        public IReadOnlyCollection<FieldEntry> Fields { get => _fields; }
        public bool IsVirtual { get; private init; }

        public void RegisterClassAttribute(string name,string parameters)
        {
            _classAttributes.Add(new AttributeEntry() { Name = name, Parameters = parameters });
        }
        public void RegisterBaseObject(ObjectEntry entry)
        {
            _baseObjects.Add(entry);
        }
        public void RegisterField(string type,string name)
        {
            _fields.Add(new FieldEntry() { Name = name, Type = type });
        }

        private List<ObjectEntry> _baseObjects;
        private List<AttributeEntry> _classAttributes;
        private List<FieldEntry> _fields;
    }
}
