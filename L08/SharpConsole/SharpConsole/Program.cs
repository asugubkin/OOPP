using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.IO;
using System.Xml.Serialization;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
using System.Runtime.Serialization.Formatters.Soap;
using System.Text.Json;

namespace SharpConsole
{
    public class Program
    {

        #region Strings
        static void Strings()
        {
            int i = 1;
            Console.WriteLine("i = {0}", i);
            string s = String.Format("i = {0}", i);
            s = $"i = {i}";
            s = @"
                First line
                Second line
                {s}
            ";
            Console.WriteLine(s);
            s = $"i = {i}";
            s = $@"
                First line
                Second line
                {s}
            ";
            Console.WriteLine(s);

            var sb1 = new StringBuilder(s);
            var sb2 = new StringBuilder(256);
            sb2.Append(sb1);
            Console.WriteLine(sb2);
        }
        #endregion

        #region Functions

        static void f1(int i, out double d, ref string s1, string s2, StringBuilder sb)
        {
            i++;
            if (!Double.TryParse(s1, out d))
                d = 0;
            s1 += $" {i}";
            s2 += $" {i}";
            sb.Append(s1);
        }
        static void f2(int i1 = 1, int i2 = 2, int i3 = 3)
        {
            Console.WriteLine($"{i1} {i2} {i3}");
        }

        static void f3(params int[] values)
        {
            foreach(var i in values)
            {
                Console.Write($"{i} ");
            }
            Console.WriteLine();
        }

        static int? f4(int i)
        {
            if(i % 2 == 0)
            {
                return null;
            }
            return i;
        }

        static void Functions()
        {
            Console.WriteLine("Functions");
            int i = 0;
            double d = 0;
            string s1 = "13.3";
            string s2 = "13.3";
            var sb = new StringBuilder("---");
            Console.WriteLine($"i = {i}, d = {d}, s1 = {s1}, s2 = {s2}, sb = {sb}");
            f1(i, out d, ref s1, s2, sb);
            Console.WriteLine($"i = {i}, d = {d}, s1 = {s1}, s2 = {s2}, sb = {sb}");

            f2(10, 20);
            f2(i2: 200, i1:100);

            f3(1, 2, 3, 4, 5);
            f3(100, 200, 300);

            for (int j = 0; j < 10; j++)
            {
                int? nI = f4(j);        // int I = f4(j) ?? 100;
                if (nI.HasValue)        // if(nI != null)
                {
                    Console.Write($"{nI} ");
                }
            }
            Console.WriteLine();
//            string? s3;
        }

        #endregion

        #region Arrays
        static void Arrays()
        {
            Console.WriteLine("Arrays");
            int[] a1 = new int[10];
            int[] a2 = new int[] { 1, 2, 3 };
            int[] a3 = { 1, 2, 3 };
            var a4 = new[]{ 1, 2, 3 };

            int[,] a5 = new int[5, 5];
            foreach (var i in a5)
            {
                Console.Write($"{i} ");
            }
            Console.WriteLine();

            for (int i = 0; i < a5.GetLength(0); i++)
            {
                for (int j = 0; j < a5.GetLength(1); j++)
                {
                    Console.Write($"{a5[i, j]} ");
                }
                Console.WriteLine();
            }

            Console.WriteLine();

            int[][] a6 = new int[5][];
            for (int i = 0; i<a6.Length; i++)
            {
                a6[i] = new int[i+5];
            }

            for (int i = 0; i < a6.Length; i++)
            {
                for (int j = 0; j < a6[i].Length; j++)
                {
                    Console.Write($"{a6[i][j]} ");
                }
                Console.WriteLine();
            }
        }
        #endregion

        #region Structures

        struct MyStruct
        {
            public int i;
            public string s;
            public void f()
            {
                Console.WriteLine($"i = {i}, s = {s}");
            }
            public MyStruct(int I, string S)
            {
                i = I;
                s = S;
            }
        }

