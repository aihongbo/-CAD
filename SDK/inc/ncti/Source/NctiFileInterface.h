#ifndef NctiFileInterface_H
#define NctiFileInterface_H
#include "ncti.h"
#include <stdio.h>
#include <vector>
#include <string>
namespace NCTI
{
	class NctiLocalFileInterface;
	class NctiEnumTable;
	class NctiDisplayObject;
	class NctiDisplayObjectList;
	class NctiPosition;
	class NctiMatrix;
	class NctiTransf;
	class NctiVector;
	class NctiRenderGeometryItem;
	class NctiRenderSegmentItem;
	enum ahFileMode
	{
		NCTI_FILE_MODE_STANDARD,
		NCTI_FILE_MODE_STREAMING
	};
	/**
	* @brief internal used
	*/
	class DECL_NCTI NctiFileInterface : public NCTI_BASE_CLASS
	{
	public:
		//NctiFileInterface(FILE* i_pFile, )
		NctiFileInterface();
		virtual ~NctiFileInterface();
	public:
		void Init(FILE* i_pFile);
		void ReadVersion();
		char* ReadObjectName();
		Ncti_Integer AppendDo(NctiDisplayObject* i_pDo); 
		void ReadTerminator();
		void SetFileMode(ahFileMode i_eMode) { m_eFileMode = i_eMode; };
		NctiDisplayObjectList* GetDoList();
		FILE* GetFilePointer() { return m_pFile; }
		NctiDisplayObject* IndexToDisplayObject(long i_iIndex);
        NCTI::NctiRenderSegmentItem* IndexToKey(Ncti_Integer i_iIndex);

        void SetSegmentKey(NCTI::NctiRenderSegmentItem* i_SegmentKey);
		void WriteVersion(Ncti_Integer i_iMajor, Ncti_Integer i_iMinor);
		void WriteEndOfFile();
		void WriteTerminator();
		Ncti_Integer AppendDoForWriteFile(NctiDisplayObject* i_pFather, NctiDisplayObject* i_pChild);
		Ncti_Integer LookupDo(NctiDisplayObject* i_pDo);
		std::string GetInputPath();
		void SetInputPath(const std::string& i_filePath);
	public:
		void write_bool(Ncti_Boolean i_value);
		Ncti_Boolean read_bool();
		void write_enum(Ncti_Integer i_value, NctiEnumTable const &i_table);
		Ncti_Integer read_enum(NctiEnumTable const &i_table);
		void write_short(short i_d);
		short read_short();
		void write_long(long i_ld);
		long read_long();
		void write_size(Ncti_Size lValue);
		Ncti_Size read_size();
		void write_float(Ncti_Float i_g);
		Ncti_Float read_float();
		void write_double(Ncti_Double i_d);
		Ncti_Double read_double();
		void write_string(const char* i_str, size_t i_len = 0);
		char* read_string(Ncti_Integer& i_len);
		char* read_string();
		void read_string(Ncti_Char* o_char, Ncti_Integer i_Length);
		void write_position(NctiPosition& i_pos);
		NctiPosition read_position();
		void write_vector(const NctiVector& i_vec);
		NctiVector read_vector();
		void write_matrix(NctiMatrix const &i_m);
		NctiMatrix read_matrix();
		void write_transf(NctiTransf const &i_t);
		NctiTransf read_transf();
		void write_newline(Ncti_Integer i_count = 1);
		void write_terminator();

		void write_packed(void* i_Buffer, size_t i_ElementSize, size_t i_ElementCount);
		void read_packed(void* o_Buffer, size_t i_ElementSize, size_t i_ElementCount);
	public:
		void GetVersion(Ncti_Integer& o_Major, Ncti_Integer& o_Minor)
		{ 
			o_Major = m_iMajor; 
			o_Minor = m_iMinor; 
		}
	protected:
		FILE* m_pFile;
		NctiLocalFileInterface* m_pFileInterface;
		NctiDisplayObjectList* m_pDoList; 
		ahFileMode	m_eFileMode;
        NCTI::NctiRenderSegmentItem* m_SegmentKey;
	private:
		Ncti_Integer m_iMajor;
		Ncti_Integer m_iMinor;
	private:
		std::string m_InputPath;
	};
}
#endif
