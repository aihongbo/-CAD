#ifndef NctiGPropDef_H
#define NctiGPropDef_H

#include "dcl_ncti_plugin.h"
#include "ncti_base.h"
#include "NctiPosition.h"
#include "NctiMatrix.h"

namespace NCTI
{
	class DECL_NCTI_PLUGIN NctiGeomProp : public NCTI_BASE_CLASS
	{
	public:
		NctiGeomProp();

		void SetGravityCenter(const NctiPosition& gravityCenter);
		const NctiPosition& GetGravityCenter() const;

		void SetInertiaMatrix(const NctiMatrix& inertiaMatrix);
		const NctiMatrix& GetInertiaMatrix() const;

		void SetWireLength(Ncti_Double fWireLength, bool bAccumulate = false);
		Ncti_Double GetWireLength() const;

		void SetArea(Ncti_Double fArea, bool bAccumulate = false);
		Ncti_Double GetArea() const;

		void SetVolumn(Ncti_Double fVolumn, bool bAccumulate = false);
		Ncti_Double GetVolumn() const;

		void SetStaticMoments(Ncti_Double fIx, Ncti_Double fIy, Ncti_Double fIz);
		void GetStaticMoments(Ncti_Double& fIx, Ncti_Double& fIy, Ncti_Double& fIz) const;

		void SetPrincipalMoments(Ncti_Double fIxx, Ncti_Double fIyy, Ncti_Double fIzz);
		void GetPrincipalMoments(Ncti_Double& fIxx, Ncti_Double& fIyy, Ncti_Double& fIzz) const;

		void SetPrincipalRadiusOfGyration(Ncti_Double fRxx, Ncti_Double fRyy, Ncti_Double fRzz);
		void GetPrincipalRadiusOfGyration(Ncti_Double& fRxx, Ncti_Double& fRyy, Ncti_Double& fRzz) const;

	private:
		//线长，对于线对象有效
		Ncti_Double m_fWireLength;

		//表面积，对于面对象或者实体对象有效
		Ncti_Double m_fArea;

		//体积，对于实体对象有效
		Ncti_Double m_fVolumn;

		//重心
		NctiPosition m_gravityCenter;

		//惯性矩
		NctiMatrix m_inertiaMatrix;

		//静态惯性矩
		Ncti_Double m_fIx;
		Ncti_Double m_fIy;
		Ncti_Double m_fIz;

		//主力矩
		Ncti_Double m_fIxx;
		Ncti_Double m_fIyy;
		Ncti_Double m_fIzz;

		//主回转半径
		Ncti_Double m_fRxx;
		Ncti_Double m_fRyy;
		Ncti_Double m_fRzz;
	};
}
#endif // !NctiGPropDef_H
