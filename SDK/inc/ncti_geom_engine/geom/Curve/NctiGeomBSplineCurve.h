 #ifndef Geom_BSplineCurve_H
 #define Geom_BSplineCurve_H
 #include "NctiGeomBoundedCurve.h"
 namespace NCTI
 {
 	class DECL_NCTI_GEOM_ENGINE NctiGeomBSplineCurve : public NctiGeomBoundedCurve
 	{
        NCTI_GEOM_FUNCTIONS(NctiGeomBSplineCurve)
 	public:
        NctiGeomBSplineCurve(
            Ncti_Boolean i_rational,
            Ncti_Boolean i_periodic,
            Ncti_GeomAbs_BSplKnotDistribution i_knotSet,
            Ncti_GeomAbs_Shape i_smooth,
            Ncti_Integer i_Degree,
 			const std::vector<NctiPosition>& i_poles,
 			const std::vector<Ncti_Double>& i_weights,
            const std::vector<Ncti_Double>& i_flatknots,
 			const std::vector<Ncti_Double>& i_knots,
 			const std::vector<Ncti_Integer>& i_mults,
			Ncti_Double i_maxderivinv,
			Ncti_Boolean i_maxderivinvok);
 		virtual ~NctiGeomBSplineCurve();
//  	public:
//  		virtual void D0(Ncti_Double i_U, gp_Pnt& o_P) const /*NCTI_OVERRIDE*/;
//  	private:
//  		void CheckCurveData(
//  			const NC_Array1_Pnt& i_poles,
//  			const NC_Array1_Double& i_knots,
//  			Ncti_Integer i_Degree,
//  			const NC_Array1_Integer& i_mults,
//  			Ncti_Boolean i_periodic);
//  		Ncti_Boolean Rational(const NC_Array1_Double& i_theWeights);
//  		void UpdateKnots();
//  		void PeriodicNormalization(Ncti_Double& o_U) const;
    public:
        Ncti_Boolean GetRational() { return m_rational; }
        Ncti_Boolean GetPeriodic() { return m_periodic; }
        Ncti_GeomAbs_BSplKnotDistribution GetKnotSet() { return m_knotSet; }
        Ncti_GeomAbs_Shape GetSmooth() { return m_smooth; }
        Ncti_Integer GetDegree() { return m_Degree; }
        const std::vector<NctiPosition>& GetPoles() { return m_poles; }
        const std::vector<Ncti_Double>& GetWeights() { return m_weights; }
        const std::vector<Ncti_Double>& GetFlatknots() { return m_flatknots; }
        const std::vector<Ncti_Double>& GetKnots() { return m_knots; }
        const std::vector<Ncti_Integer>& GetMults() { return m_mults; }
        Ncti_Double GetMaxderivinv() { return m_maxderivinv; }
        Ncti_Boolean GetMaxderivinvok() { return m_maxderivinvok; }
 	private:
 		Ncti_Boolean m_rational;
 		Ncti_Boolean m_periodic;
        Ncti_GeomAbs_BSplKnotDistribution m_knotSet;
        Ncti_GeomAbs_Shape m_smooth;
 		Ncti_Integer m_Degree;
        std::vector<NctiPosition> m_poles;
        std::vector<Ncti_Double> m_weights;
        std::vector<Ncti_Double> m_flatknots;
        std::vector<Ncti_Double> m_knots;
        std::vector<Ncti_Integer> m_mults;

		Ncti_Double m_maxderivinv;
		Ncti_Boolean m_maxderivinvok;
 	};
 }
 #endif
