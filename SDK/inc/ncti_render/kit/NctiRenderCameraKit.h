#ifndef NctiRenderCameraKit_H
#define NctiRenderCameraKit_H
#include "NctiRenderKit.h"
#include "NctiPosition.h"
#include "NctiVector.h"
#include "NctiTransf.h"

namespace NCTI
{
    /**
    * @brief camera info for view
    */
    class DECL_NCTI_RENDER NctiRenderCamaraKit : public NctiRenderObject {
        NCTI_RENDER_FUNCTIONS(NctiRenderCamaraKit);
    public:
        NctiRenderCamaraKit();

        /**
        * @brief Set Aspect,width/hight
        */
        void SetAspect(float as);

        /**
        * @brief get Aspect
        */
        float Aspect()const;

        /**
        * @brief set DepthRange
        * @param[in] ptMin world box min position
        * @param[in] ptMax world box max position
        */
        bool SetDepthRange(const NctiPosition& ptMin, const NctiPosition&ptMax);

        /**
        * @brief set DepthRange
        * @param[in] ptMin world box min position
        * @param[in] ptMax world box max position
        */
        bool AddDepthRange(const NctiPosition& ptMin, const NctiPosition& ptMax);
        /**
        * @brief set Extents to auto zoom
        * @param[in] pos auto zoom center
        * @param[in] radius auto zoom radius
        */
        void SetExtents(const NctiPosition& pos, float radius);

        /**
        * @brief get Extents to auto zoom
        * @param[out] pos auto zoom center
        * @param[out] radius auto zoom radius
        */
        void Extents(NctiPosition& pos, float& radius)const;

        /**
        * @brief fix position to world box
        * @param[in,out] io_pos position to fix
        */
        void FixPosition(NctiPosition& io_pos)const;

        /**
        * @brief set stand Orientation
        * @param[in] mode Orientation mode
        * @see EnumNctiViewMode
        */
        void SetOrientation(EnumNctiViewMode mode);

        /**
        * @brief set font vector
        * @param[in] front front vector
        * @param[in] up up vector
        */
        void SetFrontVector(const NctiVector& front, const NctiVector& up);

        /**
        * @brief set camera info
        * @param[in] eye camera position
        * @param[in] Target focus position
        * @param[in] up up vector
        */
        void SetCamera(const NctiPosition& eye, const NctiPosition& Target, const NctiVector& up);

        /**
        * @brief get camera info
        * @param[out] eye camera position
        * @param[out] Target focus position
        * @param[out] up up vector
        */
        void GetCamera(NctiPosition& eye, NctiPosition& Target, NctiVector& up)const;

        /**
        * @brief GetCameraTarget
        */
        NctiPosition GetCameraTarget()const;

        /**
        * @brief GetCameraPosition
        */
        NctiPosition GetCameraPosition()const;

        /**
        * @brief GetCameraDirection
        */
        NctiVector GetCameraDirection()const;

        /**
        * @brief GetFocusDist
        */
        Ncti_Double GetFocusDist()const;

        /**
        * @brief GetCameraUp
        */
        NctiVector GetCameraUp()const;

        /**
        * @brief set view area. 1 for whole window
        * @param[in] ox x origin. 0~1
        * @param[in] oy y origin 0~1
        * @param[in] wd x width 0~1
        * @param[in] ht y hight 0~1
        */
        void SetViewArea(double ox, double oy, double wd, double ht);

        /**
        * @brief get view area. 1 for whole window
        * @param[in] ox x origin. 0~1
        * @param[in] oy y origin 0~1
        * @param[in] xmax x max 0~1
        * @param[in] ymax y max 0~1
        */
        void GetViewPort(double& ox, double& oy, double& xmax, double& ymax)const;

        /**
        * @brief get view area. internal usage
        */
        const double* ViewArea()const;

        /**
        * @brief move view
        * @param[in] deltaX x move,0~1
        * @param[in] deltaY y move,0~1
        */
        void Pan(Ncti_Double deltaX, Ncti_Double deltaY);

        /**
        * @brief rotate view
        * @param[in] roll roll angle,in degree
        * @param[in] pitch pitch angle,in degree
        * @param[in] yaw,yaw mode if true. the angle is (roll+roll/10)
        * @param[in] center rotate center
        */
        void Orbit(Ncti_Double roll, Ncti_Double pitch, Ncti_Boolean yaw, const NctiPosition &center);

        /**
        * @brief zoom view
        * @param[in] factor zoom factor
        * @param[in] center zoom center
        */
        void Zoom(Ncti_Double factor, const NctiPosition&center);

        /**
        * @brief zoom to Extend
        */
        void ZoomAll();

        /**
        * @brief zoom factor compared with the Extend
        */
        float ZoomFactor()const;

        /**
        * @brief camera matrix
        * @return NctiTransf
        */
        NCTI::NctiTransf GetCameraTransf()const;

        /**
        * @brief get near far plane position
        * @param[in] near near plane
        * @param[in] far far plane
        */
        void GetPlaneNearFar(float& near, float& far)const;

        /**
        * @brief get current world range after zoom
        * @param[out] width world width
        * @param[out] height world hight
        */
        void GetWorldField(float& width, float& height)const;

        /**
        * @brief get camera matrix
        * @return float[16]
        */
        const Ncti_Float* GetViewMat()const;

        /**
        * @brief get projection matrix
        * @return float[16]
        */
        const Ncti_Float* GetProjectMat()const;

        /**
        * @brief calculate the view/projection matrix
        */
        void UpdateMatrix();

    private:
        float m_MatView[16]{};
        float m_ProjectMat[16]{};
        float m_nearPlane{0};
        float m_farPlane{0};
        float m_worldWidth{0};
        float m_worldHeight{0};
        NctiPosition m_ptMin,m_ptMax;
    };
}

#endif // !NctiRenderSceneItem_H
