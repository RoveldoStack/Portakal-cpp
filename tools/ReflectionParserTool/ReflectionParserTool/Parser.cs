using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ReflectionParserTool
{
    internal static class Parser
    {
      
        private static ObjectEntry? FindClass(IReadOnlyCollection<ObjectEntry> entries,string name)
        {
            foreach (ObjectEntry entry in entries)
                if (entry.Name == name)
                    return entry;

            return null;
        }
        internal static void Parse(string targetDirectory)
        {
            List<ObjectEntry> objectEntries = new List<ObjectEntry>();

            /*
             * Collect all the files with extension .h
             */
            string[] headerFiles = Directory.GetFiles(targetDirectory, "*.h", SearchOption.AllDirectories);

            /*
             * Eliminate files that does not have any reflection markings
             */
            List<string> reflectionEnabledFiles = new List<string>();
            foreach (string headerFile in headerFiles)
            {
                string fileContent = File.ReadAllText(headerFile);

                int index = fileContent.IndexOf("GENERATE_CLASS");

                if (index == -1)
                    continue;

                reflectionEnabledFiles.Add(headerFile);
            }

            /*
             * First collect all the reflected classes and their local properties
             */
            foreach(string headerFilePath in reflectionEnabledFiles)
            {
                string className = Path.GetFileNameWithoutExtension(headerFilePath);
                string fileContent = File.ReadAllText(headerFilePath);

                /*
                 * Try find class name
                 */
                int classNameCursor = fileContent.IndexOf(className);
                if (classNameCursor == -1)
                    continue;
                if (className == "Class")
                    continue;

                bool bVirtual = !fileContent.Contains("Virtual");
                objectEntries.Add(new ObjectEntry(className,headerFilePath,fileContent, ObjectType.Class,bVirtual));  
            }

            /*
             * Generate class hierarchies
             */
            foreach(ObjectEntry entry in objectEntries)
            {
                if (entry.Name == "Transform2DComponent")
                {
                    Console.WriteLine("Found");
                }
                /*
                 * Try find class name
                 */
                int classNameCursor = entry.FileContent.IndexOf(entry.Name);
                if (classNameCursor == -1)
                    continue;

                /*
                 * Try collect base classes
                 */
                int baseClassStartCursor = entry.FileContent.IndexOf(":", classNameCursor);
                int baseClassEndCursor = entry.FileContent.IndexOf("{", baseClassStartCursor);

                if (baseClassStartCursor != -1 || baseClassEndCursor != -1) // validate that we have a proper base class section
                {
                    string baseClassSubString = entry.FileContent.Substring(baseClassStartCursor + 1, (baseClassEndCursor - baseClassStartCursor) - 1);
                    string[] baseClassFragments = baseClassSubString.Split(" ");

                    foreach (string fragment in baseClassFragments)
                    {
                        string trimmmed = fragment.Trim();
                        if (trimmmed == "public" || trimmmed == " " || trimmmed == string.Empty || trimmmed == System.Environment.NewLine)
                            continue;

                        ObjectEntry? baseClass = FindClass(objectEntries, trimmmed);
                        if (baseClass == null)
                            continue;

                        entry.RegisterBaseObject(baseClass);
                    }
                }

                /*
                 * Try collect class attributes
                 */
                int classAttributeCursor = entry.FileContent.IndexOf("CLASS_ATTRIBUTE");
                while(classAttributeCursor != -1)
                {
                    int attributeEndCursor = entry.FileContent.IndexOf(System.Environment.NewLine, classAttributeCursor);
                    string subStr = entry.FileContent.Substring(classAttributeCursor, (attributeEndCursor-classAttributeCursor));
                    subStr = subStr.Trim();
                    subStr = subStr.Replace("CLASS_ATTRIBUTE(", string.Empty);
                    subStr = subStr.Replace(");", string.Empty);

                    int parameterStart = subStr.IndexOf(",");
                    if(parameterStart == -1) // has no parameters
                    {
                        classAttributeCursor = entry.FileContent.IndexOf("CLASS_ATTRIBUTE", attributeEndCursor);
                        continue;
                    }

                    string attributeName = subStr.Substring(0,parameterStart);
                    string attributeParameters = subStr.Substring(parameterStart+1);

                    entry.RegisterClassAttribute(attributeName, attributeParameters);

                    classAttributeCursor = entry.FileContent.IndexOf("CLASS_ATTRIBUTE", attributeEndCursor);
                }

                /*
                 * Try collect fields
                 */
                int fieldStartCursor = entry.FileContent.IndexOf("FIELD()");
                while(fieldStartCursor != -1)
                {
                    int fieldEndCursor = entry.FileContent.IndexOf(";",fieldStartCursor);

                    if(fieldEndCursor == -1)
                    {
                        fieldStartCursor = entry.FileContent.IndexOf("FIELD()", fieldStartCursor + "FIELD()".Length);
                        continue;
                    }

                    int fieldBodyStartCursor = fieldEndCursor;
                    int fieldBodyEndCursor = entry.FileContent.IndexOf(";", fieldBodyStartCursor+1);
                    if(fieldBodyEndCursor == -1)
                    {
                        fieldStartCursor = entry.FileContent.IndexOf("FIELD()", fieldBodyEndCursor);
                        continue;
                    }

                    string subStr = entry.FileContent.Substring(fieldBodyStartCursor+1, fieldBodyEndCursor - fieldBodyStartCursor-1);
                    subStr = subStr.Trim();

                    string[] fragments = subStr.Split(' ');
                    string fieldType = fragments[0];
                    string fieldName = fragments[1];

                    entry.RegisterField(fieldType, fieldName);

                    fieldStartCursor = entry.FileContent.IndexOf("FIELD()", fieldBodyEndCursor);
                }
            }

            /*
             * Generate functions
             */

            /*
             * Write to file
             */
            foreach(ObjectEntry entry in objectEntries)
            {
                string registerContent = "";
                foreach (ObjectEntry baseClass in entry.BaseObjects)
                {
                    registerContent += $"REGISTER_BASE_TYPE({baseClass.Name});{System.Environment.NewLine}";
                }
                foreach (AttributeEntry attribute in entry.ClassAttributes)
                {
                    string att = $"REGISTER_TYPE_ATTRIBUTE({attribute.Name},{attribute.Parameters})";
                    if (att.EndsWith(")))"))
                        att = att.Replace(")))", "))");

                    registerContent += att;

                }
                foreach(FieldEntry field in entry.Fields)
                {
                    registerContent += $"REGISTER_FIELD({entry.Name},{field.Name},{field.Type},AccessSpecifier::Public);{System.Environment.NewLine}";
                }
                string constructorType = entry.IsVirtual ? $"HAS_DEFAULT_CONSTRUCTOR({entry.Name});" : "NO_DEFAULT_CONSTRUCTOR;";
                string fileContent = $"""
#include "{entry.Name}.h" 
START_GENERATE_TYPE({entry.Name});
START_TYPE_PROPERTIES({entry.Name})
{registerContent}
END_TYPE_PROPERTIES;
{constructorType}
END_GENERATE_TYPE({entry.Name});

""";
                string fileName = entry.Folder + $@"\{entry.Name}.reflect.h";
                File.WriteAllText(fileName, fileContent);
            }
        }
    }
}
