#ifndef NctiDeleteTool_H
#define NctiDeleteTool_H
#include "dcl_ncti_pubfun.h"
#include "ncti_base.h"
#include <vector>
#include <map>
#include <functional>
namespace NCTI
{
	class NctiBaseModel;
	class NctiDisplayObjectList;

	using StartDeleteCallback = std::function<void(NctiBaseModel*, NctiDisplayObjectList&)>;
	using EndDeleteCallback = std::function<void()>;
	class DECL_NCTI_PUBFUN NctiDeleteTool
	{
	public:
		//删除对象
		static void DeleteObject(NctiBaseModel* pBaseModel);
		//移除特征
		static void RemoveFeature(NctiBaseModel* pBaseModel);
		//移除面
		static void RemoveFace(NctiBaseModel* pBaseModel);

		static void SetStartDeleteCallback(StartDeleteCallback);
		static void SetEndDeleteCallback(EndDeleteCallback);

		static void RunStartDeleteCallback(NctiBaseModel*, NctiDisplayObjectList&);
		static void RunEndDeleteCallback();
	private:
		//移除 iRemoveType	0:移除面  1:移除特征
		static void RemoveEx(NctiBaseModel* pBaseModel, Ncti_Integer iRemoveType);

		//删除前数据处理
		static StartDeleteCallback m_StartDeleteCallback;
		//删除后数据处理
		static EndDeleteCallback m_EndDeleteCallback;

	};
}
#endif
