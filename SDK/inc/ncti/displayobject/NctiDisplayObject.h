#ifndef NctiDisplayObject_H
#define NctiDisplayObject_H
#include "ncti.h"
#include "NctiPosition.h"
#include "NctiBulletinBoard.h"
#include "NctiTransf.h"
#include "NctiMutex.h"
#include <map>
#include <vector>
#include "NctiRenderMemoryPool.h"

//define the display object base head function.
#define NCTI_TTPEOBJECT_FUNCTIONS() \
public:\
    static const char* ID;\
    static const char* OBJECT_NAME;\
    const char* TypeName()const override;\
    Ncti_Boolean IsTypeName(const char* i_cTypeName)const override;\
    const char* GetDefaultObjName()override


//define the display object base head function.
#define NCTI_DISPLAYOBJECT_FUNCTIONS(DISPLAY_OBJECT_CLASS_NAME) \
    NCTI_TTPEOBJECT_FUNCTIONS();\
public:\
    DISPLAY_OBJECT_CLASS_NAME();\
    friend NctiDisplayObject* Generate_##DISPLAY_OBJECT_CLASS_NAME();\
    EnumNctiResult save_data( NctiFileInterface* i_pFileInterface )override;\
	EnumNctiResult restore_data( NctiFileInterface* i_pFileInterface )override;\
	EnumNctiResult fix_pointer( NctiFileInterface* i_pFileInterface )override;\
	NctiDisplayObject* make_copy( NctiDisplayObject* i_pDoCopyFrom )override;\
	void copy_data( NctiDisplayObject* i_pDoCopyFrom )override;\
	void swap_data( NctiDisplayObject* i_pDoSwap )override;\
private:\
    static Ncti_Integer m_CurrentVersion;\
public:
//define the display object base cpp function.
#define NCTI_DISPLAYOBJECT_DEF( DISPLAY_OBJECT_CLASS_NAME, DISPLAY_OBJECT_DERIVED_FROM, IDENTITY_STRING, OBJ_NAME_STRING ) \
	const char* DISPLAY_OBJECT_CLASS_NAME::ID = IDENTITY_STRING;\
	const char* DISPLAY_OBJECT_CLASS_NAME::OBJECT_NAME = OBJ_NAME_STRING;\
	const char* DISPLAY_OBJECT_CLASS_NAME::TypeName()const { return DISPLAY_OBJECT_CLASS_NAME::ID; }\
	Ncti_Boolean DISPLAY_OBJECT_CLASS_NAME::IsTypeName ( const char *sTypeName )const\
	{\
		if ( (DISPLAY_OBJECT_CLASS_NAME::ID)[2] != sTypeName[2] )\
		{\
			return false;\
		}\
		if ( strcmp( DISPLAY_OBJECT_CLASS_NAME::ID, sTypeName ) == 0 )\
		{\
			return true;\
		}\
		return DISPLAY_OBJECT_DERIVED_FROM::IsTypeName( sTypeName );\
	}\
	const char* DISPLAY_OBJECT_CLASS_NAME::GetDefaultObjName(){ return DISPLAY_OBJECT_CLASS_NAME::OBJECT_NAME;}
//registration the class.
#define NCTI_DISPLAYOBJECT_REGISTRATION( DISPLAY_OBJECT_CLASS_NAME ) \
namespace NCTI \
{\
	NctiDisplayObject* Generate_##DISPLAY_OBJECT_CLASS_NAME()\
	{\
		NctiDisplayObject* pDo = NCTI_NEW DISPLAY_OBJECT_CLASS_NAME();\
		return pDo;\
	}\
	static NctiObjectGenerator Register_##DISPLAY_OBJECT_CLASS_NAME(\
								(const char*)DISPLAY_OBJECT_CLASS_NAME::ID,\
								(NctiDisplayObject* (*)(NctiDisplayObjectLifeCycleManager*))Generate_##DISPLAY_OBJECT_CLASS_NAME );\
}

