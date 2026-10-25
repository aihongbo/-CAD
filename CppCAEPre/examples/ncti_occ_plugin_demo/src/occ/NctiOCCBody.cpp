#include "NctiOCCBody.h"
#include "TopExp_Explorer.hxx"
#include "TopTools_DataMapOfShapeInteger.hxx"
#include "TopoDS_Vertex.hxx"
#include "TopoDS.hxx"
#include "TopoDS_Edge.hxx"
#include "TopoDS_Face.hxx"
#include "BRep_Tool.hxx"
#include "BRep_TEdge.hxx"
#include "BRep_CurveRepresentation.hxx"
#include "Geom_Line.hxx"
#include "Geom_Circle.hxx"
#include "Geom_BezierCurve.hxx"
#include "Geom_BSplineCurve.hxx"
#include "Geom_Ellipse.hxx"
#include "BRep_TVertex.hxx"
#include "BRep_Curve3D.hxx"
#include "BRep_TFace.hxx"
#include "Geom_Plane.hxx"
#include "TopExp.hxx"
#include "TopoDS_TWire.hxx"
#include "TopoDS_TShell.hxx"
#include "TopoDS_TSolid.hxx"
#include "TopoDS_Shell.hxx"
#include "TopoDS_Wire.hxx"
#include "Geom_CylindricalSurface.hxx"
#include "Geom_BSplineSurface.hxx"
#include "Geom_ToroidalSurface.hxx"
#include "Geom_SphericalSurface.hxx"
#include "Geom_ConicalSurface.hxx"
#include "Geom_BezierSurface.hxx"
#include "Geom_TrimmedCurve.hxx"
#include "Graphic3d_Mat4d.hxx"
#include "BRepTools.hxx"
#include "Geom_RectangularTrimmedSurface.hxx"

//geom_engine
#include "NctiTopoShape.h"
#include "NctiGeomLine.h"
#include "NctiTopoEdge.h"
#include "NctiGeomCircle.h"
#include "NctiGeomBezierCurve.h"
#include "NctiGeomBSplineCurve.h"
#include "NctiGeomEllipse.h"
#include "NctiGeomPoint.h"
#include "NctiTopoVertex.h"
#include "NctiTopoFace.h"
#include "NctiGeomPlane.h"
#include "NctiGeomUnKnownCurve.h"
#include "NctiGeomCylindricalSurface.h"
#include "NctiGeomBSplineSurface.h"
#include "NctiGeomToroidalSurface.h"
#include "NctiGeomSphericalSurface.h"
#include "NctiGeomConicalSurface.h"
#include "NctiGeomBezierSurface.h"
#include "NctiTopoEdgeCurve.h"
#include "NctiGeomTrimmedCurve.h"
#include "NctiTopoLoop.h"
#include "NctiGeomRectangularTrimmedSurface.h"

#include "NctiDebug.h"
#include "NctiString.h"
#include "NctiTime.h"
#include "NctiTransf.h"
#include "NctiBaseUtility.h"
#include "gp_Pln.hxx"
#include "NctiPluginsManager.h"
// #include "NctiBRepMeshIncrementalMesh.h"
// #include "NctiBox.h"

using namespace NCTI;
namespace NCTI
{
	class NctiOCCBodyAttributeManager
	{
	public:
		NctiOCCBodyAttributeManager()
		{

		}
		virtual ~NctiOCCBodyAttributeManager()
		{

		}
	public:
		static NctiOCCBodyAttributeManager* instance() { return m_instance; }
		void add_attribute_segment(const Handle(TopoDS_TShape)& i_TShape, NctiRenderSegmentItem* i_pSegment)
		{
			if (m_MapSegment.find(i_TShape) == m_MapSegment.end())
			{
				m_MapSegment[i_TShape] = i_pSegment;
			}
		}
		NctiRenderSegmentItem* get_attribute_segment(const Handle(TopoDS_TShape)& i_TShape)
		{
			return m_MapSegment[i_TShape];
		}
	private:
		static NctiOCCBodyAttributeManager* m_instance;
	private:
		std::map<Handle(TopoDS_TShape), NctiRenderSegmentItem*> m_MapSegment;

	};
}

NCTI::NctiOCCBodyAttributeManager* NctiOCCBodyAttributeManager::m_instance = NCTI_NEW NCTI::NctiOCCBodyAttributeManager();


NCTI::NctiPosition occ_to_ge(const gp_Pnt& i_gpt)
{
	return NctiPosition(i_gpt.X(), i_gpt.Y(), i_gpt.Z());
}
NCTI::NctiUnitVector occ_to_ge(const gp_Dir& i_gdir)
{
	return NctiUnitVector(i_gdir.X(), i_gdir.Y(), i_gdir.Z());
}

NctiTransf occ_to_ge(const gp_Trsf& i_gptr)
{
	Graphic3d_Mat4d aTrsf;
	i_gptr.GetMat4(aTrsf);
	Ncti_Double matrix[16];
	matrix[0] = aTrsf.GetValue(0, 0);
	matrix[1] = aTrsf.GetValue(1, 0);
	matrix[2] = aTrsf.GetValue(2, 0);
	matrix[3] = aTrsf.GetValue(3, 0);

	matrix[4] = aTrsf.GetValue(0, 1);
	matrix[5] = aTrsf.GetValue(1, 1);
	matrix[6] = aTrsf.GetValue(2, 1);
	matrix[7] = aTrsf.GetValue(3, 1);


	matrix[8] = aTrsf.GetValue(0, 2);
	matrix[9] = aTrsf.GetValue(1, 2);
	matrix[10] = aTrsf.GetValue(2, 2);
	matrix[11] = aTrsf.GetValue(3, 2);

	matrix[12] = aTrsf.GetValue(0, 3);
	matrix[13] = aTrsf.GetValue(1, 3);
	matrix[14] = aTrsf.GetValue(2, 3);
	matrix[15] = aTrsf.GetValue(3, 3);

	NctiTransf newTran;
	api_convert_transf(matrix, newTran);
	return newTran;
}

