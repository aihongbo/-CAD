#ifndef NctiRenderSceneItem_H
#define NctiRenderSceneItem_H
#include "NctiRenderSegmentItem.h"
#include "NctiRGBAColor.h"
#include "NctiUnitVector.h"
#include "NctiGridPickSet.h"
#include <vector>
#include "array"

namespace NCTI
{
    class NctiRenderMarkerItem;
    class NctiRenderTextItem;
    class NctiViewerRenderer;
    class NctiRenderCamaraKit;
    struct NctiScenePraviteData;

    /**
     * @brief Render Scene
     * @details manager the preview display object,model object,ground,light,camera
     * @see NctiRenderCamaraKit,NctiBaseView
     */
    class DECL_NCTI_RENDER NctiRenderSceneItem : public NctiRenderSegmentItem
    {
        NCTI_RENDER_FUNCTIONS(NctiRenderSceneItem);
    public:
        NctiRenderSceneItem();
        ~NctiRenderSceneItem();

        enum SceneAttrType
        {
            e_scene_light = 0,
            e_scene_ground,
            e_scene_winsize,
            e_scene_camera,
        };

        /**
         * @brief display
         * @param[in] i_force modify the tree to rebuild the scene
         */
        void Display(Ncti_Boolean i_force = false);

        /**
         * @brief enable display
         * @param[in] en enable display
         */
        void SetDispEnable(bool en);

        /**
         * @brief get the preview root key
         */
        NctiRenderSegmentItem* GetPreviewRoot()const;

        /**
         * @brief get user scene for prev
         */
        NctiRenderSegmentItem* GetUserScene()const;

        /**
         * @brief PreviewMode for speed up Preview
         * @warning if open the preview mode ,only update the preview object
         * @param[in] en PreviewMode
         */
        void SetPreviewMode(bool en);

        /**
         * @brief BoxSelect
         */
        Ncti_Boolean PointSelect(const NctiPosition& i_ptM,std::vector<NctiPickSelectObjectStr>& o_objs)const;

        /**
         * @brief BoxSelect
         */
        Ncti_Boolean BoxSelect(const NctiPosition &i_ptM, const NctiPosition i_ptMS, std::vector<NctiPickSelectObjectStr>&o_objs)const;

        /**
         * @brief BoxAABB
         * @param[in out] io_ptM in:min window pos,out:min camera pos
         * @param[in out] io_ptMS in:max window pos,out:max camera pos
         * @param[out] o_trans camera trans
         */
        Ncti_Boolean BoxAABB(NctiPosition& io_ptM, NctiPosition &io_ptMS, NctiTransf& o_trans)const;

        /**
         * @brief transform the coord type
         * @frome the i_space to the i_out_space
         * @param[in] i_space in coord type
         * @param[in] i_pt in coord
         * @param[in] i_out_space out coord type
         * @param[out] o_pt out coord
         */
        void ConvertCoordinate(EnumRenderSpaceType i_space, const NctiPosition& i_pt, EnumRenderSpaceType i_out_space, NctiPosition& o_pt)const;

        /**
         * @brief set the axis in the scene visible
         * @param[in] i_vis the axis visible
         */
        void SetAxisVisible(Ncti_Boolean i_vis);

        /**
         * @brief set the axis in the scene visible
         * @param[in] i_vis the axis visible
         */
        Ncti_Boolean IsAxisVisible()const;

        /**
         * @brief set the rotate center in the scene visible
         * @param[in] i_vis the rotate center visible
         */
        void SetCenterVisible(Ncti_Boolean i_vis);

        /**
         * @brief set the tips text
         * @param[in] i_tips the text display in window left top
         */
        void SetViewTips(const std::vector<std::wstring>& i_tips);

        /**
         * @brief hide the tips text
         */
        void HideViewTips();

        /**
         * @brief set the tips text position
         * @param[in] i_window the window position in pixel
         * @param[in] i_world the world position in 3D space
         */
        void SetCursorPosition(const NctiPosition& i_window,const NctiPosition& i_world);

        /**
         * @brief set the cursor visible
         * @param[in] i_visible the cursor visible
         */
        void SetCursorVisible(Ncti_Boolean i_visible);

        /**
         * @brief is the cursor visible
         */
        Ncti_Boolean IsCursorVisible()const;

        /**
         * @brief display the rect
         * @details used in box select display
         * @param[in] i_c1 rect corner
         * @param[in] i_c2 rect another corner
         */
        void DisplayRubberband(const NctiPosition& i_c1, const NctiPosition& i_c2);

        /**
         * @brief SetRubberVisible
         */
        void SetRubberVisible(Ncti_Boolean i_vis);

        /**
         * @brief set the background vis
         */
        void SetBackGround(Ncti_Boolean i_vis);

        /**
         * @brief set the background top color
         */
        void SetWindowColor(const RGBAColor& i_color);

        /**
         * @brief set the background bottom color
         */
        void SetWindowContrastColor(const RGBAColor& i_color);

        /**
         * @brief get the background visible
         * @param[out] o_e_en background visible
         * @return true if has set
         */
        Ncti_Boolean ShowBackGround(Ncti_Boolean& o_en)const;

        /**
         * @brief get the background top color
         * @param[out] o_o_color background top color
         * @return true if has set
         */
        Ncti_Boolean ShowWindowColor(RGBAColor& o_color)const;

        /**
         * @brief get the background bottom color
         * @param[out] o_o_color background bottom color
         * @return true if has set
         */
        Ncti_Boolean ShowWindowContrast(RGBAColor& o_color)const;

