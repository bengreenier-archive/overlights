using RzChroma.Data;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RzChroma
{
    /// <summary>
    /// Reads RzChroma binary data from a given stream
    /// </summary>
    /// <remarks>
    /// This closes the stream on <see cref="Dispose"/>
    /// </remarks>
    public class RzChromaStreamReader : IDisposable
    {
        private BinaryReader reader;
        private Stream stream;

        /// <summary>
        /// Default ctor
        /// </summary>
        /// <param name="stream">the stream to read from</param>
        public RzChromaStreamReader(Stream stream)
        {
            this.stream = stream;
            
            this.reader = new BinaryReader(stream);
        }

        /// <summary>
        /// Blocking IO, reads a <see cref="IData"/> message from the stream
        /// </summary>
        /// <remarks>
        /// Use <see cref="IDataExtensions.As{TCast}(IData)"/> to cast the data
        /// </remarks>
        /// <returns>data that makes up the message, or null</returns>
        public IData ReadMessage()
        {
            IData data = null;

            try
            {
                data = DataMessageParsers.Root(this.reader);
            }
            catch (KeyNotFoundException)
            {
                // swallow (no parser)
            }
            catch (EndOfStreamException)
            {
                // swallow (stream closed)
            }

            return data;
        }

        #region IDisposable Support
        private bool disposedValue = false; // To detect redundant calls

        protected virtual void Dispose(bool disposing)
        {
            if (!disposedValue)
            {
                if (disposing)
                {
                    this.reader.Dispose();
                }

                disposedValue = true;
            }
        }
        
        // This code added to correctly implement the disposable pattern.
        public void Dispose()
        {
            // Do not change this code. Put cleanup code in Dispose(bool disposing) above.
            Dispose(true);
        }
        #endregion
    }
}
