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
        private static readonly Dictionary<KeyboardDataType, Func<BinaryReader, IKeyboardData>> Parsers = new Dictionary<KeyboardDataType, Func<BinaryReader, IKeyboardData>>()
        {
            { KeyboardDataType.CHROMA_REACTIVE, Reactive },
            { KeyboardDataType.CHROMA_BREATHING, Breathing },
            { KeyboardDataType.CHROMA_CUSTOM, Custom },
            { KeyboardDataType.CHROMA_CUSTOM_KEY, Custom },
            { KeyboardDataType.CHROMA_STARLIGHT, Starlight },
            { KeyboardDataType.CHROMA_STATIC, Static },
            { KeyboardDataType.CHROMA_WAVE, Wave }
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

            return new CustomKeyboardData()
            {
                ColorMap = colorMap
            };
        }

        /// <summary>
        /// Parser for reactive key data
        /// </summary>
        /// <param name="reader">a binary reader to parse from</param>
        /// <returns>the <see cref="ReactiveKeyboardData"/></returns>
        private static IKeyboardData Reactive(BinaryReader reader)
        {
            return new ReactiveKeyboardData()
            {
                Duration = (ReactiveKeyboardData.DurationType)reader.ReadInt32(),
                Color = new Color()
                {
                    R = reader.ReadByte(),
                    G = reader.ReadByte(),
                    B = reader.ReadByte(),
                    A = reader.ReadByte()
                }
            };
        }

        /// <summary>
        /// Parser for breathing key data
        /// </summary>
        /// <param name="reader">a binary reader to parse from</param>
        /// <returns>the <see cref="BreathingKeyboardData"/></returns>
        private static IKeyboardData Breathing(BinaryReader reader)
        {
            return new BreathingKeyboardData()
            {
                BreathingType = (BreathingKeyboardData.BreathingEffect)reader.ReadInt32(),
                ColorOne = new Color()
                {
                    R = reader.ReadByte(),
                    G = reader.ReadByte(),
                    B = reader.ReadByte(),
                    A = reader.ReadByte()
                },
                ColorTwo = new Color()
                {
                    R = reader.ReadByte(),
                    G = reader.ReadByte(),
                    B = reader.ReadByte(),
                    A = reader.ReadByte()
                }
            };
        }
        
        /// <summary>
        /// Parser for starlight
        /// </summary>
        /// <param name="reader">a binary reader to parse from</param>
        /// <returns>the <see cref="StarlightKeyboardData"/></returns>
        private static IKeyboardData Starlight(BinaryReader reader)
        {
            return new StarlightKeyboardData()
            {
                StarlightType = (StarlightKeyboardData.StarlightEffect)reader.ReadInt32(),
                Duration = (StarlightKeyboardData.DurationType)reader.ReadInt32(),
                ColorOne = new Color()
                {
                    R = reader.ReadByte(),
                    G = reader.ReadByte(),
                    B = reader.ReadByte(),
                    A = reader.ReadByte()
                },
                ColorTwo = new Color()
                {
                    R = reader.ReadByte(),
                    G = reader.ReadByte(),
                    B = reader.ReadByte(),
                    A = reader.ReadByte()
                }
            };
        }

        /// <summary>
        /// Parser for static
        /// </summary>
        /// <param name="reader">a binary reader to parse from</param>
        /// <returns>the <see cref="StaticKeyboardData"/></returns>
        private static IKeyboardData Static(BinaryReader reader)
        {
            return new StaticKeyboardData()
            {
                Color = new Color()
                {
                    R = reader.ReadByte(),
                    G = reader.ReadByte(),
                    B = reader.ReadByte(),
                    A = reader.ReadByte()
                }
            };
        }

        /// <summary>
        /// Parser for wave
        /// </summary>
        /// <param name="reader">a binary reader to parse from</param>
        /// <returns>the <see cref="WaveKeyboardData"/></returns>
        private static IKeyboardData Wave(BinaryReader reader)
        {
            return new WaveKeyboardData()
            {
                Direction = (WaveKeyboardData.DirectionType)reader.ReadInt32()
            };
        }
    }
}