        /**
         * @brief set the scene light
         * @param[in] i_PointLightAtt light info
         * @param[in] i_index 0~7
         * @see PointLightAtt
         */
        void SetPointLightAtt(const PointLightAtt& i_PointLightAtt,Ncti_Integer i_index);

        /**
         * @brief get the scene light
         * @param[in] i_index 0~7
         * @param[out] o_o_PointLightAtt light info
         * @return true if has set
         * @see PointLightAtt
         */
        Ncti_Boolean ShowPointLightAtt(PointLightAtt& o_PointLightAtt,Ncti_Integer i_index)const;

        /**
         * @brief get stand camera
         * @details the camera control the stand view
         * @see NctiRenderCamaraKit
         */
        NctiRenderCamaraKit* GetStandView()const;

        /**
         * @brief get axis camera
         * @details the camera control the axis view
         * @see NctiRenderCamaraKit
         */
        NctiRenderCamaraKit* GetAxisView()const;

        /**
         * @brief get window size
         * @param[out] o_width window width
         * @param[out] o_height window height
         */
        void GetWindowsSize(Ncti_Integer& o_width, Ncti_Integer& o_height)const;

        /**
         * @brief set window size
         * @param[in] i_width window width
         * @param[in] i_height window height
         */
        Ncti_Boolean SetWindowSize(Ncti_Integer i_width, Ncti_Integer i_height);

        /**
         * @brief get the camera ability
         * @param[in] i_id 0 for stand view,1 for axis view
         * @param[out] o_panen pan enable
         * @param[out] o_zoomen zoom enable
         * @param[out] o_rotateen rotate enable
         */
        Ncti_Boolean GetViewEnable(Ncti_Integer e_id, Ncti_Boolean& o_panen, Ncti_Boolean& o_zoomen, Ncti_Boolean& o_rotateen);

        /**
         * @brief set the camera ability
         * @param[in] i_id 0 for stand view,1 for axis view
         * @param[in] i_panen pan enable
         * @param[in] i_zoomen zoom enable
         * @param[in] i_rotateen rotate enable
         */
        Ncti_Boolean SetViewEnable(Ncti_Integer i_id, Ncti_Boolean i_panen, Ncti_Boolean i_zoomen, Ncti_Boolean i_rotateen);

        /**
         * @brief set the view area
         * @param[in] i_id 0 for stand view,1 for axis view
         * @param[in] i_ox origin x,0~1 in window. <0 means alingh right
         * @param[in] i_oy origin y,0~1 in window. <0 means alingh botton
         * @param[in] i_wd area width,0~1 in window
         * @param[in] i_ht area hight,0~1 in window
         */
        void SetViewPort(Ncti_Integer i_id, Ncti_Double i_ox, Ncti_Double i_oy, Ncti_Double i_wd, Ncti_Double i_ht);

        /**
         * @brief set the scene box
         * @details auto zoom will zoom to this box
         * @param[in] i_ptMin min coord in world
         * @param[in] i_ptMax max coord in world
         */
        void SetWoldBox(const NctiPosition& i_ptMin, const NctiPosition& i_ptMax);

        /**
         * @brief get the camera info
         * @param[out] o_eye camera eye
         * @param[out] o_tar camera target
         * @param[out] o_up camera up direction
         */
        void GetCameraInfo(NctiPosition& o_eye, NctiPosition& o_tar, NctiVector& o_up)const;

        /**
         * @brief get the camera info
         * @param[in] i_eye camera eye
         * @param[in] i_tar camera target
         * @param[in] i_up camera up direction
         */
        void SetCameraInfo(const NctiPosition& i_pos, const NctiPosition& i_tar, const NctiVector& i_up);

        /**
         * @brief get the front direction info
         * @details keep the target unchanged,modify the front direction
         * @param[in] i_dir camera front direction
         */
        void SetFrontDirection(NctiVector i_dir);

        /**
         * @brief set the camera orientation to the Type
         * @param[in] i_Type the target orientation
         * @see EnumNctiViewMode
         */
        void StandOrientation(EnumNctiViewMode i_Type);

        /**
         * @brief pan camera
         * @param[in] i_deltaX window dist x in pixel
         * @param[in] i_deltaX window dist y in pixel
         */
        void PanView(Ncti_Double i_deltaX, Ncti_Double i_deltaY);

        /**
         * @brief set rotate center
         * @param[in] i_cen rotate center
         */
        void SetOrbitCenter(const NctiPosition& i_cen);

        /**
         * @brief get rotate center
         * @param[in] o_cen rotate center
         */
        void GetOrbitCenter(NctiPosition& o_cen);

        /**
         * @brief rotate the scene
         * @details rotate the scene around the orbit center
         * @param[in] i_degX, x angle in degree
         * @param[in] i_degY, y angle in degree
         * @param[in] i_yaw if use the yaw rotate
         */
        void OrbitView(Ncti_Double i_degX, Ncti_Double i_degY, Ncti_Boolean i_yaw = false);

        /**
         * @brief get the scale factor
         * @details compared with the world box
         * @return scale factor
         */
        float ScaleFactor()const;

        /**
         * @brief zoom the scene
         * @param[in] i_factor scale factor
         * @param[in] i_zc scale center
         */
        void ZoomView(Ncti_Double i_factor, const NctiPosition& i_zc);

        /**
         * @brief zoom to world box
         */
        void ZoomAll();

    private:
        void InitPrevew();
        NctiRenderSegmentItem* Subsegment(const Ncti_Char* i_cpName = nullptr, Ncti_Boolean i_new = false, Ncti_Boolean i_IsInstanceKey = false);
        NctiViewerRenderer* GetViewRender()const;
        NctiScenePraviteData* _d;
    };
}

#endif // !NctiRenderSceneItem_H