NctiGeomCurve* occ_to_ge(const Handle(Geom_Curve)& curve)
{
	Handle(Standard_Type) TheType = curve->DynamicType();
	if (TheType == STANDARD_TYPE(Geom_Line))
	{
		Handle(Geom_Line) curve_line = Handle(Geom_Line)::DownCast(curve);
		gp_Ax1 pos = curve_line->Position();
		const gp_Pnt& p = pos.Location();
		gp_Dir dir = pos.Direction();
		NctiPosition pt(p.X(), p.Y(), p.Z());
		NctiUnitVector vec(dir.X(), dir.Y(), dir.Z());
		NctiGeomLine* pGeomLine = NCTI_NEW NctiGeomLine(pt, vec);
		return pGeomLine;
	}
	else if (TheType == STANDARD_TYPE(Geom_Circle))
	{
		Handle(Geom_Circle) curve_circle = Handle(Geom_Circle)::DownCast(curve);
		Ncti_Double radius = curve_circle->Radius();
		gp_Ax2 pos2 = curve_circle->Position();
		const gp_Pnt& p = pos2.Location();
		gp_Dir dirX = pos2.XDirection();
		gp_Dir dirY = pos2.YDirection();
		NctiPosition pt(p.X(), p.Y(), p.Z());
		NctiUnitVector vecX(dirX.X(), dirX.Y(), dirX.Z());
		NctiUnitVector vecY(dirY.X(), dirY.Y(), dirY.Z());
		NctiGeomCircle* pGeomCircle = NCTI_NEW NctiGeomCircle(pt, vecX, vecY, radius);
		return pGeomCircle;
	}
	else if (TheType == STANDARD_TYPE(Geom_BezierCurve))
	{
		Handle(Geom_BezierCurve) curve_beziercurve = Handle(Geom_BezierCurve)::DownCast(curve);
		Ncti_Boolean rational = curve_beziercurve->IsRational();
		Ncti_Boolean closed = curve_beziercurve->IsClosed();
		const TColgp_Array1OfPnt& poles = curve_beziercurve->Poles();
		const TColStd_Array1OfReal* weights = curve_beziercurve->Weights();
		Ncti_Double maxderivinv = 0;
		Ncti_Boolean maxderivinvok = true;
		std::vector<NctiPosition> PoleVec;
		for (Ncti_Integer ii = 0; ii < poles.Size(); ii++)
		{
			gp_Pnt pn = poles.Value(ii + 1);
			NctiPosition pt(pn.X(), pn.Y(), pn.Z());
			PoleVec.push_back(pt);
		}
		std::vector<Ncti_Double> WeightVec;
		if (weights)
		{
			for (Ncti_Integer ii = 0; ii < weights->Size(); ii++)
			{
				WeightVec.push_back((*weights)[ii + 1]);
			}
		}
		NctiGeomBezierCurve* pGeomCircle = NCTI_NEW NctiGeomBezierCurve(rational, closed, PoleVec, WeightVec, maxderivinv, maxderivinvok);
		return pGeomCircle;
	}
	else if (TheType == STANDARD_TYPE(Geom_BSplineCurve))
	{
		Handle(Geom_BSplineCurve) curve_bsplinecurve = Handle(Geom_BSplineCurve)::DownCast(curve);
		Ncti_Boolean rational = curve_bsplinecurve->IsRational();
		Ncti_Boolean periodic = curve_bsplinecurve->IsPeriodic();
		GeomAbs_BSplKnotDistribution knotSet = curve_bsplinecurve->KnotDistribution();
		GeomAbs_Shape smooth = curve_bsplinecurve->Continuity();
		Ncti_Integer Degree = curve_bsplinecurve->Degree();
		const TColgp_Array1OfPnt& poles = curve_bsplinecurve->Poles();
		const TColStd_Array1OfReal* weights = curve_bsplinecurve->Weights();
		std::vector<Ncti_Double> flatknots;
		const TColStd_Array1OfReal& knots = curve_bsplinecurve->Knots();
		const TColStd_Array1OfInteger& mults = curve_bsplinecurve->Multiplicities();

		Ncti_GeomAbs_BSplKnotDistribution knotSetN = (Ncti_GeomAbs_BSplKnotDistribution)knotSet;
		Ncti_GeomAbs_Shape smoothN = (Ncti_GeomAbs_Shape)smooth;
		std::vector<NctiPosition> PoleVec;
		Ncti_Integer nn = curve_bsplinecurve->NbPoles();
		Ncti_Integer dd = poles.Size();
		for (Ncti_Integer ii = 0; ii < poles.Size(); ii++)
		{
			gp_Pnt pn = poles.Value(ii + 1);
			NctiPosition pt(pn.X(), pn.Y(), pn.Z());
			PoleVec.push_back(pt);
		}
		std::vector<Ncti_Double> WeightVec;
		if (weights)
		{
			for (Ncti_Integer ii = 0; ii < weights->Size(); ii++)
			{
				WeightVec.push_back((*weights)[ii + 1]);
			}
		}
		std::vector<Ncti_Double> flatknotVec;
		std::vector<Ncti_Double> knotsVec;
		for (Ncti_Integer ii = 0; ii < knots.Size(); ii++)
		{
			knotsVec.push_back(knots[ii + 1]);
		}
		std::vector<Ncti_Integer> multsVec;
		for (Ncti_Integer ii = 0; ii < mults.Size(); ii++)
		{
			multsVec.push_back(mults[ii + 1]);
		}
		Ncti_Double maxderivinv = 0;
		Ncti_Boolean maxderivinvok = true;
		NctiGeomBSplineCurve* pBSplineCircle = NCTI_NEW NctiGeomBSplineCurve(
			rational,
			periodic,
			knotSetN,
			smoothN,
			Degree,
			PoleVec,
			WeightVec,
			flatknotVec,
			knotsVec,
			multsVec,
			maxderivinv,
			maxderivinvok);
		return pBSplineCircle;
	}
	else if (TheType == STANDARD_TYPE(Geom_Ellipse))
	{
		Handle(Geom_Ellipse) curve_ellipse = Handle(Geom_Ellipse)::DownCast(curve);
		Ncti_Double majorRadius = curve_ellipse->MajorRadius();
		Ncti_Double minorRadius = curve_ellipse->MinorRadius();
		gp_Ax2 pos2 = curve_ellipse->Position();
		const gp_Pnt& p = pos2.Location();
		gp_Dir dirX = pos2.XDirection();
		gp_Dir dirY = pos2.YDirection();
		NctiPosition pt(p.X(), p.Y(), p.Z());
		NctiUnitVector vecX(dirX.X(), dirX.Y(), dirX.Z());
		NctiUnitVector vecY(dirY.X(), dirY.Y(), dirY.Z());
		NctiGeomEllipse* pGeomEllipse = NCTI_NEW NctiGeomEllipse(pt, vecX, vecY, majorRadius, minorRadius);
		return pGeomEllipse;
	}
	else if (TheType == STANDARD_TYPE(Geom_TrimmedCurve))
	{
		Handle(Geom_TrimmedCurve) curve_trimmed = Handle(Geom_TrimmedCurve)::DownCast(curve);
		Standard_Real a = curve_trimmed->FirstParameter();
		Standard_Real b = curve_trimmed->LastParameter();
		Handle(Geom_Curve) curve_trimmed_geom = curve_trimmed->BasisCurve();
		NctiGeomTrimmedCurve* pGeomTrimmedCurve = NCTI_NEW NctiGeomTrimmedCurve();
		pGeomTrimmedCurve->Set_m_basisCurve(occ_to_ge(curve_trimmed_geom));
		pGeomTrimmedCurve->Set_m_uTrim1(a);
		pGeomTrimmedCurve->Set_m_uTrim2(b);
		return pGeomTrimmedCurve;
	}
	else
	{
		const char* ch = TheType->Name();
		NctiGeomUnKnownCurve* pGeomUnKnownCurve = NCTI_NEW NctiGeomUnKnownCurve();
		char cha[256];
		NctiString::LocaleSprintf(cha, "GE Curve not include %s", ch);
		NctiDebug::debug(cha);

		return pGeomUnKnownCurve;
	}
	return nullptr;
}