        static void fs(MyStruct s)
        {
            s.i++;
            s.s = "????";
            s.f();
        }

        static void Structures()
        {
            Console.WriteLine("Structures");
            MyStruct s1;
            s1.i = 12345;
            s1.s = "qwerty";
            s1.f();

            MyStruct s2 = new MyStruct();
            s2.f();

            MyStruct s3 = new MyStruct(777, "!!!");
            s3.f();
            fs(s3);
            s3.f();
        }
        #endregion

        #region Classes

        class MyClass
        {
            public readonly double PI = 3.14;
            public int i = 0;
            public string s = "---";
            public void f()
            {
                Console.WriteLine($"i = {i}, s = {s}");
            }
            public MyClass()
            {
                PI = 3.14159265359;
            }
            public MyClass(int I, string s)
                :this()
            {
                i = I;
                this.s = s;
            }
        }

        partial class PartialClass
        {
            int i;
        }

        partial class PartialClass
        {
            public PartialClass(int I)
            {
                i = I;
            }
        }

        static void fc(MyClass s)
        {
            s.i++;
            s.s = "????";
            s.f();
        }


        static void Classes()
        {
            Console.WriteLine("Classes");
            /*
            MyClass s1;
            s1.i = 12345;
            s1.s = "qwerty";
            s1.f();
            */

            MyClass s2 = new MyClass();
            s2.f();
            
            
            MyClass s3 = new MyClass(777, "!!!");
            s3.f();
            fc(s3);
            s3.f();

            MyClass s4 = new MyClass { i = 6, s = "???" };
            s4.f();
        }
        #endregion

        #region Operators
        class OpClass
        {
            int i;
            public OpClass(int I)
            {
                i = I;
            }

            public void f()
            {
                Console.WriteLine($"OpClass.f: i = {i}");
            }

            static public OpClass operator + (OpClass op1, OpClass op2)
            {
                return new OpClass(op1.i+op2.i);
            }

            static public OpClass operator++(OpClass op)
            {
                return new OpClass(op.i+1);
            }
            public static implicit operator int(OpClass op)
            {
                Console.WriteLine("implicit int()");
                return op.i;
            }
            public static explicit operator double(OpClass op)
            {
                Console.WriteLine("explicit double()");
                return op.i;
            }

        }

        static void fo(OpClass o)
        {
            o.f();
        }
        static void Operators()
        {
            Console.WriteLine("Operators");
            var o1 = new OpClass(10);
            var o2 = new OpClass(100);
            (o1 + o2).f();
            fo(++o1);
            o1.f();
            fo(o2++);
            o2.f();
            int i = o1;
            int j = (int)o2;
            double d = (double)o1;
            double f = o2;
        }
        #endregion

        #region Properties
        partial class Currency
        {
            public int k = 0;

            public Currency(int K)
            {
                k = K;
            }

            public void SetR(int r)
            {
                k = r * 100;
            }
            public int GetR()
            {
                return k / 100;
            }
            public double R
            {
                get
                {
                    return k / 100;
                }
                set
                {
                    k = (int)(value * 100);
                }
            }

            public double rate { get; set; } = 80;
            public double D
            {
                get { return R / rate; }
                set { R = value * rate; }
            }

            public void Print()
            {
                Console.WriteLine($"{k}k = {R}R = {D}D");
            }
            public string this[int index]
            {
                get
                { 
                    switch(index)
                    {
                        case 1:
                            return $"{R}";
                        case 2:
                            return $"{D}";
                        default:
                            return $"{k}";
                    }
                }
            }
        }

        static void Properties()
        {
            Console.WriteLine("Properties");
            var c = new Currency(100);
            c.Print();
            c.D = 50;
            c.Print();
            Console.WriteLine(c[0]);
            Console.WriteLine(c[1]);
            Console.WriteLine(c[2]);

        }
        #endregion

        #region Inheritance

        class BaseClass
        {
            protected int i;
            public BaseClass(int I)
            {
                i = I;
            }
            public virtual void f()
            {
                Console.WriteLine($"BaseClass: i = {i}");
            }

