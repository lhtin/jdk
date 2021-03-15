/// 加载class并创建InstanceKlass实例
#include "../src/hotspot/share/classfile/classLoader.hpp"
// 入口1
InstanceKlass* ClassLoader::load_class(Symbol* name, bool search_append_only, TRAPS);
#include "../src/hotspot/share/classfile/systemDictionary.hpp"
// 入口2
InstanceKlass* SystemDictionary::resolve_from_stream(Symbol* class_name,
                                                     Handle class_loader,
                                                     Handle protection_domain,
                                                     ClassFileStream* st,
                                                     TRAPS);
  #include "../src/hotspot/share/classfile/klassFactory.hpp"
  InstanceKlass* KlassFactory::create_from_stream(ClassFileStream* stream,
                                                  Symbol* name,
                                                  ClassLoaderData* loader_data,
                                                  const ClassLoadInfo& cl_info,
                                                  TRAPS);
    #include "../src/hotspot/share/classfile/classFileParser.hpp"
    // 解析class文件，包括虚函数表、接口函数表
    ClassFileParser::ClassFileParser(ClassFileStream* stream,
                                     Symbol* name,
                                     ClassLoaderData* loader_data,
                                     const ClassLoadInfo* cl_info,
                                     Publicity pub_level,
                                     TRAPS);
      // parsing class file
      void ClassFileParser::parse_stream(const ClassFileStream* const stream, TRAPS);
        // 解析constant_pool，生成ConstantPool对象，将Class转化为指向Klass*的index，将UTF8转化为Symbol
        void ClassFileParser::parse_constant_pool(const ClassFileStream* const stream,
                                                  ConstantPool* const cp,
                                                  const int length,
                                                  TRAPS);
          // 将class文件中的constant_pool存储到ConstantPool对象的屁股后面，同时将UTF8转化为Symbol对象
          void ClassFileParser::parse_constant_pool_entries(const ClassFileStream* const stream,
                                                            ConstantPool* cp,
                                                            const int length,
                                                            TRAPS);
        const InstanceKlass* ClassFileParser::parse_super_class(ConstantPool* const cp,
                                                                const int super_class_index,
                                                                const bool need_verify,
                                                                TRAPS);
        void ClassFileParser::parse_interfaces(const ClassFileStream* const stream,
                                               const int itfs_len,
                                               ConstantPool* const cp,
                                               bool* const has_nonstatic_concrete_methods,
                                               TRAPS);
        void ClassFileParser::parse_fields(const ClassFileStream* const cfs,
                                           bool is_interface,
                                           FieldAllocationCount* const fac,
                                           ConstantPool* cp,
                                           const int cp_size,
                                           u2* const java_fields_count_ptr,
                                           TRAPS);
        void ClassFileParser::parse_methods(const ClassFileStream* const cfs,
                                            bool is_interface,
                                            AccessFlags* promoted_flags,
                                            bool* has_final_method,
                                            bool* declares_nonstatic_concrete_methods,
                                            TRAPS);
        void ClassFileParser::parse_classfile_attributes(const ClassFileStream* const cfs,
                                                         ConstantPool* cp,
                                                         ClassFileParser::ClassAnnotationCollector* parsed_annotations,
                                                         TRAPS);
      // after class file parsed
      // 接口函数列表创建
      void ClassFileParser::post_process_parsed_stream(const ClassFileStream* const stream,
                                                       ConstantPool* cp,
                                                       TRAPS);
        // 递归计算出类实现的所有接口（包括父类实现的接口和接口继承的接口）
        static Array<InstanceKlass*>* compute_transitive_interfaces(const InstanceKlass* super,
                                                                    Array<InstanceKlass*>* local_ifs,
                                                                    ClassLoaderData* loader_data,
                                                                    TRAPS);

        #include "../src/hotspot/share/oops/klassVtable.hpp"
        // 计算itable的大小，用于存储接口表和接口方法表
        int klassItable::compute_itable_size(Array<InstanceKlass*>* transitive_interfaces);
        #include "../src/hotspot/share/classfile/fieldLayoutBuilder.hpp"
        // 计算实例字段和静态字段在oop中的偏移
        FieldLayoutBuilder::FieldLayoutBuilder(const Symbol* classname, const InstanceKlass* super_klass, ConstantPool* constant_pool,
                                               Array<u2>* fields, bool is_contended, FieldLayoutInfo* info);
        void FieldLayoutBuilder::build_layout();
    // 创建Klass实例
    InstanceKlass* ClassFileParser::create_instance_klass(bool changed_by_loadhook,
                                                          const ClassInstanceInfo& cl_inst_info,
                                                          TRAPS);

      #include "../src/hotspot/share/oops/instanceKlass.hpp"
      InstanceKlass* InstanceKlass::allocate_instance_klass(const ClassFileParser& parser, TRAPS);
      void ClassFileParser::fill_instance_klass(InstanceKlass* ik,
                                                bool changed_by_loadhook,
                                                const ClassInstanceInfo& cl_inst_info,
                                                TRAPS);
        // 初始化itable接口表部分并预留存储接口方法的内存出来（接口方法表会在链接环节初始化）
        void klassItable::setup_itable_offset_table(InstanceKlass* klass);
        #include "../src/hotspot/share/classfile/javaClasses.hpp"
        // 创建类对应的oop对象（存储类的静态字段）
        void java_lang_Class::create_mirror(Klass* k, Handle class_loader,
                                            Handle module, Handle protection_domain,
                                            Handle classData, TRAPS);
        #include "../src/hotspot/share/classfile/defaultMethods.hpp"
        // 收集类所实现的接口的默认方法
        // 奇怪里面还会去初始化ConstantPool中的klasses（PS：这是因为有一部分方法（比如接口的默认实现）在这时候才去解析，解析过程中有可能有新的引用需要添加进去，因此也需要重新创建ConstantPool）
        void DefaultMethods::generate_default_methods(InstanceKlass* klass, const GrowableArray<Method*>* mirandas, TRAPS);
          static void create_defaults_and_exceptions(GrowableArray<EmptyVtableSlot*>* slots,
                                                     InstanceKlass* klass, TRAPS);
            #include "../src/hotspot/share/oops/constantPool.hpp"
            // 给没有resolved的klass确定index，供后面确定的时候使用，奇怪的是他在DefaultMethods::generate_default_methods方法中被调用的，
            // 但是只有在接口有默认方法实现时才会调用，这就很奇怪了，还需要在check一下
            void ConstantPool::initialize_unresolved_klasses(ClassLoaderData* loader_data, TRAPS);
        