NctiGeomSurface* occ_to_ge(const Handle(Geom_Surface)& surface)
{
	Handle(Standard_Type) TheType = surface->DynamicType();
	if (TheType == STANDARD_TYPE(Geom_Plane))
	{
		Handle(Geom_Plane) surface_plane = Handle(Geom_Plane)::DownCast(surface);
		NctiGeomPlane* pGeomPlane = NCTI_NEW NctiGeomPlane();
		gp_Pnt pt = surface_plane->Pln().Position().Location();
		gp_Vec vecX = surface_plane->Pln().Position().XDirection();
		gp_Vec vecY = surface_plane->Pln().Position().YDirection();
		pGeomPlane->Set_m_pt(NctiPosition(pt.X(), pt.Y(), pt.Z()));
		pGeomPlane->Set_m_XDir(NctiUnitVector(vecX.X(), vecX.Y(), vecX.Z()));
		pGeomPlane->Set_m_YDir(NctiUnitVector(vecY.X(), vecY.Y(), vecY.Z()));

		return pGeomPlane;
	}
	else if (TheType == STANDARD_TYPE(Geom_CylindricalSurface))
	{
		Handle(Geom_CylindricalSurface) surface_cyl = Handle(Geom_CylindricalSurface)::DownCast(surface);
		NctiGeomCylindricalSurface* pGeomCylindricalSurface = NCTI_NEW NctiGeomCylindricalSurface();
		gp_Pnt gpt = surface_cyl->Location();
		gp_Ax3 gax3 = surface_cyl->Position();
		pGeomCylindricalSurface->Set_m_pt(occ_to_ge(gpt));
		pGeomCylindricalSurface->Set_m_XDir(occ_to_ge(gax3.XDirection()));
		pGeomCylindricalSurface->Set_m_YDir(occ_to_ge(gax3.YDirection()));
		pGeomCylindricalSurface->Set_m_radius(surface_cyl->Radius());
		return pGeomCylindricalSurface;
	}
	else if (TheType == STANDARD_TYPE(Geom_BSplineSurface))
	{
		Handle(Geom_BSplineSurface) surface_bspline = Handle(Geom_BSplineSurface)::DownCast(surface);
		NctiGeomBSplineSurface* pGeomBSplineSurface = NCTI_NEW NctiGeomBSplineSurface();
		pGeomBSplineSurface->Set_m_urational(surface_bspline->IsURational());
		pGeomBSplineSurface->Set_m_vrational(surface_bspline->IsVRational());
		return pGeomBSplineSurface;
	}
	else if (TheType == STANDARD_TYPE(Geom_ToroidalSurface))
	{
		Handle(Geom_ToroidalSurface) surface_toroi = Handle(Geom_ToroidalSurface)::DownCast(surface);
		NctiGeomToroidalSurface* pGeomToroidalSurface = NCTI_NEW NctiGeomToroidalSurface();
		return pGeomToroidalSurface;
	}
	else if (TheType == STANDARD_TYPE(Geom_ConicalSurface))
	{
		Handle(Geom_ConicalSurface) surface_con = Handle(Geom_ConicalSurface)::DownCast(surface);
		NctiGeomConicalSurface* pGeomConicalSurface = NCTI_NEW NctiGeomConicalSurface();
		return pGeomConicalSurface;
	}
	else if (TheType == STANDARD_TYPE(Geom_SphericalSurface))
	{
		Handle(Geom_SphericalSurface) surface_sph = Handle(Geom_SphericalSurface)::DownCast(surface);
		NctiGeomSphericalSurface* pGeomSphericalSurface = NCTI_NEW NctiGeomSphericalSurface();
		return pGeomSphericalSurface;
	}
	else if (TheType == STANDARD_TYPE(Geom_BezierSurface))
	{
		Handle(Geom_BezierSurface) surface_bez = Handle(Geom_BezierSurface)::DownCast(surface);
		NctiGeomBezierSurface* pGeomSphericalSurface = NCTI_NEW NctiGeomBezierSurface();
		pGeomSphericalSurface->Set_m_urational(surface_bez->IsURational());
		pGeomSphericalSurface->Set_m_vrational(surface_bez->IsVRational());
		return pGeomSphericalSurface; 
	}
	else if (TheType == STANDARD_TYPE(Geom_RectangularTrimmedSurface))
	{
		Handle(Geom_RectangularTrimmedSurface) surface_RectangularTrimmedSurface = Handle(Geom_RectangularTrimmedSurface)::DownCast(surface);
		NctiGeomRectangularTrimmedSurface* pGeomRectangularTrimmedSurface = NCTI_NEW NctiGeomRectangularTrimmedSurface();
		Handle(Geom_Surface) surface_trimmed_geom = surface_RectangularTrimmedSurface->BasisSurface();
		pGeomRectangularTrimmedSurface->Set_m_basisSurf(occ_to_ge(surface_trimmed_geom));
		return pGeomRectangularTrimmedSurface;
	}
	else 
	{
		NctiGeomSurface* pGeomSurface = NCTI_NEW NctiGeomSurface();
		const char* ch = TheType->Name();
		char cha[256];
		NctiString::LocaleSprintf(cha, "GE Surface not include %s", ch);
		NctiDebug::debug(cha);
		return pGeomSurface;
	}
	return nullptr;
}

TopoDS_Shape* NctiOCCBody::GetShape()
{
    return m_TopoDS_Shape;
}

Ncti_Boolean NctiOCCBody::IsVolume()
{
	return m_TopoDS_Shape->ShapeType()<= TopAbs_SHELL;
}

NctiOCCBody::NctiOCCBody(TopoDS_Shape* i_pTopoDS_Shape)
	: m_TopoDS_Shape(i_pTopoDS_Shape)
	, m_GEShape(nullptr)
	, m_Label(nullptr)
{
	Init();
	init_geobject();
}