            public override string ToString()
            {
                return $"BaseClass: i = {i}";
            }
        }

        sealed class DerivedClass: BaseClass
        {
            int j;
            public DerivedClass(int I, int J)
                :base(I)
            {
                j = J;
            }
            sealed public override void f()
            {
                Console.WriteLine($"DerivedClass: i = {i}, j = {j}");
            }
        }
        abstract class BaseAbstract
        {
            public abstract void f();
        }

        class DerivedAbstract: BaseAbstract
        {
            public override void f()
            {
                Console.WriteLine("DerivedAbstract.f");
            }
        }

        static void Inheritance()
        {
        	Console.WriteLine("Inheritance");
            BaseClass b = new DerivedClass(1, 2);
            b.f();
            Console.WriteLine(b);
            if (b is DerivedClass)
            {
                DerivedClass d = b as DerivedClass;
            }
            BaseAbstract a = new DerivedAbstract();
            a.f();
        }

        #endregion

        #region Interfaces
        interface Interface1
        {
            void f();
            int i { get; set; }
        }

        interface Interface2
        {
            void g();
        }

        class InterClass1: Interface1, Interface2
        {
            public int i { get; set; }
            public void f()
            {
                Console.WriteLine("InterClass1.f");
            }
            public void g()
            {
                Console.WriteLine("InterClass1.g");
            }
        }
        class InterClass2 : Interface2
        {
            public void g()
            {
                Console.WriteLine("InterClass2.g");
            }
        }
        static void IntF1(Interface1 i)
        {
            i.f();
        }
        static void IntF2(Interface2 i)
        {
            i.g();
        }
        static void Interfaces()
        {
            Console.WriteLine("Interfaces");
            var o1 = new InterClass1();
            var o2 = new InterClass2();
            IntF1(o1);
            IntF2(o1);
            IntF2(o2);

        }
        #endregion

        #region Delegates

        public delegate void SimpleDelegate();
        partial class Currency
        {
            public SimpleDelegate DoPrint;
            public event SimpleDelegate EventPrint;

            public void SimplePrint()
            {
                Console.WriteLine($"{k}");
            }

            public void InvokePrint()
            {
                EventPrint();
            }

        }

        static string fdin()
        {
            return Console.ReadLine();
        }
        static void fdout(string s)
        {
            Console.WriteLine(s);
        }
        static void Delegates()
        {
        	Console.WriteLine("Delegates");

            var c = new Currency(100);
            c.DoPrint = c.SimplePrint;
            c.DoPrint();
            c.DoPrint += new SimpleDelegate(c.Print);
            c.DoPrint();
            c.DoPrint -= c.SimplePrint;
            c.DoPrint += delegate /* () */ { Console.WriteLine("Anonymous delegate print"); };
            c.DoPrint += () =>  Console.WriteLine("Lambda print");
            
            c.DoPrint();

            foreach (var d in c.DoPrint.GetInvocationList())
            {
                Console.WriteLine(d.Method.ToString());
            }

            c.EventPrint += c.SimplePrint;
            c.EventPrint += c.Print;
            // c.EventPrint();
            c.InvokePrint();

            var fin = new Func<string>(fdin);
            var fout = new Action<string>(fdout);
            fout(fin());

            // public delegate bool Predicate<in T>(T obj);
            // EventHandler<T>, (object, T: EventArgs)
    
        }
        #endregion

        #region Exceptions

        static int fe(int b)
        {
            return 100 / b;
        }
        static void Exceptions()
        {
        	Console.WriteLine("Exceptions");
            try 
            {
                fe(0);
            }
            catch(Exception e)
            {
                Console.WriteLine(e.Message);
            }
            catch
            {
                Console.WriteLine("Any Exception");
            }
            finally
            {
                Console.WriteLine("finally");
            }
        }
        #endregion

