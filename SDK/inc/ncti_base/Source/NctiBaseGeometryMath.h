#ifndef NctiBaseGeometryMath_H
#define NctiBaseGeometryMath_H
#include "ncti_base.h"
namespace NCTI
{
	/**
	* @brief the math function
	*/
	class DECL_NCTI_BASE NctiBaseGeometryMath
	{
	public:
		NctiBaseGeometryMath() {}
		~NctiBaseGeometryMath() {}
	public:
		/**
	   * @brief the length of a vector
	   * @param[in] i_vector, the length is 3, Ncti_Double[3]
	   * @return Ncti_Double
	   */
		static Ncti_Double Length(const Ncti_Double* i_vector);
		/**
	   * @brief Subtract vector2 from vector 1. Put the result into vectorResult and return vectorResult
	   * @param[in] i_vector1, the length is 3, Ncti_Double[3]
	   * @param[in] i_vector2, the length is 3, Ncti_Double[3]
	   * @param[out] o_vectorResult, the length is 3, Ncti_Double[3]
	   * @return Ncti_Double, the same with o_vectorResult
	   */
		static Ncti_Double * Subtract(const Ncti_Double* i_vector1, const Ncti_Double* i_vector2, Ncti_Double* o_vectorResult);
		/**
	   * @brief Negate vector and return it
	   * @param[in] i_vector, the length is 3, Ncti_Double[3]
	   * @return Ncti_Double
	   */
		static Ncti_Double * Negate(Ncti_Double * i_vector);
		/**
	   * @brief Multiply vector by a factor and return it
	   * @param[in] i_vector, the length is 3, Ncti_Double[3]
	   * @param[in] i_factor
	   * @return Ncti_Double
	   */
		static Ncti_Double * Multiply(Ncti_Double * i_vector, const Ncti_Double i_factor);
		/**
	   * @brief Normalize a vector and return it. A vector whose length is very near zero remains unchanged
	   * @param[in] i_vector, the length is 3, Ncti_Double[3]
	   * @return Ncti_Double
	   */
		static Ncti_Double * Normalize(Ncti_Double* i_vector);
		/**
	   * @brief the scalar dot product, the length value
	   * @param[in] i_vector1, the length is 3, Ncti_Double[3]
	   * @param[in] i_vector2, the length is 3, Ncti_Double[3]
	   * @return Ncti_Double
	   */
		static Ncti_Double DotProduct(const Ncti_Double* i_vector1, const Ncti_Double* i_vector2);
		/**
	   * @brief Compute the cross product of 2 vector, put the result into vectorResult and return vectorResult
	   * @param[in] i_vectorA, the length is 3, Ncti_Double[3]
	   * @param[in] i_vectorB, the length is 3, Ncti_Double[3]
	   * @param[out] o_vectorResult, the length is 3, Ncti_Double[3]
	   * @return Ncti_Double, the same to o_vectorResult
	   */
		static Ncti_Double * CrossProduct(const Ncti_Double* i_vectorA, const Ncti_Double* i_vectorB, Ncti_Double* o_vectorResult);
		/**
	   * @brief Rotate inPoint so many degrees about inOriginPoint and inAxisVector, putting the result into outPoint
	   * @param[in] i_inPoint, the length is 3, Ncti_Double[3]
	   * @param[in] i_inDegrees, the length is 3, Ncti_Double[3]
	   * @param[in] i_inOriginPoint, the length is 3, Ncti_Double[3]
	   * @param[in] i_inAxisVector, the length is 3, Ncti_Double[3]
	   * @param[out] o_outPoint, the length is 3, Ncti_Double[3]
	   * @return Ncti_Double, the same to o_outPoint
	   */
		static void RotatePoint(const Ncti_Double* i_inPoint, Ncti_Double i_inDegrees, const Ncti_Double* i_inOriginPoint, const Ncti_Double* i_inAxisVector, Ncti_Double* o_outPoint);
		/**
	   * @brief Get the ray (a point and a vector) based on a point picked on the display screen,Results are returned in rayOrigin and rayVector.
	   * @param[in] i_Xpos, window pos x,-1~1
	   * @param[in] i_Ypos, window pos y,-1~1
	   * @param[in] i_cameraPosition, the eye of camera
	   * @param[in] i_cameraTarget, the target of camera
	   * @param[in] i_cameraUp, the up of camera
	   * @param[in] i_cameraWidth, the width of camera
	   * @param[in] i_cameraHeight, the height of camera
	   * @param[in] i_perspective, if it is perspective
	   * @param[in] o_ayOrigin, get the origin
	   * @param[in] o_rayVector, get the ray vector
	   */
		static void GetRayVector(
            Ncti_Double i_Xpos, Ncti_Double i_Ypos,
			Ncti_Double * i_cameraPosition, Ncti_Double * i_cameraTarget, Ncti_Double * i_cameraUp,
            Ncti_Double i_cameraWidth, Ncti_Double i_cameraHeight, Ncti_Boolean i_perspective,
			Ncti_Double * o_ayOrigin, Ncti_Double * o_rayVector);
		/**
	   * @brief Find the intersection of a ray (a point and a vector) and a line segment
	   * @param[in] i_lineStart,the length is 3, Ncti_Double[3]
	   * @param[in] i_lineEnd, the length is 3, Ncti_Double[3]
	   * @param[in] i_lineWidth, the length is 3, Ncti_Double[3]
	   * @param[in] i_rayOrigin, the length is 3, Ncti_Double[3]
	   * @param[in] i_rayVector, the length is 3, Ncti_Double[3]
	   * @param[in] i_hit, the length is 3, Ncti_Double[3]
	   * @param[out] o_param
	   * @return Ncti_Boolean
	   */
		static Ncti_Boolean RayHitsLineSegment(const Ncti_Double * i_lineStart, const Ncti_Double * i_lineEnd, const Ncti_Double i_lineWidth, const Ncti_Double * i_rayOrigin, const Ncti_Double * i_rayVector,
			Ncti_Double * i_hit, Ncti_Double  & o_param);
		/**
	   * @brief Find the intersection of a ray (a point and a vector) and a triangle
	   * @param[in] i_point0,
	   * @param[in] i_point1, the length is 3, Ncti_Double[3]
	   * @param[in] i_point2, the length is 3, Ncti_Double[3]
	   * @param[in] i_rayOrigin, the length is 3, Ncti_Double[3]
	   * @param[in] i_rayVector, the length is 3, Ncti_Double[3]
	   * @param[in] i_hit, the length is 3, Ncti_Double[3]
	   * @param[out] o_param
	   * @param[out] o_coincident
	   * @return Ncti_Boolean
	   */
		static Ncti_Boolean RayHitsTriangle(const Ncti_Double * i_point0, const Ncti_Double * i_point1, const Ncti_Double * i_point2, const Ncti_Double * i_rayOrigin, const Ncti_Double * i_rayVector,
			Ncti_Double * i_hit, Ncti_Double & o_param, Ncti_Boolean & o_coincident);
		/**
	   * @brief create circle by Approximation
	   * @param[in] i_x0, the center x of circle 
	   * @param[in] i_y0, the center y of circle 
	   * @param[in] i_edgen, the length
	   * @param[in] i_r, the radius of circle
	   * @param[out] o_outX, the length is i_edgen
	   * @param[out] o_outY, the length is i_edgen
	   */
		static void CircleByApproximation(Ncti_Double i_x0, Ncti_Double i_y0, Ncti_Integer i_edgen, Ncti_Double i_r, Ncti_Double* o_outX, Ncti_Double* o_outY);
	};
}
#endif