NctiOCCBody::~NctiOCCBody()
{
	for (int i = 0; i < m_FaceList.size(); i++)
	{
		if (m_FaceList[i] != nullptr)
		{
			delete m_FaceList[i];
			m_FaceList[i] = nullptr;
		}
	}
	for (int i = 0; i < m_EdgeList.size(); i++)
	{
		if (m_EdgeList[i] != nullptr)
		{
			delete m_EdgeList[i];
			m_EdgeList[i] = nullptr;
		}
	}
	for (int i = 0; i < m_VertexList.size(); i++)
	{
		if (m_VertexList[i] != nullptr)
		{
			delete m_VertexList[i];
			m_VertexList[i] = nullptr;
		}
	}
	if (m_TopoDS_Shape != nullptr)
	{
		delete m_TopoDS_Shape;
		m_TopoDS_Shape = nullptr;
	}
	if (m_GEShape != nullptr)
	{
		NCTI_DELETE_OBJECT(m_GEShape)
			m_GEShape = nullptr;
	}
	for (std::map<Ncti_Integer, NctiTopoVertex*>::iterator iter = m_GEVertexMap.begin(); iter != m_GEVertexMap.end(); ++iter)
	{
		if (iter->second)
		{
			NCTI_DELETE(iter->second);
			iter->second = nullptr;
		}
	}
	for (std::map<Ncti_Integer, NctiTopoEdge*>::iterator iter = m_GEEdgeMap.begin(); iter != m_GEEdgeMap.end(); ++iter)
	{
		if (iter->second)
		{
			NCTI_DELETE(iter->second);
			iter->second = nullptr;
		}
	}
	for (std::map<Ncti_Integer, NctiTopoFace*>::iterator iter = m_GEFaceMap.begin(); iter != m_GEFaceMap.end(); ++iter)
	{
		if (iter->second)
		{
			NCTI_DELETE(iter->second);
			iter->second = nullptr;
		}
	}
	NCTI_DELETE_CHAR(m_Label)
}

void NctiOCCBody::Init()
{
	if (m_TopoDS_Shape == nullptr)
		return;
	Ncti_Integer o_id = 0;
	TopoDS_Shape* i_pBody = m_TopoDS_Shape;
	//face

	TopTools_DataMapOfShapeInteger FaceTag;
	int numFace = 0;
	TopExp_Explorer aFaceIt(*i_pBody, TopAbs_FACE);
	for (aFaceIt.Init(*i_pBody, TopAbs_FACE); aFaceIt.More(); aFaceIt.Next())
	{
		const TopoDS_Face& Face = TopoDS::Face(aFaceIt.Current());
		if (FaceTag.IsBound(Face))
		{
			continue;
		}
		FaceTag.Bind(Face, numFace++);
		m_FaceTag[o_id] = Face;
		m_FaceList.push_back(NCTI_NEW Ncti_Integer(o_id++));
		
	}

	//edge
	TopTools_DataMapOfShapeInteger EdgeTag;
	int numEdge = 0;
	TopExp_Explorer aEdgeIt(*i_pBody, TopAbs_EDGE);
	for (aEdgeIt.Init(*i_pBody, TopAbs_EDGE); aEdgeIt.More(); aEdgeIt.Next())
	{
		const TopoDS_Edge& Edge = TopoDS::Edge(aEdgeIt.Current());
		if (BRep_Tool::Degenerated(Edge))
			continue;
		if (EdgeTag.IsBound(Edge))
		{
			continue;
		}
		EdgeTag.Bind(Edge, numEdge++);
		m_EdgeTag[o_id] = Edge;
		m_EdgeList.push_back(NCTI_NEW Ncti_Integer(o_id++));
		
	}

	//vertex
	TopTools_DataMapOfShapeInteger VertexTag;
	int numVertex = 0;
	TopExp_Explorer aVertexIt(*i_pBody, TopAbs_VERTEX);
	for (aVertexIt.Init(*i_pBody, TopAbs_VERTEX); aVertexIt.More(); aVertexIt.Next())
	{
		const TopoDS_Vertex& V = TopoDS::Vertex(aVertexIt.Current());
		if (VertexTag.IsBound(V))
		{
			continue;
		}
		VertexTag.Bind(V, numVertex++);
		m_VertexTag[o_id] = V;
		m_VertexList.push_back(NCTI_NEW Ncti_Integer(o_id++));
		
	}
}

Ncti_Boolean NctiOCCBody::get_persistent_tag(NCTI_MODEL_TAG i_ModelBody, Ncti_Long& o_id)
{
	if (m_TopoDS_Shape == nullptr || i_ModelBody == nullptr)
		return false;
	Ncti_Size nFace = m_FaceList.size();
	Ncti_Size nEdge = m_EdgeList.size();
	Ncti_Size nVertex = m_VertexList.size();
	Ncti_Integer* nId = (Ncti_Integer*)i_ModelBody;
	if ((*nId) < (nFace + nEdge + nVertex))
	{
		o_id = *nId;
		return true;
	}
	
	return false;
}

Ncti_Boolean NctiOCCBody::get_persistent_from_dimtag(int& o_ModelBody, std::pair<int, int>dimTag)const
{
	o_ModelBody = -2;
	int dim = dimTag.first;
	int tag = dimTag.second-1;
	if (tag < 0)
		return false;
	switch (dim)
	{
	case 0:
		if (tag >= m_VertexList.size())
			return false;
		o_ModelBody = *m_VertexList[tag];
		break;
    case 1:
        if (tag >= m_EdgeList.size())
            return false;
        o_ModelBody = *m_EdgeList[tag];
		break;
    case 2:
        if (tag >= m_FaceList.size())
            return false;
        o_ModelBody = *m_FaceList[tag];
		break;
    case 3:
        o_ModelBody = -1;
		break;
	default:
		break;
	}
	return o_ModelBody >= -1;
}

Ncti_Boolean NctiOCCBody::get_void_from_tag(NCTI_MODEL_TAG& o_ModelBody, Ncti_Long i_id)
{
	o_ModelBody = nullptr;
	if (m_TopoDS_Shape == nullptr || i_id < 0)
		return false;
	Ncti_Size nFace = m_FaceList.size();
	Ncti_Size nEdge = m_EdgeList.size();
	Ncti_Size nVertex = m_VertexList.size();
	if (i_id < nFace)
	{
		o_ModelBody = m_FaceList[i_id];
		return true;
	}
	if (i_id - nFace < nEdge)
	{
		o_ModelBody = m_EdgeList[i_id - nFace];
		return true;
	}
	if (i_id - nFace - nEdge < nVertex)
	{
		o_ModelBody = m_VertexList[i_id - nFace - nEdge];
		return true;
	}
	return false;
}