        #region IDisposable
        public class DisposableClass : IDisposable
        {
            string s;
            public DisposableClass(string S)
            {
                s = S;
                Console.WriteLine("DisposableClass.DisposableClass(): " + s);
            }


            public void f()
            {
                Console.WriteLine("DisposableClass.f(): " + s);
            }

            bool bDisposed = false;
            void Clean(bool bDisposing)
            {
                if (!bDisposed)
                {
                    if (bDisposing)
                    {
                        Console.WriteLine("DisposableClass.Clean() by Dispose: " + s);
                    }
                    else
                    {
                        Console.WriteLine("DisposableClass.Clean() by GC: " + s);
                    }
                    bDisposed = true;
                }
            }
            ~DisposableClass()
            {
                Console.WriteLine("DisposableClass.~DisposableClass(): " + s);
                Clean(false);
            }
            public void Dispose()
            {
                Console.WriteLine("DisposableClass.Dispose(): " + s);
                Clean(true);
                GC.SuppressFinalize(this);
            }
        }

        static void fd()
        {
            DisposableClass o = new DisposableClass("DC in fd");
            o.f();
        }
        static void IDisposable()
        {
        	Console.WriteLine("IDisposable");
            var o1 = new DisposableClass("DC1");
            using(var o2 = new DisposableClass("DC in using"))
            {
                o2.f();            
            }
            Console.WriteLine("IDisposable done");
        }
        #endregion

        #region Templates

        class Point<T>
        {
            public T x;
            public T y;
            public Point()
            {
            }

            public Point(T X, T Y)
            {
                x = X;
                y = Y;
            }

            public void Reset()
            {
                x = default(T);
                y = default(T);
            }
            public override string ToString()
            {
                return $"[{x},{y}]";
            }
        }

        static void Templates()
        {
        	Console.WriteLine("Templates");
            var p1 = new Point<double>();
            Console.WriteLine(p1);
            var p2 = new Point<int>(5, 6);
            Console.WriteLine(p2);
            p2.Reset();
            Console.WriteLine(p2);
        }
        #endregion

