#ifndef NctiMeasuringTool_H
#define NctiMeasuringTool_H
#include "dcl_ncti_pubfun.h"
#include "ncti_base.h"
#include <vector>
#include <functional>

namespace NCTI
{
	class NctiPosition;
	class NctiVector;
    using CalPositionCallback = std::function<void(const NctiPosition&)>;
    using CalLengthCallback = std::function<void(Ncti_Double)>;
	using CalVectorCallback = std::function<void(const NctiVector&)>;
	class NctiDocument;
	class NctiDisplayObject;
	class DECL_NCTI_PUBFUN NctiMeasuringTool
	{
	public:
		NctiMeasuringTool();
		~NctiMeasuringTool();
	public:
		static NctiMeasuringTool* instance();
        void Init(CalPositionCallback func_CalPosition, CalLengthCallback func_CalLength,
            CalPositionCallback func_CalMidPosition, CalPositionCallback func_CalCenter,
            CalLengthCallback func_CalRadius, CalVectorCallback func_CalVector,
            CalLengthCallback func_CalAngle);
		Ncti_Boolean GetDisplayObjectFromSelManager(NctiDocument* i_pDocment, std::vector<NctiDisplayObject*>& o_ObjVec, std::vector<NCTI_MODEL_TAG>& o_CellVec);
	public:
		void Position(NctiDocument* i_pDocment);
		void Length(NctiDocument* i_pDocment);
		void MidPosition(NctiDocument* i_pDocment);
		void Center(NctiDocument* i_pDocment);
		void Radius(NctiDocument* i_pDocment);
		void Vector(NctiDocument* i_pDocment);
		void Angle(NctiDocument* i_pDocment);
	public:
		void ResetAll();
	public:
		void SetCalPositionCallback(CalPositionCallback func) { m_CalPositionCallback = func; }
        CalPositionCallback GetCalPositionCallback() const { return m_CalPositionCallback; }

        void SetCalLengthCallback(CalLengthCallback func) { m_CalLengthCallback = func; }
        CalLengthCallback GetCalLengthCallback() const { return m_CalLengthCallback; }

        void SetCalMidPositionCallback(CalPositionCallback func) { m_CalMidPositionCallback = func; }
        CalPositionCallback GetCalMidPositionCallback() const { return m_CalMidPositionCallback; }

        void SetCalCenterCallback(CalPositionCallback func) { m_CalCenterCallback = func; }
        CalPositionCallback GetCalCenterCallback() const { return m_CalCenterCallback; }

		void SetCalRadiusCallback(CalLengthCallback func) { m_CalRadiusCallback = func; }
		CalLengthCallback GetCalRadiusCallback() const { return m_CalRadiusCallback; }

		void SetCalVectorCallback(CalVectorCallback func) { m_CalVectorCallback = func; }
		CalVectorCallback GetCalVectorCallback() const { return m_CalVectorCallback; }

		void SetCalAngleCallback(CalLengthCallback func) { m_CalAngleCallback = func; }
		CalLengthCallback GetCalAngleCallback() const { return m_CalAngleCallback; }
	private:
		static NctiMeasuringTool* m_instance;

        CalPositionCallback m_CalPositionCallback{ nullptr };
        CalLengthCallback m_CalLengthCallback{ nullptr };
        CalPositionCallback m_CalMidPositionCallback{ nullptr };
        CalPositionCallback m_CalCenterCallback{ nullptr };
		CalLengthCallback m_CalRadiusCallback{ nullptr };
		CalVectorCallback m_CalVectorCallback{ nullptr };
		CalLengthCallback m_CalAngleCallback{ nullptr };
	};
}
#endif

