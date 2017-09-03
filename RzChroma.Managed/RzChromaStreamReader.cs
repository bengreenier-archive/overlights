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
            // key count:
            var totalKeys = this.reader.ReadInt32();
            var keys = new List<NativeLayouts.KeyColor>();
            
            for (var i = 0; i < totalKeys; i++)
            {
                // key:
                var keyNum = this.reader.ReadInt32();
                var keyEnum = (NativeLayouts.RZKEY)keyNum;

                // r, g, b, a
                var rNum = this.reader.ReadSByte();
                var gNum = this.reader.ReadSByte();
                var bNum = this.reader.ReadSByte();
                var aNum = this.reader.ReadSByte();

                // done:
                keys.Add(new NativeLayouts.KeyColor()
                {
                    key = keyEnum,
                    r = rNum,
                    g = gNum,
                    b = bNum,
                    a = aNum
                });
            }

            return keys;
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
