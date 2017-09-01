using System;
using System.IO;
using System.IO.Pipes;

namespace Overlights
{
    class Program
    {
        static void Main(string[] args)
        {
            var stream = new NamedPipeClientStream(".", "RzChromaData", PipeDirection.In);

            Console.Write("Connecting...");

            stream.Connect();

            Console.WriteLine("Connected");

            using (var sr = new StreamReader(stream))
            {
                while (stream.IsConnected)
                {
                    Console.WriteLine(sr.ReadLine());
                }
            }

            stream.Close();
        }
    }
}