        #region IO
        static void IO()
        {
        	Console.WriteLine("IO");
            using (StreamWriter s = File.CreateText("File.txt"))
            {
                s.WriteLine("12345");
                s.WriteLine("45678");
                s.WriteLine("98765");
                s.WriteLine("00000");
            }
            using (StreamReader st = new StreamReader("File.txt"))
            {
                string str;
                while ((str = st.ReadLine()) != null)
                {
                    Console.WriteLine(str);
                }
            }
            File.WriteAllText("File.txt", @"
                1234567890
                1234567890
                1234567890
            ");
            //File.WriteAllBytes
            //File.WriteAllStrings
            Console.WriteLine(File.ReadAllText("File.txt"));

            FileInfo fi = new FileInfo("File.dat");
            using (BinaryWriter bw = new BinaryWriter(fi.OpenWrite()))
            {
                int i = 10;
                bw.Write(i);
            }
            using (var fs = new FileStream("File.dat", FileMode.Open))
            {
                // fs.Read
                using (BinaryReader br = new BinaryReader(fs))
                {
                    Console.WriteLine("ReadInt32: {0}", br.ReadInt32());
                }
            }
        }
        #endregion

        #region Serialization


        [Serializable]
        [XmlType (TypeName = "MyBase")]
        public class SBase: ISerializable
        {
            [XmlElement(ElementName = "MyXMLI")]
            public int i { get; set; }
            
            [NonSerialized] 
            public int n;
            public SBase()
            {
            }
            public SBase(int I)
            {
                i = I;
            }
            public virtual void f()
            {
                Console.WriteLine($"SBase: i = {i}");
            }
            public SBase(SerializationInfo info, StreamingContext context)
            {
                i = info.GetInt32("MyI");
            }
            public virtual void GetObjectData(SerializationInfo info, StreamingContext context)
            {
                info.AddValue("MyI", i);
            }
        }
        [Serializable]
        [XmlType(TypeName = "MyDerived")]
        public class SDerived : SBase 
        {
            public int j;
            public SDerived()
            {
            }
            public SDerived(int I, int J)
                :base(I)
            {
                j = J;
            }
            public override void f()
            {
                Console.WriteLine($"SDerived: i = {i}, j = {j}");
            }
            public SDerived(SerializationInfo info, StreamingContext context)
                :base(info, context)
            {
                j = info.GetInt32("MyJ");
            }
            public override void GetObjectData(SerializationInfo info, StreamingContext context)
            {
                base.GetObjectData(info, context);
                info.AddValue("MyJ", j);
            }
        }
        static void StoreBinary(List<SBase> l)
        {
            var bf = new BinaryFormatter();
            using (Stream fs = new FileStream("file.dat", FileMode.OpenOrCreate))
            {
                bf.Serialize(fs, l);
            }
        }
        static void StoreSOAP(List<SBase> l)
        {
            var sf = new SoapFormatter();
            using (Stream fs = new FileStream("file.soap.xml", FileMode.OpenOrCreate))
            {
                sf.Serialize(fs, l.Count);
                foreach(var o in l)
                {
                    sf.Serialize(fs, o);
                }
            }
        }
        static void StoreXML(List<SBase> l)
        {
            var xs = new XmlSerializer(typeof(List<SBase>), new[] { typeof(SBase), typeof(SDerived) });
            using (Stream fs = new FileStream("file.xml", FileMode.OpenOrCreate))
            {
                xs.Serialize(fs, l);
            }
        }
        static void StoreJSON(List<SBase> l)
        {
            File.WriteAllText("file.json", JsonSerializer.Serialize(l));
        }
        static List<SBase> LoadBinary()
        {
            var bf = new BinaryFormatter();
            using (Stream fs = new FileStream("file.dat", FileMode.Open))
            {
                return bf.Deserialize(fs) as List<SBase>;
            }
        }
        static List<SBase> LoadSOAP()
        {
            var sf = new SoapFormatter();
            using (Stream fs = new FileStream("file.soap.xml", FileMode.Open))
            {
                List<SBase> l = new List<SBase>();
                int? n = sf.Deserialize(fs) as int?;
                for(int i = 0; i<n; i++)
                {
                    l.Add(sf.Deserialize(fs) as SBase);
                }
                return l;
            }
        }
        static List<SBase> LoadXML()
        {
            var xs = new XmlSerializer(typeof(List<SBase>), new[] { typeof(SBase), typeof(SDerived) });
            using (Stream fs = new FileStream("file.xml", FileMode.Open))
            {
                return xs.Deserialize(fs) as List<SBase>;
            }
        }
        static List<SBase> LoadJSON()
        {
            return JsonSerializer.Deserialize<List<SBase>>(File.ReadAllText("file.json"));
        }
        static void WriteList(List<SBase> l, string s)
        {
            if (l == null)
                return;
            Console.WriteLine(s);
            foreach(var o in l)
            {
                o.f();
            }
        }
        static void Serialization()
        {
        	Console.WriteLine("Serialization");
            List<SBase> l = new List<SBase>();
            for(int i = 0; i<10; i++)
            {
                if (i % 2 == 0)
                    l.Add(new SBase(i));
                else
                    l.Add(new SDerived(i, 100*i));
            }
            WriteList(l, "Initial list");

            StoreBinary(l);
            StoreSOAP(l);
            StoreXML(l);
            StoreJSON(l);

            WriteList(LoadBinary(), "LoadBinary");
            WriteList(LoadSOAP(), "LoadSOAP");
            WriteList(LoadXML(), "LoadXML");
            WriteList(LoadJSON(), "LoadJSON");

        }
        #endregion

        static void Main(string[] args)
        {
            Strings();
            Functions();
            Arrays();
            Structures();
            Classes();
            Operators();
            Properties();
            Inheritance();
            Interfaces();
            Delegates();
            Exceptions();
            IDisposable();
            Templates();
            IO();
            Serialization();
        }
    }
}

