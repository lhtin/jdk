# The Format of Class File

```text
ClassFile {
    u4             magic;
    u2             minor_version;
    u2             major_version;
    u2             constant_pool_count;
    cp_info        constant_pool[constant_pool_count-1];
    u2             access_flags;
    u2             this_class; // constant_pool_index of CONSTANT_Class_info
    u2             super_class; // constant_pool_index of CONSTANT_Class_info
    u2             interfaces_count;
    u2             interfaces[interfaces_count]; // constant_pool_index[] of CONSTANT_Class_info
    u2             fields_count;
    field_info     fields[fields_count];
    u2             methods_count;
    method_info    methods[methods_count];
    u2             attributes_count;
    attribute_info attributes[attributes_count];
}
```

magic = `0xCAFEBABE`

Class access_flags(Table 4.1-B. Class access and property modifiers):
```text
Flag Name       Value   Interpretation
ACC_PUBLIC      0x0001  Declared public; may be accessed from outside its package.
ACC_FINAL       0x0010  Declared final; no subclasses allowed.
ACC_SUPER       0x0020  Treat superclass methods specially when invoked by the invokespecial instruction.
ACC_INTERFACE   0x0200  Is an interface, not a class.
ACC_ABSTRACT    0x0400  Declared abstract; must not be instantiated.
ACC_SYNTHETIC   0x1000  Declared synthetic; not present in the source code.
ACC_ANNOTATION  0x2000  Declared as an annotation type.
ACC_ENUM        0x4000  Declared as an enum type.
ACC_MODULE      0x8000  Is a module, not a class or interface.
```

### constant_pool

```text
cp_info {
    u1 tag;
    u1 info[]; 
}
```

tags(Table 4.4-B. Constant pool tags):
```text
Constant Kind                   Tag     class file format       Java SE
CONSTANT_Utf8                   1       45.3                    1.0.2
CONSTANT_Integer                3       45.3                    1.0.2
CONSTANT_Float                  4       45.3                    1.0.2
CONSTANT_Long                   5       45.3                    1.0.2
CONSTANT_Double                 6       45.3                    1.0.2
CONSTANT_Class                  7       45.3                    1.0.2
CONSTANT_String                 8       45.3                    1.0.2
CONSTANT_Fieldref               9       45.3                    1.0.2
CONSTANT_Methodref              10      45.3                    1.0.2
CONSTANT_InterfaceMethodref     11      45.3                    1.0.2
CONSTANT_NameAndType            12      45.3                    1.0.2
CONSTANT_MethodHandle           15      51.0                    7
CONSTANT_MethodType             16      51.0                    7
CONSTANT_Dynamic                17      55.0                    11
CONSTANT_InvokeDynamic          18      51.0                    7
CONSTANT_Module                 19      53.0                    9
CONSTANT_Package                20      53.0                    9
```

```text
CONSTANT_Class_info {
    u1 tag;
    u2 name_index; // constant_pool_index of CONSTANT_Utf8_info
}

CONSTANT_Fieldref_info {
    u1 tag;
    u2 class_index; // constant_pool_index of CONSTANT_Class_info
    u2 name_and_type_index; // constant_pool_index of CONSTANT_NameAndType_info
}

CONSTANT_Methodref_info {
    u1 tag;
    u2 class_index; // constant_pool_index of CONSTANT_Class_info, must a class, not interface
    u2 name_and_type_index; // constant_pool_index of CONSTANT_NameAndType_info
}

CONSTANT_InterfaceMethodref_info {
    u1 tag;
    u2 class_index; // constant_pool_index of CONSTANT_Class_info, must a interface
    u2 name_and_type_index; // constant_pool_index of CONSTANT_NameAndType_info
}

CONSTANT_NameAndType_info {
    u1 tag;
    u2 name_index; // constant_pool_index of CONSTANT_Utf8_info, a valid unqualified name denoting a field or method, or the special method name <init> (§2.9.1).
    u2 descriptor_index; // constant_pool_index of CONSTANT_Utf8_info, field descriptor or method descriptor
}

CONSTANT_String_info {
    u1 tag;
    u2 string_index; // constant_pool_index of CONSTANT_Utf8_info
}

CONSTANT_Integer_info {
    u1 tag;
    u4 bytes; 
}

CONSTANT_Float_info {
    u1 tag;
    u4 bytes; 
}

CONSTANT_Long_info {
    u1 tag;
    u4 high_bytes;
    u4 low_bytes;
}

CONSTANT_Double_info {
    u1 tag;
    u4 high_bytes;
    u4 low_bytes;
}

CONSTANT_Utf8_info {
    u1 tag;
    u2 length;
    u1 bytes[length];
}

CONSTANT_MethodHandle_info {
    u1 tag;
    u1 reference_kind;
    u2 reference_index; // 1,2,3,4 CONSTANT_Fieldref_info, 6,7 CONSTANT_Methodref_info, 9 CONSTANT_InterfaceMethodref_info
}

CONSTANT_MethodType_info {
    u1 tag;
    u2 descriptor_index;
}

CONSTANT_Dynamic_info {
    u1 tag;
    u2 bootstrap_method_attr_index;
    u2 name_and_type_index;
}

CONSTANT_InvokeDynamic_info {
    u1 tag;
    u2 bootstrap_method_attr_index;
    u2 name_and_type_index;
}

CONSTANT_Module_info {
    u1 tag;
    u2 name_index;
}

CONSTANT_Package_info {
    u1 tag;
    u2 name_index;
}
```


