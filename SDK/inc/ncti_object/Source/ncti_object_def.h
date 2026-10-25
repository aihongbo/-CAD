#ifndef ncti_object_def_H
#define ncti_object_def_H
namespace NCTI
{
	enum EnumNctiPopMenuItem
	{
		NCTI_POP_MENU_SHOW_ALL = 1,					//全显
		NCTI_POP_MENU_HIDE,							//隐藏
		NCTI_POP_MENU_SHOW,							//显示
		NCTI_POP_MENU_ONLY_SHOW,					//仅显
		NCTI_POP_MENU_SELECT_FACE,					//仅选面
		NCTI_POP_MENU_SELECT_LINE,					//仅选线
		NCTI_POP_MENU_SELECT_MARKER,				//仅选点
		NCTI_POP_MENU_SELECT_BODY,					//选择体
		NCTI_POP_MENU_LOOP_FACE,					//查找内环
		NCTI_POP_MENU_CONNEC_TFACE,					//查找连接
		NCTI_POP_MENU_SAME_CONNEC_TFACE,			//相似连接
		NCTI_POP_MENU_NO_PLANE_CONNECT_FACE,		//非平面连接
		NCTI_POP_MENU_EDIT,							//编辑
		NCTI_POP_MENU_DELETE,						//删除
        NCTI_POP_MENU_MERGE,						//合并节点
        NCTI_POP_MENU_SET_ALPHA,					//设置0.5透明
        NCTI_POP_MENU_SET_PETRA,					//设置0.5穿透
        NCTI_POP_MENU_GRID_NODE,					//节点显示
        NCTI_POP_MENU_GRID_NUMBER,					//编号显示
		//NCTI_POP_MENU_SELECT,						//选择
		NCTI_POP_MENU_MEASURE,						//测量
		NCTI_POP_MENU_GET_POINT,					//获取点
		NCTI_POP_MENU_GET_LENGTH,					//获取长度
		NCTI_POP_MENU_GET_MIDPOSITION,				//获取中点
		NCTI_POP_MENU_GET_CENTE,					//获取圆点
		NCTI_POP_MENU_GET_RADIUS,					//获取半径
		NCTI_POP_MENU_GET_VECTOR,					//获取向量
		NCTI_POP_MENU_GET_ANGLE,					//获取角度
		NCTI_POP_MENUSEPARATOR = 100000				//SEPARATOR
	};
}
#endif
