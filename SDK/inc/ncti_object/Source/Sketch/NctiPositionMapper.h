#ifndef NctiPositionMapper_H
#define NctiPositionMapper_H
#include "ncti.h"
#include "NctiPosition.h"
#include "NctiUnitVector.h"
#include "dcl_ncti_object.h"
using namespace NCTI;
#define POS_UNKNOWN   0		// data = NULL, param = 0

#define POS_KEYIN     1		// data = NULL, param = 0
#define POS_KEYIN_ABS 2		// data = NULL, param = 0
#define POS_KEYIN_REL 3		// data = NULL, param = 0
#define POS_KEYIN_CYL 4		// data = NULL, param = 0

#define POS_SCREEN    10	// data = NULL, param = 0
#define POS_VERTEX    20	// data = ENTITY*, param = 0

#define POS_CURVEEND  100	// data = ENTITY*, param = 0 or 1
#define POS_ONCURVE   101	// data = ENTITY*, param = param in [0, 1]
#define POS_CURVEMID  102	// data = ENTITY*, param = .5
#define POS_ARCCENTER 103	// data = ENTITY*, param = 0

#define POS_ONFACE    200	// data = ENTITY*, param = 0

#define POS_APP       1000

namespace NCTI
{
	class NctiPickRay;
	class NctiBaseView;
	class NctiRenderMouseState;
	class  DECL_NCTI_OBJECT ncti_input_position : public NCTI_BASE_CLASS
	{
	public:
		ncti_input_position();
		ncti_input_position(const NctiPosition&);
		ncti_input_position(const NctiPosition&, unsigned int, void*, double);
		virtual ~ncti_input_position() {}
		unsigned int get_type() const { return m_nType; }
		void set_type(unsigned int  i_type) { m_nType = i_type; }
		const NctiPosition& get_position() const { return m_position; }
		void set_position(const NctiPosition& i_pos) { m_position = i_pos; }
		operator const NctiPosition& () const { return m_position; }
		void* get_data() const { return m_pData; }
		void set_data(void* i_data) { m_pData = i_data; }
		double get_param() const { return m_paramData; }
		void set_param(double  i_param) { m_paramData = i_param; }

	protected:
		NctiPosition m_position;

		unsigned int m_nType;
		double m_paramData;
		void* m_pData;
	};
	class DECL_NCTI_OBJECT  NctiPositionMapper : public NCTI_BASE_CLASS
	{
		friend class NctiPositionMapperList;
	protected:
		NctiPositionMapper* m_pNextPositionMapper;
		NctiPositionMapper* m_pPrevPositionMapper;
	public:
		void set_next(NctiPositionMapper* i_pm) { m_pNextPositionMapper = i_pm; };
		void set_prev(NctiPositionMapper* i_pm) { m_pPrevPositionMapper = i_pm; };
		NctiPositionMapper* next() { return m_pNextPositionMapper; };
		NctiPositionMapper* prev() { return m_pPrevPositionMapper; };

	protected:
		unsigned int m_nTag;

	public:
		enum EMappingStatus {
			OK,
			CONTINUE,
			FAIL
		};

	public:
		NctiPositionMapper() : m_nTag(0), m_pNextPositionMapper(NULL), m_pPrevPositionMapper(NULL) {}
		NctiPositionMapper(unsigned int  i_tag) : m_nTag(i_tag) {}
		virtual ~NctiPositionMapper() {};
		virtual EMappingStatus map_position(
			NctiBaseView* i_pBaseView, const NctiPosition& i_pt,
			ncti_input_position& i_posdata,
			bool from_rb = false
		);
		unsigned int get_tag() const { return m_nTag; }
		void set_tag(unsigned int  i_tag) { m_nTag = i_tag; }
	};

	class DECL_NCTI_OBJECT  NctiScreenPositionMapper : public NctiPositionMapper
	{
	public:
		virtual EMappingStatus map_position(
			NctiBaseView* i_pBaseView, const NctiPosition& i_pt,
			ncti_input_position& i_posdata,
			bool from_rb = false
		);
	};

	class DECL_NCTI_OBJECT  NctiPlanePositionMapper : public NctiPositionMapper
	{
	protected:
		NctiPosition m_planePosition;
		NctiUnitVector m_planeNormal;

	public:
		NctiPlanePositionMapper();
		NctiPlanePositionMapper(const NctiPosition& i_pos,
			const NctiUnitVector& i_normal, unsigned int  i_tag = 0);
		void set_plane_data(const NctiPosition& i_pos, const NctiUnitVector& i_normal);
		virtual EMappingStatus map_position(
			NctiBaseView* i_pBaseView, const NctiPosition& i_pt,
			ncti_input_position& i_posdata,
			bool from_rb = false
		);

	};

	class DECL_NCTI_OBJECT  NctiLinePositionMapper : public NctiPositionMapper
	{
	protected:
		NctiPosition m_linePosition;
		NctiUnitVector m_lineDirection;

	public:
		NctiLinePositionMapper();
		NctiLinePositionMapper(const NctiPosition& i_pos,
			const NctiUnitVector& i_dir, unsigned int  i_tag = 0);
		void set_line_data(const NctiPosition& i_pos, const NctiUnitVector& i_dir);
		virtual EMappingStatus map_position(
			NctiBaseView* i_pBaseView, const NctiPosition& i_pt,
			ncti_input_position& i_posdata,
			bool from_rb = false
		);

	};
}

NctiPickRay DECL_NCTI_OBJECT ncti_get_pick_ray(NctiBaseView* i_pBaseView, const NctiPosition& i_pt, bool at_eye_distance = false);
NctiPickRay DECL_NCTI_OBJECT ncti_pick_screen_position(NctiBaseView* i_pBaseView, const NctiPosition& i_pt, NctiPosition*, NctiUnitVector*);

bool DECL_NCTI_OBJECT ncti_map_position(
	NctiBaseView* i_pBaseView, const NctiPosition& i_pt,
	ncti_input_position&,
	bool from_rb = false,
	NctiPositionMapper* default_mapper = NULL
);

bool DECL_NCTI_OBJECT ncti_map_position(
	NctiBaseView* i_pBaseView, const NctiPosition& i_pt,
	NctiPosition&,
	bool from_rb = false);

unsigned int DECL_NCTI_OBJECT ncti_get_position_mapper_tag();

#endif