using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ReflectionParserTool
{
    internal static class Parser
    {
        private struct ReflectionEnableUnit
        {
            public string HeaderFile;
            public string Content;
            public ObjectType Type;
        }
      
        private static ObjectEntry? FindClass(IReadOnlyCollection<ObjectEntry> entries,string name)
        {
            foreach (ObjectEntry entry in entries)
                if (entry.Name == name)
                    return entry;

            return null;
        }
        internal static void Clear(string targetDirectory)
        {
            /*
            * Collect all the files with extension .reflect.h
            */
            string[] headerFiles = Directory.GetFiles(targetDirectory, "*.reflect.h", SearchOption.AllDirectories);
            foreach (string headerFile in headerFiles) 
            {
                File.Delete(headerFile);
            }
        }
        internal static void Parse(string targetDirectory)
        {
            List<ObjectEntry> objectEntries = new List<ObjectEntry>();

            /*
             * Collect all the files with extension .h
             */
            string[] headerFiles = Directory.GetFiles(targetDirectory, "*.h", SearchOption.AllDirectories);

            /*
             * Collect classes
             */
            List<ReflectionEnableUnit> reflectionEnabledUnits = new List<ReflectionEnableUnit>();
            foreach (string headerFile in headerFiles)
            {
                string fileContent = File.ReadAllText(headerFile);

                int index = fileContent.IndexOf("PCLASS");
                if (index != -1)
                {
                    reflectionEnabledUnits.Add(new ReflectionEnableUnit() { HeaderFile = headerFile,Content = fileContent,Type = ObjectType.Class});
                    continue;
                }
                index = fileContent.IndexOf("PSTRUCT");
                if (index != -1)
                {
                    reflectionEnabledUnits.Add(new ReflectionEnableUnit() { HeaderFile = headerFile, Content = fileContent, Type = ObjectType.Struct });
                    continue;
                }

            }

            /*
             * Collect enums
             */
            List<string> reflectionEnabledEnums = new List<string>();
            foreach(string headerFile in headerFiles)
            {
                string fileContent = File.ReadAllText(headerFile, Encoding.UTF8);

                if (fileContent.IndexOf("#define PENUM") != -1)
                    continue;

                int index = fileContent.IndexOf("PENUM");

                if (index == -1)
                    continue;

                reflectionEnabledEnums.Add(headerFile);
            }


            /*
             * First collect all the reflected classes and their local properties
             */
            foreach(ReflectionEnableUnit unit in reflectionEnabledUnits)
            {
                string className = Path.GetFileNameWithoutExtension(unit.HeaderFile);

                /*
                 * Try find class name
                 */
                int classNameCursor = unit.Content.IndexOf(className);
                if (classNameCursor == -1)
                    continue;
                if (className == "Class")
                    continue;

                bool bVirtual = unit.Content.Contains("Virtual");
                objectEntries.Add(new ObjectEntry(className,unit.HeaderFile,unit.Content,unit.Type,bVirtual,false));  
            }

            /*
             * Collect all reflected enums and their local properties
             */
            foreach(string headerFilePath in reflectionEnabledEnums)
            {
                string enumName = Path.GetFileNameWithoutExtension(headerFilePath);
                string fileContent = File.ReadAllText(headerFilePath);

                /*
                 * Try find enum name
                 */
                int enumNameCursor = fileContent.IndexOf(enumName);
                if (enumNameCursor == -1)
                    continue;

                /*
                 * Collect enums
                 */
                int enumStartIndex = fileContent.IndexOf("{", enumNameCursor);
                if (enumStartIndex == -1)
                    continue;

                int enumEndIndex = fileContent.IndexOf("}", enumStartIndex);
                if (enumEndIndex == -1)
                    continue;

                string subStr = fileContent.Substring(enumStartIndex+1,(enumEndIndex-enumStartIndex)-1);
                subStr = subStr.Replace(Environment.NewLine, "");
                subStr = subStr.Replace("\t", "");
                string[] fragments = subStr.Split(",");

                ObjectEntry entry = new ObjectEntry(enumName, headerFilePath, fileContent, ObjectType.Class, false, true);
                objectEntries.Add(entry);

                int value = 0;
                foreach(string fragment in fragments)
                {
                    entry.RegisterEnum(fragment, value);
                    value++;
                }

            }
            /*
             * Generate class hierarchies
             */
            foreach(ObjectEntry entry in objectEntries)
            {
                if (entry.IsEnum)
                    continue;

               
                if(entry.Name == "Guid")
                {
                    Console.WriteLine("wee");
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
                if(entry.Type == ObjectType.Class)
                {
                    int baseClassStartCursor = entry.FileContent.IndexOf(":", classNameCursor);
                    int baseClassEndCursor = entry.FileContent.IndexOf("{", baseClassStartCursor == -1 ? 0 : baseClassStartCursor);
                    if (baseClassStartCursor != -1 && baseClassEndCursor != -1)
                    {
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
                    }
                }


                /*
                 * Try collect class attributes
                 */
                int classAttributeCursor = entry.FileContent.IndexOf("PCLASS_ATTRIBUTE");
                while(classAttributeCursor != -1)
                {
                    int attributeEndCursor = entry.FileContent.IndexOf(System.Environment.NewLine, classAttributeCursor);
                    string subStr = entry.FileContent.Substring(classAttributeCursor, (attributeEndCursor-classAttributeCursor));
                    subStr = subStr.Trim();
                    subStr = subStr.Replace("PCLASS_ATTRIBUTE(", string.Empty);
                    subStr = subStr.Replace(");", string.Empty);

                    int parameterStart = subStr.IndexOf(",");
                    if(parameterStart == -1) // has no parameters
                    {
                        classAttributeCursor = entry.FileContent.IndexOf("PCLASS_ATTRIBUTE", attributeEndCursor);
                        continue;
                    }

                    string attributeName = subStr.Substring(0,parameterStart);
                    string attributeParameters = subStr.Substring(parameterStart+1);

                    entry.RegisterClassAttribute(attributeName, attributeParameters);

                    classAttributeCursor = entry.FileContent.IndexOf("PCLASS_ATTRIBUTE", attributeEndCursor);
                }

                /*
                 * Try collect fields
                 */
                int fieldStartCursor = entry.FileContent.IndexOf("PFIELD");
                while(fieldStartCursor != -1)
                {
                    int fieldEndCursor = entry.FileContent.IndexOf(";",fieldStartCursor);

                    if(fieldEndCursor == -1)
                    {
                        fieldStartCursor = entry.FileContent.IndexOf("PFIELD", fieldStartCursor + "PFIELD".Length);
                        continue;
                    }

                    int fieldBodyStartCursor = fieldEndCursor;
                    int fieldBodyEndCursor = entry.FileContent.IndexOf(";", fieldBodyStartCursor+1);
                    if(fieldBodyEndCursor == -1)
                    {
                        fieldStartCursor = entry.FileContent.IndexOf("PFIELD", fieldBodyEndCursor);
                        continue;
                    }

                    string subStr = entry.FileContent.Substring(fieldBodyStartCursor+1, fieldBodyEndCursor - fieldBodyStartCursor-1);
                    subStr = subStr.Trim();

                    string[] fragments = subStr.Split(' ');
                    string fieldType = fragments[0];
                    string fieldName = fragments[1];
                    bool bArray = fieldType.Contains("Array");
                    if(bArray)
                    {
                        string elementType = fieldType;
                        elementType = elementType.Replace("Array<", "");
                        elementType = elementType.Replace(">", "");
                        entry.RegisterFieldArray(fieldType, fieldName, elementType);
                    }
                    else
                    {
                        entry.RegisterField(fieldType, fieldName);

                    }
                    fieldStartCursor = entry.FileContent.IndexOf("PFIELD", fieldBodyEndCursor);
                }
            }

            /*
             * Generate functions
             */

            /*
             * Write classes
             */
            foreach(ObjectEntry entry in objectEntries)
            {
                if (entry.IsEnum)
                    continue;

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
                    if(field.IsArray)
                    {
                        registerContent += $"REGISTER_ARRAY_FIELD({entry.Name},{field.Name},{field.ElementType},AccessSpecifier::Public);{System.Environment.NewLine}";

                    }
                    else
                    {
                        registerContent += $"REGISTER_FIELD({entry.Name},{field.Name},{field.Type},AccessSpecifier::Public);{System.Environment.NewLine}";

                    }
                }
               
                string constructorType = !entry.IsVirtual ? $"HAS_DEFAULT_CONSTRUCTOR({entry.Name});" : "NO_DEFAULT_CONSTRUCTOR;";
                string typePropertiesType = entry.Type == ObjectType.Class  ? "START_CLASS_TYPE_PROPERTIES" : "START_STRUCT_TYPE_PROPERTIES";
                string fileContent = $"""
#include "{entry.Name}.h" 
START_GENERATE_TYPE({entry.Name});
{typePropertiesType}({entry.Name})
{registerContent}
END_TYPE_PROPERTIES;
{constructorType}
END_GENERATE_TYPE({entry.Name});
""";
                string fileName = entry.Folder + $@"\{entry.Name}.reflect.h";
                File.WriteAllText(fileName, fileContent);

                Console.WriteLine($"Written reflect file for: {entry.Name}-{entry.Folder}");
            }

            foreach (ObjectEntry entry in objectEntries)
            {
                if (!entry.IsEnum)
                    continue;

                string registerContent = "";
                foreach (EnumEntry enumEntry in entry.Enums)
                {
                    registerContent += $"REGISTER_ENUM({enumEntry.Name},{enumEntry.Value});{Environment.NewLine}";
                }

                string fileContent = $"""
                    #include "{entry.Name}.h"
                    START_GENERATE_ENUM({entry.Name});
                    {registerContent}
                    END_GENERATE_ENUM({entry.Name});
                    """;

                string fileName = entry.Folder + $@"\{entry.Name}.reflect.h";
                File.WriteAllText(fileName, fileContent);
            }
        }
    }
}
