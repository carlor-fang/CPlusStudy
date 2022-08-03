#include "Binder.h"

////@brief:获取工厂类的单个实例对象  
//ClassFactory& ClassFactory::GetInstance() 
//{
//    static ClassFactory Factory;
//    return Factory;
//}
//
////@brief:通过类名称字符串获取类的实例
//void* ClassFactory::GetClassByName(string ClassName) 
//{
//    map<string, PTRCreateObject>::const_iterator Iter = ClassMap.find(ClassName);
//    if (Iter == ClassMap.end())
//        return NULL;
//    else
//        return Iter->second();
//}
//
////@brief:将给定的类名称字符串和对应的创建类对象的函数保存到map中   
//void ClassFactory::RegistClass(string Name, PTRCreateObject Method) 
//{
//    ClassMap.insert(pair<string, PTRCreateObject>(Name, Method));
//}
//
//#define REGISTER(ClassName)                                             \
//    ClassName* ObjectCreator##ClassName(){                              \
//        return new ClassName();                                           \
//    }                                                                   \
//    RegisterAction CreatorRegister##ClassName(                        \
//        #ClassName,(PTRCreateObject)ObjectCreator##ClassName)
//
//
//REGISTER(TestClassA);