#define NCTI_DOC_FILE_SUPPORT \
public:\
	virtual Ncti_Boolean GetFileExtension( const char*& i_cpFileExtension );\
	virtual Ncti_Boolean GetFileDescription( const char*& i_cpFileDescription);\
	static const char* FILE_EXTENSION;\
	static const char* FILE_DESCRIPTION;\
	virtual Ncti_Boolean IsDocFileSupported(){return true;};\
private:

#define NCTI_API_BEGIN(pHistoryManager) \
	NctiBulletinBoard* pBB = nullptr;\
	Ncti_Boolean bNewBB = false;\
	if ( pHistoryManager != nullptr )\
	{\
		if ( pHistoryManager->GetActive() )\
		{\
			NctiBulletinBoard* pCurBB = pHistoryManager->GetCurrentBulletinBoard(); \
			if ( ( pCurBB == nullptr ) ||\
				( !pCurBB->IsOpen() ) ||\
				( pCurBB->IsOpen() && pCurBB->GetBulletinBoardType() != NctiBulletinBoard::NCTI_BB_RECORD ) )\
			{\
				if ( ( pBB = pHistoryManager->CreateBulletinBoard( NctiBulletinBoard::NCTI_BB_RECORD )) != NULL )\
				{\
					pBB->Open();\
					bNewBB = true;\
				}\
			}\
		}

#define NCTI_API_END \
	}\
	if ( bNewBB )\
	{\
		pBB->Close();\
		if ( pBB->GetFirstBulletin() == nullptr )\
		{\
			/* Delete NctiBulletinBoard in future */ \
		}\
	}
#pragma region Object Swap Copy
#define NCTI_COPY_DATA_CHAR( CHAR_NAME ) \
if (CHAR_NAME != nullptr)\
{\
	NCTI_DELETE[] CHAR_NAME;\
	CHAR_NAME = nullptr;\
}\
if (pCopyData->CHAR_NAME != nullptr)\
{\
	Ncti_Integer iLen = (Ncti_Integer)strlen(pCopyData->CHAR_NAME);\
	CHAR_NAME = NCTI_NEW char[iLen + 1];\
	strcpy(CHAR_NAME, pCopyData->CHAR_NAME);\
}
#define NCTI_COPY_DATA(OBJECT_NAME)\
    OBJECT_NAME = pCopyData->OBJECT_NAME;
#define NCTI_SWAP_DATA(OBJECT_NAME)\
    std::swap(OBJECT_NAME, pSwapData->OBJECT_NAME);
