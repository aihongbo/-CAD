#ifndef NctiDCMUtils_H
#define NctiDCMUtils_H
#include "dcl_ncti_object.h"
#include "NctiDCMDef.h"
#include "NctiDCMEXVec2d.h"
namespace NCTI
{
	// Utility functions to generate valid transformation matrices.
	void DECL_NCTI_OBJECT make_transform_mx(double(*o_matrix)[3], double i_angle, double i_x, double i_y);
	void DECL_NCTI_OBJECT make_transform_mx(double(*o_matrix)[3], double i_angle, NctiDCMEXVec2d i_translation);
	// Function to copy a matrix 
	void DECL_NCTI_OBJECT copy_transform_mx(const double(*i_input)[3], double(*o_copy)[3]);
	void DECL_NCTI_OBJECT apply_transform_mx(const double(*i_input)[3], double(*o_applyto)[3]);
	void DECL_NCTI_OBJECT identify_matrix(double i_mat[3][3]);
	bool DECL_NCTI_OBJECT is_identify_matrix(const double i_mat[3][3], double i_tol = 1E-8);
	void DECL_NCTI_OBJECT describe_transform(const double(*i_matrix)[3]);
	void DECL_NCTI_OBJECT normalize_matrix(const double i_mat[3][3], double o_nmat[3][3]);
	bool DECL_NCTI_OBJECT is_equal_matrix(const double i_mat1[3][3], const double i_mat2[3][3], double i_tol = 1E-8);
}
#endif