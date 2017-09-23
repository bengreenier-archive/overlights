using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.IO;
using System.IO.Pipes;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RzChroma
{
    /// <summary>
    /// Control and interact with the underlying native plugin
    /// </summary>
    public static class RzChromaPlugin
    {
        /// <summary>
        /// The registry key in which the native plugin looks to determine if it should run
        /// </summary>
        public static readonly string RegistryEnabledKey = "RzChroma\\Enabled";

        /// <summary>
        /// Indicates if the native plugin is enabled, and can/will run
        /// </summary>
        public static bool Enabled
        {
            get
            {
                return 1 == (int)Registry.CurrentUser.GetValue(RegistryEnabledKey, 0);
            }

            set
            {
                Registry.CurrentUser.SetValue(RegistryEnabledKey, value ? 1 : 0);
            }
        }

        /// <summary>
        /// Creates a new stream to access the native plugin data feed
        /// </summary>
        /// <remarks>
        /// The task resolves when the steam is successfully open
        /// </remarks>
        /// <returns>Task that resolves to the stream</returns>
        public static async Task<Stream> CreateStreamAsync()
        {
            var stream = new NamedPipeClientStream(".", "RzChromaData", PipeDirection.In);

            await stream.ConnectAsync();

            return stream;
        }
    }
}
