using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ReflectionParserTool
{
    public struct FieldEntry
    {
        public string Type;
        public string Name;
        public string? ElementType;
        public bool IsArray;
    }
}