Ncti_Boolean NctiOCCBody::get_cell_from_tag(NCTI_MODEL_TAG i_ModelBody, TopoDS_Shape& o_cell)
{
	if (m_TopoDS_Shape == nullptr)
		return false;
	Ncti_Integer i_id = *((Ncti_Integer* )i_ModelBody);
	Ncti_Size nFace = m_FaceList.size();
	Ncti_Size nEdge = m_EdgeList.size();
	Ncti_Size nVertex = m_VertexList.size();

	Ncti_Integer nCnt = 0;
	if (i_id < nFace)
	{
		o_cell = m_FaceTag[i_id];
		return true;
		TopTools_DataMapOfShapeInteger FaceTag;
		int numFace = 0;
		TopExp_Explorer aFaceIt(*m_TopoDS_Shape, TopAbs_FACE);
		for (aFaceIt.Init(*m_TopoDS_Shape, TopAbs_FACE); aFaceIt.More(); aFaceIt.Next())
		{
			const TopoDS_Face& Face = TopoDS::Face(aFaceIt.Current());
			if (FaceTag.IsBound(Face))
			{
				continue;
			}
			FaceTag.Bind(Face, numFace++);
			if (nCnt == i_id)
			{
				o_cell = aFaceIt.Current();
				return true;
			}
			nCnt++;
		}
	}
	if (i_id < (nFace + nEdge))
	{
		o_cell = m_EdgeTag[i_id];
		return true;
		nCnt = nFace;
		TopTools_DataMapOfShapeInteger EdgeTag;
		int numEdge = 0;
		TopExp_Explorer aEdgeIt(*m_TopoDS_Shape, TopAbs_EDGE);
		for (aEdgeIt.Init(*m_TopoDS_Shape, TopAbs_EDGE); aEdgeIt.More(); aEdgeIt.Next())
		{
			const TopoDS_Edge& Edge = TopoDS::Edge(aEdgeIt.Current());
			if (BRep_Tool::Degenerated(Edge))
				continue;
			if (EdgeTag.IsBound(Edge))
			{
				continue;
			}
			EdgeTag.Bind(Edge, numEdge++);
			if (nCnt == i_id)
			{
				o_cell = aEdgeIt.Current();
				return true;
			}
			nCnt++;
		}
	}
	if (i_id < (nFace + nEdge + nVertex))
	{
		o_cell = m_VertexTag[i_id];
		return true;
		nCnt = nFace + nEdge;
		TopTools_DataMapOfShapeInteger VertexTag;
		int numVertex = 0;
		TopExp_Explorer aVertexIt(*m_TopoDS_Shape, TopAbs_VERTEX);
		for (aVertexIt.Init(*m_TopoDS_Shape, TopAbs_VERTEX); aVertexIt.More(); aVertexIt.Next())
		{
			const TopoDS_Vertex& V = TopoDS::Vertex(aVertexIt.Current());
			if (VertexTag.IsBound(V))
			{
				continue;
			}
			VertexTag.Bind(V, numVertex++);
			if (nCnt == i_id)
			{
				o_cell = aVertexIt.Current();
				return true;
			}
			nCnt++;
		}
	}
	return false;
}

Ncti_Boolean NctiOCCBody::get_tag_from_cell(NCTI_MODEL_TAG& o_ModelBody,const TopoDS_Shape& i_cell)
{
	if (m_TopoDS_Shape == nullptr)
		return false;
	Ncti_Integer nFaceCnt = 0;
	Ncti_Integer nEdgeCnt = 0;
	Ncti_Integer nVertexCnt = 0;

	if (i_cell.ShapeType() == TopAbs_FACE)
	{
		TopExp_Explorer aFaceIt(*m_TopoDS_Shape, TopAbs_FACE);
		TopTools_DataMapOfShapeInteger FaceTag;
		int numFace = 0;
		for (aFaceIt.Init(*m_TopoDS_Shape, TopAbs_FACE); aFaceIt.More(); aFaceIt.Next())
		{
			const TopoDS_Face& Face = TopoDS::Face(aFaceIt.Current());
			if (FaceTag.IsBound(Face))
			{
				continue;
			}
			FaceTag.Bind(Face, numFace++);

			if (aFaceIt.Current().IsSame(i_cell))
			{
				if (nFaceCnt < m_FaceList.size())
				{
					o_ModelBody = m_FaceList[nFaceCnt];
					return true;
				}
			}
			nFaceCnt++;
		}
	}

	if (i_cell.ShapeType() == TopAbs_EDGE)
	{
		TopExp_Explorer aEdgeIt(*m_TopoDS_Shape, TopAbs_EDGE);
		TopTools_DataMapOfShapeInteger EdgeTag;
		int numEdge = 0;
		for (aEdgeIt.Init(*m_TopoDS_Shape, TopAbs_EDGE); aEdgeIt.More(); aEdgeIt.Next())
		{
			const TopoDS_Edge& Edge = TopoDS::Edge(aEdgeIt.Current());
			if (BRep_Tool::Degenerated(Edge))
				continue;
			if (EdgeTag.IsBound(Edge))
			{
				continue;
			}
			EdgeTag.Bind(Edge, numEdge++);
			if (aEdgeIt.Current().IsSame(i_cell))
			{
				if (nEdgeCnt < m_EdgeList.size())
				{
					o_ModelBody = m_EdgeList[nEdgeCnt];
					return true;
				}
			}
			nEdgeCnt++;
		}
	}

	if (i_cell.ShapeType() == TopAbs_VERTEX)
	{
		TopExp_Explorer aVertexIt(*m_TopoDS_Shape, TopAbs_VERTEX);
		TopTools_DataMapOfShapeInteger VertexTag;
		int numVertex = 0;
		for (aVertexIt.Init(*m_TopoDS_Shape, TopAbs_VERTEX); aVertexIt.More(); aVertexIt.Next())
		{
			const TopoDS_Vertex& V = TopoDS::Vertex(aVertexIt.Current());
			if (VertexTag.IsBound(V))
			{
				continue;
			}
			VertexTag.Bind(V, numVertex++);
			if (aVertexIt.Current().IsSame(i_cell))
			{
				if (nVertexCnt < m_VertexList.size())
				{
					o_ModelBody = m_VertexList[nVertexCnt];
					return true;
				}
			}
			nVertexCnt++;
		}
	}
	return false;
}