#define NCTI_COPY_DATA_MODIFY(OBJECT_NAME)\
    NCTI_COPY_DATA(OBJECT_NAME)\
    NCTI_COPY_DATA(m_Change_##OBJECT_NAME);
#define NCTI_SWAP_DATA_MODIFY(OBJECT_NAME)\
    NCTI_SWAP_DATA(OBJECT_NAME);\
    NCTI_SWAP_DATA(m_Change_##OBJECT_NAME);
#define NCTI_COPY_DATA_CHAR_VEC(CHAR_NAME_VEC) \
for (Ncti_Integer i = 0; i < CHAR_NAME_VEC.size(); i++)\
{\
	NCTI_DELETE_CHAR(CHAR_NAME_VEC[i]);\
}\
CHAR_NAME_VEC.clear();\
for (Ncti_Integer i = 0; i < pCopyData->CHAR_NAME_VEC.size(); i++)\
{\
	char* ch = NCTI_NEW char[strlen(pCopyData->CHAR_NAME_VEC[i]) + 1];\
	strcpy(ch, pCopyData->CHAR_NAME_VEC[i]);\
	CHAR_NAME_VEC.push_back(ch);\
}
#pragma endregion

#define NCTI_DISPLAY_OBJECT_ATT(OBJECT_TYPE, OBJECT_NAME)\
   OBJECT_TYPE OBJECT_NAME;\
   Ncti_Integer m_Change_##OBJECT_NAME = 0;
#define NCTI_OBJECT_SET_ATT(OBJECT_NAME, OBJECT_VALUE)\
   OBJECT_NAME = OBJECT_VALUE;\
   if( m_Change_##OBJECT_NAME < 10000000)\
   {\
	   m_Change_##OBJECT_NAME+=1;\
   }else\
   {\
      m_Change_##OBJECT_NAME = 0;\
   }


#define NCTI_DISPLAYOBJECT_REQUIRE_VIEW_UNIT_LENGTH \
public:\
	virtual Ncti_Boolean IsViewUnitLengthDependency(){ return true; };
#define NCTI_DISPLAYOBJECT_REQUIRE_INSTANCE_REDRAW \
public:\
	virtual Ncti_Boolean IsInstanceRedrawDependency(){ return true; };
#define NCTI_DISPLAYOBJECT_REQUIRE_CAMERA \
public:\
	virtual Ncti_Boolean IsCameraDependency(){ return true; };
#define NCTI_DISPLAYOBJECT_INSTANCE \
public:\
    virtual Ncti_Boolean IsInstanceObject(){ return true; };

#pragma region Object Version Read Write
#define NCTI_VERSION(OBJECT_VERSION, OBJECT_TYPE, OBJECT_NAME, OBJECT_TYPE_VALUE)\
    OBJECT_TYPE OBJECT_NAME;\
    Ncti_Integer m_FileVersion_##OBJECT_NAME = OBJECT_TYPE_VALUE;
#define NCTI_VERSION_OBJECT(OBJECT_VERSION, OBJECT_TYPE, OBJECT_NAME, OBJECT_TYPE_VALUE)\
    NCTI_VERSION(OBJECT_VERSION, OBJECT_TYPE, OBJECT_NAME, OBJECT_TYPE_VALUE)\
    Ncti_Size m_Index_##OBJECT_NAME = SIZE_MAX;
#define NCTI_VERSION_MODIFY(OBJECT_VERSION, OBJECT_TYPE, OBJECT_NAME, OBJECT_TYPE_VALUE)\
    NCTI_VERSION(OBJECT_VERSION, OBJECT_TYPE, OBJECT_NAME, OBJECT_TYPE_VALUE)\
    Ncti_Integer m_Change_##OBJECT_NAME = 0;
#define NCTI_VERSION_OBJECT_INDEX(OBJECT_NAME)\
    m_Index_##OBJECT_NAME
#define NCTI_READ_VERSION(NCTI_FILE, OBJECT_FUNCTION, OBJECT_NAME)\
    OBJECT_NAME = NCTI_FILE->OBJECT_FUNCTION();
#define NCTI_READ_VERSION_OBJECT(NCTI_FILE, OBJECT_FUNCTION, OBJECT_NAME)\
    m_Index_##OBJECT_NAME = NCTI_FILE->OBJECT_FUNCTION();

#define NCTI_WRITE_VERSION(NCTI_FILE, OBJECT_FUNCTION, OBJECT_NAME)\
   NCTI_FILE->OBJECT_FUNCTION(OBJECT_NAME);
#define NCTI_WRITE_VERSION_OBJECT(NCTI_FILE, OBJECT_FUNCTION, OBJECT_NAME)\
   if (OBJECT_NAME)\
   {\
	   m_Index_##OBJECT_NAME = OBJECT_NAME->GetObjectId(); \
   }\
   else\
   {\
	   m_Index_##OBJECT_NAME = SIZE_MAX;\
   }\
   NCTI_FILE->OBJECT_FUNCTION(m_Index_##OBJECT_NAME);

#define NCTI_WRITE_DATA_CHECK_VERSION_BEGIN(OBJECT_TYPE)\
NctiDocViewManager* pDocViewMan = NctiDocViewManager::GetDocViewManager(m_pLCM);\
if (pDocViewMan)\
{\
	NctiFileVersionDocElement* pNCTIFileVersionDocElement = pDocViewMan->GetFileVersionDocElement();\
	if (pNCTIFileVersionDocElement)\
	{\
		if (pNCTIFileVersionDocElement->IsHasFileReadInfo(OBJECT_TYPE::ID) == false)\
		{\
			NctiFileReadInfo* pFileReadInfo = new NctiFileReadInfo();\
			NctiFileReadInfoVecTree* pNCTIFileReadInfoVecTree = nullptr;\
			NCTI_DELETE_CHAR(pFileReadInfo->m_ObjectType);\
			NCTI_COPY_CHAR(pFileReadInfo->m_ObjectType, OBJECT_TYPE::ID);\
            std::vector<Ncti_Integer> FIVec; 
#define NCTI_WRITE_DATA_CHECK_VERSION_END()\
			pNCTIFileVersionDocElement->AddFileReadInfo(pFileReadInfo);\
		}\
	}\
}

#define NCTI_READ_DATA_CHECK_VERSION(NCTI_FILE, OBJECT_VERSION, SOFT_VERSION, OBJECT_NAME) \
    if (OBJECT_VERSION > SOFT_VERSION)\
    {\
       NctiDocViewManager* pDocViewMan = NctiDocViewManager::GetDocViewManager(m_pLCM);\
       if (pDocViewMan)\
       {\
	       Ncti_Integer numHelp = SOFT_VERSION + 1;\
	       NctiFileVersionDocElement* pFileVersionDocElement = pDocViewMan->GetFileVersionDocElement();\
	       if (pFileVersionDocElement)\
	       {\
		       while (numHelp <= OBJECT_VERSION)\
		       {\
			       pFileVersionDocElement->ReadDataByRecordVersion(OBJECT_NAME, numHelp, NCTI_FILE);\
			       numHelp++;\
		       }\
	       }\
       }\
    }

#define NCTI_WRITE_DATA_CHECK_VERSION(OBJECT_NAME)\
    FIVec.push_back(m_FileVersion_##OBJECT_NAME);
#define NCTI_WRITE_DATA_CHECK_VERSION_VER(OBJECT_NAME)\
    FIVec.push_back(sd_read_long_vector);\
    {\
       pNCTIFileReadInfoVecTree = new NctiFileReadInfoVecTree(sd_read_long_vector);\
       pNCTIFileReadInfoVecTree->m_FIVersionVec.push_back(m_FileVersion_##OBJECT_NAME);\
       pFileReadInfo->m_FIHelpVec.push_back(pNCTIFileReadInfoVecTree);\
    }
#define NCTI_WRITE_DATA_CHECK_SUB_VERSION_BEGIN(SGM_VERSION)\
    pFileReadInfo->m_VersionVec.push_back(SGM_VERSION);
#define NCTI_WRITE_DATA_CHECK_SUB_VERSION_END()\
   pFileReadInfo->m_FIVecVec.push_back(FIVec);\
   FIVec.clear();
#define NCTI_READ_AND_WRITE_VERSION_FUN(FUN_VERSION)\
   void ReadVersion_##FUN_VERSION(NctiFileInterface*);\
   void WriteVersion_##FUN_VERSION(NctiFileInterface*& );
#pragma endregion

#define NCTI_OBJECT_SET_DATA(INPUT_DATA, OBJECT_NAME) \
{ \
back_up(); \
OBJECT_NAME = INPUT_DATA; \
}

#define NCTI_OSNAP_MID        1<<1
#define NCTI_OSNAP_NODE       1<<2
#define NCTI_OSNAP_VERTEXS    1<<3
#define NCTI_OSNAP_CLOSER     1<<4
#define NCTI_OSNAP_INTERSECT  1<<8
#define NCTI_OSNAP_POINT_DIM  1<<9

#define NCTI_PRODUCT_ERROR(FUN, Error)\
    if (NctiRenderManager::IsOpenDebugInfo())\
	{\
		char chNew[1024];\
		NctiString::LocaleSprintf(chNew,\
			"1000: %s is error, %s ! In %s at line %d",\
            FUN,\
            Error,\
            __FILE__,\
            __LINE__);\
		NctiRenderManager::write_product_debug(chNew);\
	}
   
#define NCTI_PRODUCT_WARN(FUN, Warn)\
    if (NctiRenderManager::IsOpenDebugInfo())\
	{\
		char chNew[1024];\
		NctiString::LocaleSprintf(chNew,\
			"1001: %s is warn, %^s! In %s at line %d",\
            FUN,\
			Warn,\
            __FILE__,\
            __LINE__);\
		NctiRenderManager::write_product_debug(chNew);\
	}
#define NCTI_PRODUCT_INFO(Infor)\
    if (NctiRenderManager::IsOpenDebugInfo())\
	{\
		char chNew[1024];\
		NctiString::LocaleSprintf(chNew,\
			"%s! In %s at line %d",\
			Infor,\
            __FILE__,\
            __LINE__);\
		NctiRenderManager::write_product_debug(chNew);\
	}

namespace NCTI
{
	enum NctiVersionValue
	{
		sd_read_bool = 0,
		sd_read_enum,
		sd_read_short,
		sd_read_long,
		sd_read_float,
		sd_read_double,
		sd_read_string,
		sd_read_position,
		sd_read_vector,
		sd_read_matrix,
		sd_read_transf,
		sd_read_long_vector,
		sd_read_bool_y,
		sd_read_bool_n,
		sd_read_size,
		sd_read_packed
	};

	class NctiData_NctiHoopsKey;
	class NctiFileInterface;
	class NctiDisplayObjectLifeCycleManager;
	class NctiBaseView;
    class NctiRenderGeometryItem;
    class NctiRenderSegmentItem;
	class NctiDisplayDocCustomContainer;
	class NctiDisplayObjectList;
     /**
	* @brief Base Class of all display object
	* @details need to implement override TypeName,IsTypeName,save_data,restore_data,fix_pointer,make_copy,copy_data,swap_data
	* @see NctiDummyBaseClass
	*/
	class DECL_NCTI NctiDisplayObject : public NctiMemoryBase
	{
	public:
		NctiDisplayObject();
		virtual ~NctiDisplayObject();
		static const char* ID;
	public:
		enum DataChangedType
		{
			DisplayInstance = 0x0000,
			FatherLayer = 0x0001,
			ReleaseObject = 0x0002,
			ObjectName = 0x0004,
			Color = 0x0008,
		};
	public:
		/**
	   * @brief Initialization during obj class creation
	   */
		virtual void Init();
		/**
	   * @brief check if the display type is correct
	   * @param[in] i_sTypeName, the type of display object
	   * @return Ncti_Boolean
	   */
		virtual Ncti_Boolean IsTypeName(const char* i_sTypeName)const;
		/**
	   * @brief get the type name
	   * @details need to implement, override
	   * @return const char*
	   */
		virtual const char* TypeName() const = 0;
		/**
	   * @brief internal used
	   * @return const char*
	   */
		virtual const char* GetDefaultObjName() { return nullptr; };
		/**
	   * @brief call back to do something
	   * @details need to implement, override
	   * @return EnumNctiDoCallbackStatus
	   */
		virtual EnumNctiDoCallbackStatus Callback(NctiBaseView* i_pBaseView, EnumNctiDoCallbackType i_eType, NctiDisplayObject* i_pDoCaller);
		/**
	   * @brief get the Original display object
	   * @details if it is a instance object, original is really object
	   * @return NctiDisplayObject
	   */
		virtual NctiDisplayObject* GetDoOriginal();
		/**
	   * @brief internal used
	   * @return Ncti_Boolean
	   */
		virtual Ncti_Boolean IsCameraDependency();
		/**
	   * @brief internal used
	   * @return Ncti_Boolean
	   */
		virtual Ncti_Boolean IsViewUnitLengthDependency();
		/**
	   * @brief internal used
	   * @return Ncti_Boolean
	   */
		virtual Ncti_Boolean IsInstanceRedrawDependency();
		/**
	   * @brief internal used
	   * @return Ncti_Boolean
	   */
		virtual Ncti_Boolean IsInstanceObject() { return false; }
		/**
	   * @brief internal used
	   * @return Ncti_Boolean
	   */
		virtual Ncti_Boolean IsNoShowTree();
		/**
	   * @brief get the transform
	   * @details the transform come from render item
	   * @return NctiTransf
	   * @see NctiTransf
	   */
		virtual NctiTransf GetTransform();
		/**
	   * @brief set the transform
	   * @details the transform come from render item
	   * @param[in] i_cTransData, the transform come from NctiRenderDrawingKit
	   * @see NctiTransf,NctiRenderDrawingKit,NctiRenderSegmentItem
	   */
		virtual void ApplyTransform(const NctiTransf& i_cTransData);

		/**
	   * @brief internal used
	   * @return EnumNctiResult
	   */
		virtual EnumNctiResult GetOsnapPoints(EnumSnapType OsnapMode, const NctiPosition& pickPoint,
			std::vector<NctiPosition>& snapPoints);
		/**
	   * @brief internal used,Set the document save state.
	   */
		void SetIsSaveOk(Ncti_Boolean boo) { m_IsSaveOk = boo; }
		/**
	   * @brief internal used
	   */
		void lose();
		/**
	   * @brief internal used
	   */
		void CreateInitSegmentKey();
		/**
	   * @brief internal used
	   */
		void NotifyDataChanged(NctiDisplayObject* i_pNotifyDataChanged, Ncti_Integer i_type, const char* i_id);
	protected:
		/**
	   * @brief internal used
	   */
		virtual void OnNotifyDataChanged(NctiDisplayObject* i_pNotifyDataChanged, Ncti_Integer i_type, const char* i_id);
		/**
	   * @brief internal used
	   * @return EnumNctiResult
	   */
		virtual EnumNctiResult OnGetOsnapPoints(EnumSnapType OsnapMode, const NctiPosition& pickPoint,
			std::vector<NctiPosition>& snapPoints);
	public:
		/**
	   * @brief get object lifecycle manager
	   * @details all display object is in NctiDisplayObjectLifeCycleManager
	   * @return NctiDisplayObjectLifeCycleManager
	   */
		NctiDisplayObjectLifeCycleManager* GetLCM() { return m_pLCM; }
		/**
	   * @brief get segment item from display object
	   * @details segment item include model key 
	   * @return NctiRenderSegmentItem
	   */
        NCTI::NctiRenderSegmentItem* GetSegKey();
		/**
	   * @brief get display object name
	   * @details the name is only one
	   * @return const char*
	   */
		const char* GetObjName() const;
		/**
	   * @brief internal used
	   */
		const Ncti_Char* GetDisplayName();
		/**
	   * @brief get nearest NctiDisplayDocCustomContainer
	   * @details the owner object or owner's owner
	   * @return NctiDisplayDocCustomContainer
	   */
		NctiDisplayDocCustomContainer* GetDocContainer()const;
		/**
	   * @brief get the owner of this display object
	   * @return NctiDisplayObject
	   */
		NctiDisplayObject* GetDoOwner();
		/**
	   * @brief check if the file needs to be saved
	   * @return NctiDisplayObject
	   */
		Ncti_Boolean GetIsSaveOk() { return m_IsSaveOk; }
		/**
	   * @brief internal used
	   */
		Ncti_Boolean IsModifyData() { return m_IsModifyData; }

		/**
	   * @brief set display instance state
	   * @param[in] Ncti_Boolean, true or false
	   */
		void SetDisplayInstance(Ncti_Boolean boo);
		/**
	   * @brief get display instance state
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean GetDisplayInstance() { return m_DisplayInstance; }

		/**
	   * @brief get display object id
	   * @details the id is only one
	   * @return Ncti_Boolean
	   */
		Ncti_Size GetObjectId() { return m_ObjectId; }
		/**
	   * @brief internal used
	   */
		Ncti_Boolean DisplayOnTree() { return m_DisplayOnTree; }
		/**
	   * @brief internal used
	   */
		void SetDisplayOnTree(Ncti_Boolean i_boo);
	public:
		/**
	   * @brief set segment key
	   * @param[in] i_key, NctiRenderSegmentItem
	   */
        void SetSegKey(NCTI::NctiRenderSegmentItem* i_key);
		/**
	   * @brief set object name
	   * @param[in] i_cpObjName
	   */
		void SetObjName(const char* i_cpObjName);
		/**
	   * @brief internal used
	   */
		void SetDisplayName(const Ncti_Char* i_DisplayName);

		/**
	   * @brief internal used
	   */
		//NctiDisplayObject* get_doOwnerTemp() { return m_pDoOwnerTempForPlugin; }
		/**
	   * @brief set the instance list by view
	   * @param[in] i_pBaseView, the render view
	   * @param[out] o_InstanceVec, the instance list 
	   */
		void GetInstance(NctiBaseView* i_pBaseView, std::vector<NctiDisplayObject*>& o_InstanceVec);
		/**
	   * @brief set the instance list by view
	   * @param[in] i_pBaseView, the render view
	   * @param[out] o_InstanceVec, the instance list
	   */
		void GetInstance(NctiBaseView* i_pBaseView, NctiDisplayObjectList* o_InstanceVec);
		/**
	   * @brief set the instance by view and NctiRenderSegmentItem
	   * @param[in] i_pBaseView, the render view
	   * @param[Ncti_Integer] insKey, NctiRenderSegmentItem
	   * @return NctiDisplayObject, the instance
	   */
        NctiDisplayObject* GetInstance(NctiBaseView* i_pBaseView, NctiRenderSegmentItem* insKey);
		/**
	   * @brief internal used
	   */
        NctiDisplayObject* GetActiveInstance()const;
        NctiRenderSegmentItem* GetActiveInsSegment()const;
        Ncti_Boolean SetActiveInstance(NctiDisplayObject* i_ins);

	protected:
		Ncti_Boolean m_IsSaveOk;
		Ncti_Boolean m_IsModifyData;

		Ncti_Boolean m_DisplayInstance;
		Ncti_Boolean m_DisplayOnTree;
		static Ncti_Integer m_CurrentVersion;
	protected:
		NctiDisplayObjectLifeCycleManager* m_pLCM;
		NctiDisplayObject* m_pDoCopyFrom;
		NctiData_NctiHoopsKey* m_pDataSegKey;
		NctiDisplayObject* m_pDoOwner;
        NCTI::NctiRenderSegmentItem* m_ModelKey;
		NctiMutex m_mutex;
		//NctiDisplayObject* m_pDoOwnerTempForPlugin;
		std::map<NctiBaseView*, std::vector<NctiDisplayObject*>> m_InstanceVec;
		NctiTransf m_TransfHelp;
#pragma endregion
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
			NCTI_READ_AND_WRITE_VERSION_FUN(2)
	private:
		NCTI_VERSION(1, NctiChar64Memory*, m_cpObjName, sd_read_string)
        NCTI_VERSION(1, NctiChar64Memory*, m_cpDisplayName, sd_read_string)
		NCTI_VERSION_OBJECT(1, NctiDisplayObject*, m_pDoOriginal, sd_read_long)
		NCTI_VERSION(1, Ncti_Float, m_ObjectAlpha, sd_read_float)
		NCTI_VERSION(1, Ncti_Float, m_ObjectRed, sd_read_float)
		NCTI_VERSION(1, Ncti_Float, m_ObjectGreen, sd_read_float)
		NCTI_VERSION(1, Ncti_Float, m_ObjectBlue, sd_read_float)
		NCTI_VERSION(1, Ncti_Size, m_ObjectId, sd_read_size)
		NCTI_VERSION(1, Ncti_Integer, m_CompressionLevel, sd_read_long)
		NCTI_VERSION(1, Ncti_Integer, m_Compressiontype, sd_read_long)
	public:
		/**
	   * @brief internal used
	   */
		void SetLCM(NctiDisplayObjectLifeCycleManager* i_pLCM);
		/**
	   * @brief internal used
	   */
		void set_do_copy_from(NctiDisplayObject* i_pDoCopyFrom);
		/**
	   * @brief internal used
	   */
		NctiDisplayObject* back_up();
		/**
	   * @brief set the owner of display object
	   * @param[in] i_pDoOwner, the owner 
	   */
		void SetDoOwner(NctiDisplayObject* i_pDoOwner);
		/**
	   * @brief internal used
	   */
        void set_segment_key(NctiData_NctiHoopsKey*&, NCTI::NctiRenderSegmentItem* i_keySegment);
		/**
	   * @brief internal used
	   */
		void set_obj_name(const char* i_cpObjName);
		/**
	   * @brief internal used
	   */
		Ncti_Integer GetReadVersion(Ncti_Integer i_ilocal_ver, Ncti_Integer i_iCurrentVersion);

		/**
	   * @brief internal used
	   */
		void Erase();
		/**
	   * @brief internal used
	   */
		void Display();
		/**
	   * @brief internal used
	   */
		Ncti_Boolean IsDisplayed();
		
		/**
		* @brief Set the red value of the color 
		*/
		void SetObjectRed(const Ncti_Float& val);

		/**
		* @brief Set the green value of the color
		*/
		void SetObjectGreen(const Ncti_Float& val);

		/**
		* @brief Set the blue value of the color
		*/
		void SetObjectBlue(const Ncti_Float& val);

		/**
		* @brief Set the alpha value of the color
		*/
		void SetObjectAlpha(const Ncti_Float& val);
		
		/**
		* @brief Get the red value of the color 
		*/
		const Ncti_Float& GetObjectRed();

		/**
		* @brief Get the green value of the color
		*/
		const Ncti_Float& GetObjectGreen();

		/**
		* @brief Get the blue value of the color
		*/
		const Ncti_Float& GetObjectBlue();

		/**
		* @brief Get the alpha value of the color
		*/
		const Ncti_Float& GetObjectAlpha();
	public:
		/**
	   * @brief internal used
	   */
		virtual EnumNctiResult ActivateData();
		virtual EnumNctiResult ActivateData(NctiDisplayDocCustomContainer* i_pDisplayDocCustomContainer, const std::vector<NCTI_MODEL_TAG>& i_ModelBodyVec);
		virtual EnumNctiResult InactivateData(NctiFileInterface* i_pFI);
		virtual EnumNctiResult fix_pointer(NctiFileInterface* i_pFI);
        virtual void update_segment(NCTI::NctiRenderSegmentItem* i_SegKey);
		virtual EnumNctiResult save_data(NctiFileInterface* i_pFI);
		virtual EnumNctiResult restore_data(NctiFileInterface* i_pFI);
		virtual NctiDisplayObject* make_copy(NctiDisplayObject* i_pDoCopyFrom);
		virtual void copy_data(NctiDisplayObject* i_pDoCopyFrom);
		virtual void swap_data(NctiDisplayObject* i_pDoSwap);
		virtual EnumNctiResult save_temp_file(NctiFileInterface* i_pFileInterface);
		virtual EnumNctiResult restore_temp_file(NctiFileInterface* i_pFileInterface);
		virtual NctiDisplayObject* CreateInstance(NctiBaseView* i_pBaseView, NctiDisplayObject* i_pDisplayObject);
        virtual void HighlightSegment(Ncti_Boolean i_bOnOff);
        virtual void HighlightGeometry(NCTI::NctiRenderGeometryItem* i_key, Ncti_Boolean i_bOnOff);
		virtual Ncti_Integer InitPackedData();
		virtual void Compress(Ncti_Integer) {};
		virtual void UnCompress(Ncti_Integer) {};
        virtual void CompressTri(Ncti_Integer) {};
        virtual void UnCompressTri(Ncti_Integer) {};
		virtual void UpdateSketch(NctiDisplayDocCustomContainer* i_pDocCustomContainer) {};
		void SetDoOriginal(NctiBaseView* i_pBaseView, NctiDisplayObject* i_pDoOriginal);
	protected:
		void UpdateRenderDataFun(NctiDisplayObject* i_pInstance);
		void UpdateColor();
		Ncti_Integer GetCompressionLevel() { return m_CompressionLevel; }
		void AddInstance(NctiBaseView* i_pBaseView, NctiDisplayObject* i_pInstance);
	public:
		void RemoveInstance(NctiDisplayObject* i_pInstance);
#pragma endregion 
	};
}
#endif
