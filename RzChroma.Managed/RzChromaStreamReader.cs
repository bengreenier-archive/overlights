using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RzChroma.Managed
{
    public class RzChromaStreamReader : IDisposable
    {
        private BinaryReader reader;
        private Stream stream;

        public RzChromaStreamReader(Stream stream)
        {
            this.stream = stream;
            this.reader = new BinaryReader(stream);
        }

        public IReadOnlyList<NativeLayouts.KeyColor> ReadMessage()
        {
            var result = new List<NativeLayouts.KeyColor>();
            var messageType = (NativeLayouts.RZKEYBOARDTYPE) this.reader.ReadInt32();

            var messageContents = this.reader.ReadBytes(4320);

            Console.WriteLine(messageType);
            
            switch (messageType)
            {
                case NativeLayouts.RZKEYBOARDTYPE.CHROMA_BREATHING:
                case NativeLayouts.RZKEYBOARDTYPE.CHROMA_REACTIVE:
                    this.reader.ReadInt32();
                    this.reader.ReadByte();
                    this.reader.ReadByte();
                    this.reader.ReadByte();
                    this.reader.ReadByte();
                    break;
                case NativeLayouts.RZKEYBOARDTYPE.CHROMA_CUSTOM:
                case NativeLayouts.RZKEYBOARDTYPE.CHROMA_CUSTOM_KEY:
                    var maxRow = this.reader.ReadInt32();
                    var maxCol = this.reader.ReadInt32();
                    for (var i = 0; i < maxRow; i++)
                    {
                        for (var j = 0; j < maxCol; j++)
                        {
                            this.reader.ReadByte();
                            this.reader.ReadByte();
                            this.reader.ReadByte();
                            this.reader.ReadByte();
                        }
                    }
                    break;
                case NativeLayouts.RZKEYBOARDTYPE.CHROMA_STARLIGHT:
                    this.reader.ReadInt32();
                    this.reader.ReadInt32();
                    this.reader.ReadByte();
                    this.reader.ReadByte();
                    this.reader.ReadByte();
                    this.reader.ReadByte();
                    this.reader.ReadByte();
                    this.reader.ReadByte();
                    this.reader.ReadByte();
                    this.reader.ReadByte();
                    break;
                case NativeLayouts.RZKEYBOARDTYPE.CHROMA_STATIC:
                    this.reader.ReadByte();
                    this.reader.ReadByte();
                    this.reader.ReadByte();
                    this.reader.ReadByte();
                    break;
                case NativeLayouts.RZKEYBOARDTYPE.CHROMA_WAVE:
                    this.reader.ReadInt32();
                    break;
            }

            return result;
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
