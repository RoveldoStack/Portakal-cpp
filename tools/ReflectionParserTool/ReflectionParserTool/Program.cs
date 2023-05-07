using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ReflectionParserTool
{
    internal static class Program
    {
        internal static void Main(string[] args)
        {
            /*
             * Validate if given path is valid
             */
            if (args.Length == 0)
            {
                Message.Error("There are no valid arguments given!, terminating the parser");
                return;
            }
            string targetDirectory = args[0];
            if (!Directory.Exists(targetDirectory))
            {
                Message.Error($"Given root directory path is invalid {targetDirectory}");
                return;
            }

            bool bClearFirst = args.Contains("-clear");

            ///*
            // * Clear first
            // */
            //if(bClearFirst)
            //    Parser.Clear(targetDirectory);

            /*
             * Parse
             */
            Parser.Parse(targetDirectory);


        }
    }
}
