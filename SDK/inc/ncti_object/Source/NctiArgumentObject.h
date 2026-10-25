#ifndef NctiArgumentObject_H
#define NctiArgumentObject_H
#include "ncti_base.h"
#include "dcl_ncti_object.h"
#include "NctiDisplayObject.h"
#include "NctiMeshDataDef.h"

typedef struct _object PyObject;

#define NCTI_ARG_DEGINE(OBJECT_TYPE,OBJECT)\
private:\
OBJECT_TYPE m_##OBJECT;\
public:\
void Set##OBJECT(const OBJECT_TYPE& i_##OBJECT){ m_##OBJECT = i_##OBJECT;}\
const OBJECT_TYPE& Get##OBJECT(){return m_##OBJECT;}

#define NCTI_OBJ_POINTER(OBJECT_TYPE,OBJECT)\
private:\
OBJECT_TYPE m_##OBJECT;\
public:\
void Set##OBJECT(OBJECT_TYPE i_##OBJECT){ m_##OBJECT = i_##OBJECT;}\
OBJECT_TYPE Get##OBJECT(){return m_##OBJECT;}

#define _DISPLAYOBJECT_ "NCTI.DisplayObject_ptr"

namespace NCTI
{
	
	/**
	* @brief Command parameter object
	*/
	class DECL_NCTI_OBJECT NctiArgumentObject : public NctiDisplayObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiArgumentObject)
	public:
		virtual ~NctiArgumentObject();
		void SetDisplayName() = delete;
		const Ncti_Char* GetDisplayName() = delete;
	private:
		Ncti_Char* m_FilePath;
		Ncti_Boolean m_DisplayMesh;
		Ncti_Integer m_DisplayMeshMode;//1 - edge, 2 - face, 3-volume, 
		NctiVector m_Dir;
		Ncti_Float m_Size;
		Ncti_Integer m_ForceType;
		NctiVector m_Displacement;
		Ncti_Float m_wMove;
		Ncti_Float m_hMove;
		Ncti_Integer m_w;
		Ncti_Integer m_h;
		std::vector<std::string> m_CommandArgumentVec;
		PyObject* m_PyObject;
		Ncti_Char* m_Char;
		Ncti_Boolean m_HasIntValue;
		Ncti_Integer m_IntValue;
		Ncti_Boolean m_HasFloatValue;
		Ncti_Float m_FloatValue;
		//create_mesh
		NCTI_ARG_DEGINE(Ncti_Mesh_Option, meshOption)

		//create_box
		NCTI_ARG_DEGINE(NctiPosition, Pt)
		NCTI_ARG_DEGINE(Ncti_Double, XLen)
		NCTI_ARG_DEGINE(Ncti_Double, YLen)
		NCTI_ARG_DEGINE(Ncti_Double, ZLen)
		//create_cylinder
		NCTI_ARG_DEGINE(Ncti_Double, Radius)
		NCTI_ARG_DEGINE(Ncti_Double, Height)
		//Select DisplayObject
		NCTI_OBJ_POINTER(NctiDisplayObject*, DisplayObject1)
		NCTI_OBJ_POINTER(NctiDisplayObject*, DisplayObject2)
		NCTI_ARG_DEGINE(std::vector<NctiDisplayObject*>, DisplayObjectVec)
		NCTI_ARG_DEGINE(std::vector<NCTI_MODEL_TAG>, CellVec)
		NCTI_ARG_DEGINE(std::vector<Ncti_Long>, CellIDVec)
		// create_sphere
		NCTI_ARG_DEGINE(NctiVector, Normal)
		NCTI_ARG_DEGINE(NctiVector, FirstDirect)
		NCTI_ARG_DEGINE(Ncti_Double, Angle1)
		NCTI_ARG_DEGINE(Ncti_Double, Angle2)
		NCTI_ARG_DEGINE(Ncti_Double, Angle3)
		// create_cone
		NCTI_ARG_DEGINE(Ncti_Double, TopRadius)
		NCTI_ARG_DEGINE(Ncti_Double, BottomRadius)
		// scale
		NCTI_ARG_DEGINE(Ncti_Double, Scale)
		// create_bezier_curve
		NCTI_ARG_DEGINE(std::vector<NctiPosition>, PtVec)
		NCTI_ARG_DEGINE(std::vector<Ncti_Double>, WeigthVec)
	    //Design Result.
		NCTI_ARG_DEGINE(std::vector<std::string>, DesignResultVec)

		
		NCTI_ARG_DEGINE(EnumModelDoc, m_ModelDoc)
		NCTI_ARG_DEGINE(EnumGCSDoc, m_constraintType)
		NCTI_ARG_DEGINE(EnumMeshDoc, m_meshType)

		NCTI_ARG_DEGINE(std::vector<NctiDisplayObject*>, CreateObjectVec)

	public:
		void SetFilePath(const Ncti_Char* i_filepath);
		const Ncti_Char* getFilePath();
		void SetDisplayMesh(Ncti_Boolean i_boo);
		Ncti_Boolean GetDisplayMesh();
		void SetDisplayMeshMode(Ncti_Boolean i_boo);
		Ncti_Boolean GetDisplayMeshMode();
		void SetDir(const NctiVector& i_dir);
		void SetSize(Ncti_Float i_f);
		const NctiVector& GetDir() { return m_Dir; }
		Ncti_Float GetSize() { return m_Size; }
		void SetForce(Ncti_Integer i_num);
		Ncti_Integer GetForce() { return m_ForceType; }
		void SetDisplacement(const NctiVector& i_dis);
		const NctiVector& GetDisplacement() { return m_Displacement; }
		void SetArray(Ncti_Float i_wMove, Ncti_Float i_hMove, Ncti_Integer i_w, Ncti_Integer i_h);
		void GetArray(Ncti_Float& o_wMove, Ncti_Float& o_hMove, Ncti_Integer& o_w, Ncti_Integer& o_h);
		void SetCommandArgumentVec(const std::vector<std::string>& i_ListVec) { m_CommandArgumentVec = i_ListVec; }
		const std::vector<std::string>& GetCommandArgumentVec() { return m_CommandArgumentVec; }
		void SetPyObject(PyObject* i_pPyObject);
		PyObject* GetPyObject() { return m_PyObject; }
		void SetChar(const Ncti_Char* i_char);
		const Ncti_Char* getChar();

		Ncti_Boolean HasIntValue() const { return m_HasIntValue; }
		void SetIntValue(Ncti_Integer i_val);
		Ncti_Integer GetIntValue() { return m_IntValue; }

		Ncti_Boolean HasFloatValue() const { return m_HasFloatValue; }
		void SetFloatValue(Ncti_Float i_val);
		Ncti_Float GetFloatValue() { return m_FloatValue; }
	};
}
#endif