// 链接class
#include "../src/hotspot/share/oops/instanceKlass.hpp"
void InstanceKlass::link_class(TRAPS);
  bool InstanceKlass::link_class_impl(TRAPS);
    // 修改字节码和创建ConstantPoolCache
    void InstanceKlass::rewrite_class(TRAPS);
      #include "../src/hotspot/share/interpreter/rewriter.hpp"
      void Rewriter::rewrite_bytecodes(TRAPS);
      void Rewriter::make_constant_pool_cache(TRAPS);
    // 方法链接
    void InstanceKlass::link_methods(TRAPS);
    #include "../src/hotspot/share/oops/klassVtable.hpp"
    // 虚函数表创建，跟methods关联
    void klassVtable::initialize_vtable(bool checkconstraints, TRAPS);
      // 复制父类的vtable到子类，index保持不变
      int klassVtable::initialize_from_super(Klass* super);
    // 接口函数表创建，将接口方法与实现类的方法（methods、default_methods）关联起来
    void klassItable::initialize_itable(bool checkconstraints, TRAPS);
    
// 类初始化
#include "../src/hotspot/share/oops/instanceKlass.hpp"
void InstanceKlass::initialize(TRAPS);
  void InstanceKlass::initialize_impl(TRAPS);

// ConstantPoolCache初始化
/*
  _putXXX
  _getXXX
  _invokeXXX
*/