void NctiOCCBody::init_geobject()
{
	if (NctiPluginsManager::instance()->IsCreateGEGeom() == false)
	{
		return;
	}
	//return;
	if (m_GEShape != nullptr)
	{
		NCTI_DELETE_OBJECT(m_GEShape)
			m_GEShape = nullptr;
	}
	m_GEFaceMap.clear();
	m_GEEdgeMap.clear();
	m_GEVertexMap.clear();
	m_GEShape = NCTI_NEW NctiTopoShape();
	m_GEShape->Set_m_LinkVoid(m_TopoDS_Shape);
	//NctiTime time("init_geobject");
	std::vector<TopoDS_Shape> FaceShapeVec;
	{
		TopTools_DataMapOfShapeInteger FaceTag;
		int numFace = 0;
		TopExp_Explorer aFaceIt(*m_TopoDS_Shape, TopAbs_FACE);
		for (aFaceIt.Init(*m_TopoDS_Shape, TopAbs_FACE); aFaceIt.More(); aFaceIt.Next())
		{
			const TopoDS_Face& Face = TopoDS::Face(aFaceIt.Current());
			if (FaceTag.IsBound(Face))
			{
				continue;
			}
			FaceTag.Bind(Face, numFace++);
			FaceShapeVec.push_back(aFaceIt.Current());
		}
	}
	

	std::vector<TopoDS_Shape> edgeShapeVec;
	{
		TopTools_DataMapOfShapeInteger EdgeTag;
		int numEdge = 0;
		TopExp_Explorer aEdgeIt(*m_TopoDS_Shape, TopAbs_EDGE);
		for (aEdgeIt.Init(*m_TopoDS_Shape, TopAbs_EDGE); aEdgeIt.More(); aEdgeIt.Next())
		{
			const TopoDS_Edge& Edge = TopoDS::Edge(aEdgeIt.Current());
			if (BRep_Tool::Degenerated(Edge))
				continue;
			if (EdgeTag.IsBound(Edge))
			{
				continue;
			}
			EdgeTag.Bind(Edge, numEdge++);
			edgeShapeVec.push_back(aEdgeIt.Current());
		}
	}
	std::vector<TopoDS_Shape> VertexShapeVec;
	{
		TopTools_DataMapOfShapeInteger VertexTag;
		int numVertex = 0;
		TopExp_Explorer aVertexIt(*m_TopoDS_Shape, TopAbs_VERTEX);
		for (aVertexIt.Init(*m_TopoDS_Shape, TopAbs_VERTEX); aVertexIt.More(); aVertexIt.Next())
		{
			const TopoDS_Vertex& V = TopoDS::Vertex(aVertexIt.Current());
			if (VertexTag.IsBound(V))
			{
				continue;
			}
			VertexTag.Bind(V, numVertex++);
			VertexShapeVec.push_back(aVertexIt.Current());
		}
	}

	std::map<Ncti_Integer, std::vector<NctiTopoEdgeCurve*>> FaceResultVec;
	std::map<Ncti_Integer, std::vector<NctiTopoLoop*>> LoopResultVec;
	std::map<Ncti_Integer, std::vector< NctiTopoEdge*>> EdgeResultVec;

	std::vector<NctiTopoFace*> NctiTopoFaceVec;
	for (Ncti_Size i = 0; i < m_FaceList.size(); i++)
	{
		Ncti_Integer* pFaceId = m_FaceList[i];
		TopoDS_Shape faceShape = FaceShapeVec[i];
		//get_cell_from_tag(pFaceId, faceShape);
		Handle(TopoDS_TShape) faceTShape = faceShape.TShape();
		if (faceTShape->ShapeType() == TopAbs_FACE)
		{
			Handle(BRep_TFace) TF = Handle(BRep_TFace)::DownCast(faceTShape);
			Handle(Geom_Surface) surface = TF->Surface();
			NctiTopoFace* pTopoFace = NCTI_NEW NctiTopoFace();
			pTopoFace->Set_m_Tranf(occ_to_ge(faceShape.Location().Transformation()));
			pTopoFace->Set_m_GeomSurface(occ_to_ge(surface));
			pTopoFace->Set_m_Orientation((Ncti_Orientation)faceShape.Orientation());
			m_GEShape->AddShape(pTopoFace);
			m_GEFaceMap[*pFaceId] = pTopoFace;
			pTopoFace->Set_m_LinkVoid(pFaceId);
			NctiTopoFaceVec.push_back(pTopoFace);
			TopTools_IndexedMapOfShape wireMap;
			TopExp::MapShapes(faceShape, TopAbs_WIRE, wireMap);
			for (Ncti_Integer iii = 1; iii <= wireMap.Extent(); iii++)
			{
				const TopoDS_Face& faceShapeEx = TopoDS::Face(faceShape);
				NctiTopoLoop* pTopoLoop = NCTI_NEW NctiTopoLoop();
				if (BRepTools::OuterWire(faceShapeEx) != wireMap(iii)) {
					pTopoLoop->Set_m_Orientation(Ncti_INTERNAL);
				}
				else
				{
					pTopoLoop->Set_m_Orientation(Ncti_EXTERNAL);
				}
				pTopoFace->AddTopoLoop(pTopoLoop);
				pTopoLoop->Set_m_TopoFace(pTopoFace);
				TopTools_IndexedMapOfShape wireedgeMap;
				TopExp::MapShapes(wireMap(iii), TopAbs_EDGE, wireedgeMap);
				for (Ncti_Integer iiii = 1; iiii <= wireedgeMap.Extent(); iiii++)
				{
					for (Ncti_Size j = 0; j < m_EdgeList.size(); j++)
					{
						Ncti_Integer* pEdgeId = m_EdgeList[j];
						TopoDS_Shape edgeShape = edgeShapeVec[j];
						//get_cell_from_tag(pEdgeId, edgeShape);
						if (wireedgeMap(iiii).IsSame(edgeShape))
						{
							NctiTopoEdgeCurve* pEdgeCurve = NCTI_NEW NctiTopoEdgeCurve();
							pEdgeCurve->Set_m_TopoFace(pTopoFace);
							pEdgeCurve->Set_m_Orientation((Ncti_Orientation)wireedgeMap(iiii).Orientation());
							FaceResultVec[*pEdgeId].push_back(pEdgeCurve);
							LoopResultVec[*pEdgeId].push_back(pTopoLoop);
							if (*pEdgeId == 384)
							{
								int nn = 0;
							}
							break;
						}
					}
				}
			}
		}
	}
	for (Ncti_Size i = 0; i < m_EdgeList.size(); i++)
	{
		Ncti_Integer* pEdgeId = m_EdgeList[i];
		TopoDS_Shape edgeShape = edgeShapeVec[i];
		//get_cell_from_tag(pEdgeId, edgeShape);
		Handle(TopoDS_TShape) edgeTShape= edgeShape.TShape();
		if (TopAbs_EDGE == edgeTShape->ShapeType())
		{
			TopoDS_Edge ff;
			
			Handle(BRep_TEdge) TE = Handle(BRep_TEdge)::DownCast(edgeTShape);
			BRep_ListIteratorOfListOfCurveRepresentation itrc(TE->Curves());
			while (itrc.More()) 
			{
				const Handle(BRep_CurveRepresentation)& CR = itrc.Value();
				if (CR->IsCurve3D()) 
				{
					if (!CR->Curve3D().IsNull()) 
					{
						const BRep_Curve3D* GC = static_cast<const BRep_Curve3D*>(CR.get());
						Ncti_Double FirstP = 0;
						Ncti_Double LastP = 0;
						GC->Range(FirstP, LastP);
						Handle(Geom_Curve) curve = CR->Curve3D();
						NctiGeomCurve* pGeomCurve = occ_to_ge(curve);
						NctiTopoEdge* pTopoEdge = NCTI_NEW NctiTopoEdge();
						pTopoEdge->Set_m_GeomCurve(pGeomCurve);
						pTopoEdge->Set_m_Tranf(occ_to_ge(edgeShape.Location().Transformation()));
						pTopoEdge->Set_m_Orientation((Ncti_Orientation)edgeShape.Orientation());
						pTopoEdge->SetRange(FirstP, LastP);
						m_GEShape->AddShape(pTopoEdge);
						m_GEEdgeMap[*pEdgeId] = pTopoEdge;
						pTopoEdge->Set_m_LinkVoid(pEdgeId);
						std::vector<NctiTopoEdgeCurve*> topofaceHelo = FaceResultVec[*pEdgeId];
						for (Ncti_Integer ii = 0; ii < topofaceHelo.size(); ii++)
						{
							pTopoEdge->AddTopoEdgeCurve(topofaceHelo[ii]);
						}
						std::vector<NctiTopoLoop*> topoLoopHelo = LoopResultVec[*pEdgeId];
						for (Ncti_Integer ii = 0; ii < topoLoopHelo.size(); ii++)
						{
							topoLoopHelo[ii]->AddTopoEdge(pTopoEdge);
						}
						
						TopTools_IndexedMapOfShape VertexMap;
						TopExp::MapShapes(edgeShape, TopAbs_VERTEX, VertexMap);
						for (Ncti_Integer ii = 1; ii <= VertexMap.Extent(); ii++)
						{
							for (Ncti_Size j = 0; j < m_VertexList.size(); j++)
							{
								Ncti_Integer* pVertexId = m_VertexList[j];
								TopoDS_Shape VertexShape = VertexShapeVec[j];
								//get_cell_from_tag(pVertexId, VertexShape);
								if (VertexMap(ii).IsSame(VertexShape))
								{
									EdgeResultVec[*pVertexId].push_back(pTopoEdge);
									break;
								}
							}
						}
					}
				}
				itrc.Next();
			}
		}
	}

	for (Ncti_Size i = 0; i < m_VertexList.size(); i++)
	{
		Ncti_Integer* pVertexId = m_VertexList[i];
		TopoDS_Shape vertexShape = VertexShapeVec[i];
		Handle(TopoDS_TShape) vertexTShape = vertexShape.TShape();
		if (TopAbs_VERTEX == vertexTShape->ShapeType())
		{
			Handle(BRep_TVertex) TV = Handle(BRep_TVertex)::DownCast(vertexTShape);
			BRep_ListIteratorOfListOfPointRepresentation itrp(TV->Points());
			while (itrp.More()) {
				const Handle(BRep_PointRepresentation)& PR = itrp.Value();
				if (PR->IsPointOnCurve()) {
					int nn = 0;
					//myCurves.Add(PR->Curve());
				}

				else if (PR->IsPointOnCurveOnSurface()) {
					int nn = 0;
					//myCurves2d.Add(PR->PCurve());
					//mySurfaces.Add(PR->Surface());
				}

				else if (PR->IsPointOnSurface()) {
					int nn = 0;
					//mySurfaces.Add(PR->Surface());
				}
				itrp.Next();
			}
			gp_Pnt p = TV->Pnt();
			NctiPosition pt(p.X(), p.Y(), p.Z());
			NctiGeomPoint* pGeomPoint= NCTI_NEW NctiGeomPoint(pt);
			NctiTopoVertex* pTopoVertex = NCTI_NEW NctiTopoVertex();
			pTopoVertex->Set_m_Tranf(occ_to_ge(vertexShape.Location().Transformation()));
			pTopoVertex->Set_m_Orientation((Ncti_Orientation)vertexShape.Orientation());
			pTopoVertex->Set_m_pGeomPoint(pGeomPoint);
			m_GEShape->AddShape(pTopoVertex);
			m_GEVertexMap[*pVertexId] = pTopoVertex;
			pTopoVertex->Set_m_LinkVoid(pVertexId);

			std::vector<NctiTopoEdge*> topoedgeHelo = EdgeResultVec[*pVertexId];
			for (Ncti_Integer ii = 0; ii < topoedgeHelo.size(); ii++)
			{
				topoedgeHelo[ii]->AddShape(pTopoVertex);
			}
		}
	}
}

