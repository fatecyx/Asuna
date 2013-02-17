using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace ResourceExtracter
{
        public unsafe class HuffmanCoding
        {
            class HuffNode
            {
                public byte content = 0;
                public int frequency;
                public HuffNode zero;
                public HuffNode one;
                public int code;
                public byte bits;
                public bool top = false;

                public void CalcFreq()
                {
                    if (zero != null && one != null)
                    {
                        zero.CalcFreq();
                        one.CalcFreq();
                        frequency = zero.frequency + one.frequency;
                    }
                }
            }

            public byte[] src;
            public int srcLen;
            int srcIndex;
            public byte[] buffer;
            public int bufferLen;
            int dstIndex;
            int field_1C;
            int bits;
            short field_22 = 8;
            short curChar;
            short filed_26;
            byte[] Dic1;
            byte[] Dic2;
            byte[] Dic3;
            byte[] Dic4;
            byte[] Dic5;
            short field_181E;
            short field_181C;
            int field_1820;
            short field_1824;
            short field_1826 = 256;
            public HuffmanCoding()
            {
                Dic1 = new byte[1022];
                Dic2 = new byte[1022];
                Dic3 = new byte[1022];
                Dic4 = new byte[1022];
                Dic5 = new byte[2044];
            }

            int sub_411920()
            {
                this.bits--;
                if (bits < 0)
                {
                    bits = 7;
                    if (srcLen > srcIndex)
                    {
                        curChar = src[srcIndex];
                        srcIndex++;
                        return curChar >> 7;
                    }
                    else
                    {
                        curChar = -1;
                        return 1;
                    }
                }
                else
                {
                    return (curChar >> bits) & 1;
                }
            }

            short Prepare()
            {
                short v4;
                if (sub_411920() > 0)
                {
                    short v3 = field_1826++;
                    if (v3 < 511)
                    {
                        fixed (byte* ptr = Dic3)
                            *(short*)&ptr[2 * v3] = Prepare();
                        fixed (byte* ptr = Dic4)
                            *(short*)&ptr[2 * v3] = Prepare();
                        v4 = v3;
                    }
                    else
                        v4 = -1;
                }
                else
                {
                    int v6 = 8, v16 = 0;
                    if (bits < 8)
                    {
                        int v8 = srcLen;
                        int v7 = v16;
                        do
                        {
                            int v14 = bits;
                            v6 -= v14;
                            v7 |= (((byte)curChar) & (ushort)((1 << v14) - 1)) << v6;
                            byte v10;
                            if (v8 > (uint)srcIndex)
                            {
                                v10 = src[srcIndex++];
                            }
                            else
                                v10 = 255;
                            curChar = v10;
                            bits = 8;
                        } while (v6 > 8);
                        v16 = v7;
                    }
                    bits -= v6;
                    v4 = (short)(v16 | ((1 << v6) - 1) & (curChar >> bits));
                }
                return v4;
            }

            public void Decompress()
            {
                short i = Prepare();
                int index = 0;
                if (bufferLen > 0)
                {
                    do
                    {
                        short v8 = i;
                        while (v8 >= 256)//if not leef
                        {
                            bits--;
                            int v9;
                            if (bits < 0)
                            {
                                bits = 7;
                                byte v11;
                                if (srcLen > srcIndex)
                                {
                                    v11 = src[srcIndex++];
                                }
                                else
                                    v11 = 255;
                                curChar = v11;
                                v9 = v11 >> 7;
                            }
                            else
                                v9 = ((byte)(curChar) >> bits) & 1;
                            if (v9 > 0)
                            {
                                fixed (byte* ptr = Dic4)
                                    v8 = *(short*)&ptr[2 * v8];
                            }
                            else
                            {
                                fixed (byte* ptr = Dic3)
                                    v8 = *(short*)&ptr[2 * v8];
                            }
                        }
                        if (bufferLen > dstIndex)
                        {
                            buffer[dstIndex++] = (byte)(sbyte)v8;
                        }
                        index++;
                    } while (index < bufferLen);
                }
            }

            HuffNode BuildHuffTree()
            {
                Dictionary<byte, int> frequency = new Dictionary<byte, int>();
                foreach (byte i in src)
                {
                    if (!frequency.ContainsKey(i))
                        frequency.Add(i, 0);
                    frequency[i]++;
                }
                var tmp = from t in frequency
                          where true
                          orderby t.Value
                          select t.Key;
                List<byte> ordered = tmp.ToList();
                List<HuffNode> nodes = new List<HuffNode>();
                HuffNode one;
                HuffNode zero;
                HuffNode root;
                int index = 0;
                while (index < ordered.Count)
                {
                    var tmp2 = from t in nodes
                               where t.top && (t.frequency < frequency[ordered[index]] || t.frequency < frequency[ordered[index + 1]])
                               orderby t.frequency
                               select t;
                    List<HuffNode> finished = tmp2.ToList();
                    int rest = 2 - finished.Count;
                    for (int i = 0; i < rest; i++)
                    {
                        HuffNode node = new HuffNode();
                        node.content = ordered[index++];
                        node.frequency = frequency[node.content];
                        node.top = true;
                        nodes.Add(node);
                        finished.Add(node);
                    }
                    zero = finished[0];
                    one = finished[1];
                    HuffNode top = new HuffNode();
                    top.zero = zero;
                    top.one = one;
                    top.top = true;
                    top.CalcFreq();
                    zero.top = false;
                    one.top = false;
                    nodes.Add(top);
                }
                {
                    root = nodes[nodes.Count - 1];
                    if (root.frequency == src.Length)
                    {
                        List<HuffNode> opend = new List<HuffNode>();
                        opend.Add(root);
                        while (opend.Count > 0)
                        {
                            HuffNode node = opend[0];
                            opend.Remove(node);
                            if (node.zero != null)
                            {
                                node.zero.bits = (byte)(node.bits + 1);
                                node.zero.code = (int)(node.code | (0 << node.zero.bits));
                                opend.Add(node.zero);
                            }
                            if (node.one != null)
                            {
                                node.one.bits = (byte)(node.bits + 1);
                                node.one.code = (int)(node.code | ((1 << (node.one.bits - 1))));
                                opend.Add(node.one);
                            }
                        }
                        return root;
                    }
                }
                return null;
            }

            void WriteHuffTree(HuffNode root, System.IO.Stream stream)
            {
                if (root.zero != null)
                {
                    WriteBits(1, 1, stream);
                    WriteHuffTree(root.zero, stream);
                    if (root.one != null)
                    {
                        WriteHuffTree(root.one, stream);
                    }
                    else throw new Exception();
                }
                else
                {
                    if (root.one == null)
                    {
                        WriteBits(0, 1, stream);
                        WriteBits(root.content, 8, stream);
                    }
                    else throw new Exception();
                }
            }
            void WriteBits(int val, int bits, System.IO.Stream stream)
            {
                WriteBits(val, bits, stream, true);
            }
            void WriteBits(int val, int bits, System.IO.Stream stream,bool flip)
            {
                int possible = 8 - this.bits;
                int rest = bits - possible;
                if (flip)
                {
                    int tmp = 0;
                    for (int i = 0; i < bits; i++)
                    {
                        tmp |= ((val >> i) & 1) << ((bits - i) - 1);
                    }
                    val = tmp;
                }
                for (int i = 0; i < possible && bits > 0; i++)
                {
                    int bit = val & 1;
                    val = (val >> 1);
                    curChar |= (short)(bit << ((8 - this.bits++) - 1));
                    bits--;
                }
                if (this.bits >= 8)
                {
                    stream.WriteByte((byte)curChar);
                    curChar = 0;
                    this.bits = 0;
                }
                for (int i = 0; i < rest && bits > 0 && this.bits < 7; i++)
                {
                    int bit = val & 1;
                    val = (val >> 1);
                    curChar |= (short)(bit << ((8 - this.bits++) - 1));
                    bits--;
                }
                if (bits > 0)
                    WriteBits(val, bits, stream, flip);
            }

            void EncodeByte(HuffNode root, byte val, out int res, out int bits)
            {
                List<HuffNode> opend = new List<HuffNode>();
                opend.Add(root);
                HuffNode found = null;
                while (opend.Count > 0)
                {
                    HuffNode node = opend[0];
                    opend.Remove(node);
                    if (node.content == val && node.zero == null && node.one == null)
                    {
                        found = node;
                        break;
                    }
                    if (node.zero != null)
                        opend.Add(node.zero);
                    if (node.one != null)
                        opend.Add(node.one);
                }
                if (found == null)
                    throw new Exception();
                res = found.code;
                bits = found.bits;
            }

            void WriteContent(HuffNode root,System.IO.Stream stream)
            {
                foreach (byte i in src)
                {
                    int code;
                    int bits;
                    EncodeByte(root, i, out code, out bits);
                    WriteBits(code, bits, stream, false);
                }
            }

            public void Compress()
            {
                HuffNode root = BuildHuffTree();
                System.IO.MemoryStream ms = new System.IO.MemoryStream();
                bits = 0;
                curChar = 0;
                WriteHuffTree(root, ms);
                WriteContent(root, ms);
                buffer = ms.ToArray();
                bufferLen = buffer.Length;
            }
        }
}
