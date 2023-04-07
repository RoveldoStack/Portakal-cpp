using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ReflectionParserTool
{
    public static class Message
    {
        public static void Info(string message)
        {
            ConsoleColor formerColor = Console.ForegroundColor;
            Console.ForegroundColor = ConsoleColor.White;
            Console.WriteLine(message);
            Console.ForegroundColor = formerColor;
        }
        public static void Warning(string message)
        {
            ConsoleColor formerColor = Console.ForegroundColor;
            Console.ForegroundColor = ConsoleColor.Yellow;
            Console.WriteLine(message);
            Console.ForegroundColor = formerColor;
        }
        public static void Error(string message)
        {
            ConsoleColor formerColor = Console.ForegroundColor;
            Console.ForegroundColor = ConsoleColor.Red;
            Console.WriteLine(message);
            Console.ForegroundColor = formerColor;
        }
    }
}