#### field descriptor

```text
FieldDescriptor: FieldType
FieldType: BaseType | ObjectType | ArrayType
BaseType: B | C | D | F | I | J | S | Z
ObjectType: L ClassName ;
ArrayType: [ ComponentType
ComponentType: FieldType
```

Table 4.3-A. Interpretation of field descriptors:
```text
FieldType term      Type            Interpretation
B                   byte            signed byte
C                   char            Unicode character code point in the Basic Multilingual Plane, encoded with UTF-16
D                   double          double-precision floating-point value
F                   float           single-precision floating-point value
I                   int             integer
J                   long            long integer
L ClassName ;       reference       an instance of class ClassName
S                   short           signed short
Z                   boolean         true or false
[                   reference       one array dimension
```

#### method descriptor

```text
MethodDescriptor: ( ParameterDescriptor* ) ReturnDescriptor
ParameterDescriptor: FieldType
ReturnDescriptor: FieldType | VoidDescriptor
VoidDescriptor: V
```

### fields

```text
fields = field_info[]
field_info {
    u2             access_flags;
    u2             name_index;
    u2             descriptor_index;
    u2             attributes_count;
    attribute_info attributes[attributes_count];
}
```

Field access_flags(Table 4.5-A. Field access and property flags):

```text
Flag Name       Value   Interpretation
ACC_PUBLIC      0x0001  Declared public; may be accessed from outside its package.
ACC_PROTECTED   0x0004  Declared protected; may be accessed within subclasses.
ACC_STATIC      0x0008  Declared static.
ACC_FINAL       0x0010  Declared final; never directly assigned to after object construction (JLS §17.5).
ACC_VOLATILE    0x0040  Declared volatile; cannot be cached.
ACC_TRANSIENT   0x0080  Declared transient; not written or read by a persistent object manager.
ACC_SYNTHETIC   0x1000  Declared synthetic; not present in the source code. 
ACC_ENUM        0x4000  Declared as an element of an enum.
```

#### methods

```text
methods = method_info[]
method_info {
    u2             access_flags;
    u2             name_index;
    u2             descriptor_index;
    u2             attributes_count;
    attribute_info attributes[attributes_count];
}
```

Method access_flags(Table 4.6-A. Method access and property flags):
```text
Flag Name           Value   Interpretation
ACC_PUBLIC          0x0001  Declared public; may be accessed from outside its package.
ACC_PROTECTED       0x0004  Declared protected; may be accessed within subclasses.
ACC_STATIC          0x0008  Declared static.
ACC_FINAL           0x0010  Declared final; must not be overridden (§5.4.5).
ACC_SYNCHRONIZED    0x0020  Declared synchronized; invocation is wrapped by a monitor use.
ACC_BRIDGE          0x0040  A bridge method, generated by the compiler.
ACC_VARARGS         0x0080  Declared with variable number of arguments.
ACC_NATIVE          0x0100  Declared native; implemented in a language other than the Java programming language.
ACC_ABSTRACT        0x0400  Declared abstract; no implementation is provided.
ACC_STRICT          0x0800  Declared strictfp; floating-point mode is FP- strict.
ACC_SYNTHETIC       0x1000  Declared synthetic; not present in the source code.
```