Ncti_Boolean NctiOCCBody::get_gecell_from_cell(NCTI_MODEL_TAG i_ModelBody, NCTI_MODEL_TAG& o_pGEShape)
{
	if (!i_ModelBody)
		return false;
	if (i_ModelBody == this)
	{
		o_pGEShape = m_GEShape;
		return true;
	}
	Ncti_Integer* nId = (Ncti_Integer*)i_ModelBody;
	if (m_GEEdgeMap.find(*nId) != m_GEEdgeMap.end())
	{
		o_pGEShape = m_GEEdgeMap[*nId];
		return true;
	}
	else if (m_GEVertexMap.find(*nId) != m_GEVertexMap.end())
	{
		o_pGEShape = m_GEVertexMap[*nId];
		return true;
	}
	else if (m_GEFaceMap.find(*nId) != m_GEFaceMap.end())
	{
		o_pGEShape = m_GEFaceMap[*nId];
		return true;
	}
	return false;
}

Ncti_Boolean NctiOCCBody::get_ncti_cell_by_occ_shape(const TopoDS_Shape& i_shape, NCTI_MODEL_TAG& o_pOCCCell)
{
	o_pOCCCell = nullptr;
	int nBaseIdx = 0;
	if (i_shape.ShapeType() == TopAbs_FACE)
	{
		for (std::map<Ncti_Integer, TopoDS_Shape>::const_iterator iter = m_FaceTag.begin(); iter != m_FaceTag.end(); ++iter)
		{
			if (i_shape.IsSame(iter->second))
			{
				if (iter->first < m_FaceList.size())
				{
					o_pOCCCell = m_FaceList[iter->first];
					break;
				}
			}
		}
	}
	else if (i_shape.ShapeType() == TopAbs_EDGE)
	{
		nBaseIdx = m_FaceList.size();
		for (std::map<Ncti_Integer, TopoDS_Shape>::const_iterator iter = m_EdgeTag.begin(); iter != m_EdgeTag.end(); ++iter)
		{
			if (i_shape.IsSame(iter->second))
			{
				int nIdx = iter->first - nBaseIdx;
				if (nIdx < m_EdgeList.size())
				{
					o_pOCCCell = m_EdgeList[nIdx];
					break;
				}
			}
		}

		if (!o_pOCCCell)
		{
			for (std::map<Ncti_Integer, TopoDS_Shape>::const_iterator iter = m_EdgeTag.begin(); iter != m_EdgeTag.end(); ++iter)
			{
				const Handle(TopoDS_TShape)& tshape1 = i_shape.TShape();
				const Handle(TopoDS_TShape)& tshape2 = iter->second.TShape();
				if (tshape1.get() == tshape2.get())
				{
					const TopLoc_Location& location1 = i_shape.Location();
					const TopLoc_Location& location2 = iter->second.Location();
					int nIdx = iter->first - nBaseIdx;
					if (nIdx < m_EdgeList.size())
					{
						o_pOCCCell = m_EdgeList[nIdx];
						break;
					}
				}
			}
		}
	}
	else if (i_shape.ShapeType() == TopAbs_VERTEX)
	{
		nBaseIdx += m_EdgeList.size();
		for (std::map<Ncti_Integer, TopoDS_Shape>::const_iterator iter = m_VertexTag.begin(); iter != m_VertexTag.end(); ++iter)
		{
			if (i_shape.IsSame(iter->second))
			{
				int nIdx = iter->first - nBaseIdx;
				if (nIdx < m_VertexList.size())
				{
					o_pOCCCell = m_VertexList[nIdx];
					break;
				}
			}
		}
	}
	return (o_pOCCCell != nullptr);
}

