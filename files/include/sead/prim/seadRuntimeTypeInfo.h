#ifndef SEAD_RUNTIMETYPEINFO_H_
#define SEAD_RUNTIMETYPEINFO_H_

namespace sead { namespace RuntimeTypeInfo {

struct Interface
{
    Interface() { }

    virtual bool isDerived(const Interface* typeInfo) const = 0;
};

struct Root : public Interface
{
    Root() { }

    virtual bool isDerived(const Interface* typeInfo) const
    {
        return typeInfo == this;
    }
};

template <typename BaseType>
struct Derive : public Interface
{
    Derive() { }

    virtual bool isDerived(const Interface* typeInfo) const
    {
        if (this == typeInfo)
            return true;

        const RuntimeTypeInfo::Interface* rootTypeInfo = BaseType::getRuntimeTypeInfoStatic();
        return rootTypeInfo->isDerived(typeInfo);
    }
};

} // namespace sead::RuntimeTypeInfo

template <typename DerivedType, typename Type>
inline bool
IsDerivedFrom(const Type* obj)
{
    const RuntimeTypeInfo::Interface* typeInfo = DerivedType::getRuntimeTypeInfoStatic();
    return obj != NULL && obj->checkDerivedRuntimeTypeInfo(typeInfo);
}

template<typename DerivedType, typename Type>
inline DerivedType*
DynamicCast(Type* obj)
{
    if (IsDerivedFrom<DerivedType, Type>(obj))
        return static_cast<DerivedType*>(obj);

    return NULL;
}

} // namespace sead

#define SEAD_RTTI_BASE(CLASS)                                                                                \
    public:                                                                                                  \
        static const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfoStatic()                            \
        {                                                                                                    \
            static const sead::RuntimeTypeInfo::Root typeInfo;                                               \
            return &typeInfo;                                                                                \
        }                                                                                                    \
                                                                                                             \
        virtual bool checkDerivedRuntimeTypeInfo(const sead::RuntimeTypeInfo::Interface* typeInfo) const     \
        {                                                                                                    \
            const sead::RuntimeTypeInfo::Interface* clsTypeInfo = CLASS::getRuntimeTypeInfoStatic();         \
            return typeInfo == clsTypeInfo;                                                                  \
        }                                                                                                    \
                                                                                                             \
        virtual const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfo() const                           \
        {                                                                                                    \
            return getRuntimeTypeInfoStatic();                                                               \
        }

#define SEAD_RTTI_OVERRIDE(CLASS, BASE)                                                                      \
    public:                                                                                                  \
        static const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfoStatic()                            \
        {                                                                                                    \
            static const sead::RuntimeTypeInfo::Derive<BASE> typeInfo;                                       \
            return &typeInfo;                                                                                \
        }                                                                                                    \
                                                                                                             \
        virtual bool checkDerivedRuntimeTypeInfo(const sead::RuntimeTypeInfo::Interface* typeInfo) const     \
        {                                                                                                    \
            const sead::RuntimeTypeInfo::Interface* clsTypeInfo = CLASS::getRuntimeTypeInfoStatic();         \
            if (typeInfo == clsTypeInfo)                                                                     \
                return true;                                                                                 \
                                                                                                             \
            return BASE::checkDerivedRuntimeTypeInfo(typeInfo);                                              \
        }                                                                                                    \
                                                                                                             \
        virtual const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfo() const                           \
        {                                                                                                    \
            return getRuntimeTypeInfoStatic();                                                               \
        }

#endif // SEAD_RUNTIMETYPEINFO_H_
