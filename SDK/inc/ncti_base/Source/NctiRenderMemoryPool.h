#pragma once

#include "ncti_base.h"

#define NCTI_MEMORY_POOL_BIT 10
#define NCTI_MEMORY_MEMO_BIT (64 - NCTI_MEMORY_POOL_BIT - 1)


namespace NCTI
{
    /**
     * @brief NctiMemoryBase
     */
    class DECL_NCTI_BASE _NctiMemoryBase {
    public:
        _NctiMemoryBase();
        virtual ~_NctiMemoryBase();

        static void* operator new(std::size_t size);
        static void operator delete(void* ptr) noexcept;
        struct
        {
            Ncti_Size isUsed : 1;
            Ncti_Size poolID : NCTI_MEMORY_POOL_BIT;
            Ncti_Size memID : NCTI_MEMORY_MEMO_BIT;
        }m_flag;
    };

    class DECL_NCTI_BASE NctiRenderMemoryPool
    {
    public:
        static NctiRenderMemoryPool* instance();
        ~NctiRenderMemoryPool();

        _NctiMemoryBase* GenMemory(int pool);
        bool ResMemory(_NctiMemoryBase* i_ptr);
        void FreeMemory();
        void LogMemory();

    private:
        NctiRenderMemoryPool();
        class PrivateData;
        PrivateData* _d;
    };


#ifdef NCTI_MEMORY_POOL
#define NctiMemoryBase _NctiMemoryBase
#else
#define NctiMemoryBase NctiDummyBaseClass
#endif

    class DECL_NCTI_BASE NctiChar64Memory :public NctiMemoryBase {
    public:
        NctiChar64Memory();
        ~NctiChar64Memory();

        const Ncti_Char* GetString()const;
        Ncti_Char* GetString();

        void set_char_by_name_id(const Ncti_Char* i_name, const Ncti_Char* i_mid, Ncti_Integer i_id, const Ncti_Char* i_include = nullptr);
        bool SetString(const Ncti_Char* i_str);

    private:
        char m_data[64];
    };

    class DECL_NCTI_BASE NctiChar64Garud {

    public:
        NctiChar64Garud();
        ~NctiChar64Garud();

        const char* GetString()const;
        void SetString(const Ncti_Char* i_name, const Ncti_Char* i_mid, Ncti_Integer i_id, const Ncti_Char* i_include = nullptr);

    private:
        NctiChar64Memory* d;
    };


}

#define NCTI_DELETE_NEW_OBJECT(obj,type,...) \
    {NCTI_DELETE_OBJECT(obj);\
    obj = NCTI_NEW type(__VA_ARGS__);}