Ncti_Boolean NctiOCCBody::get_occ_shape_by_ncti_cell(const NCTI_MODEL_TAG i_pOCCCell, int i_shapeType, TopoDS_Shape& o_shape)
{
	Ncti_Integer ncti_id = *(Ncti_Integer*)i_pOCCCell;
	if (i_shapeType == TopAbs_FACE)
	{
		std::map<Ncti_Integer, TopoDS_Shape>::const_iterator iter = m_FaceTag.find(ncti_id);
		if (iter != m_FaceTag.end())
		{
			o_shape = iter->second;
			return true;
		}
	}
	else if (i_shapeType == TopAbs_EDGE)
	{
		std::map<Ncti_Integer, TopoDS_Shape>::const_iterator iter = m_EdgeTag.find(ncti_id);
		if (iter != m_EdgeTag.end())
		{
			o_shape = iter->second;
			return true;
		}
	}
	else if (i_shapeType == TopAbs_VERTEX)
	{
		std::map<Ncti_Integer, TopoDS_Shape>::const_iterator iter = m_VertexTag.find(ncti_id);
		if (iter != m_VertexTag.end())
		{
			o_shape = iter->second;
			return true;
		}
	}
	return false;
}

const std::vector<Ncti_Integer*>& NctiOCCBody::get_face_cell()
{
    return m_FaceList;
}

const std::vector<Ncti_Integer*>& NctiOCCBody::get_edge_cell()
{
    return m_EdgeList;
}

const std::vector<Ncti_Integer*>& NctiOCCBody::get_vertex_cell()
{
	return m_VertexList;
}

void NctiOCCBody::add_attribute_segment(NctiRenderSegmentItem* i_pSegment)
{
	if (m_TopoDS_Shape == nullptr)
		return;
	Ncti_Integer o_id = 0;
	TopoDS_Shape* i_pBody = m_TopoDS_Shape;
	//face

	TopTools_DataMapOfShapeInteger FaceTag;
	int numFace = 0;
	TopExp_Explorer aFaceIt(*i_pBody, TopAbs_FACE);
	for (aFaceIt.Init(*i_pBody, TopAbs_FACE); aFaceIt.More(); aFaceIt.Next())
	{
		const TopoDS_Face& Face = TopoDS::Face(aFaceIt.Current());
		if (FaceTag.IsBound(Face))
		{
			continue;
		}
		FaceTag.Bind(Face, numFace++);
		NctiOCCBodyAttributeManager::instance()->add_attribute_segment(Face.TShape(), i_pSegment);
	}

	//edge
	TopTools_DataMapOfShapeInteger EdgeTag;
	int numEdge = 0;
	TopExp_Explorer aEdgeIt(*i_pBody, TopAbs_EDGE);
	for (aEdgeIt.Init(*i_pBody, TopAbs_EDGE); aEdgeIt.More(); aEdgeIt.Next())
	{
		const TopoDS_Edge& Edge = TopoDS::Edge(aEdgeIt.Current());
		if (BRep_Tool::Degenerated(Edge))
			continue;
		if (EdgeTag.IsBound(Edge))
		{
			continue;
		}
		EdgeTag.Bind(Edge, numEdge++);
		NctiOCCBodyAttributeManager::instance()->add_attribute_segment(Edge.TShape(), i_pSegment);
	}

	//vertex
	TopTools_DataMapOfShapeInteger VertexTag;
	int numVertex = 0;
	TopExp_Explorer aVertexIt(*i_pBody, TopAbs_VERTEX);
	for (aVertexIt.Init(*i_pBody, TopAbs_VERTEX); aVertexIt.More(); aVertexIt.Next())
	{
		const TopoDS_Vertex& V = TopoDS::Vertex(aVertexIt.Current());
		if (VertexTag.IsBound(V))
		{
			continue;
		}
		VertexTag.Bind(V, numVertex++);
		NctiOCCBodyAttributeManager::instance()->add_attribute_segment(V.TShape(), i_pSegment);
	}
}

void NctiOCCBody::get_attribute_segment(NCTI_MODEL_TAG i_Cell, NctiRenderSegmentItem*& o_pSegment)
{
	TopoDS_Shape o_Cell;
	get_cell_from_tag(i_Cell, o_Cell);

	o_pSegment = NctiOCCBodyAttributeManager::instance()->get_attribute_segment(o_Cell.TShape());
}

const std::map<Ncti_Integer, TopoDS_Shape>& NctiOCCBody::get_face_tags() {
	return m_FaceTag;
}
const std::map<Ncti_Integer, TopoDS_Shape>& NctiOCCBody::get_edge_tags() {
	return m_EdgeTag;
}
const std::map<Ncti_Integer, TopoDS_Shape>& NctiOCCBody::get_vertex_tags() {
	return m_VertexTag;
}

void NCTI::NctiOCCBody::SetLable(const char* i_label)
{
	NCTI_DELETE_CHAR(m_Label)
	NCTI_COPY_CHAR(m_Label, i_label)
}

void NCTI::NctiOCCBody::tessellation_body()
{
	//NctiBox box(NctiPosition(0, 0, 0), NctiPosition(0, 0, 0));
	//NctiBRepMeshIncrementalMesh* pBRepMeshIncrementalMesh = NCTI_NEW NctiBRepMeshIncrementalMesh(m_GEShape,1,1);
}