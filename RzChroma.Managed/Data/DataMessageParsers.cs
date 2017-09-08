using RzChroma.Data.Keyboard;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RzChroma.Data
{
    /// <summary>
    /// Data parser helpers
    /// </summary>
    /// <remarks>
    /// Capable of determining the correct parser (and parsing) any data
    /// </remarks>
    internal static class DataMessageParsers
    {
        /// <summary>
        /// Attempts to parse any data
        /// </summary>
        /// <param name="reader">a binary reader to parse from</param>
        /// <returns>the data</returns>
        /// <remarks>
        /// This can throw, or return null
        /// </remarks>
        public static IData Root(BinaryReader reader)
        {
            return Parsers[(DataType)reader.ReadInt32()](reader);
        }

        /// <summary>
        /// Map of downlevel parsers, used by <see cref="Root(BinaryReader)"/>
        /// </summary>
        private static readonly Dictionary<DataType, Func<BinaryReader, IData>> Parsers = new Dictionary<DataType, Func<BinaryReader, IData>>()
        {
            { DataType.Keyboard, KeyboardDataMessageParsers.Root }
        };
    }

    /// <summary>
    /// Parsers for keyboard data
    /// </summary>
    internal static class KeyboardDataMessageParsers
    {
        /// <summary>
        /// Attempts to parse keyboard data
        /// </summary>
        /// <param name="reader">a binary reader to parse from</param>
        /// <returns>the data</returns>
        /// <remarks>
        /// This can throw, or return null
        /// </remarks>
        public static IData Root(BinaryReader reader)
        {
            return Parsers[(Keyboard.KeyboardDataType)reader.ReadInt32()](reader);
        }

        /// <summary>
        /// Map of parser logic, used by <see cref="Root(BinaryReader)"/>
        /// </summary>
        private static readonly Dictionary<Keyboard.KeyboardDataType, Func<BinaryReader, Keyboard.IKeyboardData>> Parsers = new Dictionary<Keyboard.KeyboardDataType, Func<BinaryReader, Keyboard.IKeyboardData>>()
        {
            { KeyboardDataType.CHROMA_REACTIVE, ReactiveAndBreathingTemp },
            { KeyboardDataType.CHROMA_BREATHING, ReactiveAndBreathingTemp },
            { KeyboardDataType.CHROMA_CUSTOM, Custom },
            { KeyboardDataType.CHROMA_CUSTOM_KEY, Custom },
            { KeyboardDataType.CHROMA_STARLIGHT, StarlightTemp },
            { KeyboardDataType.CHROMA_STATIC, StaticTemp },
            { KeyboardDataType.CHROMA_WAVE, WaveTemp }
        };
        
        /// <summary>
        /// Parser for custom key data
        /// </summary>
        /// <param name="reader">a binary reader to parse from</param>
        /// <returns>the <see cref="CustomKeyboardData"/></returns>
        private static IKeyboardData Custom(BinaryReader reader)
        {
            var maxRow = reader.ReadInt32();
            var maxCol = reader.ReadInt32();
            var colorMap = new Color[maxRow][];
            for (var i = 0; i < maxRow; i++)
            {
                colorMap[i] = new Color[maxCol];
                for (var j = 0; j < maxCol; j++)
                {
                    colorMap[i][j] = new Color()
                    {
                        R = reader.ReadByte(),
                        G = reader.ReadByte(),
                        B = reader.ReadByte(),
                        A = reader.ReadByte()
                    };
                }
            }
            return new Keyboard.CustomKeyboardData()
            {
                ColorMap = colorMap
            };
        }

        /// <summary>
        /// Temporary parser for reactive and breathing
        /// </summary>
        /// <remarks>
        /// This is temporary cause it does nothing
        /// </remarks>
        /// <param name="reader">a binary reader to parse from</param>
        /// <returns>null</returns>
        private static IKeyboardData ReactiveAndBreathingTemp(BinaryReader reader)
        {
            reader.ReadInt32();
            reader.ReadByte();
            reader.ReadByte();
            reader.ReadByte();
            reader.ReadByte();

            return null;
        }

        /// <summary>
        /// Temporary parser for starlight
        /// </summary>
        /// <remarks>
        /// This is temporary cause it does nothing
        /// </remarks>
        /// <param name="reader">a binary reader to parse from</param>
        /// <returns>null</returns>
        private static IKeyboardData StarlightTemp(BinaryReader reader)
        {
            reader.ReadInt32();
            reader.ReadInt32();
            reader.ReadByte();
            reader.ReadByte();
            reader.ReadByte();
            reader.ReadByte();
            reader.ReadByte();
            reader.ReadByte();
            reader.ReadByte();
            reader.ReadByte();

            return null;
        }

        /// <summary>
        /// Temporary parser for static
        /// </summary>
        /// <remarks>
        /// This is temporary cause it does nothing
        /// </remarks>
        /// <param name="reader">a binary reader to parse from</param>
        /// <returns>null</returns>
        private static IKeyboardData StaticTemp(BinaryReader reader)
        {
            reader.ReadByte();
            reader.ReadByte();
            reader.ReadByte();
            reader.ReadByte();
        }

        /// <summary>
        /// Temporary parser for wave
        /// </summary>
        /// <remarks>
        /// This is temporary cause it does nothing
        /// </remarks>
        /// <param name="reader">a binary reader to parse from</param>
        /// <returns>null</returns>
        private static IKeyboardData WaveTemp(BinaryReader reader)
        {
            reader.ReadInt32();

        }
    }
}
