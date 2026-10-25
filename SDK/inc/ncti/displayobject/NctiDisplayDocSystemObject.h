#ifndef NctiDisplayDocSystemObject_H
#define NctiDisplayDocSystemObject_H
#include "NctiDisplayObject.h"
#include "NctiVector.h"
namespace NCTI
{
	struct DocImage
	{
		std::vector<unsigned char> Buffer;
		Ncti_Integer w;
		Ncti_Integer h;
		Ncti_Integer offset;
		Ncti_Integer rowPitch;
		DocImage()
		{
			w = 0;
			h = 0;
			offset = 0;
			rowPitch = 0;
		}
	};
	/**
	* @brief Doc system class
	* @details record the image and camera
	* @see NctiDisplayObject
	*/
	class DECL_NCTI NctiDisplayDocSystemObject : public NctiDisplayObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayDocSystemObject)
	public:
		/**
	   * @brief Initialization during obj class creation
	   */
		virtual void Init();
		virtual ~NctiDisplayDocSystemObject();
	public:
		/**
	   * @brief Set the save image data
	   * @param[in] i_ImageResult , from the render data
	   */
		void SetImageResult(const DocImage& i_ImageResult);
		/**
	   * @brief Get the save image path of document
	   * @return const Ncti_Char*
	   */
		const Ncti_Char* GetImageFile() { return m_pwsTempFileName; }
		/**
	   * @brief Set the camera data in a document
	   * @param[in] i_pos , the eye
	   * @param[in] i_tar , the target
	   * @param[in] i_up , the up vector
	   */
		void SetCamera(const NctiPosition& i_pos, const NctiPosition& i_tar, const NctiVector& i_up);
		/**
	   * @brief Get the camera data in a document
	   * @param[out] o_pos , the eye
	   * @param[out] o_tar , the target
	   * @param[out] o_up , the up vector
	   */
		void GetCamera(NctiPosition& o_pos, NctiPosition& o_tar, NctiVector& o_up)const;
	private:
		Ncti_Char* m_pwsTempFileName;
		DocImage m_DocImage;
		NctiPosition m_Pos;
		NctiPosition m_Tar;
		NctiVector m_up;
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
	};
}
#endif
