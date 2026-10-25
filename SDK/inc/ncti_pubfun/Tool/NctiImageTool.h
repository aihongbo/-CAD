#ifndef NctiImageTool_H
#define NctiImageTool_H
#include "dcl_ncti_pubfun.h"
#include "ncti_base.h"
#include <functional>
#include <vector>
#include <map>
#define _ThumbnailWidth_ 256
#define _ThumbnailHeight_ 256
namespace NCTI
{
	struct DocImage;
	using ThumbnailCallback = std::function<bool(
		const std::vector<unsigned char>& i_Buffer,
		Ncti_Integer i_w,
		Ncti_Integer i_h,
		Ncti_Integer i_rowPitch,
		Ncti_Integer i_wThumbnail,
		Ncti_Integer i_hThumbnail,
		NCTI::DocImage& ImageResult)>;
	class DECL_NCTI_PUBFUN NctiImageTool
	{
	public:
		static void SetGetThumbnailFun(ThumbnailCallback fun) { m_GetThumbnailCallback = fun; }
		static bool RunGetThumbnailFun(const std::vector<unsigned char>& i_Buffer,
			Ncti_Integer i_w,
			Ncti_Integer i_h,
			Ncti_Integer i_rowPitch,
			Ncti_Integer i_wThumbnail,
			Ncti_Integer i_hThumbnail,
			NCTI::DocImage& ImageResult);
	private:
		static ThumbnailCallback m_GetThumbnailCallback;

	};
}
#endif
