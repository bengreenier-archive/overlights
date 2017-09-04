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

        public RzChromaKeyboardData ReadMessage()
        {
            RzChromaKeyboardData data = null;

            try
            {
                var messageType = (NativeLayouts.RZKEYBOARDTYPE)this.reader.ReadInt32();
                
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
                        var colorMap = new NativeLayouts.Color[maxRow][];
                        for (var i = 0; i < maxRow; i++)
                        {
                            colorMap[i] = new NativeLayouts.Color[maxCol];
                            for (var j = 0; j < maxCol; j++)
                            {
                                colorMap[i][j] = new NativeLayouts.Color()
                                {
                                    R = this.reader.ReadByte(),
                                    G = this.reader.ReadByte(),
                                    B = this.reader.ReadByte(),
                                    A = this.reader.ReadByte()
                                };
                            }
                        }
                        data = new RzChromaKeyboardCustomData()
                        {
                            Type = messageType,
                            ColorMap = colorMap
                        };
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
            }
            catch (EndOfStreamException)
            {
                // swallow
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
