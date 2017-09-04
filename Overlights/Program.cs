using RzChroma.Managed;
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
            using (var sr = new RzChromaStreamReader(stream))
            {
                while (stream.IsConnected)
                {
                    foreach (var msg in sr.ReadMessage())
                    {
                        Console.WriteLine($"{msg.key}: {msg.r}, {msg.g}, {msg.b}, {msg.a}");
                    }
                }
            }

            stream.Close();
        }
    }
}
